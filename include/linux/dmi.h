<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DMI_H__
#घोषणा __DMI_H__

#समावेश <linux/list.h>
#समावेश <linux/kobject.h>
#समावेश <linux/mod_devicetable.h>

/* क्रमागत dmi_field is in mod_devicetable.h */

क्रमागत dmi_device_type अणु
	DMI_DEV_TYPE_ANY = 0,
	DMI_DEV_TYPE_OTHER,
	DMI_DEV_TYPE_UNKNOWN,
	DMI_DEV_TYPE_VIDEO,
	DMI_DEV_TYPE_SCSI,
	DMI_DEV_TYPE_ETHERNET,
	DMI_DEV_TYPE_TOKENRING,
	DMI_DEV_TYPE_SOUND,
	DMI_DEV_TYPE_PATA,
	DMI_DEV_TYPE_SATA,
	DMI_DEV_TYPE_SAS,
	DMI_DEV_TYPE_IPMI = -1,
	DMI_DEV_TYPE_OEM_STRING = -2,
	DMI_DEV_TYPE_DEV_ONBOARD = -3,
	DMI_DEV_TYPE_DEV_SLOT = -4,
पूर्ण;

क्रमागत dmi_entry_type अणु
	DMI_ENTRY_BIOS = 0,
	DMI_ENTRY_SYSTEM,
	DMI_ENTRY_BASEBOARD,
	DMI_ENTRY_CHASSIS,
	DMI_ENTRY_PROCESSOR,
	DMI_ENTRY_MEM_CONTROLLER,
	DMI_ENTRY_MEM_MODULE,
	DMI_ENTRY_CACHE,
	DMI_ENTRY_PORT_CONNECTOR,
	DMI_ENTRY_SYSTEM_SLOT,
	DMI_ENTRY_ONBOARD_DEVICE,
	DMI_ENTRY_OEMSTRINGS,
	DMI_ENTRY_SYSCONF,
	DMI_ENTRY_BIOS_LANG,
	DMI_ENTRY_GROUP_ASSOC,
	DMI_ENTRY_SYSTEM_EVENT_LOG,
	DMI_ENTRY_PHYS_MEM_ARRAY,
	DMI_ENTRY_MEM_DEVICE,
	DMI_ENTRY_32_MEM_ERROR,
	DMI_ENTRY_MEM_ARRAY_MAPPED_ADDR,
	DMI_ENTRY_MEM_DEV_MAPPED_ADDR,
	DMI_ENTRY_BUILTIN_POINTING_DEV,
	DMI_ENTRY_PORTABLE_BATTERY,
	DMI_ENTRY_SYSTEM_RESET,
	DMI_ENTRY_HW_SECURITY,
	DMI_ENTRY_SYSTEM_POWER_CONTROLS,
	DMI_ENTRY_VOLTAGE_PROBE,
	DMI_ENTRY_COOLING_DEV,
	DMI_ENTRY_TEMP_PROBE,
	DMI_ENTRY_ELECTRICAL_CURRENT_PROBE,
	DMI_ENTRY_OOB_REMOTE_ACCESS,
	DMI_ENTRY_BIS_ENTRY,
	DMI_ENTRY_SYSTEM_BOOT,
	DMI_ENTRY_MGMT_DEV,
	DMI_ENTRY_MGMT_DEV_COMPONENT,
	DMI_ENTRY_MGMT_DEV_THRES,
	DMI_ENTRY_MEM_CHANNEL,
	DMI_ENTRY_IPMI_DEV,
	DMI_ENTRY_SYS_POWER_SUPPLY,
	DMI_ENTRY_ADDITIONAL,
	DMI_ENTRY_ONBOARD_DEV_EXT,
	DMI_ENTRY_MGMT_CONTROLLER_HOST,
	DMI_ENTRY_INACTIVE = 126,
	DMI_ENTRY_END_OF_TABLE = 127,
पूर्ण;

काष्ठा dmi_header अणु
	u8 type;
	u8 length;
	u16 handle;
पूर्ण __packed;

काष्ठा dmi_device अणु
	काष्ठा list_head list;
	पूर्णांक type;
	स्थिर अक्षर *name;
	व्योम *device_data;	/* Type specअगरic data */
पूर्ण;

#अगर_घोषित CONFIG_DMI

