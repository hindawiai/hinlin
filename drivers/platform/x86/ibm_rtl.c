<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM Real-Time Linux driver
 *
 * Copyright (C) IBM Corporation, 2010
 *
 * Author: Keith Mannthey <kmannth@us.ibm.com>
 *         Vernon Mauery <vernux@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/dmi.h>
#समावेश <linux/efi.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/bios_ebda.h>

#समावेश <linux/io-64-nonatomic-lo-hi.h>

अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Force driver load, ignore DMI data");

अटल bool debug;
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Show debug output");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Keith Mannthey <kmmanth@us.ibm.com>");
MODULE_AUTHOR("Vernon Mauery <vernux@us.ibm.com>");

#घोषणा RTL_ADDR_TYPE_IO    1
#घोषणा RTL_ADDR_TYPE_MMIO  2

#घोषणा RTL_CMD_ENTER_PRTM  1
#घोषणा RTL_CMD_EXIT_PRTM   2

/* The RTL table as presented by the EBDA: */
काष्ठा ibm_rtl_table अणु
	अक्षर signature[5]; /* signature should be "_RTL_" */
	u8 version;
	u8 rt_status;
	u8 command;
	u8 command_status;
	u8 cmd_address_type;
	u8 cmd_granularity;
	u8 cmd_offset;
	u16 reserve1;
	u32 cmd_port_address; /* platक्रमm dependent address */
	u32 cmd_port_value;   /* platक्रमm dependent value */
पूर्ण __attribute__((packed));

/* to locate "_RTL_" signature करो a masked 5-byte पूर्णांकeger compare */
#घोषणा RTL_SIGNATURE 0x0000005f4c54525fULL
#घोषणा RTL_MASK      0x000000ffffffffffULL

