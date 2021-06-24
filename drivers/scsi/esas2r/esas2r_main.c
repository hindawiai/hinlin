<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_मुख्य.c
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश "esas2r.h"

MODULE_DESCRIPTION(ESAS2R_DRVR_NAME ": " ESAS2R_LONGNAME " driver");
MODULE_AUTHOR("ATTO Technology, Inc.");
MODULE_LICENSE("GPL");
MODULE_VERSION(ESAS2R_VERSION_STR);

/* global definitions */

अटल पूर्णांक found_adapters;
काष्ठा esas2r_adapter *esas2r_adapters[MAX_ADAPTERS];

#घोषणा ESAS2R_VDA_EVENT_PORT1       54414
#घोषणा ESAS2R_VDA_EVENT_PORT2       54415
#घोषणा ESAS2R_VDA_EVENT_SOCK_COUNT  2

अटल काष्ठा esas2r_adapter *esas2r_adapter_from_kobj(काष्ठा kobject *kobj)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *host = class_to_shost(dev);

	वापस (काष्ठा esas2r_adapter *)host->hostdata;
पूर्ण

अटल sमाप_प्रकार पढ़ो_fw(काष्ठा file *file, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *attr,
		       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);

	वापस esas2r_पढ़ो_fw(a, buf, off, count);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_fw(काष्ठा file *file, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *attr,
			अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);

	वापस esas2r_ग_लिखो_fw(a, buf, off, count);
पूर्ण

अटल sमाप_प्रकार पढ़ो_fs(काष्ठा file *file, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *attr,
		       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);

	वापस esas2r_पढ़ो_fs(a, buf, off, count);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_fs(काष्ठा file *file, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *attr,
			अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);
	पूर्णांक length = min(माप(काष्ठा esas2r_ioctl_fs), count);
	पूर्णांक result = 0;

	result = esas2r_ग_लिखो_fs(a, buf, off, count);

	अगर (result < 0)
		result = 0;

	वापस length;
पूर्ण

अटल sमाप_प्रकार पढ़ो_vda(काष्ठा file *file, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *attr,
			अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);

	वापस esas2r_पढ़ो_vda(a, buf, off, count);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_vda(काष्ठा file *file, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *attr,
			 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);

	वापस esas2r_ग_लिखो_vda(a, buf, off, count);
पूर्ण

अटल sमाप_प्रकार पढ़ो_live_nvram(काष्ठा file *file, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *attr,
			       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);
	पूर्णांक length = min_t(माप_प्रकार, माप(काष्ठा esas2r_sas_nvram), PAGE_SIZE);

	स_नकल(buf, a->nvram, length);
	वापस length;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_live_nvram(काष्ठा file *file, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr,
				अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);
	काष्ठा esas2r_request *rq;
	पूर्णांक result = -EFAULT;

	rq = esas2r_alloc_request(a);
	अगर (rq == शून्य)
		वापस -ENOMEM;

	अगर (esas2r_ग_लिखो_params(a, rq, (काष्ठा esas2r_sas_nvram *)buf))
		result = count;

	esas2r_मुक्त_request(a, rq);

	वापस result;
पूर्ण

अटल sमाप_प्रकार पढ़ो_शेष_nvram(काष्ठा file *file, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *attr,
				  अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);

	esas2r_nvram_get_शेषs(a, (काष्ठा esas2r_sas_nvram *)buf);

	वापस माप(काष्ठा esas2r_sas_nvram);
पूर्ण

अटल sमाप_प्रकार पढ़ो_hw(काष्ठा file *file, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *attr,
		       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);
	पूर्णांक length = min_t(माप_प्रकार, माप(काष्ठा atto_ioctl), PAGE_SIZE);

	अगर (!a->local_atto_ioctl)
		वापस -ENOMEM;

	अगर (handle_hba_ioctl(a, a->local_atto_ioctl) != IOCTL_SUCCESS)
		वापस -ENOMEM;

	स_नकल(buf, a->local_atto_ioctl, length);

	वापस length;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_hw(काष्ठा file *file, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *attr,
			अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);
	पूर्णांक length = min(माप(काष्ठा atto_ioctl), count);

	अगर (!a->local_atto_ioctl) अणु
		a->local_atto_ioctl = kदो_स्मृति(माप(काष्ठा atto_ioctl),
					      GFP_KERNEL);
		अगर (a->local_atto_ioctl == शून्य) अणु
			esas2r_log(ESAS2R_LOG_WARN,
				   "write_hw kzalloc failed for %zu bytes",
				   माप(काष्ठा atto_ioctl));
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	स_रखो(a->local_atto_ioctl, 0, माप(काष्ठा atto_ioctl));
	स_नकल(a->local_atto_ioctl, buf, length);

	वापस length;
पूर्ण

#घोषणा ESAS2R_RW_BIN_ATTR(_name) \
	काष्ठा bin_attribute bin_attr_ ## _name = अणु \
		.attr	= \
		अणु .name = __stringअगरy(_name), .mode  = S_IRUSR | S_IWUSR पूर्ण, \
		.size	= 0, \
		.पढ़ो	= पढ़ो_ ## _name, \
		.ग_लिखो	= ग_लिखो_ ## _name पूर्ण

ESAS2R_RW_BIN_ATTR(fw);
ESAS2R_RW_BIN_ATTR(fs);
ESAS2R_RW_BIN_ATTR(vda);
ESAS2R_RW_BIN_ATTR(hw);
ESAS2R_RW_BIN_ATTR(live_nvram);

काष्ठा bin_attribute bin_attr_शेष_nvram = अणु
	.attr	= अणु .name = "default_nvram", .mode = S_IRUGO पूर्ण,
	.size	= 0,
	.पढ़ो	= पढ़ो_शेष_nvram,
	.ग_लिखो	= शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.show_info			= esas2r_show_info,
	.name				= ESAS2R_LONGNAME,
	.info				= esas2r_info,
	.ioctl				= esas2r_ioctl,
	.queuecommand			= esas2r_queuecommand,
	.eh_पात_handler		= esas2r_eh_पात,
	.eh_device_reset_handler	= esas2r_device_reset,
	.eh_bus_reset_handler		= esas2r_bus_reset,
	.eh_host_reset_handler		= esas2r_host_reset,
	.eh_target_reset_handler	= esas2r_target_reset,
	.can_queue			= 128,
	.this_id			= -1,
	.sg_tablesize			= SG_CHUNK_SIZE,
	.cmd_per_lun			=
		ESAS2R_DEFAULT_CMD_PER_LUN,
	.present			= 0,
	.emulated			= 0,
	.proc_name			= ESAS2R_DRVR_NAME,
	.change_queue_depth		= scsi_change_queue_depth,
	.max_sectors			= 0xFFFF,
पूर्ण;

पूर्णांक sgl_page_size = 512;
module_param(sgl_page_size, पूर्णांक, 0);
MODULE_PARM_DESC(sgl_page_size,
		 "Scatter/gather list (SGL) page size in number of S/G "
		 "entries.  If your application is doing a lot of very large "
		 "transfers, you may want to increase the SGL page size.  "
		 "Default 512.");

पूर्णांक num_sg_lists = 1024;
module_param(num_sg_lists, पूर्णांक, 0);
MODULE_PARM_DESC(num_sg_lists,
		 "Number of scatter/gather lists.  Default 1024.");

पूर्णांक sg_tablesize = SG_CHUNK_SIZE;
module_param(sg_tablesize, पूर्णांक, 0);
MODULE_PARM_DESC(sg_tablesize,
		 "Maximum number of entries in a scatter/gather table.");

पूर्णांक num_requests = 256;
module_param(num_requests, पूर्णांक, 0);
MODULE_PARM_DESC(num_requests,
		 "Number of requests.  Default 256.");

