<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2sbus driver
 *
 * Copyright 2006-2008 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <sound/core.h>

#समावेश <यंत्र/macपन.स>
#समावेश <यंत्र/dbdma.h>

#समावेश "../soundbus.h"
#समावेश "i2sbus.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_DESCRIPTION("Apple Soundbus: I2S support");

अटल पूर्णांक क्रमce;
module_param(क्रमce, पूर्णांक, 0444);
MODULE_PARM_DESC(क्रमce, "Force loading i2sbus even when"
			" no layout-id property is present");

अटल स्थिर काष्ठा of_device_id i2sbus_match[] = अणु
	अणु .name = "i2s" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, i2sbus_match);

अटल पूर्णांक alloc_dbdma_descriptor_ring(काष्ठा i2sbus_dev *i2sdev,
				       काष्ठा dbdma_command_mem *r,
				       पूर्णांक numcmds)
अणु
	/* one more क्रम rounding, one क्रम branch back, one क्रम stop command */
	r->size = (numcmds + 3) * माप(काष्ठा dbdma_cmd);
	/* We use the PCI APIs क्रम now until the generic one माला_लो fixed
	 * enough or until we get some macio-specअगरic versions
	 */
	r->space = dma_alloc_coherent(&macio_get_pci_dev(i2sdev->macio)->dev,
				      r->size, &r->bus_addr, GFP_KERNEL);
	अगर (!r->space)
		वापस -ENOMEM;

	r->cmds = (व्योम*)DBDMA_ALIGN(r->space);
	r->bus_cmd_start = r->bus_addr +
			   (dma_addr_t)((अक्षर*)r->cmds - (अक्षर*)r->space);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_dbdma_descriptor_ring(काष्ठा i2sbus_dev *i2sdev,
				       काष्ठा dbdma_command_mem *r)
अणु
	अगर (!r->space) वापस;

	dma_मुक्त_coherent(&macio_get_pci_dev(i2sdev->macio)->dev,
			    r->size, r->space, r->bus_addr);
पूर्ण

अटल व्योम i2sbus_release_dev(काष्ठा device *dev)
अणु
	काष्ठा i2sbus_dev *i2sdev;
	पूर्णांक i;

	i2sdev = container_of(dev, काष्ठा i2sbus_dev, sound.ofdev.dev);
	iounmap(i2sdev->पूर्णांकfregs);
	iounmap(i2sdev->out.dbdma);
	iounmap(i2sdev->in.dbdma);
	क्रम (i = aoa_resource_i2smmio; i <= aoa_resource_rxdbdma; i++)
		release_and_मुक्त_resource(i2sdev->allocated_resource[i]);
	मुक्त_dbdma_descriptor_ring(i2sdev, &i2sdev->out.dbdma_ring);
	मुक्त_dbdma_descriptor_ring(i2sdev, &i2sdev->in.dbdma_ring);
	क्रम (i = aoa_resource_i2smmio; i <= aoa_resource_rxdbdma; i++)
		मुक्त_irq(i2sdev->पूर्णांकerrupts[i], i2sdev);
	i2sbus_control_हटाओ_dev(i2sdev->control, i2sdev);
	mutex_destroy(&i2sdev->lock);
	kमुक्त(i2sdev);
पूर्ण

अटल irqवापस_t i2sbus_bus_पूर्णांकr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा i2sbus_dev *dev = devid;
	u32 पूर्णांकreg;

	spin_lock(&dev->low_lock);
	पूर्णांकreg = in_le32(&dev->पूर्णांकfregs->पूर्णांकr_ctl);

	/* acknowledge पूर्णांकerrupt reasons */
	out_le32(&dev->पूर्णांकfregs->पूर्णांकr_ctl, पूर्णांकreg);

	spin_unlock(&dev->low_lock);

	वापस IRQ_HANDLED;
पूर्ण


/*
 * XXX FIXME: We test the layout_id's here to get the proper way of
 * mapping in various रेजिस्टरs, thanks to bugs in Apple device-trees.
 * We could instead key off the machine model and the name of the i2s
 * node (i2s-a). This we'll करो when we move it all to macio_asic.c
 * and have that export items क्रम each sub-node too.
 */
अटल पूर्णांक i2sbus_get_and_fixup_rsrc(काष्ठा device_node *np, पूर्णांक index,
				     पूर्णांक layout, काष्ठा resource *res)
