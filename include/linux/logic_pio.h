<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 HiSilicon Limited, All Rights Reserved.
 * Author: Gabriele Paoloni <gabriele.paoloni@huawei.com>
 * Author: Zhichang Yuan <yuanzhichang@hisilicon.com>
 */

#अगर_अघोषित __LINUX_LOGIC_PIO_H
#घोषणा __LINUX_LOGIC_PIO_H

#समावेश <linux/fwnode.h>

क्रमागत अणु
	LOGIC_PIO_INसूचीECT,		/* Indirect IO flag */
	LOGIC_PIO_CPU_MMIO,		/* Memory-mapped IO flag */
पूर्ण;

काष्ठा logic_pio_hwaddr अणु
	काष्ठा list_head list;
	काष्ठा fwnode_handle *fwnode;
	resource_माप_प्रकार hw_start;
	resource_माप_प्रकार io_start;
	resource_माप_प्रकार size; /* range size populated */
	अचिन्हित दीर्घ flags;

	व्योम *hostdata;
	स्थिर काष्ठा logic_pio_host_ops *ops;
पूर्ण;

काष्ठा logic_pio_host_ops अणु
	u32 (*in)(व्योम *hostdata, अचिन्हित दीर्घ addr, माप_प्रकार dwidth);
	व्योम (*out)(व्योम *hostdata, अचिन्हित दीर्घ addr, u32 val,
		    माप_प्रकार dwidth);
	u32 (*ins)(व्योम *hostdata, अचिन्हित दीर्घ addr, व्योम *buffer,
		   माप_प्रकार dwidth, अचिन्हित पूर्णांक count);
	व्योम (*outs)(व्योम *hostdata, अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,
		     माप_प्रकार dwidth, अचिन्हित पूर्णांक count);
पूर्ण;

#अगर_घोषित CONFIG_INसूचीECT_PIO
u8 logic_inb(अचिन्हित दीर्घ addr);
व्योम logic_outb(u8 value, अचिन्हित दीर्घ addr);
व्योम logic_outw(u16 value, अचिन्हित दीर्घ addr);
व्योम logic_outl(u32 value, अचिन्हित दीर्घ addr);
u16 logic_inw(अचिन्हित दीर्घ addr);
u32 logic_inl(अचिन्हित दीर्घ addr);
व्योम logic_outb(u8 value, अचिन्हित दीर्घ addr);
व्योम logic_outw(u16 value, अचिन्हित दीर्घ addr);
व्योम logic_outl(u32 value, अचिन्हित दीर्घ addr);
व्योम logic_insb(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count);
व्योम logic_insl(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count);
व्योम logic_insw(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count);
व्योम logic_outsb(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer, अचिन्हित पूर्णांक count);
व्योम logic_outsw(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer, अचिन्हित पूर्णांक count);
व्योम logic_outsl(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer, अचिन्हित पूर्णांक count);

#अगर_अघोषित inb
#घोषणा inb logic_inb
#पूर्ण_अगर

#अगर_अघोषित inw
#घोषणा inw logic_inw
#पूर्ण_अगर

#अगर_अघोषित inl
#घोषणा inl logic_inl
#पूर्ण_अगर

#अगर_अघोषित outb
#घोषणा outb logic_outb
#पूर्ण_अगर

#अगर_अघोषित outw
#घोषणा outw logic_outw
#पूर्ण_अगर

#अगर_अघोषित outl
#घोषणा outl logic_outl
#पूर्ण_अगर

#अगर_अघोषित insb
#घोषणा insb logic_insb
#पूर्ण_अगर

#अगर_अघोषित insw
#घोषणा insw logic_insw
#पूर्ण_अगर

#अगर_अघोषित insl
#घोषणा insl logic_insl
#पूर्ण_अगर

#अगर_अघोषित outsb
#घोषणा outsb logic_outsb
#पूर्ण_अगर

#अगर_अघोषित outsw
#घोषणा outsw logic_outsw
#पूर्ण_अगर

#अगर_अघोषित outsl
#घोषणा outsl logic_outsl
#पूर्ण_अगर

/*
 * We reserve 0x4000 bytes क्रम Indirect IO as so far this library is only
 * used by the HiSilicon LPC Host. If needed, we can reserve a wider IO
 * area by redefining the macro below.
 */
#घोषणा PIO_INसूचीECT_SIZE 0x4000
#अन्यथा
#घोषणा PIO_INसूचीECT_SIZE 0
#पूर्ण_अगर /* CONFIG_INसूचीECT_PIO */
#घोषणा MMIO_UPPER_LIMIT (IO_SPACE_LIMIT - PIO_INसूचीECT_SIZE)

काष्ठा logic_pio_hwaddr *find_io_range_by_fwnode(काष्ठा fwnode_handle *fwnode);
अचिन्हित दीर्घ logic_pio_trans_hwaddr(काष्ठा fwnode_handle *fwnode,
			resource_माप_प्रकार hw_addr, resource_माप_प्रकार size);
पूर्णांक logic_pio_रेजिस्टर_range(काष्ठा logic_pio_hwaddr *newrange);
व्योम logic_pio_unरेजिस्टर_range(काष्ठा logic_pio_hwaddr *range);
resource_माप_प्रकार logic_pio_to_hwaddr(अचिन्हित दीर्घ pio);
अचिन्हित दीर्घ logic_pio_trans_cpuaddr(resource_माप_प्रकार hw_addr);

#पूर्ण_अगर /* __LINUX_LOGIC_PIO_H */
