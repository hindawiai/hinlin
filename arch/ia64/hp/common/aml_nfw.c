<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OpRegion handler to allow AML to call native firmware
 *
 * (c) Copyright 2007 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 *
 * This driver implements HP Open Source Review Board proposal 1842,
 * which was approved on 9/20/2006.
 *
 * For technical करोcumentation, see the HP SPPA Firmware EAS, Appendix F.
 *
 * ACPI करोes not define a mechanism क्रम AML methods to call native firmware
 * पूर्णांकerfaces such as PAL or SAL.  This OpRegion handler adds such a mechanism.
 * After the handler is installed, an AML method can call native firmware by
 * storing the arguments and firmware entry poपूर्णांक to specअगरic offsets in the
 * OpRegion.  When AML पढ़ोs the "return value" offset from the OpRegion, this
 * handler loads up the arguments, makes the firmware call, and वापसs the
 * result.
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/sal.h>

MODULE_AUTHOR("Bjorn Helgaas <bjorn.helgaas@hp.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ACPI opregion handler for native firmware calls");

अटल bool क्रमce_रेजिस्टर;
module_param_named(क्रमce, क्रमce_रेजिस्टर, bool, 0);
MODULE_PARM_DESC(क्रमce, "Install opregion handler even without HPQ5001 device");

#घोषणा AML_NFW_SPACE		0xA1

काष्ठा ia64_pdesc अणु
	व्योम *ip;
	व्योम *gp;
पूर्ण;

/*
 * N.B.  The layout of this काष्ठाure is defined in the HP SPPA FW EAS, and
 *	 the member offsets are embedded in AML methods.
 */
काष्ठा ia64_nfw_context अणु
	u64 arg[8];
	काष्ठा ia64_sal_retval ret;
	u64 ip;
	u64 gp;
	u64 pad[2];
पूर्ण;

अटल व्योम *virt_map(u64 address)
अणु
	अगर (address & (1UL << 63))
		वापस (व्योम *) (__IA64_UNCACHED_OFFSET | address);

	वापस __va(address);
पूर्ण

अटल व्योम aml_nfw_execute(काष्ठा ia64_nfw_context *c)
अणु
	काष्ठा ia64_pdesc virt_entry;
	ia64_sal_handler entry;

	virt_entry.ip = virt_map(c->ip);
	virt_entry.gp = virt_map(c->gp);

	entry = (ia64_sal_handler) &virt_entry;

	IA64_FW_CALL(entry, c->ret,
		     c->arg[0], c->arg[1], c->arg[2], c->arg[3],
		     c->arg[4], c->arg[5], c->arg[6], c->arg[7]);
पूर्ण

अटल व्योम aml_nfw_पढ़ो_arg(u8 *offset, u32 bit_width, u64 *value)
अणु
	चयन (bit_width) अणु
	हाल 8:
		*value = *(u8 *)offset;
		अवरोध;
	हाल 16:
		*value = *(u16 *)offset;
		अवरोध;
	हाल 32:
		*value = *(u32 *)offset;
		अवरोध;
	हाल 64:
		*value = *(u64 *)offset;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम aml_nfw_ग_लिखो_arg(u8 *offset, u32 bit_width, u64 *value)
अणु
	चयन (bit_width) अणु
	हाल 8:
		*(u8 *) offset = *value;
		अवरोध;
	हाल 16:
		*(u16 *) offset = *value;
		अवरोध;
	हाल 32:
		*(u32 *) offset = *value;
		अवरोध;
	हाल 64:
		*(u64 *) offset = *value;
		अवरोध;
	पूर्ण
पूर्ण

अटल acpi_status aml_nfw_handler(u32 function, acpi_physical_address address,
	u32 bit_width, u64 *value, व्योम *handler_context,
	व्योम *region_context)
अणु
	काष्ठा ia64_nfw_context *context = handler_context;
	u8 *offset = (u8 *) context + address;

	अगर (bit_width !=  8 && bit_width != 16 &&
	    bit_width != 32 && bit_width != 64)
		वापस AE_BAD_PARAMETER;

	अगर (address + (bit_width >> 3) > माप(काष्ठा ia64_nfw_context))
		वापस AE_BAD_PARAMETER;

	चयन (function) अणु
	हाल ACPI_READ:
		अगर (address == दुरत्व(काष्ठा ia64_nfw_context, ret))
			aml_nfw_execute(context);
		aml_nfw_पढ़ो_arg(offset, bit_width, value);
		अवरोध;
	हाल ACPI_WRITE:
		aml_nfw_ग_लिखो_arg(offset, bit_width, value);
		अवरोध;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल काष्ठा ia64_nfw_context global_context;
अटल पूर्णांक global_handler_रेजिस्टरed;

अटल पूर्णांक aml_nfw_add_global_handler(व्योम)
अणु
	acpi_status status;

	अगर (global_handler_रेजिस्टरed)
		वापस 0;

	status = acpi_install_address_space_handler(ACPI_ROOT_OBJECT,
		AML_NFW_SPACE, aml_nfw_handler, शून्य, &global_context);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	global_handler_रेजिस्टरed = 1;
	prपूर्णांकk(KERN_INFO "Global 0x%02X opregion handler registered\n",
		AML_NFW_SPACE);
	वापस 0;
पूर्ण

अटल पूर्णांक aml_nfw_हटाओ_global_handler(व्योम)
अणु
	acpi_status status;

	अगर (!global_handler_रेजिस्टरed)
		वापस 0;

	status = acpi_हटाओ_address_space_handler(ACPI_ROOT_OBJECT,
		AML_NFW_SPACE, aml_nfw_handler);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	global_handler_रेजिस्टरed = 0;
	prपूर्णांकk(KERN_INFO "Global 0x%02X opregion handler removed\n",
		AML_NFW_SPACE);
	वापस 0;
पूर्ण

अटल पूर्णांक aml_nfw_add(काष्ठा acpi_device *device)
अणु
	/*
	 * We would normally allocate a new context काष्ठाure and install
	 * the address space handler क्रम the specअगरic device we found.
	 * But the HP-UX implementation shares a single global context
	 * and always माला_दो the handler at the root, so we'll करो the same.
	 */
	वापस aml_nfw_add_global_handler();
पूर्ण

अटल पूर्णांक aml_nfw_हटाओ(काष्ठा acpi_device *device)
अणु
	वापस aml_nfw_हटाओ_global_handler();
पूर्ण

अटल स्थिर काष्ठा acpi_device_id aml_nfw_ids[] = अणु
	अणु"HPQ5001", 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल काष्ठा acpi_driver acpi_aml_nfw_driver = अणु
	.name = "native firmware",
	.ids = aml_nfw_ids,
	.ops = अणु
		.add = aml_nfw_add,
		.हटाओ = aml_nfw_हटाओ,
		पूर्ण,
पूर्ण;

अटल पूर्णांक __init aml_nfw_init(व्योम)
अणु
	पूर्णांक result;

	अगर (क्रमce_रेजिस्टर)
		aml_nfw_add_global_handler();

	result = acpi_bus_रेजिस्टर_driver(&acpi_aml_nfw_driver);
	अगर (result < 0) अणु
		aml_nfw_हटाओ_global_handler();
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास aml_nfw_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_aml_nfw_driver);
	aml_nfw_हटाओ_global_handler();
पूर्ण

module_init(aml_nfw_init);
module_निकास(aml_nfw_निकास);
