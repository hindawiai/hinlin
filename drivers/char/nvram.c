<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CMOS/NV-RAM driver क्रम Linux
 *
 * Copyright (C) 1997 Roman Hodek <Roman.Hodek@inक्रमmatik.uni-erlangen.de>
 * idea by and with help from Riअक्षरd Jelinek <rj@suse.de>
 * Portions copyright (c) 2001,2002 Sun Microप्रणालीs (thockin@sun.com)
 *
 * This driver allows you to access the contents of the non-अस्थिर memory in
 * the mc146818rtc.h real-समय घड़ी. This chip is built पूर्णांकo all PCs and पूर्णांकo
 * many Atari machines. In the क्रमmer it's called "CMOS-RAM", in the latter
 * "NVRAM" (NV stands क्रम non-अस्थिर).
 *
 * The data are supplied as a (seekable) अक्षरacter device, /dev/nvram. The
 * size of this file is dependent on the controller.  The usual size is 114,
 * the number of मुक्तly available bytes in the memory (i.e., not used by the
 * RTC itself).
 *
 * Checksums over the NVRAM contents are managed by this driver. In हाल of a
 * bad checksum, पढ़ोs and ग_लिखोs वापस -EIO. The checksum can be initialized
 * to a sane state either by ioctl(NVRAM_INIT) (clear whole NVRAM) or
 * ioctl(NVRAM_SETCKS) (करोesn't change contents, just makes checksum valid
 * again; use with care!)
 *
 * 	1.1	Cesar Barros: SMP locking fixes
 * 		added changelog
 * 	1.2	Erik Gilling: Cobalt Networks support
 * 		Tim Hockin: general cleanup, Cobalt support
 * 	1.3	Wim Van Sebroeck: convert PRINT_PROC to seq_file
 */

#घोषणा NVRAM_VERSION	"1.3"

#समावेश <linux/module.h>
#समावेश <linux/nvram.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/ioport.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>

#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/nvram.h>
#पूर्ण_अगर

अटल DEFINE_MUTEX(nvram_mutex);
अटल DEFINE_SPINLOCK(nvram_state_lock);
अटल पूर्णांक nvram_खोलो_cnt;	/* #बार खोलोed */
अटल पूर्णांक nvram_खोलो_mode;	/* special खोलो modes */
अटल sमाप_प्रकार nvram_size;
#घोषणा NVRAM_WRITE		1 /* खोलोed क्रम writing (exclusive) */
#घोषणा NVRAM_EXCL		2 /* खोलोed with O_EXCL */

#अगर_घोषित CONFIG_X86
/*
 * These functions are provided to be called पूर्णांकernally or by other parts of
 * the kernel. It's up to the caller to ensure correct checksum beक्रमe पढ़ोing
 * or after writing (needs to be करोne only once).
 *
 * It is worth noting that these functions all access bytes of general
 * purpose memory in the NVRAM - that is to say, they all add the
 * NVRAM_FIRST_BYTE offset.  Pass them offsets पूर्णांकo NVRAM as अगर you did not
 * know about the RTC cruft.
 */

#घोषणा NVRAM_BYTES		(128 - NVRAM_FIRST_BYTE)

/* Note that *all* calls to CMOS_READ and CMOS_WRITE must be करोne with
 * rtc_lock held. Due to the index-port/data-port design of the RTC, we
 * करोn't want two dअगरferent things trying to get to it at once. (e.g. the
 * periodic 11 min sync from kernel/समय/ntp.c vs. this driver.)
 */

अटल अचिन्हित अक्षर __nvram_पढ़ो_byte(पूर्णांक i)
अणु
	वापस CMOS_READ(NVRAM_FIRST_BYTE + i);
पूर्ण

अटल अचिन्हित अक्षर pc_nvram_पढ़ो_byte(पूर्णांक i)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर c;

	spin_lock_irqsave(&rtc_lock, flags);
	c = __nvram_पढ़ो_byte(i);
	spin_unlock_irqrestore(&rtc_lock, flags);
	वापस c;
