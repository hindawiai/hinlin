<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  SMI methods क्रम use with dell-smbios
 *
 *  Copyright (c) Red Hat <mjg@redhat.com>
 *  Copyright (c) 2014 Gabriele Mazzotta <gabriele.mzt@gmail.com>
 *  Copyright (c) 2014 Pali Rohथँr <pali@kernel.org>
 *  Copyright (c) 2017 Dell Inc.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "dcdbas.h"
#समावेश "dell-smbios.h"

अटल पूर्णांक da_command_address;
अटल पूर्णांक da_command_code;
अटल काष्ठा calling_पूर्णांकerface_buffer *buffer;
अटल काष्ठा platक्रमm_device *platक्रमm_device;
अटल DEFINE_MUTEX(smm_mutex);

अटल स्थिर काष्ठा dmi_प्रणाली_id dell_device_table[] __initस्थिर = अणु
	अणु
		.ident = "Dell laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "9"), /*Laptop*/
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /*Notebook*/
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Computer Corporation",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, dell_device_table);

अटल व्योम parse_da_table(स्थिर काष्ठा dmi_header *dm)
अणु
	काष्ठा calling_पूर्णांकerface_काष्ठाure *table =
		container_of(dm, काष्ठा calling_पूर्णांकerface_काष्ठाure, header);

	/* 4 bytes of table header, plus 7 bytes of Dell header, plus at least
	 * 6 bytes of entry
	 */
	अगर (dm->length < 17)
		वापस;

	da_command_address = table->cmdIOAddress;
	da_command_code = table->cmdIOCode;
पूर्ण

अटल व्योम find_cmd_address(स्थिर काष्ठा dmi_header *dm, व्योम *dummy)
अणु
	चयन (dm->type) अणु
	हाल 0xda: /* Calling पूर्णांकerface */
		parse_da_table(dm);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dell_smbios_smm_call(काष्ठा calling_पूर्णांकerface_buffer *input)
अणु
	काष्ठा smi_cmd command;
	माप_प्रकार size;

	size = माप(काष्ठा calling_पूर्णांकerface_buffer);
	command.magic = SMI_CMD_MAGIC;
	command.command_address = da_command_address;
	command.command_code = da_command_code;
	command.ebx = virt_to_phys(buffer);
	command.ecx = 0x42534931;

	mutex_lock(&smm_mutex);
	स_नकल(buffer, input, size);
	dcdbas_smi_request(&command);
	स_नकल(input, buffer, size);
	mutex_unlock(&smm_mutex);
	वापस 0;
पूर्ण

/* When enabled this indicates that SMM won't work */
अटल bool test_wsmt_enabled(व्योम)
अणु
	काष्ठा calling_पूर्णांकerface_token *wsmt;

	/* अगर token करोesn't exist, SMM will work */
	wsmt = dell_smbios_find_token(WSMT_EN_TOKEN);
	अगर (!wsmt)
		वापस false;

	/* If token exists, try to access over SMM but set a dummy वापस.
	 * - If WSMT disabled it will be overwritten by SMM
	 * - If WSMT enabled then dummy value will reमुख्य
	 */
	buffer->cmd_class = CLASS_TOKEN_READ;
	buffer->cmd_select = SELECT_TOKEN_STD;
	स_रखो(buffer, 0, माप(काष्ठा calling_पूर्णांकerface_buffer));
	buffer->input[0] = wsmt->location;
	buffer->output[0] = 99;
	dell_smbios_smm_call(buffer);
	अगर (buffer->output[0] == 99)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक init_dell_smbios_smm(व्योम)
अणु
	पूर्णांक ret;
	/*
	 * Allocate buffer below 4GB क्रम SMI data--only 32-bit physical addr
	 * is passed to SMI handler.
	 */
	buffer = (व्योम *)__get_मुक्त_page(GFP_KERNEL | GFP_DMA32);
	अगर (!buffer)
		वापस -ENOMEM;

	dmi_walk(find_cmd_address, शून्य);

	अगर (test_wsmt_enabled()) अणु
		pr_debug("Disabling due to WSMT enabled\n");
		ret = -ENODEV;
		जाओ fail_wsmt;
	पूर्ण

	platक्रमm_device = platक्रमm_device_alloc("dell-smbios", 1);
	अगर (!platक्रमm_device) अणु
		ret = -ENOMEM;
		जाओ fail_platक्रमm_device_alloc;
	पूर्ण

	ret = platक्रमm_device_add(platक्रमm_device);
	अगर (ret)
		जाओ fail_platक्रमm_device_add;

	ret = dell_smbios_रेजिस्टर_device(&platक्रमm_device->dev,
					  &dell_smbios_smm_call);
	अगर (ret)
		जाओ fail_रेजिस्टर;

	वापस 0;

fail_रेजिस्टर:
	platक्रमm_device_del(platक्रमm_device);

fail_platक्रमm_device_add:
	platक्रमm_device_put(platक्रमm_device);

fail_wsmt:
fail_platक्रमm_device_alloc:
	मुक्त_page((अचिन्हित दीर्घ)buffer);
	वापस ret;
पूर्ण

व्योम निकास_dell_smbios_smm(व्योम)
अणु
	अगर (platक्रमm_device) अणु
		dell_smbios_unरेजिस्टर_device(&platक्रमm_device->dev);
		platक्रमm_device_unरेजिस्टर(platक्रमm_device);
		मुक्त_page((अचिन्हित दीर्घ)buffer);
	पूर्ण
पूर्ण
