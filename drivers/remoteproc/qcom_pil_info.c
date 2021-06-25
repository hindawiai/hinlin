<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020 Linaro Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_address.h>
#समावेश "qcom_pil_info.h"

/*
 * The PIL relocation inक्रमmation region is used to communicate memory regions
 * occupied by co-processor firmware क्रम post mortem crash analysis.
 *
 * It consists of an array of entries with an 8 byte textual identअगरier of the
 * region followed by a 64 bit base address and 32 bit size, both little
 * endian.
 */
#घोषणा PIL_RELOC_NAME_LEN	8
#घोषणा PIL_RELOC_ENTRY_SIZE	(PIL_RELOC_NAME_LEN + माप(__le64) + माप(__le32))

काष्ठा pil_reloc अणु
	व्योम __iomem *base;
	माप_प्रकार num_entries;
पूर्ण;

अटल काष्ठा pil_reloc _reloc __पढ़ो_mostly;
अटल DEFINE_MUTEX(pil_reloc_lock);

अटल पूर्णांक qcom_pil_info_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource imem;
	व्योम __iomem *base;
	पूर्णांक ret;

	/* Alपढ़ोy initialized? */
	अगर (_reloc.base)
		वापस 0;

	np = of_find_compatible_node(शून्य, शून्य, "qcom,pil-reloc-info");
	अगर (!np)
		वापस -ENOENT;

	ret = of_address_to_resource(np, 0, &imem);
	of_node_put(np);
	अगर (ret < 0)
		वापस ret;

	base = ioremap(imem.start, resource_size(&imem));
	अगर (!base) अणु
		pr_err("failed to map PIL relocation info region\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो_io(base, 0, resource_size(&imem));

	_reloc.base = base;
	_reloc.num_entries = (u32)resource_size(&imem) / PIL_RELOC_ENTRY_SIZE;

	वापस 0;
पूर्ण

/**
 * qcom_pil_info_store() - store PIL inक्रमmation of image in IMEM
 * @image:	name of the image
 * @base:	base address of the loaded image
 * @size:	size of the loaded image
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
पूर्णांक qcom_pil_info_store(स्थिर अक्षर *image, phys_addr_t base, माप_प्रकार size)
अणु
	अक्षर buf[PIL_RELOC_NAME_LEN];
	व्योम __iomem *entry;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&pil_reloc_lock);
	ret = qcom_pil_info_init();
	अगर (ret < 0) अणु
		mutex_unlock(&pil_reloc_lock);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < _reloc.num_entries; i++) अणु
		entry = _reloc.base + i * PIL_RELOC_ENTRY_SIZE;

		स_नकल_fromio(buf, entry, PIL_RELOC_NAME_LEN);

		/*
		 * An empty record means we didn't find it, given that the
		 * records are packed.
		 */
		अगर (!buf[0])
			जाओ found_unused;

		अगर (!म_भेदन(buf, image, PIL_RELOC_NAME_LEN))
			जाओ found_existing;
	पूर्ण

	pr_warn("insufficient PIL info slots\n");
	mutex_unlock(&pil_reloc_lock);
	वापस -ENOMEM;

found_unused:
	स_नकल_toio(entry, image, PIL_RELOC_NAME_LEN);
found_existing:
	/* Use two ग_लिखोl() as base is only aligned to 4 bytes on odd entries */
	ग_लिखोl(base, entry + PIL_RELOC_NAME_LEN);
	ग_लिखोl((u64)base >> 32, entry + PIL_RELOC_NAME_LEN + 4);
	ग_लिखोl(size, entry + PIL_RELOC_NAME_LEN + माप(__le64));
	mutex_unlock(&pil_reloc_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_pil_info_store);

अटल व्योम __निकास pil_reloc_निकास(व्योम)
अणु
	mutex_lock(&pil_reloc_lock);
	iounmap(_reloc.base);
	_reloc.base = शून्य;
	mutex_unlock(&pil_reloc_lock);
पूर्ण
module_निकास(pil_reloc_निकास);

MODULE_DESCRIPTION("Qualcomm PIL relocation info");
MODULE_LICENSE("GPL v2");
