<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pnpbios -- PnP BIOS driver
 *
 * This driver provides access to Plug-'n'-Play services provided by
 * the PnP BIOS firmware, described in the following करोcuments:
 *   Plug and Play BIOS Specअगरication, Version 1.0A, 5 May 1994
 *   Plug and Play BIOS Clarअगरication Paper, 6 October 1994
 *     Compaq Computer Corporation, Phoenix Technologies Ltd., Intel Corp.
 * 
 * Originally (C) 1998 Christian Schmidt <schmidt@digadd.de>
 * Modअगरications (C) 1998 Tom Lees <tom@lpsg.demon.co.uk>
 * Minor reorganizations by David Hinds <dahinds@users.sourceक्रमge.net>
 * Further modअगरications (C) 2001, 2002 by:
 *   Alan Cox <alan@redhat.com>
 *   Thomas Hood
 *   Brian Gerst <bgerst@didntduck.org>
 *
 * Ported to the PnP Layer and several additional improvements (C) 2002
 * by Adam Belay <ambx1@neo.rr.com>
 */

/* Change Log
 *
 * Adam Belay - <ambx1@neo.rr.com> - March 16, 2003
 * rev 1.01	Only call pnp_bios_dev_node_info once
 *		Added pnpbios_prपूर्णांक_status
 *		Added several new error messages and info messages
 *		Added pnpbios_पूर्णांकerface_attach_device
 *		पूर्णांकegrated core and proc init प्रणाली
 *		Introduced PNPMODE flags
 *		Removed some useless includes
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/linkage.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/pnp.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dmi.h>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "../base.h"
#समावेश "pnpbios.h"

/*
 *
 * PnP BIOS INTERFACE
 *
 */

अटल जोड़ pnp_bios_install_काष्ठा *pnp_bios_install = शून्य;

पूर्णांक pnp_bios_present(व्योम)
अणु
	वापस (pnp_bios_install != शून्य);
पूर्ण

काष्ठा pnp_dev_node_info node_info;

/*
 *
 * DOCKING FUNCTIONS
 *
 */

अटल काष्ठा completion unload_sem;

/*
 * (Much of this beदीर्घs in a shared routine somewhere)
 */
अटल पूर्णांक pnp_करोck_event(पूर्णांक करोck, काष्ठा pnp_करोcking_station_info *info)
अणु
	अटल अक्षर स्थिर sbin_pnpbios[] = "/sbin/pnpbios";
	अक्षर *argv[3], **envp, *buf, *scratch;
	पूर्णांक i = 0, value;

	अगर (!(envp = kसुस्मृति(20, माप(अक्षर *), GFP_KERNEL)))
		वापस -ENOMEM;
	अगर (!(buf = kzalloc(256, GFP_KERNEL))) अणु
		kमुक्त(envp);
		वापस -ENOMEM;
	पूर्ण

	/* FIXME: अगर there are actual users of this, it should be
	 * पूर्णांकegrated पूर्णांकo the driver core and use the usual infraकाष्ठाure
	 * like sysfs and uevents
	 */
	argv[0] = (अक्षर *)sbin_pnpbios;
	argv[1] = "dock";
	argv[2] = शून्य;

	/* minimal command environment */
	envp[i++] = "HOME=/";
	envp[i++] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";

#अगर_घोषित	DEBUG
	/* hपूर्णांक that policy agent should enter no-मानक_निकास debug mode */
	envp[i++] = "DEBUG=kernel";
#पूर्ण_अगर
	/* extensible set of named bus-specअगरic parameters,
	 * supporting multiple driver selection algorithms.
	 */
	scratch = buf;

	/* action:  add, हटाओ */
	envp[i++] = scratch;
	scratch += प्र_लिखो(scratch, "ACTION=%s", करोck ? "add" : "remove") + 1;

	/* Report the ident क्रम the करोck */
	envp[i++] = scratch;
	scratch += प्र_लिखो(scratch, "DOCK=%x/%x/%x",
			   info->location_id, info->serial, info->capabilities);
	envp[i] = शून्य;

	value = call_usermodehelper(sbin_pnpbios, argv, envp, UMH_WAIT_EXEC);
	kमुक्त(buf);
	kमुक्त(envp);
	वापस 0;
