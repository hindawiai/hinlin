<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999, 2000 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 1999, 2000 Silcon Graphics, Inc.
 * Copyright (C) 2004 Christoph Hellwig.
 *
 * Generic XTALK initialization code
 */

#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/sgi-w1.h>
#समावेश <linux/platक्रमm_data/xtalk-bridge.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/types.h>
#समावेश <यंत्र/sn/klconfig.h>
#समावेश <यंत्र/pci/bridge.h>
#समावेश <यंत्र/xtalk/xtalk.h>


#घोषणा XBOW_WIDGET_PART_NUM	0x0
#घोषणा XXBOW_WIDGET_PART_NUM	0xd000	/* Xbow in Xbridge */
#घोषणा BASE_XBOW_PORT		8     /* Lowest बाह्यal port */

अटल व्योम bridge_platक्रमm_create(nasid_t nasid, पूर्णांक widget, पूर्णांक masterwid)
अणु
	काष्ठा xtalk_bridge_platक्रमm_data *bd;
	काष्ठा sgi_w1_platक्रमm_data *wd;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource w1_res;
	अचिन्हित दीर्घ offset;

	offset = NODE_OFFSET(nasid);

	wd = kzalloc(माप(*wd), GFP_KERNEL);
	अगर (!wd)
		जाओ no_mem;

	snम_लिखो(wd->dev_id, माप(wd->dev_id), "bridge-%012lx",
		 offset + (widget << SWIN_SIZE_BITS));

	स_रखो(&w1_res, 0, माप(w1_res));
	w1_res.start = offset + (widget << SWIN_SIZE_BITS) +
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


	bd->bridge_addr = RAW_NODE_SWIN_BASE(nasid, widget);
	bd->पूर्णांकr_addr	= BIT_ULL(47) + 0x01800000 + PI_INT_PEND_MOD;
	bd->nasid	= nasid;
	bd->masterwid	= masterwid;

	bd->mem.name	= "Bridge PCI MEM";
	bd->mem.start	= offset + (widget << SWIN_SIZE_BITS) + BRIDGE_DEVIO0;
	bd->mem.end	= offset + (widget << SWIN_SIZE_BITS) + SWIN_SIZE - 1;
	bd->mem.flags	= IORESOURCE_MEM;
	bd->mem_offset	= offset;

	bd->io.name	= "Bridge PCI IO";
	bd->io.start	= offset + (widget << SWIN_SIZE_BITS) + BRIDGE_DEVIO0;
	bd->io.end	= offset + (widget << SWIN_SIZE_BITS) + SWIN_SIZE - 1;
	bd->io.flags	= IORESOURCE_IO;
	bd->io_offset	= offset;

	platक्रमm_device_add_data(pdev, bd, माप(*bd));
	platक्रमm_device_add(pdev);
	pr_info("xtalk:n%d/%x bridge widget\n", nasid, widget);
	वापस;

no_mem:
	pr_warn("xtalk:n%d/%x bridge create out of memory\n", nasid, widget);
पूर्ण

अटल पूर्णांक probe_one_port(nasid_t nasid, पूर्णांक widget, पूर्णांक masterwid)
अणु
	widgetreg_t		widget_id;
	xwidget_part_num_t	partnum;

	widget_id = *(अस्थिर widgetreg_t *)
		(RAW_NODE_SWIN_BASE(nasid, widget) + WIDGET_ID);
	partnum = XWIDGET_PART_NUM(widget_id);

	चयन (partnum) अणु
	हाल BRIDGE_WIDGET_PART_NUM:
	हाल XBRIDGE_WIDGET_PART_NUM:
		bridge_platक्रमm_create(nasid, widget, masterwid);
		अवरोध;
	शेष:
		pr_info("xtalk:n%d/%d unknown widget (0x%x)\n",
			nasid, widget, partnum);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xbow_probe(nasid_t nasid)
अणु
	lboard_t *brd;
	klxbow_t *xbow_p;
	अचिन्हित masterwid, i;

	/*
	 * found xbow, so may have multiple bridges
	 * need to probe xbow
	 */
	brd = find_lboard((lboard_t *)KL_CONFIG_INFO(nasid), KLTYPE_MIDPLANE8);
	अगर (!brd)
		वापस -ENODEV;

	xbow_p = (klxbow_t *)find_component(brd, शून्य, KLSTRUCT_XBOW);
	अगर (!xbow_p)
		वापस -ENODEV;

	/*
	 * Okay, here's a xbow. Let's arbitrate and find
	 * out अगर we should initialize it. Set enabled
	 * hub connected at highest or lowest widget as
	 * master.
	 */
#अगर_घोषित WIDGET_A
	i = HUB_WIDGET_ID_MAX + 1;
	करो अणु
		i--;
	पूर्ण जबतक ((!XBOW_PORT_TYPE_HUB(xbow_p, i)) ||
		 (!XBOW_PORT_IS_ENABLED(xbow_p, i)));
#अन्यथा
	i = HUB_WIDGET_ID_MIN - 1;
	करो अणु
		i++;
	पूर्ण जबतक ((!XBOW_PORT_TYPE_HUB(xbow_p, i)) ||
		 (!XBOW_PORT_IS_ENABLED(xbow_p, i)));
#पूर्ण_अगर

	masterwid = i;
	अगर (nasid != XBOW_PORT_NASID(xbow_p, i))
		वापस 1;

	क्रम (i = HUB_WIDGET_ID_MIN; i <= HUB_WIDGET_ID_MAX; i++) अणु
		अगर (XBOW_PORT_IS_ENABLED(xbow_p, i) &&
		    XBOW_PORT_TYPE_IO(xbow_p, i))
			probe_one_port(nasid, i, masterwid);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xtalk_probe_node(nasid_t nasid)
अणु
	अस्थिर u64		hubreg;
	xwidget_part_num_t	partnum;
	widgetreg_t		widget_id;

	hubreg = REMOTE_HUB_L(nasid, IIO_LLP_CSR);

	/* check whether the link is up */
	अगर (!(hubreg & IIO_LLP_CSR_IS_UP))
		वापस;

	widget_id = *(अस्थिर widgetreg_t *)
		       (RAW_NODE_SWIN_BASE(nasid, 0x0) + WIDGET_ID);
	partnum = XWIDGET_PART_NUM(widget_id);

	चयन (partnum) अणु
	हाल BRIDGE_WIDGET_PART_NUM:
		bridge_platक्रमm_create(nasid, 0x8, 0xa);
		अवरोध;
	हाल XBOW_WIDGET_PART_NUM:
	हाल XXBOW_WIDGET_PART_NUM:
		pr_info("xtalk:n%d/0 xbow widget\n", nasid);
		xbow_probe(nasid);
		अवरोध;
	शेष:
		pr_info("xtalk:n%d/0 unknown widget (0x%x)\n", nasid, partnum);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init xtalk_init(व्योम)
अणु
	nasid_t nasid;

	क्रम_each_online_node(nasid)
		xtalk_probe_node(nasid);

	वापस 0;
पूर्ण
arch_initcall(xtalk_init);
