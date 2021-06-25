<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * A hack to create a platक्रमm device from a DMI entry.  This will
 * allow स्वतःloading of the IPMI drive based on SMBIOS entries.
 */

#घोषणा pr_fmt(fmt) "%s" fmt, "ipmi:dmi: "
#घोषणा dev_fmt pr_fmt

#समावेश <linux/ipmi.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश "ipmi_dmi.h"
#समावेश "ipmi_plat_data.h"

#घोषणा IPMI_DMI_TYPE_KCS	0x01
#घोषणा IPMI_DMI_TYPE_SMIC	0x02
#घोषणा IPMI_DMI_TYPE_BT	0x03
#घोषणा IPMI_DMI_TYPE_SSIF	0x04

काष्ठा ipmi_dmi_info अणु
	क्रमागत si_type si_type;
	अचिन्हित पूर्णांक space; /* addr space क्रम si, पूर्णांकf# क्रम ssअगर */
	अचिन्हित दीर्घ addr;
	u8 slave_addr;
	काष्ठा ipmi_dmi_info *next;
पूर्ण;

अटल काष्ठा ipmi_dmi_info *ipmi_dmi_infos;

अटल पूर्णांक ipmi_dmi_nr __initdata;

अटल व्योम __init dmi_add_platक्रमm_ipmi(अचिन्हित दीर्घ base_addr,
					 अचिन्हित पूर्णांक space,
					 u8 slave_addr,
					 पूर्णांक irq,
					 पूर्णांक offset,
					 पूर्णांक type)
अणु
	स्थिर अक्षर *name;
	काष्ठा ipmi_dmi_info *info;
	काष्ठा ipmi_plat_data p;

	स_रखो(&p, 0, माप(p));

	name = "dmi-ipmi-si";
	p.अगरtype = IPMI_PLAT_IF_SI;
	चयन (type) अणु
	हाल IPMI_DMI_TYPE_SSIF:
		name = "dmi-ipmi-ssif";
		p.अगरtype = IPMI_PLAT_IF_SSIF;
		p.type = SI_TYPE_INVALID;
		अवरोध;
	हाल IPMI_DMI_TYPE_BT:
		p.type = SI_BT;
		अवरोध;
	हाल IPMI_DMI_TYPE_KCS:
		p.type = SI_KCS;
		अवरोध;
	हाल IPMI_DMI_TYPE_SMIC:
		p.type = SI_SMIC;
		अवरोध;
	शेष:
		pr_err("Invalid IPMI type: %d\n", type);
		वापस;
	पूर्ण

	p.addr = base_addr;
	p.space = space;
	p.regspacing = offset;
	p.irq = irq;
	p.slave_addr = slave_addr;
	p.addr_source = SI_SMBIOS;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		pr_warn("Could not allocate dmi info\n");
	पूर्ण अन्यथा अणु
		info->si_type = p.type;
		info->space = space;
		info->addr = base_addr;
		info->slave_addr = slave_addr;
		info->next = ipmi_dmi_infos;
		ipmi_dmi_infos = info;
	पूर्ण

	अगर (ipmi_platक्रमm_add(name, ipmi_dmi_nr, &p))
		ipmi_dmi_nr++;
पूर्ण

/*
 * Look up the slave address क्रम a given पूर्णांकerface.  This is here
 * because ACPI करोesn't have a slave address जबतक SMBIOS करोes, but we
 * prefer using ACPI so the ACPI code can use the IPMI namespace.
 * This function allows an ACPI-specअगरied IPMI device to look up the
 * slave address from the DMI table.
 */
पूर्णांक ipmi_dmi_get_slave_addr(क्रमागत si_type si_type, अचिन्हित पूर्णांक space,
			    अचिन्हित दीर्घ base_addr)
अणु
	काष्ठा ipmi_dmi_info *info = ipmi_dmi_infos;

	जबतक (info) अणु
		अगर (info->si_type == si_type &&
		    info->space == space &&
		    info->addr == base_addr)
			वापस info->slave_addr;
		info = info->next;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ipmi_dmi_get_slave_addr);

