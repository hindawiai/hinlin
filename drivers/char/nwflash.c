<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Flash memory पूर्णांकerface rev.5 driver क्रम the Intel
 * Flash chips used on the NetWinder.
 *
 * 20/08/2000	RMK	use __ioremap to map flash पूर्णांकo भव memory
 *			make a few more places use "volatile"
 * 22/05/2001	RMK	- Lock पढ़ो against ग_लिखो
 *			- merge prपूर्णांकk level changes (with mods) from Alan Cox.
 *			- use *ppos as the file position, not file->f_pos.
 *			- fix check क्रम out of range pos and r/w size
 *
 * Please note that we are tampering with the only flash chip in the
 * machine, which contains the bootup code.  We thereक्रमe have the
 * घातer to convert these machines पूर्णांकo करोorstops...
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>

#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/uaccess.h>

/*****************************************************************************/
#समावेश <यंत्र/nwflash.h>

#घोषणा	NWFLASH_VERSION "6.4"

अटल DEFINE_MUTEX(flash_mutex);
अटल व्योम kick_खोलो(व्योम);
अटल पूर्णांक get_flash_id(व्योम);
अटल पूर्णांक erase_block(पूर्णांक nBlock);
अटल पूर्णांक ग_लिखो_block(अचिन्हित दीर्घ p, स्थिर अक्षर __user *buf, पूर्णांक count);

#घोषणा KFLASH_SIZE	1024*1024	//1 Meg
#घोषणा KFLASH_SIZE4	4*1024*1024	//4 Meg
#घोषणा KFLASH_ID	0x89A6		//Intel flash
#घोषणा KFLASH_ID4	0xB0D4		//Intel flash 4Meg

अटल bool flashdebug;		//अगर set - we will display progress msgs

अटल पूर्णांक gbWriteEnable;
अटल पूर्णांक gbWriteBase64Enable;
अटल अस्थिर अचिन्हित अक्षर *FLASH_BASE;
अटल पूर्णांक gbFlashSize = KFLASH_SIZE;
अटल DEFINE_MUTEX(nwflash_mutex);

अटल पूर्णांक get_flash_id(व्योम)
अणु
	अस्थिर अचिन्हित पूर्णांक c1, c2;

	/*
	 * try to get flash chip ID
	 */
	kick_खोलो();
	c2 = inb(0x80);
	*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000) = 0x90;
	udelay(15);
	c1 = *(अस्थिर अचिन्हित अक्षर *) FLASH_BASE;
	c2 = inb(0x80);

	/*
	 * on 4 Meg flash the second byte is actually at offset 2...
	 */
	अगर (c1 == 0xB0)
		c2 = *(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 2);
	अन्यथा
		c2 = *(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 1);

	c2 += (c1 << 8);

	/*
	 * set it back to पढ़ो mode
	 */
	*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000) = 0xFF;

	अगर (c2 == KFLASH_ID4)
		gbFlashSize = KFLASH_SIZE4;

	वापस c2;
पूर्ण

अटल दीर्घ flash_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	mutex_lock(&flash_mutex);
	चयन (cmd) अणु
	हाल CMD_WRITE_DISABLE:
		gbWriteBase64Enable = 0;
		gbWriteEnable = 0;
		अवरोध;

	हाल CMD_WRITE_ENABLE:
		gbWriteEnable = 1;
		अवरोध;

	हाल CMD_WRITE_BASE64K_ENABLE:
		gbWriteBase64Enable = 1;
		अवरोध;

	शेष:
		gbWriteBase64Enable = 0;
		gbWriteEnable = 0;
		mutex_unlock(&flash_mutex);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&flash_mutex);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार flash_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
			  loff_t *ppos)
अणु
	sमाप_प्रकार ret;

	अगर (flashdebug)
		prपूर्णांकk(KERN_DEBUG "flash_read: flash_read: offset=0x%llx, "
		       "buffer=%p, count=0x%zx.\n", *ppos, buf, size);
	/*
	 * We now lock against पढ़ोs and ग_लिखोs. --rmk
	 */
	अगर (mutex_lock_पूर्णांकerruptible(&nwflash_mutex))
		वापस -ERESTARTSYS;

	ret = simple_पढ़ो_from_buffer(buf, size, ppos, (व्योम *)FLASH_BASE, gbFlashSize);
	mutex_unlock(&nwflash_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार flash_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार size, loff_t * ppos)