पूर्णांक num_ae_requests = 4;
module_param(num_ae_requests, पूर्णांक, 0);
MODULE_PARM_DESC(num_ae_requests,
		 "Number of VDA asynchronous event requests.  Default 4.");

पूर्णांक cmd_per_lun = ESAS2R_DEFAULT_CMD_PER_LUN;
module_param(cmd_per_lun, पूर्णांक, 0);
MODULE_PARM_DESC(cmd_per_lun,
		 "Maximum number of commands per LUN.  Default "
		 DEFINED_NUM_TO_STR(ESAS2R_DEFAULT_CMD_PER_LUN) ".");

पूर्णांक can_queue = 128;
module_param(can_queue, पूर्णांक, 0);
MODULE_PARM_DESC(can_queue,
		 "Maximum number of commands per adapter.  Default 128.");

पूर्णांक esas2r_max_sectors = 0xFFFF;
module_param(esas2r_max_sectors, पूर्णांक, 0);
MODULE_PARM_DESC(esas2r_max_sectors,
		 "Maximum number of disk sectors in a single data transfer.  "
		 "Default 65535 (largest possible setting).");

पूर्णांक पूर्णांकerrupt_mode = 1;
module_param(पूर्णांकerrupt_mode, पूर्णांक, 0);
MODULE_PARM_DESC(पूर्णांकerrupt_mode,
		 "Defines the interrupt mode to use.  0 for legacy"
		 ", 1 for MSI.  Default is MSI (1).");

अटल स्थिर काष्ठा pci_device_id
	esas2r_pci_table[] = अणु
	अणु ATTO_VENDOR_ID, 0x0049,	  ATTO_VENDOR_ID, 0x0049,
	  0,
	  0, 0 पूर्ण,
	अणु ATTO_VENDOR_ID, 0x0049,	  ATTO_VENDOR_ID, 0x004A,
	  0,
	  0, 0 पूर्ण,
	अणु ATTO_VENDOR_ID, 0x0049,	  ATTO_VENDOR_ID, 0x004B,
	  0,
	  0, 0 पूर्ण,
	अणु ATTO_VENDOR_ID, 0x0049,	  ATTO_VENDOR_ID, 0x004C,
	  0,
	  0, 0 पूर्ण,
	अणु ATTO_VENDOR_ID, 0x0049,	  ATTO_VENDOR_ID, 0x004D,
	  0,
	  0, 0 पूर्ण,
	अणु ATTO_VENDOR_ID, 0x0049,	  ATTO_VENDOR_ID, 0x004E,
	  0,
	  0, 0 पूर्ण,
	अणु 0,		  0,		  0,		  0,
	  0,
	  0, 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, esas2r_pci_table);

अटल पूर्णांक
esas2r_probe(काष्ठा pci_dev *pcid, स्थिर काष्ठा pci_device_id *id);

अटल व्योम
esas2r_हटाओ(काष्ठा pci_dev *pcid);

अटल काष्ठा pci_driver
	esas2r_pci_driver = अणु
	.name		= ESAS2R_DRVR_NAME,
	.id_table	= esas2r_pci_table,
	.probe		= esas2r_probe,
	.हटाओ		= esas2r_हटाओ,
	.driver.pm	= &esas2r_pm_ops,
पूर्ण;

अटल पूर्णांक esas2r_probe(काष्ठा pci_dev *pcid,
			स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *host = शून्य;
	काष्ठा esas2r_adapter *a;
	पूर्णांक err;

	माप_प्रकार host_alloc_size = माप(काष्ठा esas2r_adapter)
				 + ((num_requests) +
				    1) * माप(काष्ठा esas2r_request);

	esas2r_log_dev(ESAS2R_LOG_DEBG, &(pcid->dev),
		       "esas2r_probe() 0x%02x 0x%02x 0x%02x 0x%02x",
		       pcid->venकरोr,
		       pcid->device,
		       pcid->subप्रणाली_venकरोr,
		       pcid->subप्रणाली_device);

	esas2r_log_dev(ESAS2R_LOG_INFO, &(pcid->dev),
		       "before pci_enable_device() "
		       "enable_cnt: %d",
		       pcid->enable_cnt.counter);

	err = pci_enable_device(pcid);
	अगर (err != 0) अणु
		esas2r_log_dev(ESAS2R_LOG_CRIT, &(pcid->dev),
			       "pci_enable_device() FAIL (%d)",
			       err);
		वापस -ENODEV;
	पूर्ण

	esas2r_log_dev(ESAS2R_LOG_INFO, &(pcid->dev),
		       "pci_enable_device() OK");
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pcid->dev),
		       "after pci_enable_device() enable_cnt: %d",
		       pcid->enable_cnt.counter);

	host = scsi_host_alloc(&driver_ढाँचा, host_alloc_size);
	अगर (host == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT, "scsi_host_alloc() FAIL");
		वापस -ENODEV;
	पूर्ण

	स_रखो(host->hostdata, 0, host_alloc_size);

	a = (काष्ठा esas2r_adapter *)host->hostdata;

	esas2r_log(ESAS2R_LOG_INFO, "scsi_host_alloc() OK host: %p", host);

	/* override max LUN and max target id */

	host->max_id = ESAS2R_MAX_ID + 1;
	host->max_lun = 255;

	/* we can handle 16-byte CDbs */

	host->max_cmd_len = 16;

	host->can_queue = can_queue;
	host->cmd_per_lun = cmd_per_lun;
	host->this_id = host->max_id + 1;
	host->max_channel = 0;
	host->unique_id = found_adapters;
	host->sg_tablesize = sg_tablesize;
	host->max_sectors = esas2r_max_sectors;

	/* set to bus master क्रम BIOses that करोn't करो it क्रम us */

	esas2r_log(ESAS2R_LOG_INFO, "pci_set_master() called");

	pci_set_master(pcid);

	अगर (!esas2r_init_adapter(host, pcid, found_adapters)) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "unable to initialize device at PCI bus %x:%x",
			   pcid->bus->number,
			   pcid->devfn);

		esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
			       "scsi_host_put() called");

		scsi_host_put(host);

		वापस 0;

	पूर्ण

	esas2r_log(ESAS2R_LOG_INFO, "pci_set_drvdata(%p, %p) called", pcid,
		   host->hostdata);

	pci_set_drvdata(pcid, host);

	esas2r_log(ESAS2R_LOG_INFO, "scsi_add_host() called");

	err = scsi_add_host(host, &pcid->dev);

	अगर (err) अणु
		esas2r_log(ESAS2R_LOG_CRIT, "scsi_add_host returned %d", err);
		esas2r_log_dev(ESAS2R_LOG_CRIT, &(host->shost_gendev),
			       "scsi_add_host() FAIL");

		esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
			       "scsi_host_put() called");

		scsi_host_put(host);

		esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
			       "pci_set_drvdata(%p, NULL) called",
			       pcid);

		pci_set_drvdata(pcid, शून्य);

		वापस -ENODEV;
	पूर्ण


	esas2r_fw_event_on(a);

	esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
		       "scsi_scan_host() called");

	scsi_scan_host(host);

	/* Add sysfs binary files */
	अगर (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_fw))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: fw");
	अन्यथा
		a->sysfs_fw_created = 1;

	अगर (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_fs))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: fs");
	अन्यथा
		a->sysfs_fs_created = 1;

	अगर (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_vda))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: vda");
	अन्यथा
		a->sysfs_vda_created = 1;

	अगर (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_hw))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: hw");
	अन्यथा
		a->sysfs_hw_created = 1;

	अगर (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_live_nvram))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: live_nvram");
	अन्यथा
		a->sysfs_live_nvram_created = 1;

	अगर (sysfs_create_bin_file(&host->shost_dev.kobj,
				  &bin_attr_शेष_nvram))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: default_nvram");
	अन्यथा
		a->sysfs_शेष_nvram_created = 1;

	found_adapters++;

	वापस 0;
