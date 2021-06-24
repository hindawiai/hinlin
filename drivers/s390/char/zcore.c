<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * zcore module to export memory content and रेजिस्टर sets क्रम creating प्रणाली
 * dumps on SCSI/NVMe disks (zfcp/nvme dump).
 *
 * For more inक्रमmation please refer to Documentation/s390/zfcpdump.rst
 *
 * Copyright IBM Corp. 2003, 2008
 * Author(s): Michael Holzheu
 */

#घोषणा KMSG_COMPONENT "zdump"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/irqflags.h>
#समावेश <यंत्र/checksum.h>
#समावेश <यंत्र/os_info.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश "sclp.h"

#घोषणा TRACE(x...) debug_प्र_लिखो_event(zcore_dbf, 1, x)

क्रमागत arch_id अणु
	ARCH_S390	= 0,
	ARCH_S390X	= 1,
पूर्ण;

काष्ठा ipib_info अणु
	अचिन्हित दीर्घ	ipib;
	u32		checksum;
पूर्ण  __attribute__((packed));

अटल काष्ठा debug_info *zcore_dbf;
अटल पूर्णांक hsa_available;
अटल काष्ठा dentry *zcore_dir;
अटल काष्ठा dentry *zcore_reipl_file;
अटल काष्ठा dentry *zcore_hsa_file;
अटल काष्ठा ipl_parameter_block *zcore_ipl_block;

अटल अक्षर hsa_buf[PAGE_SIZE] __aligned(PAGE_SIZE);

/*
 * Copy memory from HSA to user memory (not reentrant):
 *
 * @dest:  User buffer where memory should be copied to
 * @src:   Start address within HSA where data should be copied
 * @count: Size of buffer, which should be copied
 */
