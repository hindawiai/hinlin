<शैली गुरु>
/*
 * block2mtd.c - create an mtd from a block device
 *
 * Copyright (C) 2001,2002	Simon Evans <spse@secret.org.uk>
 * Copyright (C) 2004-2006	Joern Engel <joern@wh.fh-wedel.de>
 *
 * Licence: GPL
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/*
 * When the first attempt at device initialization fails, we may need to
 * रुको a little bit and retry. This समयout, by शेष 3 seconds, gives
 * device समय to start up. Required on BCM2708 and a few other chipsets.
 */
#घोषणा MTD_DEFAULT_TIMEOUT	3

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mount.h>
#समावेश <linux/slab.h>
#समावेश <linux/major.h>

/* Info क्रम the block device */
काष्ठा block2mtd_dev अणु
	काष्ठा list_head list;
	काष्ठा block_device *blkdev;
	काष्ठा mtd_info mtd;
	काष्ठा mutex ग_लिखो_mutex;
पूर्ण;


/* Static info about the MTD, used in cleanup_module */
अटल LIST_HEAD(blkmtd_device_list);


अटल काष्ठा page *page_पढ़ो(काष्ठा address_space *mapping, pgoff_t index)
अणु
	वापस पढ़ो_mapping_page(mapping, index, शून्य);
पूर्ण

/* erase a specअगरied part of the device */
अटल पूर्णांक _block2mtd_erase(काष्ठा block2mtd_dev *dev, loff_t to, माप_प्रकार len)
अणु
	काष्ठा address_space *mapping = dev->blkdev->bd_inode->i_mapping;
	काष्ठा page *page;
	pgoff_t index = to >> PAGE_SHIFT;	// page index
	पूर्णांक pages = len >> PAGE_SHIFT;
	u_दीर्घ *p;
	u_दीर्घ *max;

	जबतक (pages) अणु
		page = page_पढ़ो(mapping, index);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		max = page_address(page) + PAGE_SIZE;
		क्रम (p=page_address(page); p<max; p++)
			अगर (*p != -1UL) अणु
				lock_page(page);
				स_रखो(page_address(page), 0xff, PAGE_SIZE);
				set_page_dirty(page);
				unlock_page(page);
				balance_dirty_pages_ratelimited(mapping);
				अवरोध;
			पूर्ण

		put_page(page);
		pages--;
		index++;
	पूर्ण
	वापस 0;
पूर्ण
अटल पूर्णांक block2mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा block2mtd_dev *dev = mtd->priv;
	माप_प्रकार from = instr->addr;
	माप_प्रकार len = instr->len;
	पूर्णांक err;

	mutex_lock(&dev->ग_लिखो_mutex);
	err = _block2mtd_erase(dev, from, len);
	mutex_unlock(&dev->ग_लिखो_mutex);
	अगर (err)
		pr_err("erase failed err = %d\n", err);

	वापस err;
पूर्ण


अटल पूर्णांक block2mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा block2mtd_dev *dev = mtd->priv;
	काष्ठा page *page;
	pgoff_t index = from >> PAGE_SHIFT;
	पूर्णांक offset = from & (PAGE_SIZE-1);
	पूर्णांक cpylen;

	जबतक (len) अणु
		अगर ((offset + len) > PAGE_SIZE)
			cpylen = PAGE_SIZE - offset;	// multiple pages
		अन्यथा
			cpylen = len;	// this page
		len = len - cpylen;

		page = page_पढ़ो(dev->blkdev->bd_inode->i_mapping, index);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		स_नकल(buf, page_address(page) + offset, cpylen);
		put_page(page);

		अगर (retlen)
			*retlen += cpylen;
		buf += cpylen;
		offset = 0;
		index++;
	पूर्ण
	वापस 0;
पूर्ण


/* ग_लिखो data to the underlying device */
अटल पूर्णांक _block2mtd_ग_लिखो(काष्ठा block2mtd_dev *dev, स्थिर u_अक्षर *buf,
		loff_t to, माप_प्रकार len, माप_प्रकार *retlen)
