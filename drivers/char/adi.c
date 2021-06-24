<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Privileged ADI driver क्रम sparc64
 *
 * Author: Tom Hromatka <tom.hromatka@oracle.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/asi.h>

#घोषणा MAX_BUF_SZ	PAGE_SIZE

अटल पूर्णांक adi_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->f_mode |= FMODE_UNSIGNED_OFFSET;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_mcd_tag(अचिन्हित दीर्घ addr)
अणु
	दीर्घ err;
	पूर्णांक ver;

	__यंत्र__ __अस्थिर__(
		"1:	ldxa [%[addr]] %[asi], %[ver]\n"
		"	mov 0, %[err]\n"
		"2:\n"
		"	.section .fixup,#alloc,#execinstr\n"
		"	.align 4\n"
		"3:	sethi %%hi(2b), %%g1\n"
		"	jmpl  %%g1 + %%lo(2b), %%g0\n"
		"	mov %[invalid], %[err]\n"
		"	.previous\n"
		"	.section __ex_table, \"a\"\n"
		"	.align 4\n"
		"	.word  1b, 3b\n"
		"	.previous\n"
		: [ver] "=r" (ver), [err] "=r" (err)
		: [addr] "r"  (addr), [invalid] "i" (EFAULT),
		  [asi] "i" (ASI_MCD_REAL)
		: "memory", "g1"
		);

	अगर (err)
		वापस -EFAULT;
	अन्यथा
		वापस ver;
पूर्ण

अटल sमाप_प्रकार adi_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *offp)
अणु
	माप_प्रकार ver_buf_sz, bytes_पढ़ो = 0;
	पूर्णांक ver_buf_idx = 0;
	loff_t offset;
	u8 *ver_buf;
	sमाप_प्रकार ret;

	ver_buf_sz = min_t(माप_प्रकार, count, MAX_BUF_SZ);
	ver_buf = kदो_स्मृति(ver_buf_sz, GFP_KERNEL);
	अगर (!ver_buf)
		वापस -ENOMEM;

	offset = (*offp) * adi_blksize();

	जबतक (bytes_पढ़ो < count) अणु
		ret = पढ़ो_mcd_tag(offset);
		अगर (ret < 0)
			जाओ out;

		ver_buf[ver_buf_idx] = (u8)ret;
		ver_buf_idx++;
		offset += adi_blksize();

		अगर (ver_buf_idx >= ver_buf_sz) अणु
			अगर (copy_to_user(buf + bytes_पढ़ो, ver_buf,
					 ver_buf_sz)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण

			bytes_पढ़ो += ver_buf_sz;
			ver_buf_idx = 0;

			ver_buf_sz = min(count - bytes_पढ़ो,
					 (माप_प्रकार)MAX_BUF_SZ);
		पूर्ण
	पूर्ण

	(*offp) += bytes_पढ़ो;
	ret = bytes_पढ़ो;
out:
	kमुक्त(ver_buf);
	वापस ret;
पूर्ण

अटल पूर्णांक set_mcd_tag(अचिन्हित दीर्घ addr, u8 ver)
अणु
	दीर्घ err;

	__यंत्र__ __अस्थिर__(
		"1:	stxa %[ver], [%[addr]] %[asi]\n"
		"	mov 0, %[err]\n"
		"2:\n"
		"	.section .fixup,#alloc,#execinstr\n"
		"	.align 4\n"
		"3:	sethi %%hi(2b), %%g1\n"
		"	jmpl %%g1 + %%lo(2b), %%g0\n"
		"	mov %[invalid], %[err]\n"
		"	.previous\n"
		"	.section __ex_table, \"a\"\n"
		"	.align 4\n"
		"	.word 1b, 3b\n"
		"	.previous\n"
		: [err] "=r" (err)
		: [ver] "r" (ver), [addr] "r"  (addr),
		  [invalid] "i" (EFAULT), [asi] "i" (ASI_MCD_REAL)
		: "memory", "g1"
		);

	अगर (err)
		वापस -EFAULT;
	अन्यथा
		वापस ver;
पूर्ण

अटल sमाप_प्रकार adi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *offp)
अणु
	माप_प्रकार ver_buf_sz, bytes_written = 0;
	loff_t offset;
	u8 *ver_buf;
	sमाप_प्रकार ret;
	पूर्णांक i;

	अगर (count <= 0)
		वापस -EINVAL;

	ver_buf_sz = min_t(माप_प्रकार, count, MAX_BUF_SZ);
	ver_buf = kदो_स्मृति(ver_buf_sz, GFP_KERNEL);
	अगर (!ver_buf)
		वापस -ENOMEM;

	offset = (*offp) * adi_blksize();

	करो अणु
		अगर (copy_from_user(ver_buf, &buf[bytes_written],
				   ver_buf_sz)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < ver_buf_sz; i++) अणु
			ret = set_mcd_tag(offset, ver_buf[i]);
			अगर (ret < 0)
				जाओ out;

			offset += adi_blksize();
		पूर्ण

		bytes_written += ver_buf_sz;
		ver_buf_sz = min(count - bytes_written, (माप_प्रकार)MAX_BUF_SZ);
	पूर्ण जबतक (bytes_written < count);

	(*offp) += bytes_written;
	ret = bytes_written;
out:
	__यंत्र__ __अस्थिर__("membar #Sync");
	kमुक्त(ver_buf);
	वापस ret;
पूर्ण

अटल loff_t adi_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	loff_t ret = -EINVAL;

	चयन (whence) अणु
	हाल अंत_से:
	हाल SEEK_DATA:
	हाल SEEK_HOLE:
		/* unsupported */
		वापस -EINVAL;
	हाल प्रस्तुत_से:
		अगर (offset == 0)
			वापस file->f_pos;

		offset += file->f_pos;
		अवरोध;
	हाल शुरू_से:
		अवरोध;
	पूर्ण

	अगर (offset != file->f_pos) अणु
		file->f_pos = offset;
		file->f_version = 0;
		ret = offset;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations adi_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= adi_llseek,
	.खोलो		= adi_खोलो,
	.पढ़ो		= adi_पढ़ो,
	.ग_लिखो		= adi_ग_लिखो,
पूर्ण;

अटल काष्ठा miscdevice adi_miscdev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = KBUILD_MODNAME,
	.fops = &adi_fops,
पूर्ण;

अटल पूर्णांक __init adi_init(व्योम)
अणु
	अगर (!adi_capable())
		वापस -EPERM;

	वापस misc_रेजिस्टर(&adi_miscdev);
पूर्ण

अटल व्योम __निकास adi_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&adi_miscdev);
पूर्ण

module_init(adi_init);
module_निकास(adi_निकास);

MODULE_AUTHOR("Tom Hromatka <tom.hromatka@oracle.com>");
MODULE_DESCRIPTION("Privileged interface to ADI");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL v2");