पूर्ण

/* This races nicely with trying to पढ़ो with checksum checking (nvram_पढ़ो) */
अटल व्योम __nvram_ग_लिखो_byte(अचिन्हित अक्षर c, पूर्णांक i)
अणु
	CMOS_WRITE(c, NVRAM_FIRST_BYTE + i);
पूर्ण

अटल व्योम pc_nvram_ग_लिखो_byte(अचिन्हित अक्षर c, पूर्णांक i)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc_lock, flags);
	__nvram_ग_लिखो_byte(c, i);
	spin_unlock_irqrestore(&rtc_lock, flags);
पूर्ण

/* On PCs, the checksum is built only over bytes 2..31 */
#घोषणा PC_CKS_RANGE_START	2
#घोषणा PC_CKS_RANGE_END	31
#घोषणा PC_CKS_LOC		32

अटल पूर्णांक __nvram_check_checksum(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित लघु sum = 0;
	अचिन्हित लघु expect;

	क्रम (i = PC_CKS_RANGE_START; i <= PC_CKS_RANGE_END; ++i)
		sum += __nvram_पढ़ो_byte(i);
	expect = __nvram_पढ़ो_byte(PC_CKS_LOC)<<8 |
	    __nvram_पढ़ो_byte(PC_CKS_LOC+1);
	वापस (sum & 0xffff) == expect;
पूर्ण

अटल व्योम __nvram_set_checksum(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित लघु sum = 0;

	क्रम (i = PC_CKS_RANGE_START; i <= PC_CKS_RANGE_END; ++i)
		sum += __nvram_पढ़ो_byte(i);
	__nvram_ग_लिखो_byte(sum >> 8, PC_CKS_LOC);
	__nvram_ग_लिखो_byte(sum & 0xff, PC_CKS_LOC + 1);
पूर्ण

अटल दीर्घ pc_nvram_set_checksum(व्योम)
अणु
	spin_lock_irq(&rtc_lock);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);
	वापस 0;
पूर्ण

अटल दीर्घ pc_nvram_initialize(व्योम)
अणु
	sमाप_प्रकार i;

	spin_lock_irq(&rtc_lock);
	क्रम (i = 0; i < NVRAM_BYTES; ++i)
		__nvram_ग_लिखो_byte(0, i);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार pc_nvram_get_size(व्योम)
अणु
	वापस NVRAM_BYTES;
पूर्ण

अटल sमाप_प्रकार pc_nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *p = buf;
	loff_t i;

	spin_lock_irq(&rtc_lock);
	अगर (!__nvram_check_checksum()) अणु
		spin_unlock_irq(&rtc_lock);
		वापस -EIO;
	पूर्ण
	क्रम (i = *ppos; count > 0 && i < NVRAM_BYTES; --count, ++i, ++p)
		*p = __nvram_पढ़ो_byte(i);
	spin_unlock_irq(&rtc_lock);

	*ppos = i;
	वापस p - buf;
पूर्ण

अटल sमाप_प्रकार pc_nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *p = buf;
	loff_t i;

	spin_lock_irq(&rtc_lock);
	अगर (!__nvram_check_checksum()) अणु
		spin_unlock_irq(&rtc_lock);
		वापस -EIO;
	पूर्ण
	क्रम (i = *ppos; count > 0 && i < NVRAM_BYTES; --count, ++i, ++p)
		__nvram_ग_लिखो_byte(*p, i);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);

	*ppos = i;
	वापस p - buf;
पूर्ण

स्थिर काष्ठा nvram_ops arch_nvram_ops = अणु
	.पढ़ो           = pc_nvram_पढ़ो,
	.ग_लिखो          = pc_nvram_ग_लिखो,
	.पढ़ो_byte      = pc_nvram_पढ़ो_byte,
	.ग_लिखो_byte     = pc_nvram_ग_लिखो_byte,
	.get_size       = pc_nvram_get_size,
	.set_checksum   = pc_nvram_set_checksum,
	.initialize     = pc_nvram_initialize,
