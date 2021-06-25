<शैली गुरु>
/*
 * IBM Automatic Server Restart driver.
 *
 * Copyright (c) 2005 Andrey Panin <pazke@करोnpac.ru>
 *
 * Based on driver written by Pete Reynolds.
 * Copyright (c) IBM Corporation, 1998-2004.
 *
 * This software may be used and distributed according to the terms
 * of the GNU Public License, incorporated herein by reference.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयr.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


क्रमागत अणु
	ASMTYPE_UNKNOWN,
	ASMTYPE_TOPAZ,
	ASMTYPE_JASPER,
	ASMTYPE_PEARL,
	ASMTYPE_JUNIPER,
	ASMTYPE_SPRUCE,
पूर्ण;

#घोषणा TOPAZ_ASR_REG_OFFSET	4
#घोषणा TOPAZ_ASR_TOGGLE	0x40
#घोषणा TOPAZ_ASR_DISABLE	0x80

/* PEARL ASR S/W REGISTER SUPERIO PORT ADDRESSES */
#घोषणा PEARL_BASE	0xe04
#घोषणा PEARL_WRITE	0xe06
#घोषणा PEARL_READ	0xe07

#घोषणा PEARL_ASR_DISABLE_MASK	0x80	/* bit 7: disable = 1, enable = 0 */
#घोषणा PEARL_ASR_TOGGLE_MASK	0x40	/* bit 6: 0, then 1, then 0 */

/* JASPER OFFSET FROM SIO BASE ADDR TO ASR S/W REGISTERS. */
#घोषणा JASPER_ASR_REG_OFFSET	0x38

#घोषणा JASPER_ASR_DISABLE_MASK	0x01	/* bit 0: disable = 1, enable = 0 */
#घोषणा JASPER_ASR_TOGGLE_MASK	0x02	/* bit 1: 0, then 1, then 0 */

#घोषणा JUNIPER_BASE_ADDRESS	0x54b	/* Base address of Juniper ASR */
#घोषणा JUNIPER_ASR_DISABLE_MASK 0x01	/* bit 0: disable = 1 enable = 0 */
#घोषणा JUNIPER_ASR_TOGGLE_MASK	0x02	/* bit 1: 0, then 1, then 0 */

#घोषणा SPRUCE_BASE_ADDRESS	0x118e	/* Base address of Spruce ASR */
#घोषणा SPRUCE_ASR_DISABLE_MASK	0x01	/* bit 1: disable = 1 enable = 0 */
#घोषणा SPRUCE_ASR_TOGGLE_MASK	0x02	/* bit 0: 0, then 1, then 0 */


अटल bool nowayout = WATCHDOG_NOWAYOUT;

अटल अचिन्हित दीर्घ asr_is_खोलो;
अटल अक्षर asr_expect_बंद;

अटल अचिन्हित पूर्णांक asr_type, asr_base, asr_length;
अटल अचिन्हित पूर्णांक asr_पढ़ो_addr, asr_ग_लिखो_addr;
अटल अचिन्हित अक्षर asr_toggle_mask, asr_disable_mask;
अटल DEFINE_SPINLOCK(asr_lock);

अटल व्योम __asr_toggle(व्योम)
अणु
	अचिन्हित अक्षर reg;

	reg = inb(asr_पढ़ो_addr);

	outb(reg & ~asr_toggle_mask, asr_ग_लिखो_addr);
	reg = inb(asr_पढ़ो_addr);

	outb(reg | asr_toggle_mask, asr_ग_लिखो_addr);
	reg = inb(asr_पढ़ो_addr);

	outb(reg & ~asr_toggle_mask, asr_ग_लिखो_addr);
	reg = inb(asr_पढ़ो_addr);
पूर्ण

अटल व्योम asr_toggle(व्योम)
अणु
	spin_lock(&asr_lock);
	__asr_toggle();
	spin_unlock(&asr_lock);
पूर्ण

अटल व्योम asr_enable(व्योम)
अणु
	अचिन्हित अक्षर reg;

	spin_lock(&asr_lock);
	अगर (asr_type == ASMTYPE_TOPAZ) अणु
		/* asr_ग_लिखो_addr == asr_पढ़ो_addr */
		reg = inb(asr_पढ़ो_addr);
		outb(reg & ~(TOPAZ_ASR_TOGGLE | TOPAZ_ASR_DISABLE),
		     asr_पढ़ो_addr);
	पूर्ण अन्यथा अणु
		/*
		 * First make sure the hardware समयr is reset by toggling
		 * ASR hardware समयr line.
		 */
		__asr_toggle();

		reg = inb(asr_पढ़ो_addr);
		outb(reg & ~asr_disable_mask, asr_ग_लिखो_addr);
	पूर्ण
	reg = inb(asr_पढ़ो_addr);
	spin_unlock(&asr_lock);