अणु
	काष्ठा device_node *parent;
	पूर्णांक pindex, rc = -ENXIO;
	स्थिर u32 *reg;

	/* Machines with layout 76 and 36 (K2 based) have a weird device
	 * tree what we need to special हाल.
	 * Normal machines just fetch the resource from the i2s-X node.
	 * Darwin further भागides normal machines पूर्णांकo old and new layouts
	 * with a subtely dअगरferent code path but that करोesn't seem necessary
	 * in practice, they just bloated it. In addition, even on our K2
	 * हाल the i2s-modem node, अगर we ever want to handle it, uses the
	 * normal layout
	 */
	अगर (layout != 76 && layout != 36)
		वापस of_address_to_resource(np, index, res);

	parent = of_get_parent(np);
	pindex = (index == aoa_resource_i2smmio) ? 0 : 1;
	rc = of_address_to_resource(parent, pindex, res);
	अगर (rc)
		जाओ bail;
	reg = of_get_property(np, "reg", शून्य);
	अगर (reg == शून्य) अणु
		rc = -ENXIO;
		जाओ bail;
	पूर्ण
	res->start += reg[index * 2];
	res->end = res->start + reg[index * 2 + 1] - 1;
 bail:
	of_node_put(parent);
	वापस rc;
पूर्ण

/* FIXME: look at device node refcounting */
अटल पूर्णांक i2sbus_add_dev(काष्ठा macio_dev *macio,
			  काष्ठा i2sbus_control *control,
			  काष्ठा device_node *np)