पूर्ण;
EXPORT_SYMBOL(arch_nvram_ops);
#पूर्ण_अगर /* CONFIG_X86 */

/*
 * The are the file operation function क्रम user access to /dev/nvram
 */

अटल loff_t nvram_misc_llseek(काष्ठा file *file, loff_t offset, पूर्णांक origin)
अणु
	वापस generic_file_llseek_size(file, offset, origin, MAX_LFS_खाताSIZE,
					nvram_size);
पूर्ण

अटल sमाप_प्रकार nvram_misc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *पंचांगp;
	sमाप_प्रकार ret;


	अगर (*ppos >= nvram_size)
		वापस 0;

	count = min_t(माप_प्रकार, count, nvram_size - *ppos);
	count = min_t(माप_प्रकार, count, PAGE_SIZE);

	पंचांगp = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	ret = nvram_पढ़ो(पंचांगp, count, ppos);
	अगर (ret <= 0)
		जाओ out;

	अगर (copy_to_user(buf, पंचांगp, ret)) अणु
		*ppos -= ret;
		ret = -EFAULT;
	पूर्ण

out:
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार nvram_misc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *पंचांगp;
	sमाप_प्रकार ret;

	अगर (*ppos >= nvram_size)
		वापस 0;

	count = min_t(माप_प्रकार, count, nvram_size - *ppos);
	count = min_t(माप_प्रकार, count, PAGE_SIZE);

	पंचांगp = memdup_user(buf, count);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	ret = nvram_ग_लिखो(पंचांगp, count, ppos);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल दीर्घ nvram_misc_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret = -ENOTTY;

	चयन (cmd) अणु
#अगर_घोषित CONFIG_PPC
	हाल OBSOLETE_PMAC_NVRAM_GET_OFFSET:
		pr_warn("nvram: Using obsolete PMAC_NVRAM_GET_OFFSET ioctl\n");
		fallthrough;
	हाल IOC_NVRAM_GET_OFFSET:
		ret = -EINVAL;
#अगर_घोषित CONFIG_PPC_PMAC
		अगर (machine_is(घातermac)) अणु
			पूर्णांक part, offset;

			अगर (copy_from_user(&part, (व्योम __user *)arg,
					   माप(part)) != 0)
				वापस -EFAULT;
			अगर (part < pmac_nvram_OF || part > pmac_nvram_NR)
				वापस -EINVAL;
			offset = pmac_get_partition(part);
			अगर (offset < 0)
				वापस -EINVAL;
			अगर (copy_to_user((व्योम __user *)arg,
					 &offset, माप(offset)) != 0)
				वापस -EFAULT;
			ret = 0;
		पूर्ण
#पूर्ण_अगर
		अवरोध;
#अगर_घोषित CONFIG_PPC32
	हाल IOC_NVRAM_SYNC:
		अगर (ppc_md.nvram_sync != शून्य) अणु
			mutex_lock(&nvram_mutex);
			ppc_md.nvram_sync();
			mutex_unlock(&nvram_mutex);
		पूर्ण
		ret = 0;
		अवरोध;
#पूर्ण_अगर
#या_अगर defined(CONFIG_X86) || defined(CONFIG_M68K)
	हाल NVRAM_INIT:
		/* initialize NVRAM contents and checksum */
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;

		अगर (arch_nvram_ops.initialize != शून्य) अणु
			mutex_lock(&nvram_mutex);
			ret = arch_nvram_ops.initialize();
			mutex_unlock(&nvram_mutex);
		पूर्ण
		अवरोध;
	हाल NVRAM_SETCKS:
		/* just set checksum, contents unchanged (maybe useful after
		 * checksum garbaged somehow...) */
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;

		अगर (arch_nvram_ops.set_checksum != शून्य) अणु
			mutex_lock(&nvram_mutex);
			ret = arch_nvram_ops.set_checksum();
			mutex_unlock(&nvram_mutex);
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_X86 || CONFIG_M68K */
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nvram_misc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&nvram_state_lock);

	/* Prevent multiple पढ़ोers/ग_लिखोrs अगर desired. */
	अगर ((nvram_खोलो_cnt && (file->f_flags & O_EXCL)) ||
	    (nvram_खोलो_mode & NVRAM_EXCL)) अणु
		spin_unlock(&nvram_state_lock);
		वापस -EBUSY;
	पूर्ण

