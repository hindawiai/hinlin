<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Procfs पूर्णांकerface क्रम the PCI bus
 *
 * Copyright (c) 1997--1999 Martin Mares <mj@ucw.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/capability.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/security.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "pci.h"

अटल पूर्णांक proc_initialized;	/* = 0 */

अटल loff_t proc_bus_pci_lseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	काष्ठा pci_dev *dev = PDE_DATA(file_inode(file));
	वापस fixed_size_llseek(file, off, whence, dev->cfg_size);
पूर्ण

अटल sमाप_प्रकार proc_bus_pci_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा pci_dev *dev = PDE_DATA(file_inode(file));
	अचिन्हित पूर्णांक pos = *ppos;
	अचिन्हित पूर्णांक cnt, size;

	/*
	 * Normal users can पढ़ो only the standardized portion of the
	 * configuration space as several chips lock up when trying to पढ़ो
	 * undefined locations (think of Intel PIIX4 as a typical example).
	 */

	अगर (capable(CAP_SYS_ADMIN))
		size = dev->cfg_size;
	अन्यथा अगर (dev->hdr_type == PCI_HEADER_TYPE_CARDBUS)
		size = 128;
	अन्यथा
		size = 64;

	अगर (pos >= size)
		वापस 0;
	अगर (nbytes >= size)
		nbytes = size;
	अगर (pos + nbytes > size)
		nbytes = size - pos;
	cnt = nbytes;

	अगर (!access_ok(buf, cnt))
		वापस -EINVAL;

	pci_config_pm_runसमय_get(dev);

	अगर ((pos & 1) && cnt) अणु
		अचिन्हित अक्षर val;
		pci_user_पढ़ो_config_byte(dev, pos, &val);
		__put_user(val, buf);
		buf++;
		pos++;
		cnt--;
	पूर्ण

	अगर ((pos & 3) && cnt > 2) अणु
		अचिन्हित लघु val;
		pci_user_पढ़ो_config_word(dev, pos, &val);
		__put_user(cpu_to_le16(val), (__le16 __user *) buf);
		buf += 2;
		pos += 2;
		cnt -= 2;
	पूर्ण

	जबतक (cnt >= 4) अणु
		अचिन्हित पूर्णांक val;
		pci_user_पढ़ो_config_dword(dev, pos, &val);
		__put_user(cpu_to_le32(val), (__le32 __user *) buf);
		buf += 4;
		pos += 4;
		cnt -= 4;
	पूर्ण

	अगर (cnt >= 2) अणु
		अचिन्हित लघु val;
		pci_user_पढ़ो_config_word(dev, pos, &val);
		__put_user(cpu_to_le16(val), (__le16 __user *) buf);
		buf += 2;
		pos += 2;
		cnt -= 2;
	पूर्ण

	अगर (cnt) अणु
		अचिन्हित अक्षर val;
		pci_user_पढ़ो_config_byte(dev, pos, &val);
		__put_user(val, buf);
		buf++;
		pos++;
		cnt--;
	पूर्ण

	pci_config_pm_runसमय_put(dev);

	*ppos = pos;
	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार proc_bus_pci_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				  माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा inode *ino = file_inode(file);
	काष्ठा pci_dev *dev = PDE_DATA(ino);
	पूर्णांक pos = *ppos;
	पूर्णांक size = dev->cfg_size;
	पूर्णांक cnt, ret;

	ret = security_locked_करोwn(LOCKDOWN_PCI_ACCESS);
	अगर (ret)
		वापस ret;

	अगर (pos >= size)
		वापस 0;
	अगर (nbytes >= size)
		nbytes = size;
	अगर (pos + nbytes > size)
		nbytes = size - pos;
	cnt = nbytes;

	अगर (!access_ok(buf, cnt))
		वापस -EINVAL;

	pci_config_pm_runसमय_get(dev);

	अगर ((pos & 1) && cnt) अणु
		अचिन्हित अक्षर val;
		__get_user(val, buf);
		pci_user_ग_लिखो_config_byte(dev, pos, val);
		buf++;
		pos++;
		cnt--;
	पूर्ण

	अगर ((pos & 3) && cnt > 2) अणु
		__le16 val;
		__get_user(val, (__le16 __user *) buf);
		pci_user_ग_लिखो_config_word(dev, pos, le16_to_cpu(val));
		buf += 2;
		pos += 2;
		cnt -= 2;
	पूर्ण

	जबतक (cnt >= 4) अणु
		__le32 val;
		__get_user(val, (__le32 __user *) buf);
		pci_user_ग_लिखो_config_dword(dev, pos, le32_to_cpu(val));
		buf += 4;
		pos += 4;
		cnt -= 4;
	पूर्ण

	अगर (cnt >= 2) अणु
		__le16 val;
		__get_user(val, (__le16 __user *) buf);
		pci_user_ग_लिखो_config_word(dev, pos, le16_to_cpu(val));
		buf += 2;
		pos += 2;
		cnt -= 2;
	पूर्ण

	अगर (cnt) अणु
		अचिन्हित अक्षर val;
		__get_user(val, buf);
		pci_user_ग_लिखो_config_byte(dev, pos, val);
		buf++;
		pos++;
		cnt--;
	पूर्ण

	pci_config_pm_runसमय_put(dev);

	*ppos = pos;
	i_size_ग_लिखो(ino, dev->cfg_size);
	वापस nbytes;
