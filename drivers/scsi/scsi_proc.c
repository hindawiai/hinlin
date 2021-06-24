<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/drivers/scsi/scsi_proc.c
 *
 * The functions in this file provide an पूर्णांकerface between
 * the PROC file प्रणाली and the SCSI device drivers
 * It is मुख्यly used क्रम debugging, statistics and to pass 
 * inक्रमmation directly to the lowlevel driver.
 *
 * (c) 1995 Michael Neuffer neuffer@goofy.zdv.uni-मुख्यz.de 
 * Version: 0.99.8   last change: 95/09/13
 * 
 * generic command parser provided by: 
 * Andreas Heilwagen <crashcar@inक्रमmatik.uni-koblenz.de>
 *
 * generic_proc_info() support of xxxx_info() by:
 * Michael A. Grअगरfith <grअगर@acm.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gfp.h>
#समावेश <linux/uaccess.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>

#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"


/* 4K page size, but our output routines, use some slack क्रम overruns */
#घोषणा PROC_BLOCK_SIZE (3*1024)

अटल काष्ठा proc_dir_entry *proc_scsi;

/* Protect sht->present and sht->proc_dir */
अटल DEFINE_MUTEX(global_host_ढाँचा_mutex);

अटल sमाप_प्रकार proc_scsi_host_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
                           माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा Scsi_Host *shost = PDE_DATA(file_inode(file));
	sमाप_प्रकार ret = -ENOMEM;
	अक्षर *page;
    
	अगर (count > PROC_BLOCK_SIZE)
		वापस -EOVERFLOW;

	अगर (!shost->hostt->ग_लिखो_info)
		वापस -EINVAL;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (page) अणु
		ret = -EFAULT;
		अगर (copy_from_user(page, buf, count))
			जाओ out;
		ret = shost->hostt->ग_लिखो_info(shost, page, count);
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस ret;
पूर्ण

अटल पूर्णांक proc_scsi_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा Scsi_Host *shost = m->निजी;
	वापस shost->hostt->show_info(m, shost);
पूर्ण

अटल पूर्णांक proc_scsi_host_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो_size(file, proc_scsi_show, PDE_DATA(inode),
				4 * PAGE_SIZE);
पूर्ण

अटल स्थिर काष्ठा proc_ops proc_scsi_ops = अणु
	.proc_खोलो	= proc_scsi_host_खोलो,
	.proc_release	= single_release,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= proc_scsi_host_ग_लिखो
पूर्ण;

/**
 * scsi_proc_hostdir_add - Create directory in /proc क्रम a scsi host
 * @sht: owner of this directory
 *
 * Sets sht->proc_dir to the new directory.
 */

व्योम scsi_proc_hostdir_add(काष्ठा scsi_host_ढाँचा *sht)
अणु
	अगर (!sht->show_info)
		वापस;

	mutex_lock(&global_host_ढाँचा_mutex);
	अगर (!sht->present++) अणु
		sht->proc_dir = proc_सूची_गढ़ो(sht->proc_name, proc_scsi);
        	अगर (!sht->proc_dir)
			prपूर्णांकk(KERN_ERR "%s: proc_mkdir failed for %s\n",
			       __func__, sht->proc_name);
	पूर्ण
	mutex_unlock(&global_host_ढाँचा_mutex);
पूर्ण

/**
 * scsi_proc_hostdir_rm - हटाओ directory in /proc क्रम a scsi host
 * @sht: owner of directory
 */
व्योम scsi_proc_hostdir_rm(काष्ठा scsi_host_ढाँचा *sht)
अणु
	अगर (!sht->show_info)
		वापस;

	mutex_lock(&global_host_ढाँचा_mutex);
	अगर (!--sht->present && sht->proc_dir) अणु
		हटाओ_proc_entry(sht->proc_name, proc_scsi);
		sht->proc_dir = शून्य;
	पूर्ण
	mutex_unlock(&global_host_ढाँचा_mutex);
पूर्ण