#अगर defined(CONFIG_X86) || defined(CONFIG_M68K)
	/* Prevent multiple ग_लिखोrs अगर the set_checksum ioctl is implemented. */
	अगर ((arch_nvram_ops.set_checksum != शून्य) &&
	    (file->f_mode & FMODE_WRITE) && (nvram_खोलो_mode & NVRAM_WRITE)) अणु
		spin_unlock(&nvram_state_lock);
		वापस -EBUSY;
	पूर्ण
#पूर्ण_अगर

	अगर (file->f_flags & O_EXCL)
		nvram_खोलो_mode |= NVRAM_EXCL;
	अगर (file->f_mode & FMODE_WRITE)
		nvram_खोलो_mode |= NVRAM_WRITE;
	nvram_खोलो_cnt++;

	spin_unlock(&nvram_state_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक nvram_misc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&nvram_state_lock);

	nvram_खोलो_cnt--;

	/* अगर only one instance is खोलो, clear the EXCL bit */
	अगर (nvram_खोलो_mode & NVRAM_EXCL)
		nvram_खोलो_mode &= ~NVRAM_EXCL;
	अगर (file->f_mode & FMODE_WRITE)
		nvram_खोलो_mode &= ~NVRAM_WRITE;

	spin_unlock(&nvram_state_lock);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_X86) && defined(CONFIG_PROC_FS)
अटल स्थिर अक्षर * स्थिर floppy_types[] = अणु
	"none", "5.25'' 360k", "5.25'' 1.2M", "3.5'' 720k", "3.5'' 1.44M",
	"3.5'' 2.88M", "3.5'' 2.88M"
पूर्ण;

अटल स्थिर अक्षर * स्थिर gfx_types[] = अणु
	"EGA, VGA, ... (with BIOS)",
	"CGA (40 cols)",
	"CGA (80 cols)",
	"monochrome",
पूर्ण;

अटल व्योम pc_nvram_proc_पढ़ो(अचिन्हित अक्षर *nvram, काष्ठा seq_file *seq,
			       व्योम *offset)
