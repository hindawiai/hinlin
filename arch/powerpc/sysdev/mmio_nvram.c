<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * memory mapped NVRAM
 *
 * (C) Copyright IBM Corp. 2005
 *
 * Authors : Utz Bacher <utz.bacher@de.ibm.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/prom.h>

अटल व्योम __iomem *mmio_nvram_start;
अटल दीर्घ mmio_nvram_len;
अटल DEFINE_SPINLOCK(mmio_nvram_lock);

अटल sमाप_प्रकार mmio_nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	अचिन्हित दीर्घ flags;

	अगर (*index >= mmio_nvram_len)
		वापस 0;
	अगर (*index + count > mmio_nvram_len)
		count = mmio_nvram_len - *index;

	spin_lock_irqsave(&mmio_nvram_lock, flags);

	स_नकल_fromio(buf, mmio_nvram_start + *index, count);

	spin_unlock_irqrestore(&mmio_nvram_lock, flags);
	
	*index += count;
	वापस count;
पूर्ण

अटल अचिन्हित अक्षर mmio_nvram_पढ़ो_val(पूर्णांक addr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;

	अगर (addr >= mmio_nvram_len)
		वापस 0xff;

	spin_lock_irqsave(&mmio_nvram_lock, flags);

	val = ioपढ़ो8(mmio_nvram_start + addr);

	spin_unlock_irqrestore(&mmio_nvram_lock, flags);

	वापस val;
पूर्ण

अटल sमाप_प्रकार mmio_nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	अचिन्हित दीर्घ flags;

	अगर (*index >= mmio_nvram_len)
		वापस 0;
	अगर (*index + count > mmio_nvram_len)
		count = mmio_nvram_len - *index;

	spin_lock_irqsave(&mmio_nvram_lock, flags);

	स_नकल_toio(mmio_nvram_start + *index, buf, count);

	spin_unlock_irqrestore(&mmio_nvram_lock, flags);
	
	*index += count;
	वापस count;
पूर्ण

अटल व्योम mmio_nvram_ग_लिखो_val(पूर्णांक addr, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;

	अगर (addr < mmio_nvram_len) अणु
		spin_lock_irqsave(&mmio_nvram_lock, flags);

		ioग_लिखो8(val, mmio_nvram_start + addr);

		spin_unlock_irqrestore(&mmio_nvram_lock, flags);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mmio_nvram_get_size(व्योम)
अणु
	वापस mmio_nvram_len;
पूर्ण

पूर्णांक __init mmio_nvram_init(व्योम)
अणु
	काष्ठा device_node *nvram_node;
	अचिन्हित दीर्घ nvram_addr;
	काष्ठा resource r;
	पूर्णांक ret;

	nvram_node = of_find_node_by_type(शून्य, "nvram");
	अगर (!nvram_node)
		nvram_node = of_find_compatible_node(शून्य, शून्य, "nvram");
	अगर (!nvram_node) अणु
		prपूर्णांकk(KERN_WARNING "nvram: no node found in device-tree\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_address_to_resource(nvram_node, 0, &r);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "nvram: failed to get address (err %d)\n",
		       ret);
		जाओ out;
	पूर्ण
	nvram_addr = r.start;
	mmio_nvram_len = resource_size(&r);
	अगर ( (!mmio_nvram_len) || (!nvram_addr) ) अणु
		prपूर्णांकk(KERN_WARNING "nvram: address or length is 0\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	mmio_nvram_start = ioremap(nvram_addr, mmio_nvram_len);
	अगर (!mmio_nvram_start) अणु
		prपूर्णांकk(KERN_WARNING "nvram: failed to ioremap\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_INFO "mmio NVRAM, %luk at 0x%lx mapped to %p\n",
	       mmio_nvram_len >> 10, nvram_addr, mmio_nvram_start);

	ppc_md.nvram_पढ़ो_val	= mmio_nvram_पढ़ो_val;
	ppc_md.nvram_ग_लिखो_val	= mmio_nvram_ग_लिखो_val;
	ppc_md.nvram_पढ़ो	= mmio_nvram_पढ़ो;
	ppc_md.nvram_ग_लिखो	= mmio_nvram_ग_लिखो;
	ppc_md.nvram_size	= mmio_nvram_get_size;

out:
	of_node_put(nvram_node);
	वापस ret;
पूर्ण
