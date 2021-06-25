<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Changes:
 * Arnalकरो Carvalho de Melo <acme@conectiva.com.br> 08/23/2000
 * - get rid of some verअगरy_areas and use __copy*user and __get/put_user
 *   क्रम the ones that reमुख्य
 */
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/sg.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "scsi_logging.h"

#घोषणा NORMAL_RETRIES			5
#घोषणा IOCTL_NORMAL_TIMEOUT			(10 * HZ)

#घोषणा MAX_BUF PAGE_SIZE

/**
 * ioctl_probe  --  वापस host identअगरication
 * @host:	host to identअगरy
 * @buffer:	userspace buffer क्रम identअगरication
 *
 * Return an identअगरying string at @buffer, अगर @buffer is non-शून्य, filling
 * to the length stored at * (पूर्णांक *) @buffer.
 */
अटल पूर्णांक ioctl_probe(काष्ठा Scsi_Host *host, व्योम __user *buffer)
अणु
	अचिन्हित पूर्णांक len, slen;
	स्थिर अक्षर *string;

	अगर (buffer) अणु
		अगर (get_user(len, (अचिन्हित पूर्णांक __user *) buffer))
			वापस -EFAULT;

		अगर (host->hostt->info)
			string = host->hostt->info(host);
		अन्यथा
			string = host->hostt->name;
		अगर (string) अणु
			slen = म_माप(string);
			अगर (len > slen)
				len = slen + 1;
			अगर (copy_to_user(buffer, string, len))
				वापस -EFAULT;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*

 * The SCSI_IOCTL_SEND_COMMAND ioctl sends a command out to the SCSI host.
 * The IOCTL_NORMAL_TIMEOUT and NORMAL_RETRIES  variables are used.  
 * 
 * dev is the SCSI device काष्ठा ptr, *(पूर्णांक *) arg is the length of the
 * input data, अगर any, not including the command string & counts, 
 * *((पूर्णांक *)arg + 1) is the output buffer size in bytes.
 * 
 * *(अक्षर *) ((पूर्णांक *) arg)[2] the actual command byte.   
 * 
 * Note that अगर more than MAX_BUF bytes are requested to be transferred,
 * the ioctl will fail with error EINVAL.
 * 
 * This size *करोes not* include the initial lengths that were passed.
 * 
 * The SCSI command is पढ़ो from the memory location immediately after the
 * length words, and the input data is right after the command.  The SCSI
 * routines know the command size based on the opcode decode.  
 * 
 * The output area is then filled in starting from the command byte. 
 */

अटल पूर्णांक ioctl_पूर्णांकernal_command(काष्ठा scsi_device *sdev, अक्षर *cmd,
				  पूर्णांक समयout, पूर्णांक retries)
अणु
	पूर्णांक result;
	काष्ठा scsi_sense_hdr sshdr;

	SCSI_LOG_IOCTL(1, sdev_prपूर्णांकk(KERN_INFO, sdev,
				      "Trying ioctl with scsi command %d\n", *cmd));

	result = scsi_execute_req(sdev, cmd, DMA_NONE, शून्य, 0,
				  &sshdr, समयout, retries, शून्य);

	SCSI_LOG_IOCTL(2, sdev_prपूर्णांकk(KERN_INFO, sdev,
				      "Ioctl returned  0x%x\n", result));

	अगर (driver_byte(result) == DRIVER_SENSE &&
	    scsi_sense_valid(&sshdr)) अणु
		चयन (sshdr.sense_key) अणु
		हाल ILLEGAL_REQUEST:
			अगर (cmd[0] == ALLOW_MEDIUM_REMOVAL)
				sdev->lockable = 0;
			अन्यथा
				sdev_prपूर्णांकk(KERN_INFO, sdev,
					    "ioctl_internal_command: "
					    "ILLEGAL REQUEST "
					    "asc=0x%x ascq=0x%x\n",
					    sshdr.asc, sshdr.ascq);
			अवरोध;
		हाल NOT_READY:	/* This happens अगर there is no disc in drive */
			अगर (sdev->removable)
				अवरोध;
			fallthrough;
		हाल UNIT_ATTENTION:
			अगर (sdev->removable) अणु
				sdev->changed = 1;
				result = 0;	/* This is no दीर्घer considered an error */
				अवरोध;
			पूर्ण
			fallthrough;	/* क्रम non-removable media */
		शेष:
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "ioctl_internal_command return code = %x\n",
				    result);
			scsi_prपूर्णांक_sense_hdr(sdev, शून्य, &sshdr);
			अवरोध;
		पूर्ण
	पूर्ण

	SCSI_LOG_IOCTL(2, sdev_prपूर्णांकk(KERN_INFO, sdev,
				      "IOCTL Releasing command\n"));
	वापस result;