पूर्ण

/*
 * Poll the PnP करोcking at regular पूर्णांकervals
 */
अटल पूर्णांक pnp_करोck_thपढ़ो(व्योम *unused)
अणु
	अटल काष्ठा pnp_करोcking_station_info now;
	पूर्णांक करोcked = -1, d = 0;

	set_मुक्तzable();
	जबतक (1) अणु
		पूर्णांक status;

		/*
		 * Poll every 2 seconds
		 */
		msleep_पूर्णांकerruptible(2000);

		अगर (try_to_मुक्तze())
			जारी;

		status = pnp_bios_करोck_station_info(&now);

		चयन (status) अणु
			/*
			 * No करोck to manage
			 */
		हाल PNP_FUNCTION_NOT_SUPPORTED:
			complete_and_निकास(&unload_sem, 0);
		हाल PNP_SYSTEM_NOT_DOCKED:
			d = 0;
			अवरोध;
		हाल PNP_SUCCESS:
			d = 1;
			अवरोध;
		शेष:
			pnpbios_prपूर्णांक_status("pnp_dock_thread", status);
			prपूर्णांकk(KERN_WARNING "PnPBIOS: disabling dock monitoring.\n");
			complete_and_निकास(&unload_sem, 0);
		पूर्ण
		अगर (d != करोcked) अणु
			अगर (pnp_करोck_event(d, &now) == 0) अणु
				करोcked = d;
#अगर 0
				prपूर्णांकk(KERN_INFO
				       "PnPBIOS: Docking station %stached\n",
				       करोcked ? "at" : "de");
#पूर्ण_अगर
			पूर्ण
		पूर्ण
	पूर्ण
	complete_and_निकास(&unload_sem, 0);
पूर्ण

अटल पूर्णांक pnpbios_get_resources(काष्ठा pnp_dev *dev)
अणु
	u8 nodक्रमागत = dev->number;
	काष्ठा pnp_bios_node *node;

	अगर (!pnpbios_is_dynamic(dev))
		वापस -EPERM;

	pnp_dbg(&dev->dev, "get resources\n");
	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	अगर (!node)
		वापस -1;
	अगर (pnp_bios_get_dev_node(&nodक्रमागत, (अक्षर)PNPMODE_DYNAMIC, node)) अणु
		kमुक्त(node);
		वापस -ENODEV;
	पूर्ण
	pnpbios_पढ़ो_resources_from_node(dev, node);
	dev->active = pnp_is_active(dev);
	kमुक्त(node);
	वापस 0;
पूर्ण

अटल पूर्णांक pnpbios_set_resources(काष्ठा pnp_dev *dev)
अणु
	u8 nodक्रमागत = dev->number;
	काष्ठा pnp_bios_node *node;
	पूर्णांक ret;

	अगर (!pnpbios_is_dynamic(dev))
		वापस -EPERM;

	pnp_dbg(&dev->dev, "set resources\n");
	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	अगर (!node)
		वापस -1;
	अगर (pnp_bios_get_dev_node(&nodक्रमागत, (अक्षर)PNPMODE_DYNAMIC, node)) अणु
		kमुक्त(node);
		वापस -ENODEV;
	पूर्ण
	अगर (pnpbios_ग_लिखो_resources_to_node(dev, node) < 0) अणु
		kमुक्त(node);
		वापस -1;
	पूर्ण
	ret = pnp_bios_set_dev_node(node->handle, (अक्षर)PNPMODE_DYNAMIC, node);
	kमुक्त(node);
	अगर (ret > 0)
		ret = -1;
	वापस ret;
पूर्ण