पूर्ण

काष्ठा pci_filp_निजी अणु
	क्रमागत pci_mmap_state mmap_state;
	पूर्णांक ग_लिखो_combine;
पूर्ण;

अटल दीर्घ proc_bus_pci_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा pci_dev *dev = PDE_DATA(file_inode(file));
#अगर_घोषित HAVE_PCI_MMAP
	काष्ठा pci_filp_निजी *fpriv = file->निजी_data;
#पूर्ण_अगर /* HAVE_PCI_MMAP */
	पूर्णांक ret = 0;

	ret = security_locked_करोwn(LOCKDOWN_PCI_ACCESS);
	अगर (ret)
		वापस ret;

	चयन (cmd) अणु
	हाल PCIIOC_CONTROLLER:
		ret = pci_करोमुख्य_nr(dev->bus);
		अवरोध;

#अगर_घोषित HAVE_PCI_MMAP
	हाल PCIIOC_MMAP_IS_IO:
		अगर (!arch_can_pci_mmap_io())
			वापस -EINVAL;
		fpriv->mmap_state = pci_mmap_io;
		अवरोध;

	हाल PCIIOC_MMAP_IS_MEM:
		fpriv->mmap_state = pci_mmap_mem;
		अवरोध;

	हाल PCIIOC_WRITE_COMBINE:
		अगर (arch_can_pci_mmap_wc()) अणु
			अगर (arg)
				fpriv->ग_लिखो_combine = 1;
			अन्यथा
				fpriv->ग_लिखो_combine = 0;
			अवरोध;
		पूर्ण
		/* If arch decided it can't, fall through... */
#पूर्ण_अगर /* HAVE_PCI_MMAP */
		fallthrough;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित HAVE_PCI_MMAP
अटल पूर्णांक proc_bus_pci_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा pci_dev *dev = PDE_DATA(file_inode(file));
	काष्ठा pci_filp_निजी *fpriv = file->निजी_data;
	पूर्णांक i, ret, ग_लिखो_combine = 0, res_bit = IORESOURCE_MEM;

	अगर (!capable(CAP_SYS_RAWIO) ||
	    security_locked_करोwn(LOCKDOWN_PCI_ACCESS))
		वापस -EPERM;

	अगर (fpriv->mmap_state == pci_mmap_io) अणु
		अगर (!arch_can_pci_mmap_io())
			वापस -EINVAL;
		res_bit = IORESOURCE_IO;
	पूर्ण

	/* Make sure the caller is mapping a real resource क्रम this device */
	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (dev->resource[i].flags & res_bit &&
		    pci_mmap_fits(dev, i, vma,  PCI_MMAP_PROCFS))
			अवरोध;
	पूर्ण

	अगर (i >= PCI_STD_NUM_BARS)
		वापस -ENODEV;

	अगर (fpriv->mmap_state == pci_mmap_mem &&
	    fpriv->ग_लिखो_combine) अणु
		अगर (dev->resource[i].flags & IORESOURCE_PREFETCH)
			ग_लिखो_combine = 1;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (dev->resource[i].flags & IORESOURCE_MEM &&
	    iomem_is_exclusive(dev->resource[i].start))
		वापस -EINVAL;

	ret = pci_mmap_page_range(dev, i, vma,
				  fpriv->mmap_state, ग_लिखो_combine);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक proc_bus_pci_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pci_filp_निजी *fpriv = kदो_स्मृति(माप(*fpriv), GFP_KERNEL);

	अगर (!fpriv)
		वापस -ENOMEM;

	fpriv->mmap_state = pci_mmap_io;
	fpriv->ग_लिखो_combine = 0;

	file->निजी_data = fpriv;
	file->f_mapping = iomem_get_mapping();

	वापस 0;
पूर्ण

अटल पूर्णांक proc_bus_pci_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	file->निजी_data = शून्य;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* HAVE_PCI_MMAP */

अटल स्थिर काष्ठा proc_ops proc_bus_pci_ops = अणु
	.proc_lseek	= proc_bus_pci_lseek,
	.proc_पढ़ो	= proc_bus_pci_पढ़ो,
	.proc_ग_लिखो	= proc_bus_pci_ग_लिखो,
	.proc_ioctl	= proc_bus_pci_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.proc_compat_ioctl = proc_bus_pci_ioctl,