पूर्ण

अटल व्योम esas2r_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)host->hostdata;

	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "esas2r_remove(%p) called; "
		       "host:%p", pdev,
		       host);

	esas2r_समाप्त_adapter(a->index);
	found_adapters--;
पूर्ण

अटल पूर्णांक __init esas2r_init(व्योम)
अणु
	पूर्णांक i;

	esas2r_log(ESAS2R_LOG_INFO, "%s called", __func__);

	/* verअगरy valid parameters */

	अगर (can_queue < 1) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "warning: can_queue must be at least 1, value "
			   "forced.");
		can_queue = 1;
	पूर्ण अन्यथा अगर (can_queue > 2048) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "warning: can_queue must be no larger than 2048, "
			   "value forced.");
		can_queue = 2048;
	पूर्ण

	अगर (cmd_per_lun < 1) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "warning: cmd_per_lun must be at least 1, value "
			   "forced.");
		cmd_per_lun = 1;
	पूर्ण अन्यथा अगर (cmd_per_lun > 2048) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "warning: cmd_per_lun must be no larger than "
			   "2048, value forced.");
		cmd_per_lun = 2048;
	पूर्ण

	अगर (sg_tablesize < 32) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "warning: sg_tablesize must be at least 32, "
			   "value forced.");
		sg_tablesize = 32;
	पूर्ण

	अगर (esas2r_max_sectors < 1) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "warning: esas2r_max_sectors must be at least "
			   "1, value forced.");
		esas2r_max_sectors = 1;
	पूर्ण अन्यथा अगर (esas2r_max_sectors > 0xffff) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "warning: esas2r_max_sectors must be no larger "
			   "than 0xffff, value forced.");
		esas2r_max_sectors = 0xffff;
	पूर्ण

	sgl_page_size &= ~(ESAS2R_SGL_ALIGN - 1);

	अगर (sgl_page_size < SGL_PG_SZ_MIN)
		sgl_page_size = SGL_PG_SZ_MIN;
	अन्यथा अगर (sgl_page_size > SGL_PG_SZ_MAX)
		sgl_page_size = SGL_PG_SZ_MAX;

	अगर (num_sg_lists < NUM_SGL_MIN)
		num_sg_lists = NUM_SGL_MIN;
	अन्यथा अगर (num_sg_lists > NUM_SGL_MAX)
		num_sg_lists = NUM_SGL_MAX;

	अगर (num_requests < NUM_REQ_MIN)
		num_requests = NUM_REQ_MIN;
	अन्यथा अगर (num_requests > NUM_REQ_MAX)
		num_requests = NUM_REQ_MAX;

	अगर (num_ae_requests < NUM_AE_MIN)
		num_ae_requests = NUM_AE_MIN;
	अन्यथा अगर (num_ae_requests > NUM_AE_MAX)
		num_ae_requests = NUM_AE_MAX;

	/* set up other globals */

	क्रम (i = 0; i < MAX_ADAPTERS; i++)
		esas2r_adapters[i] = शून्य;

	वापस pci_रेजिस्टर_driver(&esas2r_pci_driver);
पूर्ण

/* Handle ioctl calls to "/proc/scsi/esas2r/ATTOnode" */
अटल स्थिर काष्ठा file_operations esas2r_proc_fops = अणु
	.compat_ioctl	= compat_ptr_ioctl,
	.unlocked_ioctl = esas2r_proc_ioctl,
पूर्ण;

अटल स्थिर काष्ठा proc_ops esas2r_proc_ops = अणु
	.proc_lseek		= शेष_llseek,
	.proc_ioctl		= esas2r_proc_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.proc_compat_ioctl	= compat_ptr_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा Scsi_Host *esas2r_proc_host;
अटल पूर्णांक esas2r_proc_major;

दीर्घ esas2r_proc_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस esas2r_ioctl_handler(esas2r_proc_host->hostdata,
				    cmd, (व्योम __user *)arg);
पूर्ण

अटल व्योम __निकास esas2r_निकास(व्योम)
अणु
	esas2r_log(ESAS2R_LOG_INFO, "%s called", __func__);

	अगर (esas2r_proc_major > 0) अणु
		esas2r_log(ESAS2R_LOG_INFO, "unregister proc");

		हटाओ_proc_entry(ATTONODE_NAME,
				  esas2r_proc_host->hostt->proc_dir);
		unरेजिस्टर_chrdev(esas2r_proc_major, ESAS2R_DRVR_NAME);

		esas2r_proc_major = 0;
	पूर्ण

	esas2r_log(ESAS2R_LOG_INFO, "pci_unregister_driver() called");

	pci_unरेजिस्टर_driver(&esas2r_pci_driver);
पूर्ण

पूर्णांक esas2r_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *sh)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)sh->hostdata;

	काष्ठा esas2r_target *t;
	पूर्णांक dev_count = 0;

	esas2r_log(ESAS2R_LOG_DEBG, "esas2r_show_info (%p,%d)", m, sh->host_no);

	seq_म_लिखो(m, ESAS2R_LONGNAME "\n"
		   "Driver version: "ESAS2R_VERSION_STR "\n"
		   "Flash version: %s\n"
		   "Firmware version: %s\n"
		   "Copyright "ESAS2R_COPYRIGHT_YEARS "\n"
		   "http://www.attotech.com\n"
		   "\n",
		   a->flash_rev,
		   a->fw_rev[0] ? a->fw_rev : "(none)");


	seq_म_लिखो(m, "Adapter information:\n"
		   "--------------------\n"
		   "Model: %s\n"
		   "SAS address: %02X%02X%02X%02X:%02X%02X%02X%02X\n",
		   esas2r_get_model_name(a),
		   a->nvram->sas_addr[0],
		   a->nvram->sas_addr[1],
		   a->nvram->sas_addr[2],
		   a->nvram->sas_addr[3],
		   a->nvram->sas_addr[4],
		   a->nvram->sas_addr[5],
		   a->nvram->sas_addr[6],
		   a->nvram->sas_addr[7]);

	seq_माला_दो(m, "\n"
		   "Discovered devices:\n"
		   "\n"
		   "   #  Target ID\n"
		   "---------------\n");

	क्रम (t = a->targetdb; t < a->targetdb_end; t++)
		अगर (t->buffered_target_state == TS_PRESENT) अणु
			seq_म_लिखो(m, " %3d   %3d\n",
				   ++dev_count,
				   (u16)(uपूर्णांकptr_t)(t - a->targetdb));
		पूर्ण

	अगर (dev_count == 0)
		seq_माला_दो(m, "none\n");

	seq_अ_दो(m, '\n');
	वापस 0;

पूर्ण

स्थिर अक्षर *esas2r_info(काष्ठा Scsi_Host *sh)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)sh->hostdata;
	अटल अक्षर esas2r_info_str[512];

	esas2r_log_dev(ESAS2R_LOG_INFO, &(sh->shost_gendev),
		       "esas2r_info() called");

	/*
	 * अगर we haven't करोne so alपढ़ोy, रेजिस्टर as a अक्षर driver
	 * and stick a node under "/proc/scsi/esas2r/ATTOnode"
	 */

	अगर (esas2r_proc_major <= 0) अणु
		esas2r_proc_host = sh;

		esas2r_proc_major = रेजिस्टर_chrdev(0, ESAS2R_DRVR_NAME,
						    &esas2r_proc_fops);

		esas2r_log_dev(ESAS2R_LOG_DEBG, &(sh->shost_gendev),
			       "register_chrdev (major %d)",
			       esas2r_proc_major);

		अगर (esas2r_proc_major > 0) अणु
			काष्ठा proc_dir_entry *pde;

			pde = proc_create(ATTONODE_NAME, 0,
					  sh->hostt->proc_dir,
					  &esas2r_proc_ops);

			अगर (!pde) अणु
				esas2r_log_dev(ESAS2R_LOG_WARN,
					       &(sh->shost_gendev),
					       "failed to create_proc_entry");
				esas2r_proc_major = -1;
			पूर्ण
		पूर्ण
	पूर्ण

	प्र_लिखो(esas2r_info_str,
		ESAS2R_LONGNAME " (bus 0x%02X, device 0x%02X, IRQ 0x%02X)"
		" driver version: "ESAS2R_VERSION_STR "  firmware version: "
		"%s\n",
		a->pcid->bus->number, a->pcid->devfn, a->pcid->irq,
		a->fw_rev[0] ? a->fw_rev : "(none)");

	वापस esas2r_info_str;
