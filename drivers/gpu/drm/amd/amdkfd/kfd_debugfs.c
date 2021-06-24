<शैली गुरु>
/*
 * Copyright 2016-2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>

#समावेश "kfd_priv.h"

अटल काष्ठा dentry *debugfs_root;

अटल पूर्णांक kfd_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक (*show)(काष्ठा seq_file *, व्योम *) = inode->i_निजी;

	वापस single_खोलो(file, show, शून्य);
पूर्ण
अटल पूर्णांक kfd_debugfs_hang_hws_पढ़ो(काष्ठा seq_file *m, व्योम *data)
अणु
	seq_म_लिखो(m, "echo gpu_id > hang_hws\n");
	वापस 0;
पूर्ण

अटल sमाप_प्रकार kfd_debugfs_hang_hws_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *user_buf, माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा kfd_dev *dev;
	अक्षर पंचांगp[16];
	uपूर्णांक32_t gpu_id;
	पूर्णांक ret = -EINVAL;

	स_रखो(पंचांगp, 0, 16);
	अगर (size >= 16) अणु
		pr_err("Invalid input for gpu id.\n");
		जाओ out;
	पूर्ण
	अगर (copy_from_user(पंचांगp, user_buf, size)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (kstrtoपूर्णांक(पंचांगp, 10, &gpu_id)) अणु
		pr_err("Invalid input for gpu id.\n");
		जाओ out;
	पूर्ण
	dev = kfd_device_by_id(gpu_id);
	अगर (dev) अणु
		kfd_debugfs_hang_hws(dev);
		ret = size;
	पूर्ण अन्यथा
		pr_err("Cannot find device %d.\n", gpu_id);

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations kfd_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = kfd_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations kfd_debugfs_hang_hws_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = kfd_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = kfd_debugfs_hang_hws_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

व्योम kfd_debugfs_init(व्योम)
अणु
	debugfs_root = debugfs_create_dir("kfd", शून्य);

	debugfs_create_file("mqds", S_IFREG | 0444, debugfs_root,
			    kfd_debugfs_mqds_by_process, &kfd_debugfs_fops);
	debugfs_create_file("hqds", S_IFREG | 0444, debugfs_root,
			    kfd_debugfs_hqds_by_device, &kfd_debugfs_fops);
	debugfs_create_file("rls", S_IFREG | 0444, debugfs_root,
			    kfd_debugfs_rls_by_device, &kfd_debugfs_fops);
	debugfs_create_file("hang_hws", S_IFREG | 0200, debugfs_root,
			    kfd_debugfs_hang_hws_पढ़ो, &kfd_debugfs_hang_hws_fops);
पूर्ण

व्योम kfd_debugfs_fini(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_root);
पूर्ण