#पूर्ण_अगर
#अगर_घोषित HAVE_PCI_MMAP
	.proc_खोलो	= proc_bus_pci_खोलो,
	.proc_release	= proc_bus_pci_release,
	.proc_mmap	= proc_bus_pci_mmap,
#अगर_घोषित HAVE_ARCH_PCI_GET_UNMAPPED_AREA
	.proc_get_unmapped_area = get_pci_unmapped_area,
#पूर्ण_अगर /* HAVE_ARCH_PCI_GET_UNMAPPED_AREA */
#पूर्ण_अगर /* HAVE_PCI_MMAP */
पूर्ण;

/* iterator */
अटल व्योम *pci_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा pci_dev *dev = शून्य;
	loff_t n = *pos;

	क्रम_each_pci_dev(dev) अणु
		अगर (!n--)
			अवरोध;
	पूर्ण
	वापस dev;
पूर्ण

अटल व्योम *pci_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा pci_dev *dev = v;

	(*pos)++;
	dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, dev);
	वापस dev;
पूर्ण

अटल व्योम pci_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (v) अणु
		काष्ठा pci_dev *dev = v;
		pci_dev_put(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक show_device(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर काष्ठा pci_dev *dev = v;
	स्थिर काष्ठा pci_driver *drv;
	पूर्णांक i;

	अगर (dev == शून्य)
		वापस 0;

	drv = pci_dev_driver(dev);
	seq_म_लिखो(m, "%02x%02x\t%04x%04x\t%x",
			dev->bus->number,
			dev->devfn,
			dev->venकरोr,
			dev->device,
			dev->irq);

	/* only prपूर्णांक standard and ROM resources to preserve compatibility */
	क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++) अणु
		resource_माप_प्रकार start, end;
		pci_resource_to_user(dev, i, &dev->resource[i], &start, &end);
		seq_म_लिखो(m, "\t%16llx",
			(अचिन्हित दीर्घ दीर्घ)(start |
			(dev->resource[i].flags & PCI_REGION_FLAG_MASK)));
	पूर्ण
	क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++) अणु
		resource_माप_प्रकार start, end;
		pci_resource_to_user(dev, i, &dev->resource[i], &start, &end);
		seq_म_लिखो(m, "\t%16llx",
			dev->resource[i].start < dev->resource[i].end ?
			(अचिन्हित दीर्घ दीर्घ)(end - start) + 1 : 0);
	पूर्ण
	seq_अ_दो(m, '\t');
	अगर (drv)
		seq_माला_दो(m, drv->name);
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations proc_bus_pci_devices_op = अणु
	.start	= pci_seq_start,
	.next	= pci_seq_next,
	.stop	= pci_seq_stop,
	.show	= show_device
पूर्ण;

अटल काष्ठा proc_dir_entry *proc_bus_pci_dir;

पूर्णांक pci_proc_attach_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus = dev->bus;
	काष्ठा proc_dir_entry *e;
	अक्षर name[16];

	अगर (!proc_initialized)
		वापस -EACCES;

	अगर (!bus->procdir) अणु
		अगर (pci_proc_करोमुख्य(bus)) अणु
			प्र_लिखो(name, "%04x:%02x", pci_करोमुख्य_nr(bus),
					bus->number);
		पूर्ण अन्यथा अणु
			प्र_लिखो(name, "%02x", bus->number);
		पूर्ण
		bus->procdir = proc_सूची_गढ़ो(name, proc_bus_pci_dir);
		अगर (!bus->procdir)
			वापस -ENOMEM;
	पूर्ण

	प्र_लिखो(name, "%02x.%x", PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn));
	e = proc_create_data(name, S_IFREG | S_IRUGO | S_IWUSR, bus->procdir,
			     &proc_bus_pci_ops, dev);
	अगर (!e)
		वापस -ENOMEM;
	proc_set_size(e, dev->cfg_size);
	dev->procent = e;

	वापस 0;
पूर्ण

पूर्णांक pci_proc_detach_device(काष्ठा pci_dev *dev)
अणु
	proc_हटाओ(dev->procent);
	dev->procent = शून्य;
	वापस 0;
पूर्ण

पूर्णांक pci_proc_detach_bus(काष्ठा pci_bus *bus)
अणु
	proc_हटाओ(bus->procdir);
	वापस 0;
पूर्ण

अटल पूर्णांक __init pci_proc_init(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	proc_bus_pci_dir = proc_सूची_गढ़ो("bus/pci", शून्य);
	proc_create_seq("devices", 0, proc_bus_pci_dir,
		    &proc_bus_pci_devices_op);
	proc_initialized = 1;
	क्रम_each_pci_dev(dev)
		pci_proc_attach_device(dev);

	वापस 0;
पूर्ण
device_initcall(pci_proc_init);