अणु
	अचिन्हित दीर्घ p = *ppos;
	अचिन्हित पूर्णांक count = size;
	पूर्णांक written;
	पूर्णांक nBlock, temp, rc;
	पूर्णांक i, j;

	अगर (flashdebug)
		prपूर्णांकk("flash_write: offset=0x%lX, buffer=0x%p, count=0x%X.\n",
		       p, buf, count);

	अगर (!gbWriteEnable)
		वापस -EINVAL;

	अगर (p < 64 * 1024 && (!gbWriteBase64Enable))
		वापस -EINVAL;

	/*
	 * check क्रम out of range pos or count
	 */
	अगर (p >= gbFlashSize)
		वापस count ? -ENXIO : 0;

	अगर (count > gbFlashSize - p)
		count = gbFlashSize - p;
			
	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	/*
	 * We now lock against पढ़ोs and ग_लिखोs. --rmk
	 */
	अगर (mutex_lock_पूर्णांकerruptible(&nwflash_mutex))
		वापस -ERESTARTSYS;

	written = 0;

	nBlock = (पूर्णांक) p >> 16;	//block # of 64K bytes

	/*
	 * # of 64K blocks to erase and ग_लिखो
	 */
	temp = ((पूर्णांक) (p + count) >> 16) - nBlock + 1;

	/*
	 * ग_लिखो ends at exactly 64k boundary?
	 */
	अगर (((पूर्णांक) (p + count) & 0xFFFF) == 0)
		temp -= 1;

	अगर (flashdebug)
		prपूर्णांकk(KERN_DEBUG "flash_write: writing %d block(s) "
			"starting at %d.\n", temp, nBlock);

	क्रम (; temp; temp--, nBlock++) अणु
		अगर (flashdebug)
			prपूर्णांकk(KERN_DEBUG "flash_write: erasing block %d.\n", nBlock);

		/*
		 * first we have to erase the block(s), where we will ग_लिखो...
		 */
		i = 0;
		j = 0;
	  RetryBlock:
		करो अणु
			rc = erase_block(nBlock);
			i++;
		पूर्ण जबतक (rc && i < 10);

		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "flash_write: erase error %x\n", rc);
			अवरोध;
		पूर्ण
		अगर (flashdebug)
			prपूर्णांकk(KERN_DEBUG "flash_write: writing offset %lX, "
			       "from buf %p, bytes left %X.\n", p, buf,
			       count - written);

		/*
		 * ग_लिखो_block will limit ग_लिखो to space left in this block
		 */
		rc = ग_लिखो_block(p, buf, count - written);
		j++;

		/*
		 * अगर somehow ग_लिखो verअगरy failed? Can't happen??
		 */
		अगर (!rc) अणु
			/*
			 * retry up to 10 बार
			 */
			अगर (j < 10)
				जाओ RetryBlock;
			अन्यथा
				/*
				 * अन्यथा quit with error...
				 */
				rc = -1;

		पूर्ण
		अगर (rc < 0) अणु
			prपूर्णांकk(KERN_ERR "flash_write: write error %X\n", rc);
			अवरोध;
		पूर्ण
		p += rc;
		buf += rc;
		written += rc;
		*ppos += rc;

		अगर (flashdebug)
			prपूर्णांकk(KERN_DEBUG "flash_write: written 0x%X bytes OK.\n", written);
	पूर्ण

	mutex_unlock(&nwflash_mutex);

	वापस written;
पूर्ण


/*
 * The memory devices use the full 32/64 bits of the offset, and so we cannot
 * check against negative addresses: they are ok. The वापस value is weird,
 * though, in that हाल (0).
 *
 * also note that seeking relative to the "end of file" isn't supported:
 * it has no meaning, so it वापसs -EINVAL.
 */
अटल loff_t flash_llseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	loff_t ret;

	mutex_lock(&flash_mutex);
	अगर (flashdebug)
		prपूर्णांकk(KERN_DEBUG "flash_llseek: offset=0x%X, orig=0x%X.\n",
		       (अचिन्हित पूर्णांक) offset, orig);

	ret = no_seek_end_llseek_size(file, offset, orig, gbFlashSize);
	mutex_unlock(&flash_mutex);
	वापस ret;
पूर्ण


/*
 * assume that मुख्य Write routine did the parameter checking...
 * so just go ahead and erase, what requested!
 */