काष्ठा dmi_dev_onboard अणु
	काष्ठा dmi_device dev;
	पूर्णांक instance;
	पूर्णांक segment;
	पूर्णांक bus;
	पूर्णांक devfn;
पूर्ण;

बाह्य काष्ठा kobject *dmi_kobj;
बाह्य पूर्णांक dmi_check_प्रणाली(स्थिर काष्ठा dmi_प्रणाली_id *list);
स्थिर काष्ठा dmi_प्रणाली_id *dmi_first_match(स्थिर काष्ठा dmi_प्रणाली_id *list);
बाह्य स्थिर अक्षर * dmi_get_प्रणाली_info(पूर्णांक field);
बाह्य स्थिर काष्ठा dmi_device * dmi_find_device(पूर्णांक type, स्थिर अक्षर *name,
	स्थिर काष्ठा dmi_device *from);
बाह्य व्योम dmi_setup(व्योम);
बाह्य bool dmi_get_date(पूर्णांक field, पूर्णांक *yearp, पूर्णांक *monthp, पूर्णांक *dayp);
बाह्य पूर्णांक dmi_get_bios_year(व्योम);
बाह्य पूर्णांक dmi_name_in_venकरोrs(स्थिर अक्षर *str);
बाह्य पूर्णांक dmi_name_in_serial(स्थिर अक्षर *str);
बाह्य पूर्णांक dmi_available;
बाह्य पूर्णांक dmi_walk(व्योम (*decode)(स्थिर काष्ठा dmi_header *, व्योम *),
	व्योम *निजी_data);
बाह्य bool dmi_match(क्रमागत dmi_field f, स्थिर अक्षर *str);
बाह्य व्योम dmi_memdev_name(u16 handle, स्थिर अक्षर **bank, स्थिर अक्षर **device);
बाह्य u64 dmi_memdev_size(u16 handle);
बाह्य u8 dmi_memdev_type(u16 handle);
बाह्य u16 dmi_memdev_handle(पूर्णांक slot);

#अन्यथा

अटल अंतरभूत पूर्णांक dmi_check_प्रणाली(स्थिर काष्ठा dmi_प्रणाली_id *list) अणु वापस 0; पूर्ण
अटल अंतरभूत स्थिर अक्षर * dmi_get_प्रणाली_info(पूर्णांक field) अणु वापस शून्य; पूर्ण
अटल अंतरभूत स्थिर काष्ठा dmi_device * dmi_find_device(पूर्णांक type, स्थिर अक्षर *name,
	स्थिर काष्ठा dmi_device *from) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम dmi_setup(व्योम) अणु पूर्ण
अटल अंतरभूत bool dmi_get_date(पूर्णांक field, पूर्णांक *yearp, पूर्णांक *monthp, पूर्णांक *dayp)
अणु
	अगर (yearp)
		*yearp = 0;
	अगर (monthp)
		*monthp = 0;
	अगर (dayp)
		*dayp = 0;
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक dmi_get_bios_year(व्योम) अणु वापस -ENXIO; पूर्ण
अटल अंतरभूत पूर्णांक dmi_name_in_venकरोrs(स्थिर अक्षर *s) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dmi_name_in_serial(स्थिर अक्षर *s) अणु वापस 0; पूर्ण
#घोषणा dmi_available 0
अटल अंतरभूत पूर्णांक dmi_walk(व्योम (*decode)(स्थिर काष्ठा dmi_header *, व्योम *),
	व्योम *निजी_data) अणु वापस -ENXIO; पूर्ण
अटल अंतरभूत bool dmi_match(क्रमागत dmi_field f, स्थिर अक्षर *str)
	अणु वापस false; पूर्ण
अटल अंतरभूत व्योम dmi_memdev_name(u16 handle, स्थिर अक्षर **bank,
		स्थिर अक्षर **device) अणु पूर्ण
अटल अंतरभूत u64 dmi_memdev_size(u16 handle) अणु वापस ~0ul; पूर्ण
अटल अंतरभूत u8 dmi_memdev_type(u16 handle) अणु वापस 0x0; पूर्ण
अटल अंतरभूत u16 dmi_memdev_handle(पूर्णांक slot) अणु वापस 0xffff; पूर्ण
अटल अंतरभूत स्थिर काष्ठा dmi_प्रणाली_id *
	dmi_first_match(स्थिर काष्ठा dmi_प्रणाली_id *list) अणु वापस शून्य; पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर	/* __DMI_H__ */