अटल व्योम pnpbios_zero_data_stream(काष्ठा pnp_bios_node *node)
अणु
	अचिन्हित अक्षर *p = (अक्षर *)node->data;
	अचिन्हित अक्षर *end = (अक्षर *)(node->data + node->size);
	अचिन्हित पूर्णांक len;
	पूर्णांक i;

	जबतक ((अक्षर *)p < (अक्षर *)end) अणु
		अगर (p[0] & 0x80) अणु	/* large tag */
			len = (p[2] << 8) | p[1];
			p += 3;
		पूर्ण अन्यथा अणु
			अगर (((p[0] >> 3) & 0x0f) == 0x0f)
				वापस;
			len = p[0] & 0x07;
			p += 1;
		पूर्ण
		क्रम (i = 0; i < len; i++)
			p[i] = 0;
		p += len;
	पूर्ण
	prपूर्णांकk(KERN_ERR
	       "PnPBIOS: Resource structure did not contain an end tag.\n");
पूर्ण

अटल पूर्णांक pnpbios_disable_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_bios_node *node;
	u8 nodक्रमागत = dev->number;
	पूर्णांक ret;

	अगर (dev->flags & PNPBIOS_NO_DISABLE || !pnpbios_is_dynamic(dev))
		वापस -EPERM;

	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	अगर (pnp_bios_get_dev_node(&nodक्रमागत, (अक्षर)PNPMODE_DYNAMIC, node)) अणु
		kमुक्त(node);
		वापस -ENODEV;
	पूर्ण
	pnpbios_zero_data_stream(node);

	ret = pnp_bios_set_dev_node(dev->number, (अक्षर)PNPMODE_DYNAMIC, node);
	kमुक्त(node);
	अगर (ret > 0)
		ret = -1;
	वापस ret;
पूर्ण

/* PnP Layer support */

काष्ठा pnp_protocol pnpbios_protocol = अणु
	.name = "Plug and Play BIOS",
	.get = pnpbios_get_resources,
	.set = pnpbios_set_resources,
	.disable = pnpbios_disable_resources,
पूर्ण;

अटल पूर्णांक __init insert_device(काष्ठा pnp_bios_node *node)
अणु
	काष्ठा list_head *pos;
	काष्ठा pnp_dev *dev;
	अक्षर id[8];
	पूर्णांक error;

	/* check अगर the device is alपढ़ोy added */
	list_क्रम_each(pos, &pnpbios_protocol.devices) अणु
		dev = list_entry(pos, काष्ठा pnp_dev, protocol_list);
		अगर (dev->number == node->handle)
			वापस -EEXIST;
	पूर्ण

	pnp_eisa_id_to_string(node->eisa_id & PNP_EISA_ID_MASK, id);
	dev = pnp_alloc_dev(&pnpbios_protocol, node->handle, id);
	अगर (!dev)
		वापस -ENOMEM;

	pnpbios_parse_data_stream(dev, node);
	dev->active = pnp_is_active(dev);
	dev->flags = node->flags;
	अगर (!(dev->flags & PNPBIOS_NO_CONFIG))
		dev->capabilities |= PNP_CONFIGURABLE;
	अगर (!(dev->flags & PNPBIOS_NO_DISABLE) && pnpbios_is_dynamic(dev))
		dev->capabilities |= PNP_DISABLE;
	dev->capabilities |= PNP_READ;
	अगर (pnpbios_is_dynamic(dev))
		dev->capabilities |= PNP_WRITE;
	अगर (dev->flags & PNPBIOS_REMOVABLE)
		dev->capabilities |= PNP_REMOVABLE;

	/* clear out the damaged flags */
	अगर (!dev->active)
		pnp_init_resources(dev);

	error = pnp_add_device(dev);
	अगर (error) अणु
		put_device(&dev->dev);
		वापस error;
	पूर्ण

	pnpbios_पूर्णांकerface_attach_device(node);

	वापस 0;
पूर्ण

