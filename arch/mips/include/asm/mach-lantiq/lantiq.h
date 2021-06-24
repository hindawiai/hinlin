<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */
#अगर_अघोषित _LANTIQ_H__
#घोषणा _LANTIQ_H__

#समावेश <linux/irq.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>

/* generic reg access functions */
#घोषणा ltq_r32(reg)		__raw_पढ़ोl(reg)
#घोषणा ltq_w32(val, reg)	__raw_ग_लिखोl(val, reg)
#घोषणा ltq_w32_mask(clear, set, reg)	\
	ltq_w32((ltq_r32(reg) & ~(clear)) | (set), reg)
#घोषणा ltq_r8(reg)		__raw_पढ़ोb(reg)
#घोषणा ltq_w8(val, reg)	__raw_ग_लिखोb(val, reg)

/* रेजिस्टर access macros क्रम EBU and CGU */
#घोषणा ltq_ebu_w32(x, y)	ltq_w32((x), ltq_ebu_membase + (y))
#घोषणा ltq_ebu_r32(x)		ltq_r32(ltq_ebu_membase + (x))
#घोषणा ltq_ebu_w32_mask(x, y, z) \
	ltq_w32_mask(x, y, ltq_ebu_membase + (z))
बाह्य __iomem व्योम *ltq_ebu_membase;

/* spinlock all ebu i/o */
बाह्य spinlock_t ebu_lock;

/* some irq helpers */
बाह्य व्योम ltq_disable_irq(काष्ठा irq_data *data);
बाह्य व्योम ltq_mask_and_ack_irq(काष्ठा irq_data *data);
बाह्य व्योम ltq_enable_irq(काष्ठा irq_data *data);
बाह्य पूर्णांक ltq_eiu_get_irq(पूर्णांक exin);

/* घड़ी handling */
बाह्य पूर्णांक clk_activate(काष्ठा clk *clk);
बाह्य व्योम clk_deactivate(काष्ठा clk *clk);
बाह्य काष्ठा clk *clk_get_cpu(व्योम);
बाह्य काष्ठा clk *clk_get_fpi(व्योम);
बाह्य काष्ठा clk *clk_get_io(व्योम);
बाह्य काष्ठा clk *clk_get_ppe(व्योम);

/* find out what bootsource we have */
बाह्य अचिन्हित अक्षर ltq_boot_select(व्योम);
/* find out the soc type */
बाह्य पूर्णांक ltq_soc_type(व्योम);

#घोषणा IOPORT_RESOURCE_START	0x10000000
#घोषणा IOPORT_RESOURCE_END	0xffffffff
#घोषणा IOMEM_RESOURCE_START	0x10000000
#घोषणा IOMEM_RESOURCE_END	0xffffffff

#पूर्ण_अगर