अटल पूर्णांक erase_block(पूर्णांक nBlock)
अणु
	अस्थिर अचिन्हित पूर्णांक c1;
	अस्थिर अचिन्हित अक्षर *pWritePtr;
	अचिन्हित दीर्घ समयout;
	पूर्णांक temp, temp1;

	/*
	 * reset footbridge to the correct offset 0 (...0..3)
	 */
	*CSR_ROMWRITEREG = 0;

	/*
	 * dummy ROM पढ़ो
	 */
	c1 = *(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000);

	kick_खोलो();
	/*
	 * reset status अगर old errors
	 */
	*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000) = 0x50;

	/*
	 * erase a block...
	 * aim at the middle of a current block...
	 */
	pWritePtr = (अचिन्हित अक्षर *) ((अचिन्हित पूर्णांक) (FLASH_BASE + 0x8000 + (nBlock << 16)));
	/*
	 * dummy पढ़ो
	 */
	c1 = *pWritePtr;

	kick_खोलो();
	/*
	 * erase
	 */
	*(अस्थिर अचिन्हित अक्षर *) pWritePtr = 0x20;

	/*
	 * confirm
	 */
	*(अस्थिर अचिन्हित अक्षर *) pWritePtr = 0xD0;

	/*
	 * रुको 10 ms
	 */
	msleep(10);

	/*
	 * रुको जबतक erasing in process (up to 10 sec)
	 */
	समयout = jअगरfies + 10 * HZ;
	c1 = 0;
	जबतक (!(c1 & 0x80) && समय_beक्रमe(jअगरfies, समयout)) अणु
		msleep(10);
		/*
		 * पढ़ो any address
		 */
		c1 = *(अस्थिर अचिन्हित अक्षर *) (pWritePtr);
		//              prपूर्णांकk("Flash_erase: status=%X.\n",c1);
	पूर्ण

	/*
	 * set flash क्रम normal पढ़ो access
	 */
	kick_खोलो();
//      *(अस्थिर अचिन्हित अक्षर*)(FLASH_BASE+0x8000) = 0xFF;
	*(अस्थिर अचिन्हित अक्षर *) pWritePtr = 0xFF;	//back to normal operation

	/*
	 * check अगर erase errors were reported
	 */
	अगर (c1 & 0x20) अणु
		prपूर्णांकk(KERN_ERR "flash_erase: err at %p\n", pWritePtr);

		/*
		 * reset error
		 */
		*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000) = 0x50;
		वापस -2;
	पूर्ण

	/*
	 * just to make sure - verअगरy अगर erased OK...
	 */
	msleep(10);

	pWritePtr = (अचिन्हित अक्षर *) ((अचिन्हित पूर्णांक) (FLASH_BASE + (nBlock << 16)));

	क्रम (temp = 0; temp < 16 * 1024; temp++, pWritePtr += 4) अणु
		अगर ((temp1 = *(अस्थिर अचिन्हित पूर्णांक *) pWritePtr) != 0xFFFFFFFF) अणु
			prपूर्णांकk(KERN_ERR "flash_erase: verify err at %p = %X\n",
			       pWritePtr, temp1);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

/*
 * ग_लिखो_block will limit number of bytes written to the space in this block
 */