#घोषणा DMI_IPMI_MIN_LENGTH	0x10
#घोषणा DMI_IPMI_VER2_LENGTH	0x12
#घोषणा DMI_IPMI_TYPE		4
#घोषणा DMI_IPMI_SLAVEADDR	6
#घोषणा DMI_IPMI_ADDR		8
#घोषणा DMI_IPMI_ACCESS		0x10
#घोषणा DMI_IPMI_IRQ		0x11
#घोषणा DMI_IPMI_IO_MASK	0xfffe

अटल व्योम __init dmi_decode_ipmi(स्थिर काष्ठा dmi_header *dm)
अणु
	स्थिर u8 *data = (स्थिर u8 *) dm;
	पूर्णांक space = IPMI_IO_ADDR_SPACE;
	अचिन्हित दीर्घ base_addr;
	u8 len = dm->length;
	u8 slave_addr;
	पूर्णांक irq = 0, offset = 0;
	पूर्णांक type;

	अगर (len < DMI_IPMI_MIN_LENGTH)
		वापस;

	type = data[DMI_IPMI_TYPE];
	slave_addr = data[DMI_IPMI_SLAVEADDR];

	स_नकल(&base_addr, data + DMI_IPMI_ADDR, माप(अचिन्हित दीर्घ));
	अगर (!base_addr) अणु
		pr_err("Base address is zero, assuming no IPMI interface\n");
		वापस;
	पूर्ण
	अगर (len >= DMI_IPMI_VER2_LENGTH) अणु
		अगर (type == IPMI_DMI_TYPE_SSIF) अणु
			space = 0; /* Match I2C पूर्णांकerface 0. */
			base_addr = data[DMI_IPMI_ADDR] >> 1;
			अगर (base_addr == 0) अणु
				/*
				 * Some broken प्रणालीs put the I2C address in
				 * the slave address field.  We try to
				 * accommodate them here.
				 */
				base_addr = data[DMI_IPMI_SLAVEADDR] >> 1;
				slave_addr = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (base_addr & 1) अणु
				/* I/O */
				base_addr &= DMI_IPMI_IO_MASK;
			पूर्ण अन्यथा अणु
				/* Memory */
				space = IPMI_MEM_ADDR_SPACE;
			पूर्ण

			/*
			 * If bit 4 of byte 0x10 is set, then the lsb
			 * क्रम the address is odd.
			 */
			base_addr |= (data[DMI_IPMI_ACCESS] >> 4) & 1;

			irq = data[DMI_IPMI_IRQ];

			/*
			 * The top two bits of byte 0x10 hold the
			 * रेजिस्टर spacing.
			 */
			चयन ((data[DMI_IPMI_ACCESS] >> 6) & 3) अणु
			हाल 0: /* Byte boundaries */
				offset = 1;
				अवरोध;
			हाल 1: /* 32-bit boundaries */
				offset = 4;
				अवरोध;
			हाल 2: /* 16-byte boundaries */
				offset = 16;
				अवरोध;
			शेष:
				pr_err("Invalid offset: 0\n");
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Old DMI spec. */
		/*
		 * Note that technically, the lower bit of the base
		 * address should be 1 अगर the address is I/O and 0 अगर
		 * the address is in memory.  So many प्रणालीs get that
		 * wrong (and all that I have seen are I/O) so we just
		 * ignore that bit and assume I/O.  Systems that use
		 * memory should use the newer spec, anyway.
		 */
		base_addr = base_addr & DMI_IPMI_IO_MASK;
		offset = 1;
	पूर्ण

	dmi_add_platक्रमm_ipmi(base_addr, space, slave_addr, irq,
			      offset, type);
पूर्ण

अटल पूर्णांक __init scan_क्रम_dmi_ipmi(व्योम)
अणु
	स्थिर काष्ठा dmi_device *dev = शून्य;

	जबतक ((dev = dmi_find_device(DMI_DEV_TYPE_IPMI, शून्य, dev)))
		dmi_decode_ipmi((स्थिर काष्ठा dmi_header *) dev->device_data);

	वापस 0;
पूर्ण
subsys_initcall(scan_क्रम_dmi_ipmi);
