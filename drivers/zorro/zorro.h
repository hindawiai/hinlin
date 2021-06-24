<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

    /*
     *  Zorro bus
     */

बाह्य काष्ठा bus_type zorro_bus_type;


#अगर_घोषित CONFIG_ZORRO_NAMES
बाह्य व्योम zorro_name_device(काष्ठा zorro_dev *z);
#अन्यथा
अटल अंतरभूत व्योम zorro_name_device(काष्ठा zorro_dev *dev) अणु पूर्ण
#पूर्ण_अगर

बाह्य स्थिर काष्ठा attribute_group *zorro_device_attribute_groups[];
