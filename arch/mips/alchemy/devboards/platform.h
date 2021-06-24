<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DEVBOARD_PLATFORM_H_
#घोषणा _DEVBOARD_PLATFORM_H_

#समावेश <linux/init.h>

पूर्णांक __init db1x_रेजिस्टर_pcmcia_socket(phys_addr_t pcmcia_attr_start,
				       phys_addr_t pcmcia_attr_len,
				       phys_addr_t pcmcia_mem_start,
				       phys_addr_t pcmcia_mem_end,
				       phys_addr_t pcmcia_io_start,
				       phys_addr_t pcmcia_io_end,
				       पूर्णांक card_irq,
				       पूर्णांक cd_irq,
				       पूर्णांक stschg_irq,
				       पूर्णांक eject_irq,
				       पूर्णांक id);

पूर्णांक __init db1x_रेजिस्टर_norflash(अचिन्हित दीर्घ size, पूर्णांक width,
				  पूर्णांक swapped);

#पूर्ण_अगर