पूर्ण

/* Callback क्रम building a request scatter/gather list */
अटल u32 get_physaddr_from_sgc(काष्ठा esas2r_sg_context *sgc, u64 *addr)
अणु
	u32 len;

	अगर (likely(sgc->cur_offset == sgc->exp_offset)) अणु
		/*
		 * the normal हाल: caller used all bytes from previous call, so
		 * expected offset is the same as the current offset.
		 */

		अगर (sgc->sgel_count < sgc->num_sgel) अणु
			/* retrieve next segment, except क्रम first समय */
			अगर (sgc->exp_offset > (u8 *)0) अणु
				/* advance current segment */
				sgc->cur_sgel = sg_next(sgc->cur_sgel);
				++(sgc->sgel_count);
			पूर्ण


			len = sg_dma_len(sgc->cur_sgel);
			(*addr) = sg_dma_address(sgc->cur_sgel);

			/* save the total # bytes वापसed to caller so far */
			sgc->exp_offset += len;

		पूर्ण अन्यथा अणु
			len = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (sgc->cur_offset < sgc->exp_offset) अणु
		/*
		 * caller did not use all bytes from previous call. need to
		 * compute the address based on current segment.
		 */

		len = sg_dma_len(sgc->cur_sgel);
		(*addr) = sg_dma_address(sgc->cur_sgel);

		sgc->exp_offset -= len;

		/* calculate PA based on prev segment address and offsets */
		*addr = *addr +
			(sgc->cur_offset - sgc->exp_offset);

		sgc->exp_offset += len;

		/* re-calculate length based on offset */
		len = lower_32_bits(
			sgc->exp_offset - sgc->cur_offset);
	पूर्ण अन्यथा अणु   /* अगर ( sgc->cur_offset > sgc->exp_offset ) */
		   /*
		    * we करोn't expect the caller to skip ahead.
		    * cur_offset will never exceed the len we वापस
		    */
		len = 0;
	पूर्ण

	वापस len;
पूर्ण

पूर्णांक esas2r_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esas2r_adapter *a =
		(काष्ठा esas2r_adapter *)cmd->device->host->hostdata;
	काष्ठा esas2r_request *rq;
	काष्ठा esas2r_sg_context sgc;
	अचिन्हित bufflen;

	/* Assume success, अगर it fails we will fix the result later. */
	cmd->result = DID_OK << 16;

	अगर (unlikely(test_bit(AF_DEGRADED_MODE, &a->flags))) अणु
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण

	rq = esas2r_alloc_request(a);
	अगर (unlikely(rq == शून्य)) अणु
		esas2r_debug("esas2r_alloc_request failed");
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	rq->cmd = cmd;
	bufflen = scsi_bufflen(cmd);

	अगर (likely(bufflen != 0)) अणु
		अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
			rq->vrq->scsi.flags |= cpu_to_le32(FCP_CMND_WRD);
		अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
			rq->vrq->scsi.flags |= cpu_to_le32(FCP_CMND_RDD);
	पूर्ण

	स_नकल(rq->vrq->scsi.cdb, cmd->cmnd, cmd->cmd_len);
	rq->vrq->scsi.length = cpu_to_le32(bufflen);
	rq->target_id = cmd->device->id;
	rq->vrq->scsi.flags |= cpu_to_le32(cmd->device->lun);
	rq->sense_buf = cmd->sense_buffer;
	rq->sense_len = SCSI_SENSE_BUFFERSIZE;

	esas2r_sgc_init(&sgc, a, rq, शून्य);

	sgc.length = bufflen;
	sgc.cur_offset = शून्य;

	sgc.cur_sgel = scsi_sglist(cmd);
	sgc.exp_offset = शून्य;
	sgc.num_sgel = scsi_dma_map(cmd);
	sgc.sgel_count = 0;

	अगर (unlikely(sgc.num_sgel < 0)) अणु
		esas2r_मुक्त_request(a, rq);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	sgc.get_phys_addr = (PGETPHYSADDR)get_physaddr_from_sgc;

	अगर (unlikely(!esas2r_build_sg_list(a, rq, &sgc))) अणु
		scsi_dma_unmap(cmd);
		esas2r_मुक्त_request(a, rq);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	esas2r_debug("start request %p to %d:%d\n", rq, (पूर्णांक)cmd->device->id,
		     (पूर्णांक)cmd->device->lun);

	esas2r_start_request(a, rq);

	वापस 0;
पूर्ण

अटल व्योम complete_task_management_request(काष्ठा esas2r_adapter *a,
					     काष्ठा esas2r_request *rq)
अणु
	(*rq->task_management_status_ptr) = rq->req_stat;
	esas2r_मुक्त_request(a, rq);
पूर्ण

/*
 * Searches the specअगरied queue क्रम the specअगरied queue क्रम the command
 * to पात.
 *
 * Return 0 on failure, 1 अगर command was not found, 2 अगर command was found
 */
अटल पूर्णांक esas2r_check_active_queue(काष्ठा esas2r_adapter *a,
				     काष्ठा esas2r_request **पात_request,
				     काष्ठा scsi_cmnd *cmd,
				     काष्ठा list_head *queue)
अणु
	bool found = false;
	काष्ठा esas2r_request *ar = *पात_request;
	काष्ठा esas2r_request *rq;
	काष्ठा list_head *element, *next;

	list_क्रम_each_safe(element, next, queue) अणु

		rq = list_entry(element, काष्ठा esas2r_request, req_list);

		अगर (rq->cmd == cmd) अणु

			/* Found the request.  See what to करो with it. */
			अगर (queue == &a->active_list) अणु
				/*
				 * We are searching the active queue, which
				 * means that we need to send an पात request
				 * to the firmware.
				 */
				ar = esas2r_alloc_request(a);
				अगर (ar == शून्य) अणु
					esas2r_log_dev(ESAS2R_LOG_WARN,
						       &(a->host->shost_gendev),
						       "unable to allocate an abort request for cmd %p",
						       cmd);
					वापस 0; /* Failure */
				पूर्ण

				/*
				 * Task management request must be क्रमmatted
				 * with a lock held.
				 */
				ar->sense_len = 0;
				ar->vrq->scsi.length = 0;
				ar->target_id = rq->target_id;
				ar->vrq->scsi.flags |= cpu_to_le32(
					(u8)le32_to_cpu(rq->vrq->scsi.flags));

				स_रखो(ar->vrq->scsi.cdb, 0,
				       माप(ar->vrq->scsi.cdb));

				ar->vrq->scsi.flags |= cpu_to_le32(
					FCP_CMND_TRM);
				ar->vrq->scsi.u.पात_handle =
					rq->vrq->scsi.handle;
			पूर्ण अन्यथा अणु
				/*
				 * The request is pending but not active on
				 * the firmware.  Just मुक्त it now and we'll
				 * report the successful पात below.
				 */
				list_del_init(&rq->req_list);
				esas2r_मुक्त_request(a, rq);
			पूर्ण

			found = true;
			अवरोध;
		पूर्ण

	पूर्ण

	अगर (!found)
		वापस 1;       /* Not found */

	वापस 2;               /* found */