अणु
	काष्ठा page *page;
	काष्ठा address_space *mapping = dev->blkdev->bd_inode->i_mapping;
	pgoff_t index = to >> PAGE_SHIFT;	// page index
	पूर्णांक offset = to & ~PAGE_MASK;	// page offset
	पूर्णांक cpylen;

	जबतक (len) अणु
		अगर ((offset+len) > PAGE_SIZE)
			cpylen = PAGE_SIZE - offset;	// multiple pages
		अन्यथा
			cpylen = len;			// this page
		len = len - cpylen;

		page = page_पढ़ो(mapping, index);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		अगर (स_भेद(page_address(page)+offset, buf, cpylen)) अणु
			lock_page(page);
			स_नकल(page_address(page) + offset, buf, cpylen);
			set_page_dirty(page);
			unlock_page(page);
			balance_dirty_pages_ratelimited(mapping);
		पूर्ण
		put_page(page);

		अगर (retlen)
			*retlen += cpylen;

		buf += cpylen;
		offset = 0;
		index++;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक block2mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा block2mtd_dev *dev = mtd->priv;
	पूर्णांक err;

	mutex_lock(&dev->ग_लिखो_mutex);
	err = _block2mtd_ग_लिखो(dev, buf, to, len, retlen);
	mutex_unlock(&dev->ग_लिखो_mutex);
	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण


/* sync the device - रुको until the ग_लिखो queue is empty */
अटल व्योम block2mtd_sync(काष्ठा mtd_info *mtd)
अणु
	काष्ठा block2mtd_dev *dev = mtd->priv;
	sync_blockdev(dev->blkdev);
	वापस;
पूर्ण


