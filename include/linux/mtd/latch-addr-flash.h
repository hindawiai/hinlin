<शैली गुरु>
/*
 * Interface क्रम NOR flash driver whose high address lines are latched
 *
 * Copyright तऊ 2008 MontaVista Software, Inc. <source@mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */
#अगर_अघोषित __LATCH_ADDR_FLASH__
#घोषणा __LATCH_ADDR_FLASH__

काष्ठा map_info;
काष्ठा mtd_partition;

काष्ठा latch_addr_flash_data अणु
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		size;

	पूर्णांक			(*init)(व्योम *data, पूर्णांक cs);
	व्योम			(*करोne)(व्योम *data);
	व्योम			(*set_winकरोw)(अचिन्हित दीर्घ offset, व्योम *data);
	व्योम			*data;

	अचिन्हित पूर्णांक		nr_parts;
	काष्ठा mtd_partition	*parts;
पूर्ण;

#पूर्ण_अगर