/**
 * scsi_proc_host_add - Add entry क्रम this host to appropriate /proc dir
 * @shost: host to add
 */
व्योम scsi_proc_host_add(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_host_ढाँचा *sht = shost->hostt;
	काष्ठा proc_dir_entry *p;
	अक्षर name[10];

	अगर (!sht->proc_dir)
		वापस;

	प्र_लिखो(name,"%d", shost->host_no);
	p = proc_create_data(name, S_IRUGO | S_IWUSR,
		sht->proc_dir, &proc_scsi_ops, shost);
	अगर (!p)
		prपूर्णांकk(KERN_ERR "%s: Failed to register host %d in"
		       "%s\n", __func__, shost->host_no,
		       sht->proc_name);
पूर्ण

/**
 * scsi_proc_host_rm - हटाओ this host's entry from /proc
 * @shost: which host
 */
व्योम scsi_proc_host_rm(काष्ठा Scsi_Host *shost)
अणु
	अक्षर name[10];

	अगर (!shost->hostt->proc_dir)
		वापस;

	प्र_लिखो(name,"%d", shost->host_no);
	हटाओ_proc_entry(name, shost->hostt->proc_dir);
पूर्ण
/**
 * proc_prपूर्णांक_scsidevice - वापस data about this host
 * @dev: A scsi device
 * @data: &काष्ठा seq_file to output to.
 *
 * Description: prपूर्णांकs Host, Channel, Id, Lun, Venकरोr, Model, Rev, Type,
 * and revision.
 */
अटल पूर्णांक proc_prपूर्णांक_scsidevice(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा seq_file *s = data;
	पूर्णांक i;

	अगर (!scsi_is_sdev_device(dev))
		जाओ out;

	sdev = to_scsi_device(dev);
	seq_म_लिखो(s,
		"Host: scsi%d Channel: %02d Id: %02d Lun: %02llu\n  Vendor: ",
		sdev->host->host_no, sdev->channel, sdev->id, sdev->lun);
	क्रम (i = 0; i < 8; i++) अणु
		अगर (sdev->venकरोr[i] >= 0x20)
			seq_अ_दो(s, sdev->venकरोr[i]);
		अन्यथा
			seq_अ_दो(s, ' ');
	पूर्ण

	seq_माला_दो(s, " Model: ");
	क्रम (i = 0; i < 16; i++) अणु
		अगर (sdev->model[i] >= 0x20)
			seq_अ_दो(s, sdev->model[i]);
		अन्यथा
			seq_अ_दो(s, ' ');
	पूर्ण

	seq_माला_दो(s, " Rev: ");
	क्रम (i = 0; i < 4; i++) अणु
		अगर (sdev->rev[i] >= 0x20)
			seq_अ_दो(s, sdev->rev[i]);
		अन्यथा
			seq_अ_दो(s, ' ');
	पूर्ण

	seq_अ_दो(s, '\n');

	seq_म_लिखो(s, "  Type:   %s ", scsi_device_type(sdev->type));
	seq_म_लिखो(s, "               ANSI  SCSI revision: %02x",
			sdev->scsi_level - (sdev->scsi_level > 1));
	अगर (sdev->scsi_level == 2)
		seq_माला_दो(s, " CCS\n");
	अन्यथा
		seq_अ_दो(s, '\n');

out:
	वापस 0;
पूर्ण

/**
 * scsi_add_single_device - Respond to user request to probe क्रम/add device
 * @host: user-supplied decimal पूर्णांकeger
 * @channel: user-supplied decimal पूर्णांकeger
 * @id: user-supplied decimal पूर्णांकeger
 * @lun: user-supplied decimal पूर्णांकeger
 *
 * Description: called by writing "scsi add-single-device" to /proc/scsi/scsi.
 *
 * करोes scsi_host_lookup() and either user_scan() अगर that transport
 * type supports it, or अन्यथा scsi_scan_host_selected()
 *
 * Note: this seems to be aimed exclusively at SCSI parallel busses.
 */

अटल पूर्णांक scsi_add_single_device(uपूर्णांक host, uपूर्णांक channel, uपूर्णांक id, uपूर्णांक lun)
अणु
	काष्ठा Scsi_Host *shost;
	पूर्णांक error = -ENXIO;

	shost = scsi_host_lookup(host);
	अगर (!shost)
		वापस error;

	अगर (shost->transportt->user_scan)
		error = shost->transportt->user_scan(shost, channel, id, lun);
	अन्यथा
		error = scsi_scan_host_selected(shost, channel, id, lun,
						SCSI_SCAN_MANUAL);
	scsi_host_put(shost);
	वापस error;
पूर्ण

/**
 * scsi_हटाओ_single_device - Respond to user request to हटाओ a device
 * @host: user-supplied decimal पूर्णांकeger
 * @channel: user-supplied decimal पूर्णांकeger
 * @id: user-supplied decimal पूर्णांकeger
 * @lun: user-supplied decimal पूर्णांकeger
 *
 * Description: called by writing "scsi remove-single-device" to
 * /proc/scsi/scsi.  Does a scsi_device_lookup() and scsi_हटाओ_device()
 */
अटल पूर्णांक scsi_हटाओ_single_device(uपूर्णांक host, uपूर्णांक channel, uपूर्णांक id, uपूर्णांक lun)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा Scsi_Host *shost;
	पूर्णांक error = -ENXIO;

	shost = scsi_host_lookup(host);
	अगर (!shost)
		वापस error;
	sdev = scsi_device_lookup(shost, channel, id, lun);
	अगर (sdev) अणु
		scsi_हटाओ_device(sdev);
		scsi_device_put(sdev);
		error = 0;
	पूर्ण

	scsi_host_put(shost);
	वापस error;
पूर्ण

/**
 * proc_scsi_ग_लिखो - handle ग_लिखोs to /proc/scsi/scsi
 * @file: not used
 * @buf: buffer to ग_लिखो
 * @length: length of buf, at most PAGE_SIZE
 * @ppos: not used
 *
 * Description: this provides a legacy mechanism to add or हटाओ devices by
 * Host, Channel, ID, and Lun.  To use,
 * "echo 'scsi add-single-device 0 1 2 3' > /proc/scsi/scsi" or
 * "echo 'scsi remove-single-device 0 1 2 3' > /proc/scsi/scsi" with
 * "0 1 2 3" replaced by the Host, Channel, Id, and Lun.
 *
 * Note: this seems to be aimed at parallel SCSI. Most modern busses (USB,
 * SATA, Firewire, Fibre Channel, etc) dynamically assign these values to
 * provide a unique identअगरier and nothing more.
 */


अटल sमाप_प्रकार proc_scsi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			       माप_प्रकार length, loff_t *ppos)
अणु
	पूर्णांक host, channel, id, lun;
	अक्षर *buffer, *p;
	पूर्णांक err;

	अगर (!buf || length > PAGE_SIZE)
		वापस -EINVAL;

	buffer = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	err = -EFAULT;
	अगर (copy_from_user(buffer, buf, length))
		जाओ out;

	err = -EINVAL;
	अगर (length < PAGE_SIZE)
		buffer[length] = '\0';
	अन्यथा अगर (buffer[PAGE_SIZE-1])
		जाओ out;

	/*
	 * Usage: echo "scsi add-single-device 0 1 2 3" >/proc/scsi/scsi
	 * with  "0 1 2 3" replaced by your "Host Channel Id Lun".
	 */
	अगर (!म_भेदन("scsi add-single-device", buffer, 22)) अणु
		p = buffer + 23;

		host = simple_म_से_अदीर्घ(p, &p, 0);
		channel = simple_म_से_अदीर्घ(p + 1, &p, 0);
		id = simple_म_से_अदीर्घ(p + 1, &p, 0);
		lun = simple_म_से_अदीर्घ(p + 1, &p, 0);

		err = scsi_add_single_device(host, channel, id, lun);

	/*
	 * Usage: echo "scsi remove-single-device 0 1 2 3" >/proc/scsi/scsi
	 * with  "0 1 2 3" replaced by your "Host Channel Id Lun".
	 */
	पूर्ण अन्यथा अगर (!म_भेदन("scsi remove-single-device", buffer, 25)) अणु
		p = buffer + 26;

		host = simple_म_से_अदीर्घ(p, &p, 0);
		channel = simple_म_से_अदीर्घ(p + 1, &p, 0);
		id = simple_म_से_अदीर्घ(p + 1, &p, 0);
		lun = simple_म_से_अदीर्घ(p + 1, &p, 0);

		err = scsi_हटाओ_single_device(host, channel, id, lun);
	पूर्ण

	/*
	 * convert success वापसs so that we वापस the 
	 * number of bytes consumed.
	 */
	अगर (!err)
		err = length;

 out:
	मुक्त_page((अचिन्हित दीर्घ)buffer);
	वापस err;
पूर्ण

अटल अंतरभूत काष्ठा device *next_scsi_device(काष्ठा device *start)
अणु
	काष्ठा device *next = bus_find_next_device(&scsi_bus_type, start);

	put_device(start);
	वापस next;
पूर्ण

अटल व्योम *scsi_seq_start(काष्ठा seq_file *sfile, loff_t *pos)
अणु
	काष्ठा device *dev = शून्य;
	loff_t n = *pos;

	जबतक ((dev = next_scsi_device(dev))) अणु
		अगर (!n--)
			अवरोध;
		sfile->निजी++;
	पूर्ण
	वापस dev;
पूर्ण

अटल व्योम *scsi_seq_next(काष्ठा seq_file *sfile, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	sfile->निजी++;
	वापस next_scsi_device(v);
पूर्ण

अटल व्योम scsi_seq_stop(काष्ठा seq_file *sfile, व्योम *v)
अणु
	put_device(v);
पूर्ण

अटल पूर्णांक scsi_seq_show(काष्ठा seq_file *sfile, व्योम *dev)
अणु
	अगर (!sfile->निजी)
		seq_माला_दो(sfile, "Attached devices:\n");

	वापस proc_prपूर्णांक_scsidevice(dev, sfile);
पूर्ण

अटल स्थिर काष्ठा seq_operations scsi_seq_ops = अणु
	.start	= scsi_seq_start,
	.next	= scsi_seq_next,
	.stop	= scsi_seq_stop,
	.show	= scsi_seq_show
पूर्ण;

/**
 * proc_scsi_खोलो - glue function
 * @inode: not used
 * @file: passed to single_खोलो()
 *
 * Associates proc_scsi_show with this file
 */
अटल पूर्णांक proc_scsi_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * We करोn't really need this for the write case but it doesn't
	 * harm either.
	 */
	वापस seq_खोलो(file, &scsi_seq_ops);
पूर्ण

अटल स्थिर काष्ठा proc_ops scsi_scsi_proc_ops = अणु
	.proc_खोलो	= proc_scsi_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= proc_scsi_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;

/**
 * scsi_init_procfs - create scsi and scsi/scsi in procfs
 */
पूर्णांक __init scsi_init_procfs(व्योम)
अणु
	काष्ठा proc_dir_entry *pde;

	proc_scsi = proc_सूची_गढ़ो("scsi", शून्य);
	अगर (!proc_scsi)
		जाओ err1;

	pde = proc_create("scsi/scsi", 0, शून्य, &scsi_scsi_proc_ops);
	अगर (!pde)
		जाओ err2;

	वापस 0;

err2:
	हटाओ_proc_entry("scsi", शून्य);
err1:
	वापस -ENOMEM;
पूर्ण

/**
 * scsi_निकास_procfs - Remove scsi/scsi and scsi from procfs
 */
व्योम scsi_निकास_procfs(व्योम)
अणु
	हटाओ_proc_entry("scsi/scsi", शून्य);
	हटाओ_proc_entry("scsi", शून्य);
पूर्ण