पूर्ण

पूर्णांक esas2r_eh_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esas2r_adapter *a =
		(काष्ठा esas2r_adapter *)cmd->device->host->hostdata;
	काष्ठा esas2r_request *पात_request = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *queue;
	पूर्णांक result;

	esas2r_log(ESAS2R_LOG_INFO, "eh_abort (%p)", cmd);

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags)) अणु
		cmd->result = DID_ABORT << 16;

		scsi_set_resid(cmd, 0);

		cmd->scsi_करोne(cmd);

		वापस SUCCESS;
	पूर्ण

	spin_lock_irqsave(&a->queue_lock, flags);

	/*
	 * Run through the defer and active queues looking क्रम the request
	 * to पात.
	 */

	queue = &a->defer_list;

check_active_queue:

	result = esas2r_check_active_queue(a, &पात_request, cmd, queue);

	अगर (!result) अणु
		spin_unlock_irqrestore(&a->queue_lock, flags);
		वापस FAILED;
	पूर्ण अन्यथा अगर (result == 2 && (queue == &a->defer_list)) अणु
		queue = &a->active_list;
		जाओ check_active_queue;
	पूर्ण

	spin_unlock_irqrestore(&a->queue_lock, flags);

	अगर (पात_request) अणु
		u8 task_management_status = RS_PENDING;

		/*
		 * the request is alपढ़ोy active, so we need to tell
		 * the firmware to पात it and रुको क्रम the response.
		 */

		पात_request->comp_cb = complete_task_management_request;
		पात_request->task_management_status_ptr =
			&task_management_status;

		esas2r_start_request(a, पात_request);

		अगर (atomic_पढ़ो(&a->disable_cnt) == 0)
			esas2r_करो_deferred_processes(a);

		जबतक (task_management_status == RS_PENDING)
			msleep(10);

		/*
		 * Once we get here, the original request will have been
		 * completed by the firmware and the पात request will have
		 * been cleaned up.  we're करोne!
		 */

		वापस SUCCESS;
	पूर्ण

	/*
	 * If we get here, either we found the inactive request and
	 * मुक्तd it, or we didn't find it at all.  Either way, success!
	 */

	cmd->result = DID_ABORT << 16;

	scsi_set_resid(cmd, 0);

	cmd->scsi_करोne(cmd);

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक esas2r_host_bus_reset(काष्ठा scsi_cmnd *cmd, bool host_reset)
अणु
	काष्ठा esas2r_adapter *a =
		(काष्ठा esas2r_adapter *)cmd->device->host->hostdata;

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		वापस FAILED;

	अगर (host_reset)
		esas2r_reset_adapter(a);
	अन्यथा
		esas2r_reset_bus(a);

	/* above call sets the AF_OS_RESET flag.  रुको क्रम it to clear. */

	जबतक (test_bit(AF_OS_RESET, &a->flags)) अणु
		msleep(10);

		अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
			वापस FAILED;
	पूर्ण

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		वापस FAILED;

	वापस SUCCESS;
पूर्ण

पूर्णांक esas2r_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	esas2r_log(ESAS2R_LOG_INFO, "host_reset (%p)", cmd);

	वापस esas2r_host_bus_reset(cmd, true);
पूर्ण

पूर्णांक esas2r_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	esas2r_log(ESAS2R_LOG_INFO, "bus_reset (%p)", cmd);

	वापस esas2r_host_bus_reset(cmd, false);
पूर्ण

अटल पूर्णांक esas2r_dev_targ_reset(काष्ठा scsi_cmnd *cmd, bool target_reset)
अणु
	काष्ठा esas2r_adapter *a =
		(काष्ठा esas2r_adapter *)cmd->device->host->hostdata;
	काष्ठा esas2r_request *rq;
	u8 task_management_status = RS_PENDING;
	bool completed;

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		वापस FAILED;

retry:
	rq = esas2r_alloc_request(a);
	अगर (rq == शून्य) अणु
		अगर (target_reset) अणु
			esas2r_log(ESAS2R_LOG_CRIT,
				   "unable to allocate a request for a "
				   "target reset (%d)!",
				   cmd->device->id);
		पूर्ण अन्यथा अणु
			esas2r_log(ESAS2R_LOG_CRIT,
				   "unable to allocate a request for a "
				   "device reset (%d:%llu)!",
				   cmd->device->id,
				   cmd->device->lun);
		पूर्ण


		वापस FAILED;
	पूर्ण

	rq->target_id = cmd->device->id;
	rq->vrq->scsi.flags |= cpu_to_le32(cmd->device->lun);
	rq->req_stat = RS_PENDING;

	rq->comp_cb = complete_task_management_request;
	rq->task_management_status_ptr = &task_management_status;

	अगर (target_reset) अणु
		esas2r_debug("issuing target reset (%p) to id %d", rq,
			     cmd->device->id);
		completed = esas2r_send_task_mgmt(a, rq, 0x20);
	पूर्ण अन्यथा अणु
		esas2r_debug("issuing device reset (%p) to id %d lun %d", rq,
			     cmd->device->id, cmd->device->lun);
		completed = esas2r_send_task_mgmt(a, rq, 0x10);
	पूर्ण

	अगर (completed) अणु
		/* Task management cmd completed right away, need to मुक्त it. */

		esas2r_मुक्त_request(a, rq);
	पूर्ण अन्यथा अणु
		/*
		 * Wait क्रम firmware to complete the request.  Completion
		 * callback will मुक्त it.
		 */
		जबतक (task_management_status == RS_PENDING)
			msleep(10);
	पूर्ण

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		वापस FAILED;

	अगर (task_management_status == RS_BUSY) अणु
		/*
		 * Busy, probably because we are flashing.  Wait a bit and
		 * try again.
		 */
		msleep(100);
		जाओ retry;
	पूर्ण

	वापस SUCCESS;
पूर्ण

पूर्णांक esas2r_device_reset(काष्ठा scsi_cmnd *cmd)
अणु
	esas2r_log(ESAS2R_LOG_INFO, "device_reset (%p)", cmd);

	वापस esas2r_dev_targ_reset(cmd, false);

पूर्ण

पूर्णांक esas2r_target_reset(काष्ठा scsi_cmnd *cmd)
अणु
	esas2r_log(ESAS2R_LOG_INFO, "target_reset (%p)", cmd);

	वापस esas2r_dev_targ_reset(cmd, true);
पूर्ण

व्योम esas2r_log_request_failure(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq)
अणु
	u8 reqstatus = rq->req_stat;

	अगर (reqstatus == RS_SUCCESS)
		वापस;

	अगर (rq->vrq->scsi.function == VDA_FUNC_SCSI) अणु
		अगर (reqstatus == RS_SCSI_ERROR) अणु
			अगर (rq->func_rsp.scsi_rsp.sense_len >= 13) अणु
				esas2r_log(ESAS2R_LOG_WARN,
					   "request failure - SCSI error %x ASC:%x ASCQ:%x CDB:%x",
					   rq->sense_buf[2], rq->sense_buf[12],
					   rq->sense_buf[13],
					   rq->vrq->scsi.cdb[0]);
			पूर्ण अन्यथा अणु
				esas2r_log(ESAS2R_LOG_WARN,
					   "request failure - SCSI error CDB:%x\n",
					   rq->vrq->scsi.cdb[0]);
			पूर्ण
		पूर्ण अन्यथा अगर ((rq->vrq->scsi.cdb[0] != INQUIRY
			    && rq->vrq->scsi.cdb[0] != REPORT_LUNS)
			   || (reqstatus != RS_SEL
			       && reqstatus != RS_SEL2)) अणु
			अगर ((reqstatus == RS_UNDERRUN) &&
			    (rq->vrq->scsi.cdb[0] == INQUIRY)) अणु
				/* Don't log inquiry underruns */
			पूर्ण अन्यथा अणु
				esas2r_log(ESAS2R_LOG_WARN,
					   "request failure - cdb:%x reqstatus:%d target:%d",
					   rq->vrq->scsi.cdb[0], reqstatus,
					   rq->target_id);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम esas2r_रुको_request(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq)