अटल व्योम block2mtd_मुक्त_device(काष्ठा block2mtd_dev *dev)
अणु
	अगर (!dev)
		वापस;

	kमुक्त(dev->mtd.name);

	अगर (dev->blkdev) अणु
		invalidate_mapping_pages(dev->blkdev->bd_inode->i_mapping,
					0, -1);
		blkdev_put(dev->blkdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
	पूर्ण

	kमुक्त(dev);
पूर्ण


अटल काष्ठा block2mtd_dev *add_device(अक्षर *devname, पूर्णांक erase_size,
		पूर्णांक समयout)
अणु
#अगर_अघोषित MODULE
	पूर्णांक i;
#पूर्ण_अगर
	स्थिर भ_शेषe_t mode = FMODE_READ | FMODE_WRITE | FMODE_EXCL;
	काष्ठा block_device *bdev;
	काष्ठा block2mtd_dev *dev;
	अक्षर *name;

	अगर (!devname)
		वापस शून्य;

	dev = kzalloc(माप(काष्ठा block2mtd_dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	/* Get a handle on the device */
	bdev = blkdev_get_by_path(devname, mode, dev);

#अगर_अघोषित MODULE
	/*
	 * We might not have the root device mounted at this poपूर्णांक.
	 * Try to resolve the device name by other means.
	 */
	क्रम (i = 0; IS_ERR(bdev) && i <= समयout; i++) अणु
		dev_t devt;

		अगर (i)
			/*
			 * Calling रुको_क्रम_device_probe in the first loop
			 * was not enough, sleep क्रम a bit in subsequent
			 * go-arounds.
			 */
			msleep(1000);
		रुको_क्रम_device_probe();

		devt = name_to_dev_t(devname);
		अगर (!devt)
			जारी;
		bdev = blkdev_get_by_dev(devt, mode, dev);
	पूर्ण
#पूर्ण_अगर

	अगर (IS_ERR(bdev)) अणु
		pr_err("error: cannot open device %s\n", devname);
		जाओ err_मुक्त_block2mtd;
	पूर्ण
	dev->blkdev = bdev;

	अगर (MAJOR(bdev->bd_dev) == MTD_BLOCK_MAJOR) अणु
		pr_err("attempting to use an MTD device as a block device\n");
		जाओ err_मुक्त_block2mtd;
	पूर्ण

	अगर ((दीर्घ)dev->blkdev->bd_inode->i_size % erase_size) अणु
		pr_err("erasesize must be a divisor of device size\n");
		जाओ err_मुक्त_block2mtd;
	पूर्ण

	mutex_init(&dev->ग_लिखो_mutex);

	/* Setup the MTD काष्ठाure */
	/* make the name contain the block device in */
	name = kaप्र_लिखो(GFP_KERNEL, "block2mtd: %s", devname);
	अगर (!name)
		जाओ err_destroy_mutex;

	dev->mtd.name = name;

	dev->mtd.size = dev->blkdev->bd_inode->i_size & PAGE_MASK;
	dev->mtd.erasesize = erase_size;
	dev->mtd.ग_लिखोsize = 1;
	dev->mtd.ग_लिखोbufsize = PAGE_SIZE;
	dev->mtd.type = MTD_RAM;
	dev->mtd.flags = MTD_CAP_RAM;
	dev->mtd._erase = block2mtd_erase;
	dev->mtd._ग_लिखो = block2mtd_ग_लिखो;
	dev->mtd._sync = block2mtd_sync;
	dev->mtd._पढ़ो = block2mtd_पढ़ो;
	dev->mtd.priv = dev;
	dev->mtd.owner = THIS_MODULE;

	अगर (mtd_device_रेजिस्टर(&dev->mtd, शून्य, 0)) अणु
		/* Device didn't get added, so मुक्त the entry */
		जाओ err_destroy_mutex;
	पूर्ण

	list_add(&dev->list, &blkmtd_device_list);
	pr_info("mtd%d: [%s] erase_size = %dKiB [%d]\n",
		dev->mtd.index,
		dev->mtd.name + म_माप("block2mtd: "),
		dev->mtd.erasesize >> 10, dev->mtd.erasesize);
	वापस dev;

err_destroy_mutex:
	mutex_destroy(&dev->ग_लिखो_mutex);
err_मुक्त_block2mtd:
	block2mtd_मुक्त_device(dev);
	वापस शून्य;
पूर्ण


/* This function works similar to reguler म_से_अदीर्घ.  In addition, it
 * allows some suffixes क्रम a more human-पढ़ोable number क्रमmat:
 * ki, Ki, kiB, KiB	- multiply result with 1024
 * Mi, MiB		- multiply result with 1024^2
 * Gi, GiB		- multiply result with 1024^3
 */
अटल पूर्णांक uम_से_अदीर्घ(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित दीर्घ result = simple_म_से_अदीर्घ(cp, endp, base);
	चयन (**endp) अणु
	हाल 'G' :
		result *= 1024;
		fallthrough;
	हाल 'M':
		result *= 1024;
		fallthrough;
	हाल 'K':
	हाल 'k':
		result *= 1024;
	/* By dwmw2 editorial decree, "ki", "Mi" or "Gi" are to be used. */
		अगर ((*endp)[1] == 'i') अणु
			अगर ((*endp)[2] == 'B')
				(*endp) += 3;
			अन्यथा
				(*endp) += 2;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण


अटल पूर्णांक parse_num(माप_प्रकार *num, स्थिर अक्षर *token)
अणु
	अक्षर *endp;
	माप_प्रकार n;

	n = (माप_प्रकार) uम_से_अदीर्घ(token, &endp, 0);
	अगर (*endp)
		वापस -EINVAL;

	*num = n;
	वापस 0;
पूर्ण


अटल अंतरभूत व्योम समाप्त_final_newline(अक्षर *str)
अणु
	अक्षर *newline = म_खोजप(str, '\n');
	अगर (newline && !newline[1])
		*newline = 0;
पूर्ण


#अगर_अघोषित MODULE
अटल पूर्णांक block2mtd_init_called = 0;
/* 80 क्रम device, 12 क्रम erase size */
अटल अक्षर block2mtd_paramline[80 + 12];
#पूर्ण_अगर

अटल पूर्णांक block2mtd_setup2(स्थिर अक्षर *val)
अणु
	/* 80 क्रम device, 12 क्रम erase size, 80 क्रम name, 8 क्रम समयout */
	अक्षर buf[80 + 12 + 80 + 8];
	अक्षर *str = buf;
	अक्षर *token[2];
	अक्षर *name;
	माप_प्रकार erase_size = PAGE_SIZE;
	अचिन्हित दीर्घ समयout = MTD_DEFAULT_TIMEOUT;
	पूर्णांक i, ret;

	अगर (strnlen(val, माप(buf)) >= माप(buf)) अणु
		pr_err("parameter too long\n");
		वापस 0;
	पूर्ण

	म_नकल(str, val);
	समाप्त_final_newline(str);

	क्रम (i = 0; i < 2; i++)
		token[i] = strsep(&str, ",");

	अगर (str) अणु
		pr_err("too many arguments\n");
		वापस 0;
	पूर्ण

	अगर (!token[0]) अणु
		pr_err("no argument\n");
		वापस 0;
	पूर्ण

	name = token[0];
	अगर (म_माप(name) + 1 > 80) अणु
		pr_err("device name too long\n");
		वापस 0;
	पूर्ण

	अगर (token[1]) अणु
		ret = parse_num(&erase_size, token[1]);
		अगर (ret) अणु
			pr_err("illegal erase size\n");
			वापस 0;
		पूर्ण
	पूर्ण

	add_device(name, erase_size, समयout);

	वापस 0;
पूर्ण


अटल पूर्णांक block2mtd_setup(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
#अगर_घोषित MODULE
	वापस block2mtd_setup2(val);
#अन्यथा
	/* If more parameters are later passed in via
	   /sys/module/block2mtd/parameters/block2mtd
	   and block2mtd_init() has alपढ़ोy been called,
	   we can parse the argument now. */

	अगर (block2mtd_init_called)
		वापस block2mtd_setup2(val);

	/* During early boot stage, we only save the parameters
	   here. We must parse them later: अगर the param passed
	   from kernel boot command line, block2mtd_setup() is
	   called so early that it is not possible to resolve
	   the device (even kदो_स्मृति() fails). Deter that work to
	   block2mtd_setup2(). */

	strlcpy(block2mtd_paramline, val, माप(block2mtd_paramline));

	वापस 0;
#पूर्ण_अगर
पूर्ण


module_param_call(block2mtd, block2mtd_setup, शून्य, शून्य, 0200);
MODULE_PARM_DESC(block2mtd, "Device to use. \"block2mtd=<dev>[,<erasesize>]\"");

अटल पूर्णांक __init block2mtd_init(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर_अघोषित MODULE
	अगर (म_माप(block2mtd_paramline))
		ret = block2mtd_setup2(block2mtd_paramline);
	block2mtd_init_called = 1;
#पूर्ण_अगर

	वापस ret;
पूर्ण


अटल व्योम block2mtd_निकास(व्योम)
अणु
	काष्ठा list_head *pos, *next;

	/* Remove the MTD devices */
	list_क्रम_each_safe(pos, next, &blkmtd_device_list) अणु
		काष्ठा block2mtd_dev *dev = list_entry(pos, typeof(*dev), list);
		block2mtd_sync(&dev->mtd);
		mtd_device_unरेजिस्टर(&dev->mtd);
		mutex_destroy(&dev->ग_लिखो_mutex);
		pr_info("mtd%d: [%s] removed\n",
			dev->mtd.index,
			dev->mtd.name + म_माप("block2mtd: "));
		list_del(&dev->list);
		block2mtd_मुक्त_device(dev);
	पूर्ण
पूर्ण

late_initcall(block2mtd_init);
module_निकास(block2mtd_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joern Engel <joern@lazybastard.org>");
MODULE_DESCRIPTION("Emulate an MTD using a block device");