अटल व्योम __init build_devlist(व्योम)
अणु
	u8 nodक्रमागत;
	अचिन्हित पूर्णांक nodes_got = 0;
	अचिन्हित पूर्णांक devs = 0;
	काष्ठा pnp_bios_node *node;

	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	अगर (!node)
		वापस;

	क्रम (nodक्रमागत = 0; nodक्रमागत < 0xff;) अणु
		u8 thisnodक्रमागत = nodक्रमागत;
		/* eventually we will want to use PNPMODE_STATIC here but क्रम now
		 * dynamic will help us catch buggy bioses to add to the blacklist.
		 */
		अगर (!pnpbios_करोnt_use_current_config) अणु
			अगर (pnp_bios_get_dev_node
			    (&nodक्रमागत, (अक्षर)PNPMODE_DYNAMIC, node))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (pnp_bios_get_dev_node
			    (&nodक्रमागत, (अक्षर)PNPMODE_STATIC, node))
				अवरोध;
		पूर्ण
		nodes_got++;
		अगर (insert_device(node) == 0)
			devs++;
		अगर (nodक्रमागत <= thisnodक्रमागत) अणु
			prपूर्णांकk(KERN_ERR
			       "PnPBIOS: build_devlist: Node number 0x%x is out of sequence following node 0x%x. Aborting.\n",
			       (अचिन्हित पूर्णांक)nodक्रमागत,
			       (अचिन्हित पूर्णांक)thisnodक्रमागत);
			अवरोध;
		पूर्ण
	पूर्ण
	kमुक्त(node);

	prपूर्णांकk(KERN_INFO
	       "PnPBIOS: %i node%s reported by PnP BIOS; %i recorded by driver\n",
	       nodes_got, nodes_got != 1 ? "s" : "", devs);
पूर्ण

/*
 *
 * INIT AND EXIT
 *
 */

अटल पूर्णांक pnpbios_disabled;
पूर्णांक pnpbios_करोnt_use_current_config;

अटल पूर्णांक __init pnpbios_setup(अक्षर *str)
अणु
	पूर्णांक invert;

	जबतक ((str != शून्य) && (*str != '\0')) अणु
		अगर (म_भेदन(str, "off", 3) == 0)
			pnpbios_disabled = 1;
		अगर (म_भेदन(str, "on", 2) == 0)
			pnpbios_disabled = 0;
		invert = (म_भेदन(str, "no-", 3) == 0);
		अगर (invert)
			str += 3;
		अगर (म_भेदन(str, "curr", 4) == 0)
			pnpbios_करोnt_use_current_config = invert;
		str = म_अक्षर(str, ',');
		अगर (str != शून्य)
			str += म_अखोज(str, ", \t");
	पूर्ण

	वापस 1;
पूर्ण

__setup("pnpbios=", pnpbios_setup);

/* PnP BIOS signature: "$PnP" */
#घोषणा PNP_SIGNATURE   (('$' << 0) + ('P' << 8) + ('n' << 16) + ('P' << 24))

