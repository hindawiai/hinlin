<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#घोषणा pr_fmt(fmt) "of_pmem: " fmt

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>

काष्ठा of_pmem_निजी अणु
	काष्ठा nvdimm_bus_descriptor bus_desc;
	काष्ठा nvdimm_bus *bus;
पूर्ण;

अटल पूर्णांक of_pmem_region_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा of_pmem_निजी *priv;
	काष्ठा device_node *np;
	काष्ठा nvdimm_bus *bus;
	bool is_अस्थिर;
	पूर्णांक i;

	np = dev_of_node(&pdev->dev);
	अगर (!np)
		वापस -ENXIO;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->bus_desc.provider_name = kstrdup(pdev->name, GFP_KERNEL);
	priv->bus_desc.module = THIS_MODULE;
	priv->bus_desc.of_node = np;

	priv->bus = bus = nvdimm_bus_रेजिस्टर(&pdev->dev, &priv->bus_desc);
	अगर (!bus) अणु
		kमुक्त(priv);
		वापस -ENODEV;
	पूर्ण
	platक्रमm_set_drvdata(pdev, priv);

	is_अस्थिर = !!of_find_property(np, "volatile", शून्य);
	dev_dbg(&pdev->dev, "Registering %s regions from %pOF\n",
			is_अस्थिर ? "volatile" : "non-volatile",  np);

	क्रम (i = 0; i < pdev->num_resources; i++) अणु
		काष्ठा nd_region_desc ndr_desc;
		काष्ठा nd_region *region;

		/*
		 * NB: libnvdimm copies the data from ndr_desc पूर्णांकo it's own
		 * काष्ठाures so passing a stack poपूर्णांकer is fine.
		 */
		स_रखो(&ndr_desc, 0, माप(ndr_desc));
		ndr_desc.numa_node = dev_to_node(&pdev->dev);
		ndr_desc.target_node = ndr_desc.numa_node;
		ndr_desc.res = &pdev->resource[i];
		ndr_desc.of_node = np;
		set_bit(ND_REGION_PAGEMAP, &ndr_desc.flags);

		अगर (is_अस्थिर)
			region = nvdimm_अस्थिर_region_create(bus, &ndr_desc);
		अन्यथा अणु
			set_bit(ND_REGION_PERSIST_MEMCTRL, &ndr_desc.flags);
			region = nvdimm_pmem_region_create(bus, &ndr_desc);
		पूर्ण

		अगर (!region)
			dev_warn(&pdev->dev, "Unable to register region %pR from %pOF\n",
					ndr_desc.res, np);
		अन्यथा
			dev_dbg(&pdev->dev, "Registered region %pR from %pOF\n",
					ndr_desc.res, np);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक of_pmem_region_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा of_pmem_निजी *priv = platक्रमm_get_drvdata(pdev);

	nvdimm_bus_unरेजिस्टर(priv->bus);
	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pmem_region_match[] = अणु
	अणु .compatible = "pmem-region" पूर्ण,
	अणु .compatible = "pmem-region-v2" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver of_pmem_region_driver = अणु
	.probe = of_pmem_region_probe,
	.हटाओ = of_pmem_region_हटाओ,
	.driver = अणु
		.name = "of_pmem",
		.of_match_table = of_pmem_region_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(of_pmem_region_driver);
MODULE_DEVICE_TABLE(of, of_pmem_region_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("IBM Corporation");