अणु
	u32 startसमय;
	u32 समयout;

	startसमय = jअगरfies_to_msecs(jअगरfies);
	समयout = rq->समयout ? rq->समयout : 5000;

	जबतक (true) अणु
		esas2r_polled_पूर्णांकerrupt(a);

		अगर (rq->req_stat != RS_STARTED)
			अवरोध;

		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

		अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > समयout) अणु
			esas2r_hdebug("request TMO");
			esas2r_bugon();

			rq->req_stat = RS_TIMEOUT;

			esas2r_local_reset_adapter(a);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

u32 esas2r_map_data_winकरोw(काष्ठा esas2r_adapter *a, u32 addr_lo)
अणु
	u32 offset = addr_lo & (MW_DATA_WINDOW_SIZE - 1);
	u32 base = addr_lo & -(चिन्हित पूर्णांक)MW_DATA_WINDOW_SIZE;

	अगर (a->winकरोw_base != base) अणु
		esas2r_ग_लिखो_रेजिस्टर_dword(a, MVR_PCI_WIN1_REMAP,
					    base | MVRPW1R_ENABLE);
		esas2r_flush_रेजिस्टर_dword(a, MVR_PCI_WIN1_REMAP);
		a->winकरोw_base = base;
	पूर्ण

	वापस offset;
पूर्ण

/* Read a block of data from chip memory */
bool esas2r_पढ़ो_mem_block(काष्ठा esas2r_adapter *a,
			   व्योम *to,
			   u32 from,
			   u32 size)
अणु
	u8 *end = (u8 *)to;

	जबतक (size) अणु
		u32 len;
		u32 offset;
		u32 iatvr;

		iatvr = (from & -(चिन्हित पूर्णांक)MW_DATA_WINDOW_SIZE);

		esas2r_map_data_winकरोw(a, iatvr);

		offset = from & (MW_DATA_WINDOW_SIZE - 1);
		len = size;

		अगर (len > MW_DATA_WINDOW_SIZE - offset)
			len = MW_DATA_WINDOW_SIZE - offset;

		from += len;
		size -= len;

		जबतक (len--) अणु
			*end++ = esas2r_पढ़ो_data_byte(a, offset);
			offset++;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

व्योम esas2r_nuxi_mgt_data(u8 function, व्योम *data)
अणु
	काष्ठा atto_vda_grp_info *g;
	काष्ठा atto_vda_devinfo *d;
	काष्ठा atto_vdapart_info *p;
	काष्ठा atto_vda_dh_info *h;
	काष्ठा atto_vda_metrics_info *m;
	काष्ठा atto_vda_schedule_info *s;
	काष्ठा atto_vda_buzzer_info *b;
	u8 i;

	चयन (function) अणु
	हाल VDAMGT_BUZZER_INFO:
	हाल VDAMGT_BUZZER_SET:

		b = (काष्ठा atto_vda_buzzer_info *)data;

		b->duration = le32_to_cpu(b->duration);
		अवरोध;

	हाल VDAMGT_SCHEDULE_INFO:
	हाल VDAMGT_SCHEDULE_EVENT:

		s = (काष्ठा atto_vda_schedule_info *)data;

		s->id = le32_to_cpu(s->id);

		अवरोध;

	हाल VDAMGT_DEV_INFO:
	हाल VDAMGT_DEV_CLEAN:
	हाल VDAMGT_DEV_PT_INFO:
	हाल VDAMGT_DEV_FEATURES:
	हाल VDAMGT_DEV_PT_FEATURES:
	हाल VDAMGT_DEV_OPERATION:

		d = (काष्ठा atto_vda_devinfo *)data;

		d->capacity = le64_to_cpu(d->capacity);
		d->block_size = le32_to_cpu(d->block_size);
		d->ses_dev_index = le16_to_cpu(d->ses_dev_index);
		d->target_id = le16_to_cpu(d->target_id);
		d->lun = le16_to_cpu(d->lun);
		d->features = le16_to_cpu(d->features);
		अवरोध;

	हाल VDAMGT_GRP_INFO:
	हाल VDAMGT_GRP_CREATE:
	हाल VDAMGT_GRP_DELETE:
	हाल VDAMGT_ADD_STORAGE:
	हाल VDAMGT_MEMBER_ADD:
	हाल VDAMGT_GRP_COMMIT:
	हाल VDAMGT_GRP_REBUILD:
	हाल VDAMGT_GRP_COMMIT_INIT:
	हाल VDAMGT_QUICK_RAID:
	हाल VDAMGT_GRP_FEATURES:
	हाल VDAMGT_GRP_COMMIT_INIT_AUTOMAP:
	हाल VDAMGT_QUICK_RAID_INIT_AUTOMAP:
	हाल VDAMGT_SPARE_LIST:
	हाल VDAMGT_SPARE_ADD:
	हाल VDAMGT_SPARE_REMOVE:
	हाल VDAMGT_LOCAL_SPARE_ADD:
	हाल VDAMGT_GRP_OPERATION:

		g = (काष्ठा atto_vda_grp_info *)data;

		g->capacity = le64_to_cpu(g->capacity);
		g->block_size = le32_to_cpu(g->block_size);
		g->पूर्णांकerleave = le32_to_cpu(g->पूर्णांकerleave);
		g->features = le16_to_cpu(g->features);

		क्रम (i = 0; i < 32; i++)
			g->members[i] = le16_to_cpu(g->members[i]);

		अवरोध;

	हाल VDAMGT_PART_INFO:
	हाल VDAMGT_PART_MAP:
	हाल VDAMGT_PART_UNMAP:
	हाल VDAMGT_PART_AUTOMAP:
	हाल VDAMGT_PART_SPLIT:
	हाल VDAMGT_PART_MERGE:

		p = (काष्ठा atto_vdapart_info *)data;

		p->part_size = le64_to_cpu(p->part_size);
		p->start_lba = le32_to_cpu(p->start_lba);
		p->block_size = le32_to_cpu(p->block_size);
		p->target_id = le16_to_cpu(p->target_id);
		अवरोध;

	हाल VDAMGT_DEV_HEALTH_REQ:

		h = (काष्ठा atto_vda_dh_info *)data;

		h->med_defect_cnt = le32_to_cpu(h->med_defect_cnt);
		h->info_exc_cnt = le32_to_cpu(h->info_exc_cnt);
		अवरोध;

	हाल VDAMGT_DEV_METRICS:

		m = (काष्ठा atto_vda_metrics_info *)data;

		क्रम (i = 0; i < 32; i++)
			m->dev_indexes[i] = le16_to_cpu(m->dev_indexes[i]);

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम esas2r_nuxi_cfg_data(u8 function, व्योम *data)
अणु
	काष्ठा atto_vda_cfg_init *ci;

	चयन (function) अणु
	हाल VDA_CFG_INIT:
	हाल VDA_CFG_GET_INIT:
	हाल VDA_CFG_GET_INIT2:

		ci = (काष्ठा atto_vda_cfg_init *)data;

		ci->date_समय.year = le16_to_cpu(ci->date_समय.year);
		ci->sgl_page_size = le32_to_cpu(ci->sgl_page_size);
		ci->vda_version = le32_to_cpu(ci->vda_version);
		ci->epoch_समय = le32_to_cpu(ci->epoch_समय);
		ci->ioctl_tunnel = le32_to_cpu(ci->ioctl_tunnel);
		ci->num_tarमाला_लो_backend = le32_to_cpu(ci->num_tarमाला_लो_backend);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम esas2r_nuxi_ae_data(जोड़ atto_vda_ae *ae)