अटल पूर्णांक ग_लिखो_block(अचिन्हित दीर्घ p, स्थिर अक्षर __user *buf, पूर्णांक count)
अणु
	अस्थिर अचिन्हित पूर्णांक c1;
	अस्थिर अचिन्हित पूर्णांक c2;
	अचिन्हित अक्षर *pWritePtr;
	अचिन्हित पूर्णांक uAddress;
	अचिन्हित पूर्णांक offset;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ समयout1;

	pWritePtr = (अचिन्हित अक्षर *) ((अचिन्हित पूर्णांक) (FLASH_BASE + p));

	/*
	 * check अगर ग_लिखो will end in this block....
	 */
	offset = p & 0xFFFF;

	अगर (offset + count > 0x10000)
		count = 0x10000 - offset;

	/*
	 * रुको up to 30 sec क्रम this block
	 */
	समयout = jअगरfies + 30 * HZ;

	क्रम (offset = 0; offset < count; offset++, pWritePtr++) अणु
		uAddress = (अचिन्हित पूर्णांक) pWritePtr;
		uAddress &= 0xFFFFFFFC;
		अगर (__get_user(c2, buf + offset))
			वापस -EFAULT;

	  WriteRetry:
	  	/*
	  	 * dummy पढ़ो
	  	 */
		c1 = *(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000);

		/*
		 * kick खोलो the ग_लिखो gate
		 */
		kick_खोलो();

		/*
		 * program footbridge to the correct offset...0..3
		 */
		*CSR_ROMWRITEREG = (अचिन्हित पूर्णांक) pWritePtr & 3;

		/*
		 * ग_लिखो cmd
		 */
		*(अस्थिर अचिन्हित अक्षर *) (uAddress) = 0x40;

		/*
		 * data to ग_लिखो
		 */
		*(अस्थिर अचिन्हित अक्षर *) (uAddress) = c2;

		/*
		 * get status
		 */
		*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x10000) = 0x70;

		c1 = 0;

		/*
		 * रुको up to 1 sec क्रम this byte
		 */
		समयout1 = jअगरfies + 1 * HZ;

		/*
		 * जबतक not पढ़ोy...
		 */
		जबतक (!(c1 & 0x80) && समय_beक्रमe(jअगरfies, समयout1))
			c1 = *(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000);

		/*
		 * अगर समयout getting status
		 */
		अगर (समय_after_eq(jअगरfies, समयout1)) अणु
			kick_खोलो();
			/*
			 * reset err
			 */
			*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000) = 0x50;

			जाओ WriteRetry;
		पूर्ण
		/*
		 * चयन on पढ़ो access, as a शेष flash operation mode
		 */
		kick_खोलो();
		/*
		 * पढ़ो access
		 */
		*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000) = 0xFF;

		/*
		 * अगर hardware reports an error writing, and not समयout - 
		 * reset the chip and retry
		 */
		अगर (c1 & 0x10) अणु
			kick_खोलो();
			/*
			 * reset err
			 */
			*(अस्थिर अचिन्हित अक्षर *) (FLASH_BASE + 0x8000) = 0x50;

			/*
			 * beक्रमe समयout?
			 */
			अगर (समय_beक्रमe(jअगरfies, समयout)) अणु
				अगर (flashdebug)
					prपूर्णांकk(KERN_DEBUG "write_block: Retrying write at 0x%X)n",
					       pWritePtr - FLASH_BASE);

				/*
				 * रुको couple ms
				 */
				msleep(10);

				जाओ WriteRetry;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_ERR "write_block: timeout at 0x%X\n",
				       pWritePtr - FLASH_BASE);
				/*
				 * वापस error -2
				 */
				वापस -2;

			पूर्ण
		पूर्ण
	पूर्ण

	msleep(10);

	pWritePtr = (अचिन्हित अक्षर *) ((अचिन्हित पूर्णांक) (FLASH_BASE + p));

	क्रम (offset = 0; offset < count; offset++) अणु
		अक्षर c, c1;
		अगर (__get_user(c, buf))
			वापस -EFAULT;
		buf++;
		अगर ((c1 = *pWritePtr++) != c) अणु
			prपूर्णांकk(KERN_ERR "write_block: verify error at 0x%X (%02X!=%02X)\n",
			       pWritePtr - FLASH_BASE, c1, c);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण


अटल व्योम kick_खोलो(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * we want to ग_लिखो a bit pattern XXX1 to Xilinx to enable
	 * the ग_लिखो gate, which will be खोलो क्रम about the next 2ms.
	 */
	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_cpld_modअगरy(CPLD_FLASH_WR_ENABLE, CPLD_FLASH_WR_ENABLE);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);

	/*
	 * let the ISA bus to catch on...
	 */
	udelay(25);
पूर्ण

अटल स्थिर काष्ठा file_operations flash_fops =
अणु
	.owner		= THIS_MODULE,
	.llseek		= flash_llseek,
	.पढ़ो		= flash_पढ़ो,
	.ग_लिखो		= flash_ग_लिखो,
	.unlocked_ioctl	= flash_ioctl,
पूर्ण;

अटल काष्ठा miscdevice flash_miscdev =
अणु
	NWFLASH_MINOR,
	"nwflash",
	&flash_fops
पूर्ण;

अटल पूर्णांक __init nwflash_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (machine_is_netwinder()) अणु
		पूर्णांक id;

		FLASH_BASE = ioremap(DC21285_FLASH, KFLASH_SIZE4);
		अगर (!FLASH_BASE)
			जाओ out;

		id = get_flash_id();
		अगर ((id != KFLASH_ID) && (id != KFLASH_ID4)) अणु
			ret = -ENXIO;
			iounmap((व्योम *)FLASH_BASE);
			prपूर्णांकk("Flash: incorrect ID 0x%04X.\n", id);
			जाओ out;
		पूर्ण

		prपूर्णांकk("Flash ROM driver v.%s, flash device ID 0x%04X, size %d Mb.\n",
		       NWFLASH_VERSION, id, gbFlashSize / (1024 * 1024));

		ret = misc_रेजिस्टर(&flash_miscdev);
		अगर (ret < 0) अणु
			iounmap((व्योम *)FLASH_BASE);
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास nwflash_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&flash_miscdev);
	iounmap((व्योम *)FLASH_BASE);
पूर्ण

MODULE_LICENSE("GPL");

module_param(flashdebug, bool, 0644);

module_init(nwflash_init);
module_निकास(nwflash_निकास);
