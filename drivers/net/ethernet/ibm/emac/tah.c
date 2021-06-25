<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/ibm/emac/tah.c
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, TAH support.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright 2004 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 *
 * Copyright (c) 2005 Eugene Surovegin <ebs@ebshome.net>
 */
#समावेश <linux/of_address.h>
#समावेश <यंत्र/पन.स>

#समावेश "emac.h"
#समावेश "core.h"

पूर्णांक tah_attach(काष्ठा platक्रमm_device *ofdev, पूर्णांक channel)
अणु
	काष्ठा tah_instance *dev = platक्रमm_get_drvdata(ofdev);

	mutex_lock(&dev->lock);
	/* Reset has been करोne at probe() समय... nothing अन्यथा to करो क्रम now */
	++dev->users;
	mutex_unlock(&dev->lock);

	वापस 0;
पूर्ण

व्योम tah_detach(काष्ठा platक्रमm_device *ofdev, पूर्णांक channel)
अणु
	काष्ठा tah_instance *dev = platक्रमm_get_drvdata(ofdev);

	mutex_lock(&dev->lock);
	--dev->users;
	mutex_unlock(&dev->lock);
पूर्ण

व्योम tah_reset(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा tah_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा tah_regs __iomem *p = dev->base;
	पूर्णांक n;

	/* Reset TAH */
	out_be32(&p->mr, TAH_MR_SR);
	n = 100;
	जबतक ((in_be32(&p->mr) & TAH_MR_SR) && n)
		--n;

	अगर (unlikely(!n))
		prपूर्णांकk(KERN_ERR "%pOF: reset timeout\n", ofdev->dev.of_node);

	/* 10KB TAH TX FIFO accommodates the max MTU of 9000 */
	out_be32(&p->mr,
		 TAH_MR_CVR | TAH_MR_ST_768 | TAH_MR_TFS_10KB | TAH_MR_DTFP |
		 TAH_MR_DIG);
पूर्ण

पूर्णांक tah_get_regs_len(काष्ठा platक्रमm_device *ofdev)
अणु
	वापस माप(काष्ठा emac_ethtool_regs_subhdr) +
		माप(काष्ठा tah_regs);
पूर्ण

व्योम *tah_dump_regs(काष्ठा platक्रमm_device *ofdev, व्योम *buf)
अणु
	काष्ठा tah_instance *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा emac_ethtool_regs_subhdr *hdr = buf;
	काष्ठा tah_regs *regs = (काष्ठा tah_regs *)(hdr + 1);

	hdr->version = 0;
	hdr->index = 0; /* क्रम now, are there chips with more than one
			 * zmii ? अगर yes, then we'll add a cell_index
			 * like we करो क्रम emac
			 */
	स_नकल_fromio(regs, dev->base, माप(काष्ठा tah_regs));
	वापस regs + 1;
पूर्ण

अटल पूर्णांक tah_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा tah_instance *dev;
	काष्ठा resource regs;
	पूर्णांक rc;

	rc = -ENOMEM;
	dev = kzalloc(माप(काष्ठा tah_instance), GFP_KERNEL);
	अगर (dev == शून्य)
		जाओ err_gone;

	mutex_init(&dev->lock);
	dev->ofdev = ofdev;

	rc = -ENXIO;
	अगर (of_address_to_resource(np, 0, &regs)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get registers address\n", np);
		जाओ err_मुक्त;
	पूर्ण

	rc = -ENOMEM;
	dev->base = (काष्ठा tah_regs __iomem *)ioremap(regs.start,
					       माप(काष्ठा tah_regs));
	अगर (dev->base == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map device registers!\n", np);
		जाओ err_मुक्त;
	पूर्ण

	platक्रमm_set_drvdata(ofdev, dev);

	/* Initialize TAH and enable IPv4 checksum verअगरication, no TSO yet */
	tah_reset(ofdev);

	prपूर्णांकk(KERN_INFO "TAH %pOF initialized\n", ofdev->dev.of_node);
	wmb();

	वापस 0;

 err_मुक्त:
	kमुक्त(dev);
 err_gone:
	वापस rc;
पूर्ण

अटल पूर्णांक tah_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा tah_instance *dev = platक्रमm_get_drvdata(ofdev);

	WARN_ON(dev->users != 0);

	iounmap(dev->base);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tah_match[] =
अणु
	अणु
		.compatible	= "ibm,tah",
	पूर्ण,
	/* For backward compat with old DT */
	अणु
		.type		= "tah",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tah_driver = अणु
	.driver = अणु
		.name = "emac-tah",
		.of_match_table = tah_match,
	पूर्ण,
	.probe = tah_probe,
	.हटाओ = tah_हटाओ,
पूर्ण;

पूर्णांक __init tah_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tah_driver);
पूर्ण

व्योम tah_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tah_driver);
पूर्ण
