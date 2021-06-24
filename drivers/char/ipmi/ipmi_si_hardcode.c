<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#घोषणा pr_fmt(fmt) "ipmi_hardcode: " fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "ipmi_si.h"
#समावेश "ipmi_plat_data.h"

/*
 * There can be 4 IO ports passed in (with or without IRQs), 4 addresses,
 * a शेष IO port, and 1 ACPI/SPMI address.  That sets SI_MAX_DRIVERS.
 */

#घोषणा SI_MAX_PARMS 4

#घोषणा MAX_SI_TYPE_STR 30
अटल अक्षर          si_type_str[MAX_SI_TYPE_STR] __initdata;
अटल अचिन्हित दीर्घ addrs[SI_MAX_PARMS];
अटल अचिन्हित पूर्णांक num_addrs;
अटल अचिन्हित पूर्णांक  ports[SI_MAX_PARMS];
अटल अचिन्हित पूर्णांक num_ports;
अटल पूर्णांक           irqs[SI_MAX_PARMS] __initdata;
अटल अचिन्हित पूर्णांक num_irqs __initdata;
अटल पूर्णांक           regspacings[SI_MAX_PARMS] __initdata;
अटल अचिन्हित पूर्णांक num_regspacings __initdata;
अटल पूर्णांक           regsizes[SI_MAX_PARMS] __initdata;
अटल अचिन्हित पूर्णांक num_regsizes __initdata;
अटल पूर्णांक           regshअगरts[SI_MAX_PARMS] __initdata;
अटल अचिन्हित पूर्णांक num_regshअगरts __initdata;
अटल पूर्णांक slave_addrs[SI_MAX_PARMS] __initdata;
अटल अचिन्हित पूर्णांक num_slave_addrs __initdata;

module_param_string(type, si_type_str, MAX_SI_TYPE_STR, 0);
MODULE_PARM_DESC(type,
		 "Defines the type of each interface, each interface separated by commas.  The types are 'kcs', 'smic', and 'bt'.  For example si_type=kcs,bt will set the first interface to kcs and the second to bt");
module_param_hw_array(addrs, uदीर्घ, iomem, &num_addrs, 0);
MODULE_PARM_DESC(addrs,
		 "Sets the memory address of each interface, the addresses separated by commas.  Only use if an interface is in memory.  Otherwise, set it to zero or leave it blank.");
module_param_hw_array(ports, uपूर्णांक, ioport, &num_ports, 0);
MODULE_PARM_DESC(ports,
		 "Sets the port address of each interface, the addresses separated by commas.  Only use if an interface is a port.  Otherwise, set it to zero or leave it blank.");
module_param_hw_array(irqs, पूर्णांक, irq, &num_irqs, 0);
MODULE_PARM_DESC(irqs,
		 "Sets the interrupt of each interface, the addresses separated by commas.  Only use if an interface has an interrupt.  Otherwise, set it to zero or leave it blank.");
module_param_hw_array(regspacings, पूर्णांक, other, &num_regspacings, 0);
MODULE_PARM_DESC(regspacings,
		 "The number of bytes between the start address and each successive register used by the interface.  For instance, if the start address is 0xca2 and the spacing is 2, then the second address is at 0xca4.  Defaults to 1.");
module_param_hw_array(regsizes, पूर्णांक, other, &num_regsizes, 0);
MODULE_PARM_DESC(regsizes,
		 "The size of the specific IPMI register in bytes. This should generally be 1, 2, 4, or 8 for an 8-bit, 16-bit, 32-bit, or 64-bit register.  Use this if you the 8-bit IPMI register has to be read from a larger register.");
module_param_hw_array(regshअगरts, पूर्णांक, other, &num_regshअगरts, 0);
MODULE_PARM_DESC(regshअगरts,
		 "The amount to shift the data read from the. IPMI register, in bits.  For instance, if the data is read from a 32-bit word and the IPMI data is in bit 8-15, then the shift would be 8");
module_param_hw_array(slave_addrs, पूर्णांक, other, &num_slave_addrs, 0);
MODULE_PARM_DESC(slave_addrs,
		 "Set the default IPMB slave address for the controller.  Normally this is 0x20, but can be overridden by this parm.  This is an array indexed by interface number.");

अटल व्योम __init ipmi_hardcode_init_one(स्थिर अक्षर *si_type_str,
					  अचिन्हित पूर्णांक i,
					  अचिन्हित दीर्घ addr,
					  क्रमागत ipmi_addr_space addr_space)
अणु
	काष्ठा ipmi_plat_data p;
	पूर्णांक t;

	स_रखो(&p, 0, माप(p));

	p.अगरtype = IPMI_PLAT_IF_SI;
	अगर (!si_type_str || !*si_type_str) अणु
		p.type = SI_KCS;
	पूर्ण अन्यथा अणु
		t = match_string(si_to_str, -1, si_type_str);
		अगर (t < 0) अणु
			pr_warn("Interface type specified for interface %d, was invalid: %s\n",
				i, si_type_str);
			वापस;
		पूर्ण
		p.type = t;
	पूर्ण

	p.regsize = regsizes[i];
	p.slave_addr = slave_addrs[i];
	p.addr_source = SI_HARDCODED;
	p.regshअगरt = regshअगरts[i];
	p.regsize = regsizes[i];
	p.addr = addr;
	p.space = addr_space;

	ipmi_platक्रमm_add("hardcode-ipmi-si", i, &p);
पूर्ण

व्योम __init ipmi_hardcode_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर *str;
	अक्षर *si_type[SI_MAX_PARMS];

	स_रखो(si_type, 0, माप(si_type));

	/* Parse out the si_type string पूर्णांकo its components. */
	str = si_type_str;
	अगर (*str != '\0') अणु
		क्रम (i = 0; (i < SI_MAX_PARMS) && (*str != '\0'); i++) अणु
			si_type[i] = str;
			str = म_अक्षर(str, ',');
			अगर (str) अणु
				*str = '\0';
				str++;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SI_MAX_PARMS; i++) अणु
		अगर (i < num_ports && ports[i])
			ipmi_hardcode_init_one(si_type[i], i, ports[i],
					       IPMI_IO_ADDR_SPACE);
		अगर (i < num_addrs && addrs[i])
			ipmi_hardcode_init_one(si_type[i], i, addrs[i],
					       IPMI_MEM_ADDR_SPACE);
	पूर्ण
पूर्ण


व्योम ipmi_si_hardcode_निकास(व्योम)
अणु
	ipmi_हटाओ_platक्रमm_device_by_name("hardcode-ipmi-si");
पूर्ण

/*
 * Returns true of the given address exists as a hardcoded address,
 * false अगर not.
 */
पूर्णांक ipmi_si_hardcode_match(पूर्णांक addr_space, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक i;

	अगर (addr_space == IPMI_IO_ADDR_SPACE) अणु
		क्रम (i = 0; i < num_ports; i++) अणु
			अगर (ports[i] == addr)
				वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < num_addrs; i++) अणु
			अगर (addrs[i] == addr)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