अटल पूर्णांक __init pnpbios_probe_प्रणाली(व्योम)
अणु
	जोड़ pnp_bios_install_काष्ठा *check;
	u8 sum;
	पूर्णांक length, i;

	prपूर्णांकk(KERN_INFO "PnPBIOS: Scanning system for PnP BIOS support...\n");

	/*
	 * Search the defined area (0xf0000-0xffff0) क्रम a valid PnP BIOS
	 * काष्ठाure and, अगर one is found, sets up the selectors and
	 * entry poपूर्णांकs
	 */
	क्रम (check = (जोड़ pnp_bios_install_काष्ठा *)__va(0xf0000);
	     check < (जोड़ pnp_bios_install_काष्ठा *)__va(0xffff0);
	     check = (व्योम *)check + 16) अणु
		अगर (check->fields.signature != PNP_SIGNATURE)
			जारी;
		prपूर्णांकk(KERN_INFO
		       "PnPBIOS: Found PnP BIOS installation structure at 0x%p\n",
		       check);
		length = check->fields.length;
		अगर (!length) अणु
			prपूर्णांकk(KERN_ERR
			       "PnPBIOS: installation structure is invalid, skipping\n");
			जारी;
		पूर्ण
		क्रम (sum = 0, i = 0; i < length; i++)
			sum += check->अक्षरs[i];
		अगर (sum) अणु
			prपूर्णांकk(KERN_ERR
			       "PnPBIOS: installation structure is corrupted, skipping\n");
			जारी;
		पूर्ण
		अगर (check->fields.version < 0x10) अणु
			prपूर्णांकk(KERN_WARNING
			       "PnPBIOS: PnP BIOS version %d.%d is not supported\n",
			       check->fields.version >> 4,
			       check->fields.version & 15);
			जारी;
		पूर्ण
		prपूर्णांकk(KERN_INFO
		       "PnPBIOS: PnP BIOS version %d.%d, entry 0x%x:0x%x, dseg 0x%x\n",
		       check->fields.version >> 4, check->fields.version & 15,
		       check->fields.pm16cseg, check->fields.pm16offset,
		       check->fields.pm16dseg);
		pnp_bios_install = check;
		वापस 1;
	पूर्ण

	prपूर्णांकk(KERN_INFO "PnPBIOS: PnP BIOS support was not detected.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __init exploding_pnp_bios(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	prपूर्णांकk(KERN_WARNING "%s detected. Disabling PnPBIOS\n", d->ident);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pnpbios_dmi_table[] __initस्थिर = अणु
	अणु			/* PnPBIOS GPF on boot */
	 .callback = exploding_pnp_bios,
	 .ident = "Higraded P14H",
	 .matches = अणु
		     DMI_MATCH(DMI_BIOS_VENDOR, "American Megatrends Inc."),
		     DMI_MATCH(DMI_BIOS_VERSION, "07.00T"),
		     DMI_MATCH(DMI_SYS_VENDOR, "Higraded"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "P14H"),
		     पूर्ण,
	 पूर्ण,
	अणु			/* PnPBIOS GPF on boot */
	 .callback = exploding_pnp_bios,
	 .ident = "ASUS P4P800",
	 .matches = अणु
		     DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer Inc."),
		     DMI_MATCH(DMI_BOARD_NAME, "P4P800"),
		     पूर्ण,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init pnpbios_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (pnpbios_disabled || dmi_check_प्रणाली(pnpbios_dmi_table) ||
	    arch_pnpbios_disabled()) अणु
		prपूर्णांकk(KERN_INFO "PnPBIOS: Disabled\n");
		वापस -ENODEV;
	पूर्ण

#अगर_घोषित CONFIG_PNPACPI
	अगर (!acpi_disabled && !pnpacpi_disabled) अणु
		pnpbios_disabled = 1;
		prपूर्णांकk(KERN_INFO "PnPBIOS: Disabled by ACPI PNP\n");
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर				/* CONFIG_ACPI */

	/* scan the प्रणाली क्रम pnpbios support */
	अगर (!pnpbios_probe_प्रणाली())
		वापस -ENODEV;

	/* make preparations क्रम bios calls */
	pnpbios_calls_init(pnp_bios_install);

	/* पढ़ो the node info */
	ret = pnp_bios_dev_node_info(&node_info);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: Unable to get node info.  Aborting.\n");
		वापस ret;
	पूर्ण

	/* रेजिस्टर with the pnp layer */
	ret = pnp_रेजिस्टर_protocol(&pnpbios_protocol);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: Unable to register driver.  Aborting.\n");
		वापस ret;
	पूर्ण

	/* start the proc पूर्णांकerface */
	ret = pnpbios_proc_init();
	अगर (ret)
		prपूर्णांकk(KERN_ERR "PnPBIOS: Failed to create proc interface.\n");

	/* scan क्रम pnpbios devices */
	build_devlist();

	pnp_platक्रमm_devices = 1;
	वापस 0;
पूर्ण

fs_initcall(pnpbios_init);

अटल पूर्णांक __init pnpbios_thपढ़ो_init(व्योम)
अणु
	काष्ठा task_काष्ठा *task;

	अगर (pnpbios_disabled)
		वापस 0;

	init_completion(&unload_sem);
	task = kthपढ़ो_run(pnp_करोck_thपढ़ो, शून्य, "kpnpbiosd");
	वापस PTR_ERR_OR_ZERO(task);
पूर्ण

/* Start the kernel thपढ़ो later: */
device_initcall(pnpbios_thपढ़ो_init);

EXPORT_SYMBOL(pnpbios_protocol);