अणु
	काष्ठा atto_vda_ae_raid *r = &ae->raid;
	काष्ठा atto_vda_ae_lu *l = &ae->lu;

	चयन (ae->hdr.bytype) अणु
	हाल VDAAE_HDR_TYPE_RAID:

		r->dwflags = le32_to_cpu(r->dwflags);
		अवरोध;

	हाल VDAAE_HDR_TYPE_LU:

		l->dwevent = le32_to_cpu(l->dwevent);
		l->wphys_target_id = le16_to_cpu(l->wphys_target_id);
		l->id.tgtlun.wtarget_id = le16_to_cpu(l->id.tgtlun.wtarget_id);

		अगर (l->hdr.bylength >= दुरत्व(काष्ठा atto_vda_ae_lu, id)
		    + माप(काष्ठा atto_vda_ae_lu_tgt_lun_raid)) अणु
			l->id.tgtlun_raid.dwपूर्णांकerleave
				= le32_to_cpu(l->id.tgtlun_raid.dwपूर्णांकerleave);
			l->id.tgtlun_raid.dwblock_size
				= le32_to_cpu(l->id.tgtlun_raid.dwblock_size);
		पूर्ण

		अवरोध;

	हाल VDAAE_HDR_TYPE_DISK:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम esas2r_मुक्त_request(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq)
अणु
	अचिन्हित दीर्घ flags;

	esas2r_rq_destroy_request(rq, a);
	spin_lock_irqsave(&a->request_lock, flags);
	list_add(&rq->comp_list, &a->avail_request);
	spin_unlock_irqrestore(&a->request_lock, flags);
पूर्ण

काष्ठा esas2r_request *esas2r_alloc_request(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_request *rq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&a->request_lock, flags);

	अगर (unlikely(list_empty(&a->avail_request))) अणु
		spin_unlock_irqrestore(&a->request_lock, flags);
		वापस शून्य;
	पूर्ण

	rq = list_first_entry(&a->avail_request, काष्ठा esas2r_request,
			      comp_list);
	list_del(&rq->comp_list);
	spin_unlock_irqrestore(&a->request_lock, flags);
	esas2r_rq_init_request(rq, a);

	वापस rq;

पूर्ण

व्योम esas2r_complete_request_cb(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq)
अणु
	esas2r_debug("completing request %p\n", rq);

	scsi_dma_unmap(rq->cmd);

	अगर (unlikely(rq->req_stat != RS_SUCCESS)) अणु
		esas2r_debug("[%x STATUS %x:%x (%x)]", rq->target_id,
			     rq->req_stat,
			     rq->func_rsp.scsi_rsp.scsi_stat,
			     rq->cmd);

		rq->cmd->result =
			((esas2r_req_status_to_error(rq->req_stat) << 16)
			 | (rq->func_rsp.scsi_rsp.scsi_stat & STATUS_MASK));

		अगर (rq->req_stat == RS_UNDERRUN)
			scsi_set_resid(rq->cmd,
				       le32_to_cpu(rq->func_rsp.scsi_rsp.
						   residual_length));
		अन्यथा
			scsi_set_resid(rq->cmd, 0);
	पूर्ण

	rq->cmd->scsi_करोne(rq->cmd);

	esas2r_मुक्त_request(a, rq);
पूर्ण

/* Run tasklet to handle stuff outside of पूर्णांकerrupt context. */
व्योम esas2r_adapter_tasklet(अचिन्हित दीर्घ context)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)context;

	अगर (unlikely(test_bit(AF2_TIMER_TICK, &a->flags2))) अणु
		clear_bit(AF2_TIMER_TICK, &a->flags2);
		esas2r_समयr_tick(a);
	पूर्ण

	अगर (likely(test_bit(AF2_INT_PENDING, &a->flags2))) अणु
		clear_bit(AF2_INT_PENDING, &a->flags2);
		esas2r_adapter_पूर्णांकerrupt(a);
	पूर्ण

	अगर (esas2r_is_tasklet_pending(a))
		esas2r_करो_tasklet_tasks(a);

	अगर (esas2r_is_tasklet_pending(a)
	    || (test_bit(AF2_INT_PENDING, &a->flags2))
	    || (test_bit(AF2_TIMER_TICK, &a->flags2))) अणु
		clear_bit(AF_TASKLET_SCHEDULED, &a->flags);
		esas2r_schedule_tasklet(a);
	पूर्ण अन्यथा अणु
		clear_bit(AF_TASKLET_SCHEDULED, &a->flags);
	पूर्ण
पूर्ण

अटल व्योम esas2r_समयr_callback(काष्ठा समयr_list *t);

व्योम esas2r_kickoff_समयr(काष्ठा esas2r_adapter *a)
अणु
	समयr_setup(&a->समयr, esas2r_समयr_callback, 0);

	a->समयr.expires = jअगरfies +
			   msecs_to_jअगरfies(100);

	add_समयr(&a->समयr);
पूर्ण

अटल व्योम esas2r_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा esas2r_adapter *a = from_समयr(a, t, समयr);

	set_bit(AF2_TIMER_TICK, &a->flags2);

	esas2r_schedule_tasklet(a);

	esas2r_kickoff_समयr(a);
पूर्ण

/*
 * Firmware events need to be handled outside of पूर्णांकerrupt context
 * so we schedule a delayed_work to handle them.
 */