#घोषणा RTL_DEBUG(fmt, ...)				\
करो अणु							\
	अगर (debug)					\
		pr_info(fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

अटल DEFINE_MUTEX(rtl_lock);
अटल काष्ठा ibm_rtl_table __iomem *rtl_table;
अटल व्योम __iomem *ebda_map;
अटल व्योम __iomem *rtl_cmd_addr;
अटल u8 rtl_cmd_type;
अटल u8 rtl_cmd_width;

अटल व्योम __iomem *rtl_port_map(phys_addr_t addr, अचिन्हित दीर्घ len)
अणु
	अगर (rtl_cmd_type == RTL_ADDR_TYPE_MMIO)
		वापस ioremap(addr, len);
	वापस ioport_map(addr, len);
पूर्ण

अटल व्योम rtl_port_unmap(व्योम __iomem *addr)
अणु
	अगर (addr && rtl_cmd_type == RTL_ADDR_TYPE_MMIO)
		iounmap(addr);
	अन्यथा
		ioport_unmap(addr);
पूर्ण

अटल पूर्णांक ibm_rtl_ग_लिखो(u8 value)
अणु
	पूर्णांक ret = 0, count = 0;
	u32 cmd_port_val;

	RTL_DEBUG("%s(%d)\n", __func__, value);

	value = value == 1 ? RTL_CMD_ENTER_PRTM : RTL_CMD_EXIT_PRTM;

	mutex_lock(&rtl_lock);

	अगर (ioपढ़ो8(&rtl_table->rt_status) != value) अणु
		ioग_लिखो8(value, &rtl_table->command);

		चयन (rtl_cmd_width) अणु
		हाल 8:
			cmd_port_val = ioपढ़ो8(&rtl_table->cmd_port_value);
			RTL_DEBUG("cmd_port_val = %u\n", cmd_port_val);
			ioग_लिखो8((u8)cmd_port_val, rtl_cmd_addr);
			अवरोध;
		हाल 16:
			cmd_port_val = ioपढ़ो16(&rtl_table->cmd_port_value);
			RTL_DEBUG("cmd_port_val = %u\n", cmd_port_val);
			ioग_लिखो16((u16)cmd_port_val, rtl_cmd_addr);
			अवरोध;
		हाल 32:
			cmd_port_val = ioपढ़ो32(&rtl_table->cmd_port_value);
			RTL_DEBUG("cmd_port_val = %u\n", cmd_port_val);
			ioग_लिखो32(cmd_port_val, rtl_cmd_addr);
			अवरोध;
		पूर्ण

		जबतक (ioपढ़ो8(&rtl_table->command)) अणु
			msleep(10);
			अगर (count++ > 500) अणु
				pr_err("Hardware not responding to "
				       "mode switch request\n");
				ret = -EIO;
				अवरोध;
			पूर्ण

		पूर्ण

		अगर (ioपढ़ो8(&rtl_table->command_status)) अणु
			RTL_DEBUG("command_status reports failed command\n");
			ret = -EIO;
		पूर्ण
	पूर्ण

	mutex_unlock(&rtl_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार rtl_show_version(काष्ठा device *dev,
                                काष्ठा device_attribute *attr,
                                अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)ioपढ़ो8(&rtl_table->version));
पूर्ण

अटल sमाप_प्रकार rtl_show_state(काष्ठा device *dev,
                              काष्ठा device_attribute *attr,
                              अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", ioपढ़ो8(&rtl_table->rt_status));
पूर्ण

अटल sमाप_प्रकार rtl_set_state(काष्ठा device *dev,
                             काष्ठा device_attribute *attr,
                             स्थिर अक्षर *buf,
                             माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	अगर (count < 1 || count > 2)
		वापस -EINVAL;

	चयन (buf[0]) अणु
	हाल '0':
		ret = ibm_rtl_ग_लिखो(0);
		अवरोध;
	हाल '1':
		ret = ibm_rtl_ग_लिखो(1);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (ret >= 0)
		ret = count;

	वापस ret;
पूर्ण

अटल काष्ठा bus_type rtl_subsys = अणु
	.name = "ibm_rtl",
	.dev_name = "ibm_rtl",
पूर्ण;

अटल DEVICE_ATTR(version, S_IRUGO, rtl_show_version, शून्य);
अटल DEVICE_ATTR(state, 0600, rtl_show_state, rtl_set_state);

अटल काष्ठा device_attribute *rtl_attributes[] = अणु
	&dev_attr_version,
	&dev_attr_state,
	शून्य
पूर्ण;


अटल पूर्णांक rtl_setup_sysfs(व्योम) अणु
	पूर्णांक ret, i;

	ret = subsys_प्रणाली_रेजिस्टर(&rtl_subsys, शून्य);
	अगर (!ret) अणु
		क्रम (i = 0; rtl_attributes[i]; i ++)
			device_create_file(rtl_subsys.dev_root, rtl_attributes[i]);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rtl_tearकरोwn_sysfs(व्योम) अणु
	पूर्णांक i;
	क्रम (i = 0; rtl_attributes[i]; i ++)
		device_हटाओ_file(rtl_subsys.dev_root, rtl_attributes[i]);
	bus_unरेजिस्टर(&rtl_subsys);
पूर्ण


अटल स्थिर काष्ठा dmi_प्रणाली_id ibm_rtl_dmi_table[] __initस्थिर = अणु
	अणु                                                  \
		.matches = अणु                               \
			DMI_MATCH(DMI_SYS_VENDOR, "IBM"),  \
		पूर्ण,                                         \
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init ibm_rtl_init(व्योम) अणु
	अचिन्हित दीर्घ ebda_addr, ebda_size;
	अचिन्हित पूर्णांक ebda_kb;
	पूर्णांक ret = -ENODEV, i;

	अगर (क्रमce)
		pr_warn("module loaded by force\n");
	/* first ensure that we are running on IBM HW */
	अन्यथा अगर (efi_enabled(EFI_BOOT) || !dmi_check_प्रणाली(ibm_rtl_dmi_table))
		वापस -ENODEV;

	/* Get the address क्रम the Extended BIOS Data Area */
	ebda_addr = get_bios_ebda();
	अगर (!ebda_addr) अणु
		RTL_DEBUG("no BIOS EBDA found\n");
		वापस -ENODEV;
	पूर्ण

	ebda_map = ioremap(ebda_addr, 4);
	अगर (!ebda_map)
		वापस -ENOMEM;

	/* First word in the EDBA is the Size in KB */
	ebda_kb = ioपढ़ो16(ebda_map);
	RTL_DEBUG("EBDA is %d kB\n", ebda_kb);

	अगर (ebda_kb == 0)
		जाओ out;

	iounmap(ebda_map);
	ebda_size = ebda_kb*1024;

	/* Remap the whole table */
	ebda_map = ioremap(ebda_addr, ebda_size);
	अगर (!ebda_map)
		वापस -ENOMEM;

	/* search क्रम the _RTL_ signature at the start of the table */
	क्रम (i = 0 ; i < ebda_size/माप(अचिन्हित पूर्णांक); i++) अणु
		काष्ठा ibm_rtl_table __iomem * पंचांगp;
		पंचांगp = (काष्ठा ibm_rtl_table __iomem *) (ebda_map+i);
		अगर ((पढ़ोq(&पंचांगp->signature) & RTL_MASK) == RTL_SIGNATURE) अणु
			phys_addr_t addr;
			अचिन्हित पूर्णांक plen;
			RTL_DEBUG("found RTL_SIGNATURE at %p\n", पंचांगp);
			rtl_table = पंचांगp;
			/* The address, value, width and offset are platक्रमm
			 * dependent and found in the ibm_rtl_table */
			rtl_cmd_width = ioपढ़ो8(&rtl_table->cmd_granularity);
			rtl_cmd_type = ioपढ़ो8(&rtl_table->cmd_address_type);
			RTL_DEBUG("rtl_cmd_width = %u, rtl_cmd_type = %u\n",
				  rtl_cmd_width, rtl_cmd_type);
			addr = ioपढ़ो32(&rtl_table->cmd_port_address);
			RTL_DEBUG("addr = %#llx\n", (अचिन्हित दीर्घ दीर्घ)addr);
			plen = rtl_cmd_width/माप(अक्षर);
			rtl_cmd_addr = rtl_port_map(addr, plen);
			RTL_DEBUG("rtl_cmd_addr = %p\n", rtl_cmd_addr);
			अगर (!rtl_cmd_addr) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
			ret = rtl_setup_sysfs();
			अवरोध;
		पूर्ण
	पूर्ण

out:
	अगर (ret) अणु
		iounmap(ebda_map);
		rtl_port_unmap(rtl_cmd_addr);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास ibm_rtl_निकास(व्योम)
अणु
	अगर (rtl_table) अणु
		RTL_DEBUG("cleaning up");
		/* करो not leave the machine in SMI-मुक्त mode */
		ibm_rtl_ग_लिखो(0);
		/* unmap, unlink and हटाओ all traces */
		rtl_tearकरोwn_sysfs();
		iounmap(ebda_map);
		rtl_port_unmap(rtl_cmd_addr);
	पूर्ण
पूर्ण

module_init(ibm_rtl_init);
module_निकास(ibm_rtl_निकास);