पूर्ण

पूर्णांक scsi_set_medium_removal(काष्ठा scsi_device *sdev, अक्षर state)
अणु
	अक्षर scsi_cmd[MAX_COMMAND_SIZE];
	पूर्णांक ret;

	अगर (!sdev->removable || !sdev->lockable)
	       वापस 0;

	scsi_cmd[0] = ALLOW_MEDIUM_REMOVAL;
	scsi_cmd[1] = 0;
	scsi_cmd[2] = 0;
	scsi_cmd[3] = 0;
	scsi_cmd[4] = state;
	scsi_cmd[5] = 0;

	ret = ioctl_पूर्णांकernal_command(sdev, scsi_cmd,
			IOCTL_NORMAL_TIMEOUT, NORMAL_RETRIES);
	अगर (ret == 0)
		sdev->locked = (state == SCSI_REMOVAL_PREVENT);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(scsi_set_medium_removal);

/*
 * The scsi_ioctl_get_pci() function places पूर्णांकo arg the value
 * pci_dev::slot_name (8 अक्षरacters) क्रम the PCI device (अगर any).
 * Returns: 0 on success
 *          -ENXIO अगर there isn't a PCI device poपूर्णांकer
 *                 (could be because the SCSI driver hasn't been
 *                  updated yet, or because it isn't a SCSI
 *                  device)
 *          any copy_to_user() error on failure there
 */
अटल पूर्णांक scsi_ioctl_get_pci(काष्ठा scsi_device *sdev, व्योम __user *arg)
अणु
	काष्ठा device *dev = scsi_get_device(sdev->host);
	स्थिर अक्षर *name;

        अगर (!dev)
		वापस -ENXIO;

	name = dev_name(dev);

	/* compatibility with old ioctl which only वापसed
	 * 20 अक्षरacters */
        वापस copy_to_user(arg, name, min(म_माप(name), (माप_प्रकार)20))
		? -EFAULT: 0;
पूर्ण