अणु
	काष्ठा i2sbus_dev *dev;
	काष्ठा device_node *child, *sound = शून्य;
	काष्ठा resource *r;
	पूर्णांक i, layout = 0, rlen, ok = क्रमce;
	अक्षर node_name[6];
	अटल स्थिर अक्षर *rnames[] = अणु "i2sbus: %pOFn (control)",
					"i2sbus: %pOFn (tx)",
					"i2sbus: %pOFn (rx)" पूर्ण;
	अटल स्थिर irq_handler_t पूर्णांकs[] = अणु
		i2sbus_bus_पूर्णांकr,
		i2sbus_tx_पूर्णांकr,
		i2sbus_rx_पूर्णांकr
	पूर्ण;

	अगर (snम_लिखो(node_name, माप(node_name), "%pOFn", np) != 5)
		वापस 0;
	अगर (म_भेदन(node_name, "i2s-", 4))
		वापस 0;

	dev = kzalloc(माप(काष्ठा i2sbus_dev), GFP_KERNEL);
	अगर (!dev)
		वापस 0;

	i = 0;
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_node_name_eq(child, "sound")) अणु
			i++;
			sound = child;
		पूर्ण
	पूर्ण
	अगर (i == 1) अणु
		स्थिर u32 *id = of_get_property(sound, "layout-id", शून्य);

		अगर (id) अणु
			layout = *id;
			snम_लिखो(dev->sound.modalias, 32,
				 "sound-layout-%d", layout);
			ok = 1;
		पूर्ण अन्यथा अणु
			id = of_get_property(sound, "device-id", शून्य);
			/*
			 * We probably cannot handle all device-id machines,
			 * so restrict to those we करो handle क्रम now.
			 */
			अगर (id && (*id == 22 || *id == 14 || *id == 35 ||
				   *id == 31 || *id == 44)) अणु
				snम_लिखो(dev->sound.modalias, 32,
					 "aoa-device-id-%d", *id);
				ok = 1;
				layout = -1;
			पूर्ण
		पूर्ण
	पूर्ण
	/* क्रम the समय being, until we can handle non-layout-id
	 * things in some fabric, refuse to attach अगर there is no
	 * layout-id property or we haven't been क्रमced to attach.
	 * When there are two i2s busses and only one has a layout-id,
	 * then this depends on the order, but that isn't important
	 * either as the second one in that हाल is just a modem. */
	अगर (!ok) अणु
		kमुक्त(dev);
		वापस -ENODEV;
	पूर्ण

	mutex_init(&dev->lock);
	spin_lock_init(&dev->low_lock);
	dev->sound.ofdev.archdata.dma_mask = macio->ofdev.archdata.dma_mask;
	dev->sound.ofdev.dev.of_node = np;
	dev->sound.ofdev.dev.dma_mask = &dev->sound.ofdev.archdata.dma_mask;
	dev->sound.ofdev.dev.parent = &macio->ofdev.dev;
	dev->sound.ofdev.dev.release = i2sbus_release_dev;
	dev->sound.attach_codec = i2sbus_attach_codec;
	dev->sound.detach_codec = i2sbus_detach_codec;
	dev->sound.pcmid = -1;
	dev->macio = macio;
	dev->control = control;
	dev->bus_number = node_name[4] - 'a';
	INIT_LIST_HEAD(&dev->sound.codec_list);

	क्रम (i = aoa_resource_i2smmio; i <= aoa_resource_rxdbdma; i++) अणु
		dev->पूर्णांकerrupts[i] = -1;
		snम_लिखो(dev->rnames[i], माप(dev->rnames[i]),
			 rnames[i], np);
	पूर्ण
	क्रम (i = aoa_resource_i2smmio; i <= aoa_resource_rxdbdma; i++) अणु
		पूर्णांक irq = irq_of_parse_and_map(np, i);
		अगर (request_irq(irq, पूर्णांकs[i], 0, dev->rnames[i], dev))
			जाओ err;
		dev->पूर्णांकerrupts[i] = irq;
	पूर्ण


	/* Resource handling is problematic as some device-trees contain
	 * useless crap (ugh ugh ugh). We work around that here by calling
	 * specअगरic functions क्रम calculating the appropriate resources.
	 *
	 * This will all be moved to macio_asic.c at one poपूर्णांक
	 */
	क्रम (i = aoa_resource_i2smmio; i <= aoa_resource_rxdbdma; i++) अणु
		अगर (i2sbus_get_and_fixup_rsrc(np,i,layout,&dev->resources[i]))
			जाओ err;
		/* If only we could use our resource dev->resources[i]...
		 * but request_resource करोesn't know about parents and
		 * contained resources...
		 */
		dev->allocated_resource[i] =
			request_mem_region(dev->resources[i].start,
					   resource_size(&dev->resources[i]),
					   dev->rnames[i]);
		अगर (!dev->allocated_resource[i]) अणु
			prपूर्णांकk(KERN_ERR "i2sbus: failed to claim resource %d!\n", i);
			जाओ err;
		पूर्ण
	पूर्ण

	r = &dev->resources[aoa_resource_i2smmio];
	rlen = resource_size(r);
	अगर (rlen < माप(काष्ठा i2s_पूर्णांकerface_regs))
		जाओ err;
	dev->पूर्णांकfregs = ioremap(r->start, rlen);

	r = &dev->resources[aoa_resource_txdbdma];
	rlen = resource_size(r);
	अगर (rlen < माप(काष्ठा dbdma_regs))
		जाओ err;
	dev->out.dbdma = ioremap(r->start, rlen);

	r = &dev->resources[aoa_resource_rxdbdma];
	rlen = resource_size(r);
	अगर (rlen < माप(काष्ठा dbdma_regs))
		जाओ err;
	dev->in.dbdma = ioremap(r->start, rlen);

	अगर (!dev->पूर्णांकfregs || !dev->out.dbdma || !dev->in.dbdma)
		जाओ err;

	अगर (alloc_dbdma_descriptor_ring(dev, &dev->out.dbdma_ring,
					MAX_DBDMA_COMMANDS))
		जाओ err;
	अगर (alloc_dbdma_descriptor_ring(dev, &dev->in.dbdma_ring,
					MAX_DBDMA_COMMANDS))
		जाओ err;

	अगर (i2sbus_control_add_dev(dev->control, dev)) अणु
		prपूर्णांकk(KERN_ERR "i2sbus: control layer didn't like bus\n");
		जाओ err;
	पूर्ण

	अगर (soundbus_add_one(&dev->sound)) अणु
		prपूर्णांकk(KERN_DEBUG "i2sbus: device registration error!\n");
		जाओ err;
	पूर्ण

	/* enable this cell */
	i2sbus_control_cell(dev->control, dev, 1);
	i2sbus_control_enable(dev->control, dev);
	i2sbus_control_घड़ी(dev->control, dev, 1);

	वापस 1;
 err:
	क्रम (i=0;i<3;i++)
		अगर (dev->पूर्णांकerrupts[i] != -1)
			मुक्त_irq(dev->पूर्णांकerrupts[i], dev);
	मुक्त_dbdma_descriptor_ring(dev, &dev->out.dbdma_ring);
	मुक्त_dbdma_descriptor_ring(dev, &dev->in.dbdma_ring);
	iounmap(dev->पूर्णांकfregs);
	iounmap(dev->out.dbdma);
	iounmap(dev->in.dbdma);
	क्रम (i=0;i<3;i++)
		release_and_मुक्त_resource(dev->allocated_resource[i]);
	mutex_destroy(&dev->lock);
	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक i2sbus_probe(काष्ठा macio_dev* dev, स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा device_node *np = शून्य;
	पूर्णांक got = 0, err;
	काष्ठा i2sbus_control *control = शून्य;

	err = i2sbus_control_init(dev, &control);
	अगर (err)
		वापस err;
	अगर (!control) अणु
		prपूर्णांकk(KERN_ERR "i2sbus_control_init API breakage\n");
		वापस -ENODEV;
	पूर्ण

	जबतक ((np = of_get_next_child(dev->ofdev.dev.of_node, np))) अणु
		अगर (of_device_is_compatible(np, "i2sbus") ||
		    of_device_is_compatible(np, "i2s-modem")) अणु
			got += i2sbus_add_dev(dev, control, np);
		पूर्ण
	पूर्ण

	अगर (!got) अणु
		/* found none, clean up */
		i2sbus_control_destroy(control);
		वापस -ENODEV;
	पूर्ण

	dev_set_drvdata(&dev->ofdev.dev, control);

	वापस 0;
पूर्ण

अटल पूर्णांक i2sbus_हटाओ(काष्ठा macio_dev* dev)
अणु
	काष्ठा i2sbus_control *control = dev_get_drvdata(&dev->ofdev.dev);
	काष्ठा i2sbus_dev *i2sdev, *पंचांगp;

	list_क्रम_each_entry_safe(i2sdev, पंचांगp, &control->list, item)
		soundbus_हटाओ_one(&i2sdev->sound);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2sbus_suspend(काष्ठा macio_dev* dev, pm_message_t state)
अणु
	काष्ठा i2sbus_control *control = dev_get_drvdata(&dev->ofdev.dev);
	काष्ठा codec_info_item *cii;
	काष्ठा i2sbus_dev* i2sdev;
	पूर्णांक err, ret = 0;

	list_क्रम_each_entry(i2sdev, &control->list, item) अणु
		/* Notअगरy codecs */
		list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list) अणु
			err = 0;
			अगर (cii->codec->suspend)
				err = cii->codec->suspend(cii, state);
			अगर (err)
				ret = err;
		पूर्ण

		/* रुको until streams are stopped */
		i2sbus_रुको_क्रम_stop_both(i2sdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक i2sbus_resume(काष्ठा macio_dev* dev)
अणु
	काष्ठा i2sbus_control *control = dev_get_drvdata(&dev->ofdev.dev);
	काष्ठा codec_info_item *cii;
	काष्ठा i2sbus_dev* i2sdev;
	पूर्णांक err, ret = 0;

	list_क्रम_each_entry(i2sdev, &control->list, item) अणु
		/* reset i2s bus क्रमmat etc. */
		i2sbus_pcm_prepare_both(i2sdev);

		/* Notअगरy codecs so they can re-initialize */
		list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list) अणु
			err = 0;
			अगर (cii->codec->resume)
				err = cii->codec->resume(cii);
			अगर (err)
				ret = err;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक i2sbus_shutकरोwn(काष्ठा macio_dev* dev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा macio_driver i2sbus_drv = अणु
	.driver = अणु
		.name = "soundbus-i2s",
		.owner = THIS_MODULE,
		.of_match_table = i2sbus_match,
	पूर्ण,
	.probe = i2sbus_probe,
	.हटाओ = i2sbus_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = i2sbus_suspend,
	.resume = i2sbus_resume,
#पूर्ण_अगर
	.shutकरोwn = i2sbus_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init soundbus_i2sbus_init(व्योम)
अणु
	वापस macio_रेजिस्टर_driver(&i2sbus_drv);
पूर्ण

अटल व्योम __निकास soundbus_i2sbus_निकास(व्योम)
अणु
	macio_unरेजिस्टर_driver(&i2sbus_drv);
पूर्ण

module_init(soundbus_i2sbus_init);
module_निकास(soundbus_i2sbus_निकास);