पूर्ण

अटल व्योम asr_disable(व्योम)
अणु
	अचिन्हित अक्षर reg;

	spin_lock(&asr_lock);
	reg = inb(asr_पढ़ो_addr);

	अगर (asr_type == ASMTYPE_TOPAZ)
		/* asr_ग_लिखो_addr == asr_पढ़ो_addr */
		outb(reg | TOPAZ_ASR_TOGGLE | TOPAZ_ASR_DISABLE,
		     asr_पढ़ो_addr);
	अन्यथा अणु
		outb(reg | asr_toggle_mask, asr_ग_लिखो_addr);
		reg = inb(asr_पढ़ो_addr);

		outb(reg | asr_disable_mask, asr_ग_लिखो_addr);
	पूर्ण
	reg = inb(asr_पढ़ो_addr);
	spin_unlock(&asr_lock);
पूर्ण

अटल पूर्णांक __init asr_get_base_address(व्योम)
अणु
	अचिन्हित अक्षर low, high;
	स्थिर अक्षर *type = "";

	asr_length = 1;

	चयन (asr_type) अणु
	हाल ASMTYPE_TOPAZ:
		/* SELECT SuperIO CHIP FOR QUERYING
		   (WRITE 0x07 TO BOTH 0x2E and 0x2F) */
		outb(0x07, 0x2e);
		outb(0x07, 0x2f);

		/* SELECT AND READ THE HIGH-NIBBLE OF THE GPIO BASE ADDRESS */
		outb(0x60, 0x2e);
		high = inb(0x2f);

		/* SELECT AND READ THE LOW-NIBBLE OF THE GPIO BASE ADDRESS */
		outb(0x61, 0x2e);
		low = inb(0x2f);

		asr_base = (high << 16) | low;
		asr_पढ़ो_addr = asr_ग_लिखो_addr =
			asr_base + TOPAZ_ASR_REG_OFFSET;
		asr_length = 5;

		अवरोध;

	हाल ASMTYPE_JASPER:
		type = "Jaspers ";
#अगर 0
		u32 r;
		/* Suggested fix */
		pdev = pci_get_bus_and_slot(0, DEVFN(0x1f, 0));
		अगर (pdev == शून्य)
			वापस -ENODEV;
		pci_पढ़ो_config_dword(pdev, 0x58, &r);
		asr_base = r & 0xFFFE;
		pci_dev_put(pdev);
#अन्यथा
		/* FIXME: need to use pci_config_lock here,
		   but it's not exported */

/*		spin_lock_irqsave(&pci_config_lock, flags);*/

		/* Select the SuperIO chip in the PCI I/O port रेजिस्टर */
		outl(0x8000f858, 0xcf8);

		/* BUS 0, Slot 1F, fnc 0, offset 58 */

		/*
		 * Read the base address क्रम the SuperIO chip.
		 * Only the lower 16 bits are valid, but the address is word
		 * aligned so the last bit must be masked off.
		 */
		asr_base = inl(0xcfc) & 0xfffe;

/*		spin_unlock_irqrestore(&pci_config_lock, flags);*/
#पूर्ण_अगर
		asr_पढ़ो_addr = asr_ग_लिखो_addr =
			asr_base + JASPER_ASR_REG_OFFSET;
		asr_toggle_mask = JASPER_ASR_TOGGLE_MASK;
		asr_disable_mask = JASPER_ASR_DISABLE_MASK;
		asr_length = JASPER_ASR_REG_OFFSET + 1;

		अवरोध;

	हाल ASMTYPE_PEARL:
		type = "Pearls ";
		asr_base = PEARL_BASE;
		asr_पढ़ो_addr = PEARL_READ;
		asr_ग_लिखो_addr = PEARL_WRITE;
		asr_toggle_mask = PEARL_ASR_TOGGLE_MASK;
		asr_disable_mask = PEARL_ASR_DISABLE_MASK;
		asr_length = 4;
		अवरोध;

	हाल ASMTYPE_JUNIPER:
		type = "Junipers ";
		asr_base = JUNIPER_BASE_ADDRESS;
		asr_पढ़ो_addr = asr_ग_लिखो_addr = asr_base;
		asr_toggle_mask = JUNIPER_ASR_TOGGLE_MASK;
		asr_disable_mask = JUNIPER_ASR_DISABLE_MASK;
		अवरोध;

	हाल ASMTYPE_SPRUCE:
		type = "Spruce's ";
		asr_base = SPRUCE_BASE_ADDRESS;
		asr_पढ़ो_addr = asr_ग_लिखो_addr = asr_base;
		asr_toggle_mask = SPRUCE_ASR_TOGGLE_MASK;
		asr_disable_mask = SPRUCE_ASR_DISABLE_MASK;
		अवरोध;
	पूर्ण

	अगर (!request_region(asr_base, asr_length, "ibmasr")) अणु
		pr_err("address %#x already in use\n", asr_base);
		वापस -EBUSY;
	पूर्ण

	pr_info("found %sASR @ addr %#x\n", type, asr_base);

	वापस 0;
