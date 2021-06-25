<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#अगर_अघोषित _RMI_DRIVER_H
#घोषणा _RMI_DRIVER_H

#समावेश <linux/प्रकार.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/input.h>
#समावेश "rmi_bus.h"

#घोषणा SYNAPTICS_INPUT_DEVICE_NAME "Synaptics RMI4 Touch Sensor"
#घोषणा SYNAPTICS_VENDOR_ID 0x06cb

#घोषणा GROUP(_attrs) अणु \
	.attrs = _attrs,  \
पूर्ण

#घोषणा PDT_PROPERTIES_LOCATION 0x00EF
#घोषणा BSR_LOCATION 0x00FE

#घोषणा RMI_PDT_PROPS_HAS_BSR 0x02

#घोषणा NAME_BUFFER_SIZE 256

#घोषणा RMI_PDT_ENTRY_SIZE 6
#घोषणा RMI_PDT_FUNCTION_VERSION_MASK   0x60
#घोषणा RMI_PDT_INT_SOURCE_COUNT_MASK   0x07

#घोषणा PDT_START_SCAN_LOCATION 0x00e9
#घोषणा PDT_END_SCAN_LOCATION	0x0005
#घोषणा RMI4_END_OF_PDT(id) ((id) == 0x00 || (id) == 0xff)

काष्ठा pdt_entry अणु
	u16 page_start;
	u8 query_base_addr;
	u8 command_base_addr;
	u8 control_base_addr;
	u8 data_base_addr;
	u8 पूर्णांकerrupt_source_count;
	u8 function_version;
	u8 function_number;
पूर्ण;

#घोषणा RMI_REG_DESC_PRESENSE_BITS	(32 * BITS_PER_BYTE)
#घोषणा RMI_REG_DESC_SUBPACKET_BITS	(37 * BITS_PER_BYTE)

/* describes a single packet रेजिस्टर */
काष्ठा rmi_रेजिस्टर_desc_item अणु
	u16 reg;
	अचिन्हित दीर्घ reg_size;
	u8 num_subpackets;
	अचिन्हित दीर्घ subpacket_map[BITS_TO_LONGS(
				RMI_REG_DESC_SUBPACKET_BITS)];
पूर्ण;

/*
 * describes the packet रेजिस्टरs क्रम a particular type
 * (ie query, control, data)
 */
काष्ठा rmi_रेजिस्टर_descriptor अणु
	अचिन्हित दीर्घ काष्ठा_size;
	अचिन्हित दीर्घ presense_map[BITS_TO_LONGS(RMI_REG_DESC_PRESENSE_BITS)];
	u8 num_रेजिस्टरs;
	काष्ठा rmi_रेजिस्टर_desc_item *रेजिस्टरs;
पूर्ण;

पूर्णांक rmi_पढ़ो_रेजिस्टर_desc(काष्ठा rmi_device *d, u16 addr,
				काष्ठा rmi_रेजिस्टर_descriptor *rdesc);
स्थिर काष्ठा rmi_रेजिस्टर_desc_item *rmi_get_रेजिस्टर_desc_item(
				काष्ठा rmi_रेजिस्टर_descriptor *rdesc, u16 reg);

/*
 * Calculate the total size of all of the रेजिस्टरs described in the
 * descriptor.
 */
माप_प्रकार rmi_रेजिस्टर_desc_calc_size(काष्ठा rmi_रेजिस्टर_descriptor *rdesc);
पूर्णांक rmi_रेजिस्टर_desc_calc_reg_offset(
			काष्ठा rmi_रेजिस्टर_descriptor *rdesc, u16 reg);
bool rmi_रेजिस्टर_desc_has_subpacket(स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item,
			u8 subpacket);

bool rmi_is_physical_driver(काष्ठा device_driver *);
पूर्णांक rmi_रेजिस्टर_physical_driver(व्योम);
व्योम rmi_unरेजिस्टर_physical_driver(व्योम);
व्योम rmi_मुक्त_function_list(काष्ठा rmi_device *rmi_dev);
काष्ठा rmi_function *rmi_find_function(काष्ठा rmi_device *rmi_dev, u8 number);
पूर्णांक rmi_enable_sensor(काष्ठा rmi_device *rmi_dev);
पूर्णांक rmi_scan_pdt(काष्ठा rmi_device *rmi_dev, व्योम *ctx,
		 पूर्णांक (*callback)(काष्ठा rmi_device *rmi_dev, व्योम *ctx,
		 स्थिर काष्ठा pdt_entry *entry));
पूर्णांक rmi_probe_पूर्णांकerrupts(काष्ठा rmi_driver_data *data);
व्योम rmi_enable_irq(काष्ठा rmi_device *rmi_dev, bool clear_wake);
व्योम rmi_disable_irq(काष्ठा rmi_device *rmi_dev, bool enable_wake);
पूर्णांक rmi_init_functions(काष्ठा rmi_driver_data *data);
पूर्णांक rmi_initial_reset(काष्ठा rmi_device *rmi_dev, व्योम *ctx,
		      स्थिर काष्ठा pdt_entry *pdt);

स्थिर अक्षर *rmi_f01_get_product_ID(काष्ठा rmi_function *fn);

#अगर_घोषित CONFIG_RMI4_F03
पूर्णांक rmi_f03_overग_लिखो_button(काष्ठा rmi_function *fn, अचिन्हित पूर्णांक button,
			     पूर्णांक value);
व्योम rmi_f03_commit_buttons(काष्ठा rmi_function *fn);
#अन्यथा
अटल अंतरभूत पूर्णांक rmi_f03_overग_लिखो_button(काष्ठा rmi_function *fn,
					   अचिन्हित पूर्णांक button, पूर्णांक value)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम rmi_f03_commit_buttons(काष्ठा rmi_function *fn) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_RMI4_F34
पूर्णांक rmi_f34_create_sysfs(काष्ठा rmi_device *rmi_dev);
व्योम rmi_f34_हटाओ_sysfs(काष्ठा rmi_device *rmi_dev);
#अन्यथा
अटल अंतरभूत पूर्णांक rmi_f34_create_sysfs(काष्ठा rmi_device *rmi_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rmi_f34_हटाओ_sysfs(काष्ठा rmi_device *rmi_dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RMI_F34 */

बाह्य काष्ठा rmi_function_handler rmi_f01_handler;
बाह्य काष्ठा rmi_function_handler rmi_f03_handler;
बाह्य काष्ठा rmi_function_handler rmi_f11_handler;
बाह्य काष्ठा rmi_function_handler rmi_f12_handler;
बाह्य काष्ठा rmi_function_handler rmi_f30_handler;
बाह्य काष्ठा rmi_function_handler rmi_f34_handler;
बाह्य काष्ठा rmi_function_handler rmi_f3a_handler;
बाह्य काष्ठा rmi_function_handler rmi_f54_handler;
बाह्य काष्ठा rmi_function_handler rmi_f55_handler;
#पूर्ण_अगर