अणु
	पूर्णांक checksum;
	पूर्णांक type;

	spin_lock_irq(&rtc_lock);
	checksum = __nvram_check_checksum();
	spin_unlock_irq(&rtc_lock);

	seq_म_लिखो(seq, "Checksum status: %svalid\n", checksum ? "" : "not ");

	seq_म_लिखो(seq, "# floppies     : %d\n",
	    (nvram[6] & 1) ? (nvram[6] >> 6) + 1 : 0);
	seq_म_लिखो(seq, "Floppy 0 type  : ");
	type = nvram[2] >> 4;
	अगर (type < ARRAY_SIZE(floppy_types))
		seq_म_लिखो(seq, "%s\n", floppy_types[type]);
	अन्यथा
		seq_म_लिखो(seq, "%d (unknown)\n", type);
	seq_म_लिखो(seq, "Floppy 1 type  : ");
	type = nvram[2] & 0x0f;
	अगर (type < ARRAY_SIZE(floppy_types))
		seq_म_लिखो(seq, "%s\n", floppy_types[type]);
	अन्यथा
		seq_म_लिखो(seq, "%d (unknown)\n", type);

	seq_म_लिखो(seq, "HD 0 type      : ");
	type = nvram[4] >> 4;
	अगर (type)
		seq_म_लिखो(seq, "%02x\n", type == 0x0f ? nvram[11] : type);
	अन्यथा
		seq_म_लिखो(seq, "none\n");

	seq_म_लिखो(seq, "HD 1 type      : ");
	type = nvram[4] & 0x0f;
	अगर (type)
		seq_म_लिखो(seq, "%02x\n", type == 0x0f ? nvram[12] : type);
	अन्यथा
		seq_म_लिखो(seq, "none\n");

	seq_म_लिखो(seq, "HD type 48 data: %d/%d/%d C/H/S, precomp %d, lz %d\n",
	    nvram[18] | (nvram[19] << 8),
	    nvram[20], nvram[25],
	    nvram[21] | (nvram[22] << 8), nvram[23] | (nvram[24] << 8));
	seq_म_लिखो(seq, "HD type 49 data: %d/%d/%d C/H/S, precomp %d, lz %d\n",
	    nvram[39] | (nvram[40] << 8),
	    nvram[41], nvram[46],
	    nvram[42] | (nvram[43] << 8), nvram[44] | (nvram[45] << 8));

	seq_म_लिखो(seq, "DOS base memory: %d kB\n", nvram[7] | (nvram[8] << 8));
	seq_म_लिखो(seq, "Extended memory: %d kB (configured), %d kB (tested)\n",
	    nvram[9] | (nvram[10] << 8), nvram[34] | (nvram[35] << 8));

	seq_म_लिखो(seq, "Gfx adapter    : %s\n",
	    gfx_types[(nvram[6] >> 4) & 3]);

	seq_म_लिखो(seq, "FPU            : %sinstalled\n",
	    (nvram[6] & 2) ? "" : "not ");

	वापस;
पूर्ण

अटल पूर्णांक nvram_proc_पढ़ो(काष्ठा seq_file *seq, व्योम *offset)
अणु
	अचिन्हित अक्षर contents[NVRAM_BYTES];
	पूर्णांक i = 0;

	spin_lock_irq(&rtc_lock);
	क्रम (i = 0; i < NVRAM_BYTES; ++i)
		contents[i] = __nvram_पढ़ो_byte(i);
	spin_unlock_irq(&rtc_lock);

	pc_nvram_proc_पढ़ो(contents, seq, offset);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86 && CONFIG_PROC_FS */

अटल स्थिर काष्ठा file_operations nvram_misc_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= nvram_misc_llseek,
	.पढ़ो		= nvram_misc_पढ़ो,
	.ग_लिखो		= nvram_misc_ग_लिखो,
	.unlocked_ioctl	= nvram_misc_ioctl,
	.खोलो		= nvram_misc_खोलो,
	.release	= nvram_misc_release,
पूर्ण;

अटल काष्ठा miscdevice nvram_misc = अणु
	NVRAM_MINOR,
	"nvram",
	&nvram_misc_fops,
पूर्ण;

अटल पूर्णांक __init nvram_module_init(व्योम)
अणु
	पूर्णांक ret;

	nvram_size = nvram_get_size();
	अगर (nvram_size < 0)
		वापस nvram_size;

	ret = misc_रेजिस्टर(&nvram_misc);
	अगर (ret) अणु
		pr_err("nvram: can't misc_register on minor=%d\n", NVRAM_MINOR);
		वापस ret;
	पूर्ण

#अगर defined(CONFIG_X86) && defined(CONFIG_PROC_FS)
	अगर (!proc_create_single("driver/nvram", 0, शून्य, nvram_proc_पढ़ो)) अणु
		pr_err("nvram: can't create /proc/driver/nvram\n");
		misc_deरेजिस्टर(&nvram_misc);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	pr_info("Non-volatile memory driver v" NVRAM_VERSION "\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास nvram_module_निकास(व्योम)
अणु
#अगर defined(CONFIG_X86) && defined(CONFIG_PROC_FS)
	हटाओ_proc_entry("driver/nvram", शून्य);
#पूर्ण_अगर
	misc_deरेजिस्टर(&nvram_misc);
पूर्ण

module_init(nvram_module_init);
module_निकास(nvram_module_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(NVRAM_MINOR);
MODULE_ALIAS("devname:nvram");
