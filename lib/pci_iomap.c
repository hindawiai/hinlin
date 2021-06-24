<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement the शेष iomap पूर्णांकerfaces
 *
 * (C) Copyright 2004 Linus Torvalds
 */
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>

#समावेश <linux/export.h>

#अगर_घोषित CONFIG_PCI
/**
 * pci_iomap_range - create a भव mapping cookie क्रम a PCI BAR
 * @dev: PCI device that owns the BAR
 * @bar: BAR number
 * @offset: map memory at the given offset in BAR
 * @maxlen: max length of the memory to map
 *
 * Using this function you will get a __iomem address to your device BAR.
 * You can access it using ioपढ़ो*() and ioग_लिखो*(). These functions hide
 * the details अगर this is a MMIO or PIO address space and will just करो what
 * you expect from them in the correct way.
 *
 * @maxlen specअगरies the maximum length to map. If you want to get access to
 * the complete BAR from offset to the end, pass %0 here.
 * */
व्योम __iomem *pci_iomap_range(काष्ठा pci_dev *dev,
			      पूर्णांक bar,
			      अचिन्हित दीर्घ offset,
			      अचिन्हित दीर्घ maxlen)
अणु
	resource_माप_प्रकार start = pci_resource_start(dev, bar);
	resource_माप_प्रकार len = pci_resource_len(dev, bar);
	अचिन्हित दीर्घ flags = pci_resource_flags(dev, bar);

	अगर (len <= offset || !start)
		वापस शून्य;
	len -= offset;
	start += offset;
	अगर (maxlen && len > maxlen)
		len = maxlen;
	अगर (flags & IORESOURCE_IO)
		वापस __pci_ioport_map(dev, start, len);
	अगर (flags & IORESOURCE_MEM)
		वापस ioremap(start, len);
	/* What? */
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_iomap_range);

/**
 * pci_iomap_wc_range - create a भव WC mapping cookie क्रम a PCI BAR
 * @dev: PCI device that owns the BAR
 * @bar: BAR number
 * @offset: map memory at the given offset in BAR
 * @maxlen: max length of the memory to map
 *
 * Using this function you will get a __iomem address to your device BAR.
 * You can access it using ioपढ़ो*() and ioग_लिखो*(). These functions hide
 * the details अगर this is a MMIO or PIO address space and will just करो what
 * you expect from them in the correct way. When possible ग_लिखो combining
 * is used.
 *
 * @maxlen specअगरies the maximum length to map. If you want to get access to
 * the complete BAR from offset to the end, pass %0 here.
 * */
व्योम __iomem *pci_iomap_wc_range(काष्ठा pci_dev *dev,
				 पूर्णांक bar,
				 अचिन्हित दीर्घ offset,
				 अचिन्हित दीर्घ maxlen)
अणु
	resource_माप_प्रकार start = pci_resource_start(dev, bar);
	resource_माप_प्रकार len = pci_resource_len(dev, bar);
	अचिन्हित दीर्घ flags = pci_resource_flags(dev, bar);


	अगर (flags & IORESOURCE_IO)
		वापस शून्य;

	अगर (len <= offset || !start)
		वापस शून्य;

	len -= offset;
	start += offset;
	अगर (maxlen && len > maxlen)
		len = maxlen;

	अगर (flags & IORESOURCE_MEM)
		वापस ioremap_wc(start, len);

	/* What? */
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pci_iomap_wc_range);

/**
 * pci_iomap - create a भव mapping cookie क्रम a PCI BAR
 * @dev: PCI device that owns the BAR
 * @bar: BAR number
 * @maxlen: length of the memory to map
 *
 * Using this function you will get a __iomem address to your device BAR.
 * You can access it using ioपढ़ो*() and ioग_लिखो*(). These functions hide
 * the details अगर this is a MMIO or PIO address space and will just करो what
 * you expect from them in the correct way.
 *
 * @maxlen specअगरies the maximum length to map. If you want to get access to
 * the complete BAR without checking क्रम its length first, pass %0 here.
 * */
व्योम __iomem *pci_iomap(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ maxlen)
अणु
	वापस pci_iomap_range(dev, bar, 0, maxlen);
पूर्ण
EXPORT_SYMBOL(pci_iomap);

/**
 * pci_iomap_wc - create a भव WC mapping cookie क्रम a PCI BAR
 * @dev: PCI device that owns the BAR
 * @bar: BAR number
 * @maxlen: length of the memory to map
 *
 * Using this function you will get a __iomem address to your device BAR.
 * You can access it using ioपढ़ो*() and ioग_लिखो*(). These functions hide
 * the details अगर this is a MMIO or PIO address space and will just करो what
 * you expect from them in the correct way. When possible ग_लिखो combining
 * is used.
 *
 * @maxlen specअगरies the maximum length to map. If you want to get access to
 * the complete BAR without checking क्रम its length first, pass %0 here.
 * */
व्योम __iomem *pci_iomap_wc(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ maxlen)
अणु
	वापस pci_iomap_wc_range(dev, bar, 0, maxlen);
पूर्ण
EXPORT_SYMBOL_GPL(pci_iomap_wc);
#पूर्ण_अगर /* CONFIG_PCI */