पूर्ण


अटल sमाप_प्रकार asr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			asr_expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					asr_expect_बंद = 42;
			पूर्ण
		पूर्ण
		asr_toggle();
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ asr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =	WDIOF_KEEPALIVEPING |
				WDIOF_MAGICCLOSE,
		.identity =	"IBM ASR",
	पूर्ण;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक heartbeat;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक new_options, retval = -EINVAL;
		अगर (get_user(new_options, p))
			वापस -EFAULT;
		अगर (new_options & WDIOS_DISABLECARD) अणु
			asr_disable();
			retval = 0;
		पूर्ण
		अगर (new_options & WDIOS_ENABLECARD) अणु
			asr_enable();
			asr_toggle();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		asr_toggle();
		वापस 0;
	/*
	 * The hardware has a fixed समयout value, so no WDIOC_SETTIMEOUT
	 * and WDIOC_GETTIMEOUT always वापसs 256.
	 */
	हाल WDIOC_GETTIMEOUT:
		heartbeat = 256;
		वापस put_user(heartbeat, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक asr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &asr_is_खोलो))
		वापस -EBUSY;

	asr_toggle();
	asr_enable();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक asr_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (asr_expect_बंद == 42)
		asr_disable();
	अन्यथा अणु
		pr_crit("unexpected close, not stopping watchdog!\n");
		asr_toggle();
	पूर्ण
	clear_bit(0, &asr_is_खोलो);
	asr_expect_बंद = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations asr_fops = अणु
	.owner =		THIS_MODULE,
	.llseek =		no_llseek,
	.ग_लिखो =		asr_ग_लिखो,
	.unlocked_ioctl =	asr_ioctl,
	.compat_ioctl =		compat_ptr_ioctl,
	.खोलो =			asr_खोलो,
	.release =		asr_release,
पूर्ण;

अटल काष्ठा miscdevice asr_miscdev = अणु
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&asr_fops,
पूर्ण;


काष्ठा ibmasr_id अणु
	स्थिर अक्षर *desc;
	पूर्णांक type;
पूर्ण;

अटल काष्ठा ibmasr_id ibmasr_id_table[] __initdata = अणु
	अणु "IBM Automatic Server Restart - eserver xSeries 220", ASMTYPE_TOPAZ पूर्ण,
	अणु "IBM Automatic Server Restart - Machine Type 8673", ASMTYPE_PEARL पूर्ण,
	अणु "IBM Automatic Server Restart - Machine Type 8480", ASMTYPE_JASPER पूर्ण,
	अणु "IBM Automatic Server Restart - Machine Type 8482", ASMTYPE_JUNIPER पूर्ण,
	अणु "IBM Automatic Server Restart - Machine Type 8648", ASMTYPE_SPRUCE पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल पूर्णांक __init ibmasr_init(व्योम)
अणु
	काष्ठा ibmasr_id *id;
	पूर्णांक rc;

	क्रम (id = ibmasr_id_table; id->desc; id++) अणु
		अगर (dmi_find_device(DMI_DEV_TYPE_OTHER, id->desc, शून्य)) अणु
			asr_type = id->type;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!asr_type)
		वापस -ENODEV;

	rc = asr_get_base_address();
	अगर (rc)
		वापस rc;

	rc = misc_रेजिस्टर(&asr_miscdev);
	अगर (rc < 0) अणु
		release_region(asr_base, asr_length);
		pr_err("failed to register misc device\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास ibmasr_निकास(व्योम)
अणु
	अगर (!nowayout)
		asr_disable();

	misc_deरेजिस्टर(&asr_miscdev);

	release_region(asr_base, asr_length);
पूर्ण

module_init(ibmasr_init);
module_निकास(ibmasr_निकास);

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_DESCRIPTION("IBM Automatic Server Restart driver");
MODULE_AUTHOR("Andrey Panin");
MODULE_LICENSE("GPL");