अटल व्योम
esas2r_मुक्त_fw_event(काष्ठा esas2r_fw_event_work *fw_event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा esas2r_adapter *a = fw_event->a;

	spin_lock_irqsave(&a->fw_event_lock, flags);
	list_del(&fw_event->list);
	kमुक्त(fw_event);
	spin_unlock_irqrestore(&a->fw_event_lock, flags);
पूर्ण

व्योम
esas2r_fw_event_off(काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&a->fw_event_lock, flags);
	a->fw_events_off = 1;
	spin_unlock_irqrestore(&a->fw_event_lock, flags);
पूर्ण

व्योम
esas2r_fw_event_on(काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&a->fw_event_lock, flags);
	a->fw_events_off = 0;
	spin_unlock_irqrestore(&a->fw_event_lock, flags);
पूर्ण

अटल व्योम esas2r_add_device(काष्ठा esas2r_adapter *a, u16 target_id)
अणु
	पूर्णांक ret;
	काष्ठा scsi_device *scsi_dev;

	scsi_dev = scsi_device_lookup(a->host, 0, target_id, 0);

	अगर (scsi_dev) अणु
		esas2r_log_dev(
			ESAS2R_LOG_WARN,
			&(scsi_dev->
			  sdev_gendev),
			"scsi device already exists at id %d", target_id);

		scsi_device_put(scsi_dev);
	पूर्ण अन्यथा अणु
		esas2r_log_dev(
			ESAS2R_LOG_INFO,
			&(a->host->
			  shost_gendev),
			"scsi_add_device() called for 0:%d:0",
			target_id);

		ret = scsi_add_device(a->host, 0, target_id, 0);
		अगर (ret) अणु
			esas2r_log_dev(
				ESAS2R_LOG_CRIT,
				&(a->host->
				  shost_gendev),
				"scsi_add_device failed with %d for id %d",
				ret, target_id);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esas2r_हटाओ_device(काष्ठा esas2r_adapter *a, u16 target_id)
अणु
	काष्ठा scsi_device *scsi_dev;

	scsi_dev = scsi_device_lookup(a->host, 0, target_id, 0);

	अगर (scsi_dev) अणु
		scsi_device_set_state(scsi_dev, SDEV_OFFLINE);

		esas2r_log_dev(
			ESAS2R_LOG_INFO,
			&(scsi_dev->
			  sdev_gendev),
			"scsi_remove_device() called for 0:%d:0",
			target_id);

		scsi_हटाओ_device(scsi_dev);

		esas2r_log_dev(
			ESAS2R_LOG_INFO,
			&(scsi_dev->
			  sdev_gendev),
			"scsi_device_put() called");

		scsi_device_put(scsi_dev);
	पूर्ण अन्यथा अणु
		esas2r_log_dev(
			ESAS2R_LOG_WARN,
			&(a->host->shost_gendev),
			"no target found at id %d",
			target_id);
	पूर्ण
पूर्ण

/*
 * Sends a firmware asynchronous event to anyone who happens to be
 * listening on the defined ATTO VDA event ports.
 */
अटल व्योम esas2r_send_ae_event(काष्ठा esas2r_fw_event_work *fw_event)
अणु
	काष्ठा esas2r_vda_ae *ae = (काष्ठा esas2r_vda_ae *)fw_event->data;
	अक्षर *type;

	चयन (ae->vda_ae.hdr.bytype) अणु
	हाल VDAAE_HDR_TYPE_RAID:
		type = "RAID group state change";
		अवरोध;

	हाल VDAAE_HDR_TYPE_LU:
		type = "Mapped destination LU change";
		अवरोध;

	हाल VDAAE_HDR_TYPE_DISK:
		type = "Physical disk inventory change";
		अवरोध;

	हाल VDAAE_HDR_TYPE_RESET:
		type = "Firmware reset";
		अवरोध;

	हाल VDAAE_HDR_TYPE_LOG_INFO:
		type = "Event Log message (INFO level)";
		अवरोध;

	हाल VDAAE_HDR_TYPE_LOG_WARN:
		type = "Event Log message (WARN level)";
		अवरोध;

	हाल VDAAE_HDR_TYPE_LOG_CRIT:
		type = "Event Log message (CRIT level)";
		अवरोध;

	हाल VDAAE_HDR_TYPE_LOG_FAIL:
		type = "Event Log message (FAIL level)";
		अवरोध;

	हाल VDAAE_HDR_TYPE_NVC:
		type = "NVCache change";
		अवरोध;

	हाल VDAAE_HDR_TYPE_TLG_INFO:
		type = "Time stamped log message (INFO level)";
		अवरोध;

	हाल VDAAE_HDR_TYPE_TLG_WARN:
		type = "Time stamped log message (WARN level)";
		अवरोध;

	हाल VDAAE_HDR_TYPE_TLG_CRIT:
		type = "Time stamped log message (CRIT level)";
		अवरोध;

	हाल VDAAE_HDR_TYPE_PWRMGT:
		type = "Power management";
		अवरोध;

	हाल VDAAE_HDR_TYPE_MUTE:
		type = "Mute button pressed";
		अवरोध;

	हाल VDAAE_HDR_TYPE_DEV:
		type = "Device attribute change";
		अवरोध;

	शेष:
		type = "Unknown";
		अवरोध;
	पूर्ण

	esas2r_log(ESAS2R_LOG_WARN,
		   "An async event of type \"%s\" was received from the firmware.  The event contents are:",
		   type);
	esas2r_log_hexdump(ESAS2R_LOG_WARN, &ae->vda_ae,
			   ae->vda_ae.hdr.bylength);

पूर्ण

अटल व्योम
esas2r_firmware_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा esas2r_fw_event_work *fw_event =
		container_of(work, काष्ठा esas2r_fw_event_work, work.work);

	काष्ठा esas2r_adapter *a = fw_event->a;

	u16 target_id = *(u16 *)&fw_event->data[0];

	अगर (a->fw_events_off)
		जाओ करोne;

	चयन (fw_event->type) अणु
	हाल fw_event_null:
		अवरोध; /* करो nothing */

	हाल fw_event_lun_change:
		esas2r_हटाओ_device(a, target_id);
		esas2r_add_device(a, target_id);
		अवरोध;

	हाल fw_event_present:
		esas2r_add_device(a, target_id);
		अवरोध;

	हाल fw_event_not_present:
		esas2r_हटाओ_device(a, target_id);
		अवरोध;

	हाल fw_event_vda_ae:
		esas2r_send_ae_event(fw_event);
		अवरोध;
	पूर्ण

करोne:
	esas2r_मुक्त_fw_event(fw_event);
पूर्ण

व्योम esas2r_queue_fw_event(काष्ठा esas2r_adapter *a,
			   क्रमागत fw_event_type type,
			   व्योम *data,
			   पूर्णांक data_sz)
अणु
	काष्ठा esas2r_fw_event_work *fw_event;
	अचिन्हित दीर्घ flags;

	fw_event = kzalloc(माप(काष्ठा esas2r_fw_event_work), GFP_ATOMIC);
	अगर (!fw_event) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "esas2r_queue_fw_event failed to alloc");
		वापस;
	पूर्ण

	अगर (type == fw_event_vda_ae) अणु
		काष्ठा esas2r_vda_ae *ae =
			(काष्ठा esas2r_vda_ae *)fw_event->data;

		ae->signature = ESAS2R_VDA_EVENT_SIG;
		ae->bus_number = a->pcid->bus->number;
		ae->devfn = a->pcid->devfn;
		स_नकल(&ae->vda_ae, data, माप(ae->vda_ae));
	पूर्ण अन्यथा अणु
		स_नकल(fw_event->data, data, data_sz);
	पूर्ण

	fw_event->type = type;
	fw_event->a = a;

	spin_lock_irqsave(&a->fw_event_lock, flags);
	list_add_tail(&fw_event->list, &a->fw_event_list);
	INIT_DELAYED_WORK(&fw_event->work, esas2r_firmware_event_work);
	queue_delayed_work_on(
		smp_processor_id(), a->fw_event_q, &fw_event->work,
		msecs_to_jअगरfies(1));
	spin_unlock_irqrestore(&a->fw_event_lock, flags);
पूर्ण

व्योम esas2r_target_state_changed(काष्ठा esas2r_adapter *a, u16 targ_id,
				 u8 state)
अणु
	अगर (state == TS_LUN_CHANGE)
		esas2r_queue_fw_event(a, fw_event_lun_change, &targ_id,
				      माप(targ_id));
	अन्यथा अगर (state == TS_PRESENT)
		esas2r_queue_fw_event(a, fw_event_present, &targ_id,
				      माप(targ_id));
	अन्यथा अगर (state == TS_NOT_PRESENT)
		esas2r_queue_fw_event(a, fw_event_not_present, &targ_id,
				      माप(targ_id));
पूर्ण

/* Translate status to a Linux SCSI mid-layer error code */
पूर्णांक esas2r_req_status_to_error(u8 req_stat)
अणु
	चयन (req_stat) अणु
	हाल RS_OVERRUN:
	हाल RS_UNDERRUN:
	हाल RS_SUCCESS:
	/*
	 * NOTE: SCSI mid-layer wants a good status क्रम a SCSI error, because
	 *       it will check the scsi_stat value in the completion anyway.
	 */
	हाल RS_SCSI_ERROR:
		वापस DID_OK;

	हाल RS_SEL:
	हाल RS_SEL2:
		वापस DID_NO_CONNECT;

	हाल RS_RESET:
		वापस DID_RESET;

	हाल RS_ABORTED:
		वापस DID_ABORT;

	हाल RS_BUSY:
		वापस DID_BUS_BUSY;
	पूर्ण

	/* everything अन्यथा is just an error. */

	वापस DID_ERROR;
पूर्ण

module_init(esas2r_init);
module_निकास(esas2r_निकास);