अटल पूर्णांक scsi_ioctl_common(काष्ठा scsi_device *sdev, पूर्णांक cmd, व्योम __user *arg)
अणु
	अक्षर scsi_cmd[MAX_COMMAND_SIZE];
	काष्ठा scsi_sense_hdr sense_hdr;

	/* Check क्रम deprecated ioctls ... all the ioctls which करोn't
	 * follow the new unique numbering scheme are deprecated */
	चयन (cmd) अणु
	हाल SCSI_IOCTL_SEND_COMMAND:
	हाल SCSI_IOCTL_TEST_UNIT_READY:
	हाल SCSI_IOCTL_BENCHMARK_COMMAND:
	हाल SCSI_IOCTL_SYNC:
	हाल SCSI_IOCTL_START_UNIT:
	हाल SCSI_IOCTL_STOP_UNIT:
		prपूर्णांकk(KERN_WARNING "program %s is using a deprecated SCSI "
		       "ioctl, please convert it to SG_IO\n", current->comm);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (cmd) अणु
	हाल SCSI_IOCTL_GET_IDLUN: अणु
		काष्ठा scsi_idlun v = अणु
			.dev_id = (sdev->id & 0xff)
				 + ((sdev->lun & 0xff) << 8)
				 + ((sdev->channel & 0xff) << 16)
				 + ((sdev->host->host_no & 0xff) << 24),
			.host_unique_id = sdev->host->unique_id
		पूर्ण;
		अगर (copy_to_user(arg, &v, माप(काष्ठा scsi_idlun)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल SCSI_IOCTL_GET_BUS_NUMBER:
		वापस put_user(sdev->host->host_no, (पूर्णांक __user *)arg);
	हाल SCSI_IOCTL_PROBE_HOST:
		वापस ioctl_probe(sdev->host, arg);
	हाल SCSI_IOCTL_SEND_COMMAND:
		अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		वापस sg_scsi_ioctl(sdev->request_queue, शून्य, 0, arg);
	हाल SCSI_IOCTL_DOORLOCK:
		वापस scsi_set_medium_removal(sdev, SCSI_REMOVAL_PREVENT);
	हाल SCSI_IOCTL_DOORUNLOCK:
		वापस scsi_set_medium_removal(sdev, SCSI_REMOVAL_ALLOW);
	हाल SCSI_IOCTL_TEST_UNIT_READY:
		वापस scsi_test_unit_पढ़ोy(sdev, IOCTL_NORMAL_TIMEOUT,
					    NORMAL_RETRIES, &sense_hdr);
	हाल SCSI_IOCTL_START_UNIT:
		scsi_cmd[0] = START_STOP;
		scsi_cmd[1] = 0;
		scsi_cmd[2] = scsi_cmd[3] = scsi_cmd[5] = 0;
		scsi_cmd[4] = 1;
		वापस ioctl_पूर्णांकernal_command(sdev, scsi_cmd,
				     START_STOP_TIMEOUT, NORMAL_RETRIES);
	हाल SCSI_IOCTL_STOP_UNIT:
		scsi_cmd[0] = START_STOP;
		scsi_cmd[1] = 0;
		scsi_cmd[2] = scsi_cmd[3] = scsi_cmd[5] = 0;
		scsi_cmd[4] = 0;
		वापस ioctl_पूर्णांकernal_command(sdev, scsi_cmd,
				     START_STOP_TIMEOUT, NORMAL_RETRIES);
        हाल SCSI_IOCTL_GET_PCI:
                वापस scsi_ioctl_get_pci(sdev, arg);
	हाल SG_SCSI_RESET:
		वापस scsi_ioctl_reset(sdev, arg);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

/**
 * scsi_ioctl - Dispatch ioctl to scsi device
 * @sdev: scsi device receiving ioctl
 * @cmd: which ioctl is it
 * @arg: data associated with ioctl
 *
 * Description: The scsi_ioctl() function dअगरfers from most ioctls in that it
 * करोes not take a major/minor number as the dev field.  Rather, it takes
 * a poपूर्णांकer to a &काष्ठा scsi_device.
 */
पूर्णांक scsi_ioctl(काष्ठा scsi_device *sdev, पूर्णांक cmd, व्योम __user *arg)
अणु
	पूर्णांक ret = scsi_ioctl_common(sdev, cmd, arg);

	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	अगर (sdev->host->hostt->ioctl)
		वापस sdev->host->hostt->ioctl(sdev, cmd, arg);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(scsi_ioctl);

#अगर_घोषित CONFIG_COMPAT
पूर्णांक scsi_compat_ioctl(काष्ठा scsi_device *sdev, पूर्णांक cmd, व्योम __user *arg)
अणु
	पूर्णांक ret = scsi_ioctl_common(sdev, cmd, arg);

	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	अगर (sdev->host->hostt->compat_ioctl)
		वापस sdev->host->hostt->compat_ioctl(sdev, cmd, arg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(scsi_compat_ioctl);
#पूर्ण_अगर

/*
 * We can process a reset even when a device isn't fully operable.
 */
पूर्णांक scsi_ioctl_block_when_processing_errors(काष्ठा scsi_device *sdev, पूर्णांक cmd,
		bool ndelay)
अणु
	अगर (cmd == SG_SCSI_RESET && ndelay) अणु
		अगर (scsi_host_in_recovery(sdev->host))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (!scsi_block_when_processing_errors(sdev))
			वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_ioctl_block_when_processing_errors);
