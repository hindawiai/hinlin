<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip30-xtalk.c - Very basic Crosstalk (XIO) detection support.
 *   Copyright (C) 2004-2007 Stanislaw Skowronek <skylark@unaligned.org>
 *   Copyright (C) 2009 Johannes Dickgreber <tanzy@gmx.de>
 *   Copyright (C) 2007, 2014-2016 Joshua Kinard <kumba@gentoo.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/sgi-w1.h>
#समावेश <linux/platक्रमm_data/xtalk-bridge.h>

#समावेश <यंत्र/xtalk/xwidget.h>
#समावेश <यंत्र/pci/bridge.h>

#घोषणा IP30_SWIN_BASE(widget) \
		(0x0000000010000000 | (((अचिन्हित दीर्घ)(widget)) << 24))

#घोषणा IP30_RAW_SWIN_BASE(widget)	(IO_BASE + IP30_SWIN_BASE(widget))

#घोषणा IP30_SWIN_SIZE		(1 << 24)

#घोषणा IP30_WIDGET_XBOW        _AC(0x0, UL)    /* XBow is always 0 */
#घोषणा IP30_WIDGET_HEART       _AC(0x8, UL)    /* HEART is always 8 */
#घोषणा IP30_WIDGET_PCI_BASE    _AC(0xf, UL)    /* BaseIO PCI is always 15 */

#घोषणा XTALK_NODEV             0xffffffff

#घोषणा XBOW_REG_LINK_STAT_0    0x114
#घोषणा XBOW_REG_LINK_BLK_SIZE  0x40
#घोषणा XBOW_REG_LINK_ALIVE     0x80000000

#घोषणा HEART_INTR_ADDR		0x00000080

#घोषणा xtalk_पढ़ो	__raw_पढ़ोl

अटल व्योम bridge_platक्रमm_create(पूर्णांक widget, पूर्णांक masterwid)
अणु
	काष्ठा xtalk_bridge_platक्रमm_data *bd;
	काष्ठा sgi_w1_platक्रमm_data *wd;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource w1_res;

	wd = kzalloc(माप(*wd), GFP_KERNEL);
	अगर (!wd)
		जाओ no_mem;

	snम_लिखो(wd->dev_id, माप(wd->dev_id), "bridge-%012lx",
		 IP30_SWIN_BASE(widget));

	स_रखो(&w1_res, 0, माप(w1_res));
	w1_res.start = IP30_SWIN_BASE(widget) +
				दुरत्व(काष्ठा bridge_regs, b_nic);
	w1_res.end = w1_res.start + 3;
	w1_res.flags = IORESOURCE_MEM;

	pdev = platक्रमm_device_alloc("sgi_w1", PLATFORM_DEVID_AUTO);
	अगर (!pdev) अणु
		kमुक्त(wd);
		जाओ no_mem;
	पूर्ण
	platक्रमm_device_add_resources(pdev, &w1_res, 1);
	platक्रमm_device_add_data(pdev, wd, माप(*wd));
	platक्रमm_device_add(pdev);

	bd = kzalloc(माप(*bd), GFP_KERNEL);
	अगर (!bd)
		जाओ no_mem;
	pdev = platक्रमm_device_alloc("xtalk-bridge", PLATFORM_DEVID_AUTO);
	अगर (!pdev) अणु
		kमुक्त(bd);
		जाओ no_mem;
	पूर्ण

	bd->bridge_addr	= IP30_RAW_SWIN_BASE(widget);
	bd->पूर्णांकr_addr	= HEART_INTR_ADDR;
	bd->nasid	= 0;
	bd->masterwid	= masterwid;

	bd->mem.name	= "Bridge PCI MEM";
	bd->mem.start	= IP30_SWIN_BASE(widget) + BRIDGE_DEVIO0;
	bd->mem.end	= IP30_SWIN_BASE(widget) + IP30_SWIN_SIZE - 1;
	bd->mem.flags	= IORESOURCE_MEM;
	bd->mem_offset	= IP30_SWIN_BASE(widget);

	bd->io.name	= "Bridge PCI IO";
	bd->io.start	= IP30_SWIN_BASE(widget) + BRIDGE_DEVIO0;
	bd->io.end	= IP30_SWIN_BASE(widget) + IP30_SWIN_SIZE - 1;
	bd->io.flags	= IORESOURCE_IO;
	bd->io_offset	= IP30_SWIN_BASE(widget);

	platक्रमm_device_add_data(pdev, bd, माप(*bd));
	platक्रमm_device_add(pdev);
	pr_info("xtalk:%x bridge widget\n", widget);
	वापस;

no_mem:
	pr_warn("xtalk:%x bridge create out of memory\n", widget);
पूर्ण

अटल अचिन्हित पूर्णांक __init xbow_widget_active(s8 wid)
अणु
	अचिन्हित पूर्णांक link_stat;

	link_stat = xtalk_पढ़ो((व्योम *)(IP30_RAW_SWIN_BASE(IP30_WIDGET_XBOW) +
					XBOW_REG_LINK_STAT_0 +
					XBOW_REG_LINK_BLK_SIZE *
					(wid - 8)));

	वापस (link_stat & XBOW_REG_LINK_ALIVE) ? 1 : 0;
पूर्ण

अटल व्योम __init xtalk_init_widget(s8 wid, s8 masterwid)
अणु
	xwidget_part_num_t partnum;
	widgetreg_t widget_id;

	अगर (!xbow_widget_active(wid))
		वापस;

	widget_id = xtalk_पढ़ो((व्योम *)(IP30_RAW_SWIN_BASE(wid) + WIDGET_ID));

	partnum = XWIDGET_PART_NUM(widget_id);

	चयन (partnum) अणु
	हाल BRIDGE_WIDGET_PART_NUM:
	हाल XBRIDGE_WIDGET_PART_NUM:
		bridge_platक्रमm_create(wid, masterwid);
		अवरोध;
	शेष:
		pr_info("xtalk:%x unknown widget (0x%x)\n", wid, partnum);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init ip30_xtalk_init(व्योम)
अणु
	पूर्णांक i;

	/*
	 * Walk widget IDs backwards so that BaseIO is probed first.  This
	 * ensures that the BaseIO IOC3 is always detected as eth0.
	 */
	क्रम (i = IP30_WIDGET_PCI_BASE; i > IP30_WIDGET_HEART; i--)
		xtalk_init_widget(i, IP30_WIDGET_HEART);

	वापस 0;
पूर्ण

arch_initcall(ip30_xtalk_init);
