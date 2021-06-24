<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Platक्रमm Monitory Technology Telemetry driver
 *
 * Copyright (c) 2020, Intel Corporation.
 * All Rights Reserved.
 *
 * Author: "David E. Box" <david.e.box@linux.पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/overflow.h>

#समावेश "intel_pmt_class.h"

#घोषणा TELEM_DEV_NAME		"pmt_telemetry"

#घोषणा TELEM_SIZE_OFFSET	0x0
#घोषणा TELEM_GUID_OFFSET	0x4
#घोषणा TELEM_BASE_OFFSET	0x8
#घोषणा TELEM_ACCESS(v)		((v) & GENMASK(3, 0))
/* size is in bytes */
#घोषणा TELEM_SIZE(v)		(((v) & GENMASK(27, 12)) >> 10)

/* Used by client hardware to identअगरy a fixed telemetry entry*/
#घोषणा TELEM_CLIENT_FIXED_BLOCK_GUID	0x10000000

काष्ठा pmt_telem_priv अणु
	पूर्णांक				num_entries;
	काष्ठा पूर्णांकel_pmt_entry		entry[];
पूर्ण;

अटल bool pmt_telem_region_overlaps(काष्ठा पूर्णांकel_pmt_entry *entry,
				      काष्ठा device *dev)
अणु
	u32 guid = पढ़ोl(entry->disc_table + TELEM_GUID_OFFSET);

	अगर (guid != TELEM_CLIENT_FIXED_BLOCK_GUID)
		वापस false;

	वापस पूर्णांकel_pmt_is_early_client_hw(dev);
पूर्ण

अटल पूर्णांक pmt_telem_header_decode(काष्ठा पूर्णांकel_pmt_entry *entry,
				   काष्ठा पूर्णांकel_pmt_header *header,
				   काष्ठा device *dev)
अणु
	व्योम __iomem *disc_table = entry->disc_table;

	अगर (pmt_telem_region_overlaps(entry, dev))
		वापस 1;

	header->access_type = TELEM_ACCESS(पढ़ोl(disc_table));
	header->guid = पढ़ोl(disc_table + TELEM_GUID_OFFSET);
	header->base_offset = पढ़ोl(disc_table + TELEM_BASE_OFFSET);

	/* Size is measured in DWORDS, but accessor वापसs bytes */
	header->size = TELEM_SIZE(पढ़ोl(disc_table));

	वापस 0;
पूर्ण

अटल DEFINE_XARRAY_ALLOC(telem_array);
अटल काष्ठा पूर्णांकel_pmt_namespace pmt_telem_ns = अणु
	.name = "telem",
	.xa = &telem_array,
	.pmt_header_decode = pmt_telem_header_decode,
पूर्ण;

अटल पूर्णांक pmt_telem_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmt_telem_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_entries; i++)
		पूर्णांकel_pmt_dev_destroy(&priv->entry[i], &pmt_telem_ns);

	वापस 0;
पूर्ण

अटल पूर्णांक pmt_telem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmt_telem_priv *priv;
	माप_प्रकार size;
	पूर्णांक i, ret;

	size = काष्ठा_size(priv, entry, pdev->num_resources);
	priv = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	क्रम (i = 0; i < pdev->num_resources; i++) अणु
		काष्ठा पूर्णांकel_pmt_entry *entry = &priv->entry[i];

		ret = पूर्णांकel_pmt_dev_create(entry, &pmt_telem_ns, pdev, i);
		अगर (ret < 0)
			जाओ पात_probe;
		अगर (ret)
			जारी;

		priv->num_entries++;
	पूर्ण

	वापस 0;
पात_probe:
	pmt_telem_हटाओ(pdev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver pmt_telem_driver = अणु
	.driver = अणु
		.name   = TELEM_DEV_NAME,
	पूर्ण,
	.हटाओ = pmt_telem_हटाओ,
	.probe  = pmt_telem_probe,
पूर्ण;

अटल पूर्णांक __init pmt_telem_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pmt_telem_driver);
पूर्ण
module_init(pmt_telem_init);

अटल व्योम __निकास pmt_telem_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pmt_telem_driver);
	xa_destroy(&telem_array);
पूर्ण
module_निकास(pmt_telem_निकास);

MODULE_AUTHOR("David E. Box <david.e.box@linux.intel.com>");
MODULE_DESCRIPTION("Intel PMT Telemetry driver");
MODULE_ALIAS("platform:" TELEM_DEV_NAME);
MODULE_LICENSE("GPL v2");
