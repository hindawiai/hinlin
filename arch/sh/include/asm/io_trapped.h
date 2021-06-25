<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_IO_TRAPPED_H
#घोषणा __ASM_SH_IO_TRAPPED_H

#समावेश <linux/list.h>
#समावेश <linux/ioport.h>
#समावेश <यंत्र/page.h>

#घोषणा IO_TRAPPED_MAGIC 0xfeedbeef

काष्ठा trapped_io अणु
	अचिन्हित पूर्णांक magic;
	काष्ठा resource *resource;
	अचिन्हित पूर्णांक num_resources;
	अचिन्हित पूर्णांक minimum_bus_width;
	काष्ठा list_head list;
	व्योम __iomem *virt_base;
पूर्ण __aligned(PAGE_SIZE);

#अगर_घोषित CONFIG_IO_TRAPPED
पूर्णांक रेजिस्टर_trapped_io(काष्ठा trapped_io *tiop);
पूर्णांक handle_trapped_io(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address);

व्योम __iomem *match_trapped_io_handler(काष्ठा list_head *list,
				       अचिन्हित दीर्घ offset,
				       अचिन्हित दीर्घ size);

#अगर_घोषित CONFIG_HAS_IOMEM
बाह्य काष्ठा list_head trapped_mem;

अटल अंतरभूत व्योम __iomem *
__ioremap_trapped(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	वापस match_trapped_io_handler(&trapped_mem, offset, size);
पूर्ण
#अन्यथा
#घोषणा __ioremap_trapped(offset, size) शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAS_IOPORT_MAP
बाह्य काष्ठा list_head trapped_io;

अटल अंतरभूत व्योम __iomem *
__ioport_map_trapped(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	वापस match_trapped_io_handler(&trapped_io, offset, size);
पूर्ण
#अन्यथा
#घोषणा __ioport_map_trapped(offset, size) शून्य
#पूर्ण_अगर

#अन्यथा
#घोषणा रेजिस्टर_trapped_io(tiop) (-1)
#घोषणा handle_trapped_io(tiop, address) 0
#घोषणा __ioremap_trapped(offset, size) शून्य
#घोषणा __ioport_map_trapped(offset, size) शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_IO_TRAPPED_H */