पूर्णांक स_नकल_hsa_user(व्योम __user *dest, अचिन्हित दीर्घ src, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ offset, bytes;

	अगर (!hsa_available)
		वापस -ENODATA;

	जबतक (count) अणु
		अगर (sclp_sdias_copy(hsa_buf, src / PAGE_SIZE + 2, 1)) अणु
			TRACE("sclp_sdias_copy() failed\n");
			वापस -EIO;
		पूर्ण
		offset = src % PAGE_SIZE;
		bytes = min(PAGE_SIZE - offset, count);
		अगर (copy_to_user(dest, hsa_buf + offset, bytes))
			वापस -EFAULT;
		src += bytes;
		dest += bytes;
		count -= bytes;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Copy memory from HSA to kernel memory (not reentrant):
 *
 * @dest:  Kernel or user buffer where memory should be copied to
 * @src:   Start address within HSA where data should be copied
 * @count: Size of buffer, which should be copied
 */
पूर्णांक स_नकल_hsa_kernel(व्योम *dest, अचिन्हित दीर्घ src, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ offset, bytes;

	अगर (!hsa_available)
		वापस -ENODATA;

	जबतक (count) अणु
		अगर (sclp_sdias_copy(hsa_buf, src / PAGE_SIZE + 2, 1)) अणु
			TRACE("sclp_sdias_copy() failed\n");
			वापस -EIO;
		पूर्ण
		offset = src % PAGE_SIZE;
		bytes = min(PAGE_SIZE - offset, count);
		स_नकल(dest, hsa_buf + offset, bytes);
		src += bytes;
		dest += bytes;
		count -= bytes;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init init_cpu_info(व्योम)
अणु
	काष्ठा save_area *sa;

	/* get info क्रम boot cpu from lowcore, stored in the HSA */
	sa = save_area_boot_cpu();
	अगर (!sa)
		वापस -ENOMEM;
	अगर (स_नकल_hsa_kernel(hsa_buf, __LC_FPREGS_SAVE_AREA, 512) < 0) अणु
		TRACE("could not copy from HSA\n");
		वापस -EIO;
	पूर्ण
	save_area_add_regs(sa, hsa_buf); /* vx रेजिस्टरs are saved in smp.c */
	वापस 0;
पूर्ण

/*
 * Release the HSA
 */
अटल व्योम release_hsa(व्योम)
अणु
	diag308(DIAG308_REL_HSA, शून्य);
	hsa_available = 0;
पूर्ण

अटल sमाप_प्रकार zcore_reipl_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	अगर (zcore_ipl_block) अणु
		diag308(DIAG308_SET, zcore_ipl_block);
		diag308(DIAG308_LOAD_CLEAR, शून्य);
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक zcore_reipl_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस stream_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक zcore_reipl_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations zcore_reipl_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= zcore_reipl_ग_लिखो,
	.खोलो		= zcore_reipl_खोलो,
	.release	= zcore_reipl_release,
	.llseek		= no_llseek,
पूर्ण;

अटल sमाप_प्रकार zcore_hsa_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अटल अक्षर str[18];

	अगर (hsa_available)
		snम_लिखो(str, माप(str), "%lx\n", sclp.hsa_size);
	अन्यथा
		snम_लिखो(str, माप(str), "0\n");
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, str, म_माप(str));
पूर्ण

अटल sमाप_प्रकार zcore_hsa_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर value;

	अगर (*ppos != 0)
		वापस -EPIPE;
	अगर (copy_from_user(&value, buf, 1))
		वापस -EFAULT;
	अगर (value != '0')
		वापस -EINVAL;
	release_hsa();
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations zcore_hsa_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= zcore_hsa_ग_लिखो,
	.पढ़ो		= zcore_hsa_पढ़ो,
	.खोलो		= nonseekable_खोलो,
	.llseek		= no_llseek,
पूर्ण;

अटल पूर्णांक __init check_sdias(व्योम)
अणु
	अगर (!sclp.hsa_size) अणु
		TRACE("Could not determine HSA size\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Provide IPL parameter inक्रमmation block from either HSA or memory
 * क्रम future reipl
 */
अटल पूर्णांक __init zcore_reipl_init(व्योम)
अणु
	काष्ठा ipib_info ipib_info;
	पूर्णांक rc;

	rc = स_नकल_hsa_kernel(&ipib_info, __LC_DUMP_REIPL, माप(ipib_info));
	अगर (rc)
		वापस rc;
	अगर (ipib_info.ipib == 0)
		वापस 0;
	zcore_ipl_block = (व्योम *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!zcore_ipl_block)
		वापस -ENOMEM;
	अगर (ipib_info.ipib < sclp.hsa_size)
		rc = स_नकल_hsa_kernel(zcore_ipl_block, ipib_info.ipib,
				       PAGE_SIZE);
	अन्यथा
		rc = स_नकल_real(zcore_ipl_block, (व्योम *) ipib_info.ipib,
				 PAGE_SIZE);
	अगर (rc || (__क्रमce u32)csum_partial(zcore_ipl_block, zcore_ipl_block->hdr.len, 0) !=
	    ipib_info.checksum) अणु
		TRACE("Checksum does not match\n");
		मुक्त_page((अचिन्हित दीर्घ) zcore_ipl_block);
		zcore_ipl_block = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक zcore_reboot_and_on_panic_handler(काष्ठा notअगरier_block *self,
					     अचिन्हित दीर्घ	   event,
					     व्योम		   *data)
अणु
	अगर (hsa_available)
		release_hsa();

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block zcore_reboot_notअगरier = अणु
	.notअगरier_call	= zcore_reboot_and_on_panic_handler,
	/* we need to be notअगरied beक्रमe reipl and kdump */
	.priority	= पूर्णांक_उच्च,
पूर्ण;

अटल काष्ठा notअगरier_block zcore_on_panic_notअगरier = अणु
	.notअगरier_call	= zcore_reboot_and_on_panic_handler,
	/* we need to be notअगरied beक्रमe reipl and kdump */
	.priority	= पूर्णांक_उच्च,
पूर्ण;

अटल पूर्णांक __init zcore_init(व्योम)
अणु
	अचिन्हित अक्षर arch;
	पूर्णांक rc;

	अगर (!is_ipl_type_dump())
		वापस -ENODATA;
	अगर (OLDMEM_BASE)
		वापस -ENODATA;

	zcore_dbf = debug_रेजिस्टर("zcore", 4, 1, 4 * माप(दीर्घ));
	debug_रेजिस्टर_view(zcore_dbf, &debug_प्र_लिखो_view);
	debug_set_level(zcore_dbf, 6);

	अगर (ipl_info.type == IPL_TYPE_FCP_DUMP) अणु
		TRACE("type:   fcp\n");
		TRACE("devno:  %x\n", ipl_info.data.fcp.dev_id.devno);
		TRACE("wwpn:   %llx\n", (अचिन्हित दीर्घ दीर्घ) ipl_info.data.fcp.wwpn);
		TRACE("lun:    %llx\n", (अचिन्हित दीर्घ दीर्घ) ipl_info.data.fcp.lun);
	पूर्ण अन्यथा अगर (ipl_info.type == IPL_TYPE_NVME_DUMP) अणु
		TRACE("type:   nvme\n");
		TRACE("fid:    %x\n", ipl_info.data.nvme.fid);
		TRACE("nsid:   %x\n", ipl_info.data.nvme.nsid);
	पूर्ण

	rc = sclp_sdias_init();
	अगर (rc)
		जाओ fail;

	rc = check_sdias();
	अगर (rc)
		जाओ fail;
	hsa_available = 1;

	rc = स_नकल_hsa_kernel(&arch, __LC_AR_MODE_ID, 1);
	अगर (rc)
		जाओ fail;

	अगर (arch == ARCH_S390) अणु
		pr_alert("The 64-bit dump tool cannot be used for a "
			 "32-bit system\n");
		rc = -EINVAL;
		जाओ fail;
	पूर्ण

	pr_alert("The dump process started for a 64-bit operating system\n");
	rc = init_cpu_info();
	अगर (rc)
		जाओ fail;

	rc = zcore_reipl_init();
	अगर (rc)
		जाओ fail;

	zcore_dir = debugfs_create_dir("zcore" , शून्य);
	zcore_reipl_file = debugfs_create_file("reipl", S_IRUSR, zcore_dir,
						शून्य, &zcore_reipl_fops);
	zcore_hsa_file = debugfs_create_file("hsa", S_IRUSR|S_IWUSR, zcore_dir,
					     शून्य, &zcore_hsa_fops);

	रेजिस्टर_reboot_notअगरier(&zcore_reboot_notअगरier);
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &zcore_on_panic_notअगरier);

	वापस 0;
fail:
	diag308(DIAG308_REL_HSA, शून्य);
	वापस rc;
पूर्ण
subsys_initcall(zcore_init);
