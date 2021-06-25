<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kobject.h>
#समावेश <boot_param.h>

अटल sमाप_प्रकार boardinfo_show(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर board_manufacturer[64] = अणु0पूर्ण;
	अक्षर *पंचांगp_board_manufacturer = board_manufacturer;
	अक्षर bios_venकरोr[64] = अणु0पूर्ण;
	अक्षर *पंचांगp_bios_venकरोr = bios_venकरोr;

	म_नकल(board_manufacturer, eboard->name);
	म_नकल(bios_venकरोr, eपूर्णांकer->description);

	वापस प्र_लिखो(buf,
		       "Board Info\n"
		       "Manufacturer\t\t: %s\n"
		       "Board Name\t\t: %s\n"
		       "Family\t\t\t: LOONGSON3\n\n"
		       "BIOS Info\n"
		       "Vendor\t\t\t: %s\n"
		       "Version\t\t\t: %s\n"
		       "ROM Size\t\t: %d KB\n"
		       "Release Date\t\t: %s\n",
		       strsep(&पंचांगp_board_manufacturer, "-"),
		       eboard->name,
		       strsep(&पंचांगp_bios_venकरोr, "-"),
		       eपूर्णांकer->description,
		       eपूर्णांकer->size,
		       especial->special_name);
पूर्ण
अटल काष्ठा kobj_attribute boardinfo_attr = __ATTR(boardinfo, 0444,
						     boardinfo_show, शून्य);

अटल पूर्णांक __init boardinfo_init(व्योम)
अणु
	काष्ठा kobject *lefi_kobj;

	lefi_kobj = kobject_create_and_add("lefi", firmware_kobj);
	अगर (!lefi_kobj) अणु
		pr_err("lefi: Firmware registration failed.\n");
		वापस -ENOMEM;
	पूर्ण

	वापस sysfs_create_file(lefi_kobj, &boardinfo_attr.attr);
पूर्ण
late_initcall(boardinfo_init);
