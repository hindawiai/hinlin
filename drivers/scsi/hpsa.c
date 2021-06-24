<शैली गुरु>
/*
 *    Disk Array driver क्रम HP Smart Array SAS controllers
 *    Copyright (c) 2019-2020 Microchip Technology Inc. and its subsidiaries
 *    Copyright 2016 Microsemi Corporation
 *    Copyright 2014-2015 PMC-Sierra, Inc.
 *    Copyright 2000,2009-2015 Hewlett-Packard Development Company, L.P.
 *
 *    This program is मुक्त software; you can redistribute it and/or modअगरy
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; version 2 of the License.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 *    NON INFRINGEMENT.  See the GNU General Public License क्रम more details.
 *
 *    Questions/Comments/Bugfixes to esc.storagedev@microsemi.com
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/compat.h>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/completion.h>
#समावेश <linux/moduleparam.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <linux/cciss_ioctl.h>
#समावेश <linux/माला.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/atomic.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "hpsa_cmd.h"
#समावेश "hpsa.h"

/*
 * HPSA_DRIVER_VERSION must be 3 byte values (0-255) separated by '.'
 * with an optional trailing '-' followed by a byte value (0-255).
 */
#घोषणा HPSA_DRIVER_VERSION "3.4.20-200"
#घोषणा DRIVER_NAME "HP HPSA Driver (v " HPSA_DRIVER_VERSION ")"
#घोषणा HPSA "hpsa"

/* How दीर्घ to रुको क्रम CISS करोorbell communication */
#घोषणा CLEAR_EVENT_WAIT_INTERVAL 20	/* ms क्रम each msleep() call */
#घोषणा MODE_CHANGE_WAIT_INTERVAL 10	/* ms क्रम each msleep() call */
#घोषणा MAX_CLEAR_EVENT_WAIT 30000	/* बार 20 ms = 600 s */
#घोषणा MAX_MODE_CHANGE_WAIT 2000	/* बार 10 ms = 20 s */
#घोषणा MAX_IOCTL_CONFIG_WAIT 1000

/*define how many बार we will try a command because of bus resets */
#घोषणा MAX_CMD_RETRIES 3
/* How दीर्घ to रुको beक्रमe giving up on a command */
#घोषणा HPSA_EH_PTRAID_TIMEOUT (240 * HZ)

/* Embedded module करोcumentation macros - see modules.h */
MODULE_AUTHOR("Hewlett-Packard Company");
MODULE_DESCRIPTION("Driver for HP Smart Array Controller version " \
	HPSA_DRIVER_VERSION);
MODULE_VERSION(HPSA_DRIVER_VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("cciss");

अटल पूर्णांक hpsa_simple_mode;
module_param(hpsa_simple_mode, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(hpsa_simple_mode,
	"Use 'simple mode' rather than 'performant mode'");

/* define the PCI info क्रम the cards we can control */
अटल स्थिर काष्ठा pci_device_id hpsa_pci_device_id[] = अणु
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x3241पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x3243पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x3245पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x3247पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x3249पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x324Aपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x324Bपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSE,     0x103C, 0x3233पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSF,     0x103C, 0x3350पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSF,     0x103C, 0x3351पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSF,     0x103C, 0x3352पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSF,     0x103C, 0x3353पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSF,     0x103C, 0x3354पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSF,     0x103C, 0x3355पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSF,     0x103C, 0x3356पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103c, 0x1920पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103C, 0x1921पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103C, 0x1922पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103C, 0x1923पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103C, 0x1924पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103c, 0x1925पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103C, 0x1926पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103C, 0x1928पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSH,     0x103C, 0x1929पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21BDपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21BEपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21BFपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C0पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C1पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C2पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C3पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C4पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C5पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C6पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C7पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C8पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21C9पूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21CAपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21CBपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21CCपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21CDपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_DEVICE_ID_HP_CISSI,     0x103C, 0x21CEपूर्ण,
	अणुPCI_VENDOR_ID_ADAPTEC2, 0x0290, 0x9005, 0x0580पूर्ण,
	अणुPCI_VENDOR_ID_ADAPTEC2, 0x0290, 0x9005, 0x0581पूर्ण,
	अणुPCI_VENDOR_ID_ADAPTEC2, 0x0290, 0x9005, 0x0582पूर्ण,
	अणुPCI_VENDOR_ID_ADAPTEC2, 0x0290, 0x9005, 0x0583पूर्ण,
	अणुPCI_VENDOR_ID_ADAPTEC2, 0x0290, 0x9005, 0x0584पूर्ण,
	अणुPCI_VENDOR_ID_ADAPTEC2, 0x0290, 0x9005, 0x0585पूर्ण,
	अणुPCI_VENDOR_ID_HP_3PAR, 0x0075, 0x1590, 0x0076पूर्ण,
	अणुPCI_VENDOR_ID_HP_3PAR, 0x0075, 0x1590, 0x0087पूर्ण,
	अणुPCI_VENDOR_ID_HP_3PAR, 0x0075, 0x1590, 0x007Dपूर्ण,
	अणुPCI_VENDOR_ID_HP_3PAR, 0x0075, 0x1590, 0x0088पूर्ण,
	अणुPCI_VENDOR_ID_HP, 0x333f, 0x103c, 0x333fपूर्ण,
	अणुPCI_VENDOR_ID_HP,     PCI_ANY_ID,	PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_STORAGE_RAID << 8, 0xffff << 8, 0पूर्ण,
	अणुPCI_VENDOR_ID_COMPAQ,     PCI_ANY_ID,	PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_STORAGE_RAID << 8, 0xffff << 8, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, hpsa_pci_device_id);

/*  board_id = Subप्रणाली Device ID & Venकरोr ID
 *  product = Marketing Name क्रम the board
 *  access = Address of the काष्ठा of function poपूर्णांकers
 */
अटल काष्ठा board_type products[] = अणु
	अणु0x40700E11, "Smart Array 5300", &SA5A_accessपूर्ण,
	अणु0x40800E11, "Smart Array 5i", &SA5B_accessपूर्ण,
	अणु0x40820E11, "Smart Array 532", &SA5B_accessपूर्ण,
	अणु0x40830E11, "Smart Array 5312", &SA5B_accessपूर्ण,
	अणु0x409A0E11, "Smart Array 641", &SA5A_accessपूर्ण,
	अणु0x409B0E11, "Smart Array 642", &SA5A_accessपूर्ण,
	अणु0x409C0E11, "Smart Array 6400", &SA5A_accessपूर्ण,
	अणु0x409D0E11, "Smart Array 6400 EM", &SA5A_accessपूर्ण,
	अणु0x40910E11, "Smart Array 6i", &SA5A_accessपूर्ण,
	अणु0x3225103C, "Smart Array P600", &SA5A_accessपूर्ण,
	अणु0x3223103C, "Smart Array P800", &SA5A_accessपूर्ण,
	अणु0x3234103C, "Smart Array P400", &SA5A_accessपूर्ण,
	अणु0x3235103C, "Smart Array P400i", &SA5A_accessपूर्ण,
	अणु0x3211103C, "Smart Array E200i", &SA5A_accessपूर्ण,
	अणु0x3212103C, "Smart Array E200", &SA5A_accessपूर्ण,
	अणु0x3213103C, "Smart Array E200i", &SA5A_accessपूर्ण,
	अणु0x3214103C, "Smart Array E200i", &SA5A_accessपूर्ण,
	अणु0x3215103C, "Smart Array E200i", &SA5A_accessपूर्ण,
	अणु0x3237103C, "Smart Array E500", &SA5A_accessपूर्ण,
	अणु0x323D103C, "Smart Array P700m", &SA5A_accessपूर्ण,
	अणु0x3241103C, "Smart Array P212", &SA5_accessपूर्ण,
	अणु0x3243103C, "Smart Array P410", &SA5_accessपूर्ण,
	अणु0x3245103C, "Smart Array P410i", &SA5_accessपूर्ण,
	अणु0x3247103C, "Smart Array P411", &SA5_accessपूर्ण,
	अणु0x3249103C, "Smart Array P812", &SA5_accessपूर्ण,
	अणु0x324A103C, "Smart Array P712m", &SA5_accessपूर्ण,
	अणु0x324B103C, "Smart Array P711m", &SA5_accessपूर्ण,
	अणु0x3233103C, "HP StorageWorks 1210m", &SA5_accessपूर्ण, /* alias of 333f */
	अणु0x3350103C, "Smart Array P222", &SA5_accessपूर्ण,
	अणु0x3351103C, "Smart Array P420", &SA5_accessपूर्ण,
	अणु0x3352103C, "Smart Array P421", &SA5_accessपूर्ण,
	अणु0x3353103C, "Smart Array P822", &SA5_accessपूर्ण,
	अणु0x3354103C, "Smart Array P420i", &SA5_accessपूर्ण,
	अणु0x3355103C, "Smart Array P220i", &SA5_accessपूर्ण,
	अणु0x3356103C, "Smart Array P721m", &SA5_accessपूर्ण,
	अणु0x1920103C, "Smart Array P430i", &SA5_accessपूर्ण,
	अणु0x1921103C, "Smart Array P830i", &SA5_accessपूर्ण,
	अणु0x1922103C, "Smart Array P430", &SA5_accessपूर्ण,
	अणु0x1923103C, "Smart Array P431", &SA5_accessपूर्ण,
	अणु0x1924103C, "Smart Array P830", &SA5_accessपूर्ण,
	अणु0x1925103C, "Smart Array P831", &SA5_accessपूर्ण,
	अणु0x1926103C, "Smart Array P731m", &SA5_accessपूर्ण,
	अणु0x1928103C, "Smart Array P230i", &SA5_accessपूर्ण,
	अणु0x1929103C, "Smart Array P530", &SA5_accessपूर्ण,
	अणु0x21BD103C, "Smart Array P244br", &SA5_accessपूर्ण,
	अणु0x21BE103C, "Smart Array P741m", &SA5_accessपूर्ण,
	अणु0x21BF103C, "Smart HBA H240ar", &SA5_accessपूर्ण,
	अणु0x21C0103C, "Smart Array P440ar", &SA5_accessपूर्ण,
	अणु0x21C1103C, "Smart Array P840ar", &SA5_accessपूर्ण,
	अणु0x21C2103C, "Smart Array P440", &SA5_accessपूर्ण,
	अणु0x21C3103C, "Smart Array P441", &SA5_accessपूर्ण,
	अणु0x21C4103C, "Smart Array", &SA5_accessपूर्ण,
	अणु0x21C5103C, "Smart Array P841", &SA5_accessपूर्ण,
	अणु0x21C6103C, "Smart HBA H244br", &SA5_accessपूर्ण,
	अणु0x21C7103C, "Smart HBA H240", &SA5_accessपूर्ण,
	अणु0x21C8103C, "Smart HBA H241", &SA5_accessपूर्ण,
	अणु0x21C9103C, "Smart Array", &SA5_accessपूर्ण,
	अणु0x21CA103C, "Smart Array P246br", &SA5_accessपूर्ण,
	अणु0x21CB103C, "Smart Array P840", &SA5_accessपूर्ण,
	अणु0x21CC103C, "Smart Array", &SA5_accessपूर्ण,
	अणु0x21CD103C, "Smart Array", &SA5_accessपूर्ण,
	अणु0x21CE103C, "Smart HBA", &SA5_accessपूर्ण,
	अणु0x05809005, "SmartHBA-SA", &SA5_accessपूर्ण,
	अणु0x05819005, "SmartHBA-SA 8i", &SA5_accessपूर्ण,
	अणु0x05829005, "SmartHBA-SA 8i8e", &SA5_accessपूर्ण,
	अणु0x05839005, "SmartHBA-SA 8e", &SA5_accessपूर्ण,
	अणु0x05849005, "SmartHBA-SA 16i", &SA5_accessपूर्ण,
	अणु0x05859005, "SmartHBA-SA 4i4e", &SA5_accessपूर्ण,
	अणु0x00761590, "HP Storage P1224 Array Controller", &SA5_accessपूर्ण,
	अणु0x00871590, "HP Storage P1224e Array Controller", &SA5_accessपूर्ण,
	अणु0x007D1590, "HP Storage P1228 Array Controller", &SA5_accessपूर्ण,
	अणु0x00881590, "HP Storage P1228e Array Controller", &SA5_accessपूर्ण,
	अणु0x333f103c, "HP StorageWorks 1210m Array Controller", &SA5_accessपूर्ण,
	अणु0xFFFF103C, "Unknown Smart Array", &SA5_accessपूर्ण,
पूर्ण;

अटल काष्ठा scsi_transport_ढाँचा *hpsa_sas_transport_ढाँचा;
अटल पूर्णांक hpsa_add_sas_host(काष्ठा ctlr_info *h);
अटल व्योम hpsa_delete_sas_host(काष्ठा ctlr_info *h);
अटल पूर्णांक hpsa_add_sas_device(काष्ठा hpsa_sas_node *hpsa_sas_node,
			काष्ठा hpsa_scsi_dev_t *device);
अटल व्योम hpsa_हटाओ_sas_device(काष्ठा hpsa_scsi_dev_t *device);
अटल काष्ठा hpsa_scsi_dev_t
	*hpsa_find_device_by_sas_rphy(काष्ठा ctlr_info *h,
		काष्ठा sas_rphy *rphy);

#घोषणा SCSI_CMD_BUSY ((काष्ठा scsi_cmnd *)&hpsa_cmd_busy)
अटल स्थिर काष्ठा scsi_cmnd hpsa_cmd_busy;
#घोषणा SCSI_CMD_IDLE ((काष्ठा scsi_cmnd *)&hpsa_cmd_idle)
अटल स्थिर काष्ठा scsi_cmnd hpsa_cmd_idle;
अटल पूर्णांक number_of_controllers;

अटल irqवापस_t करो_hpsa_पूर्णांकr_पूर्णांकx(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t करो_hpsa_पूर्णांकr_msi(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक hpsa_ioctl(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
		      व्योम __user *arg);
अटल पूर्णांक hpsa_passthru_ioctl(काष्ठा ctlr_info *h,
			       IOCTL_Command_काष्ठा *iocommand);
अटल पूर्णांक hpsa_big_passthru_ioctl(काष्ठा ctlr_info *h,
				   BIG_IOCTL_Command_काष्ठा *ioc);

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक hpsa_compat_ioctl(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
	व्योम __user *arg);
#पूर्ण_अगर

अटल व्योम cmd_मुक्त(काष्ठा ctlr_info *h, काष्ठा CommandList *c);
अटल काष्ठा CommandList *cmd_alloc(काष्ठा ctlr_info *h);
अटल व्योम cmd_tagged_मुक्त(काष्ठा ctlr_info *h, काष्ठा CommandList *c);
अटल काष्ठा CommandList *cmd_tagged_alloc(काष्ठा ctlr_info *h,
					    काष्ठा scsi_cmnd *scmd);
अटल पूर्णांक fill_cmd(काष्ठा CommandList *c, u8 cmd, काष्ठा ctlr_info *h,
	व्योम *buff, माप_प्रकार size, u16 page_code, अचिन्हित अक्षर *scsi3addr,
	पूर्णांक cmd_type);
अटल व्योम hpsa_मुक्त_cmd_pool(काष्ठा ctlr_info *h);
#घोषणा VPD_PAGE (1 << 8)
#घोषणा HPSA_SIMPLE_ERROR_BITS 0x03

अटल पूर्णांक hpsa_scsi_queue_command(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *cmd);
अटल व्योम hpsa_scan_start(काष्ठा Scsi_Host *);
अटल पूर्णांक hpsa_scan_finished(काष्ठा Scsi_Host *sh,
	अचिन्हित दीर्घ elapsed_समय);
अटल पूर्णांक hpsa_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth);

अटल पूर्णांक hpsa_eh_device_reset_handler(काष्ठा scsi_cmnd *scsicmd);
अटल पूर्णांक hpsa_slave_alloc(काष्ठा scsi_device *sdev);
अटल पूर्णांक hpsa_slave_configure(काष्ठा scsi_device *sdev);
अटल व्योम hpsa_slave_destroy(काष्ठा scsi_device *sdev);

अटल व्योम hpsa_update_scsi_devices(काष्ठा ctlr_info *h);
अटल पूर्णांक check_क्रम_unit_attention(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c);
अटल व्योम check_ioctl_unit_attention(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c);
/* perक्रमmant mode helper functions */
अटल व्योम calc_bucket_map(पूर्णांक *bucket, पूर्णांक num_buckets,
	पूर्णांक nsgs, पूर्णांक min_blocks, u32 *bucket_map);
अटल व्योम hpsa_मुक्त_perक्रमmant_mode(काष्ठा ctlr_info *h);
अटल पूर्णांक hpsa_put_ctlr_पूर्णांकo_perक्रमmant_mode(काष्ठा ctlr_info *h);
अटल अंतरभूत u32 next_command(काष्ठा ctlr_info *h, u8 q);
अटल पूर्णांक hpsa_find_cfg_addrs(काष्ठा pci_dev *pdev, व्योम __iomem *vaddr,
			       u32 *cfg_base_addr, u64 *cfg_base_addr_index,
			       u64 *cfg_offset);
अटल पूर्णांक hpsa_pci_find_memory_BAR(काष्ठा pci_dev *pdev,
				    अचिन्हित दीर्घ *memory_bar);
अटल पूर्णांक hpsa_lookup_board_id(काष्ठा pci_dev *pdev, u32 *board_id,
				bool *legacy_board);
अटल पूर्णांक रुको_क्रम_device_to_become_पढ़ोy(काष्ठा ctlr_info *h,
					   अचिन्हित अक्षर lunaddr[],
					   पूर्णांक reply_queue);
अटल पूर्णांक hpsa_रुको_क्रम_board_state(काष्ठा pci_dev *pdev, व्योम __iomem *vaddr,
				     पूर्णांक रुको_क्रम_पढ़ोy);
अटल अंतरभूत व्योम finish_cmd(काष्ठा CommandList *c);
अटल पूर्णांक hpsa_रुको_क्रम_mode_change_ack(काष्ठा ctlr_info *h);
#घोषणा BOARD_NOT_READY 0
#घोषणा BOARD_READY 1
अटल व्योम hpsa_drain_accel_commands(काष्ठा ctlr_info *h);
अटल व्योम hpsa_flush_cache(काष्ठा ctlr_info *h);
अटल पूर्णांक hpsa_scsi_ioaccel_queue_command(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, u32 ioaccel_handle, u8 *cdb, पूर्णांक cdb_len,
	u8 *scsi3addr, काष्ठा hpsa_scsi_dev_t *phys_disk);
अटल व्योम hpsa_command_resubmit_worker(काष्ठा work_काष्ठा *work);
अटल u32 lockup_detected(काष्ठा ctlr_info *h);
अटल पूर्णांक detect_controller_lockup(काष्ठा ctlr_info *h);
अटल व्योम hpsa_disable_rld_caching(काष्ठा ctlr_info *h);
अटल अंतरभूत पूर्णांक hpsa_scsi_करो_report_phys_luns(काष्ठा ctlr_info *h,
	काष्ठा ReportExtendedLUNdata *buf, पूर्णांक bufsize);
अटल bool hpsa_vpd_page_supported(काष्ठा ctlr_info *h,
	अचिन्हित अक्षर scsi3addr[], u8 page);
अटल पूर्णांक hpsa_luns_changed(काष्ठा ctlr_info *h);
अटल bool hpsa_cmd_dev_match(काष्ठा ctlr_info *h, काष्ठा CommandList *c,
			       काष्ठा hpsa_scsi_dev_t *dev,
			       अचिन्हित अक्षर *scsi3addr);

अटल अंतरभूत काष्ठा ctlr_info *sdev_to_hba(काष्ठा scsi_device *sdev)
अणु
	अचिन्हित दीर्घ *priv = shost_priv(sdev->host);
	वापस (काष्ठा ctlr_info *) *priv;
पूर्ण

अटल अंतरभूत काष्ठा ctlr_info *shost_to_hba(काष्ठा Scsi_Host *sh)
अणु
	अचिन्हित दीर्घ *priv = shost_priv(sh);
	वापस (काष्ठा ctlr_info *) *priv;
पूर्ण

अटल अंतरभूत bool hpsa_is_cmd_idle(काष्ठा CommandList *c)
अणु
	वापस c->scsi_cmd == SCSI_CMD_IDLE;
पूर्ण

/* extract sense key, asc, and ascq from sense data.  -1 means invalid. */
अटल व्योम decode_sense_data(स्थिर u8 *sense_data, पूर्णांक sense_data_len,
			u8 *sense_key, u8 *asc, u8 *ascq)
अणु
	काष्ठा scsi_sense_hdr sshdr;
	bool rc;

	*sense_key = -1;
	*asc = -1;
	*ascq = -1;

	अगर (sense_data_len < 1)
		वापस;

	rc = scsi_normalize_sense(sense_data, sense_data_len, &sshdr);
	अगर (rc) अणु
		*sense_key = sshdr.sense_key;
		*asc = sshdr.asc;
		*ascq = sshdr.ascq;
	पूर्ण
पूर्ण

अटल पूर्णांक check_क्रम_unit_attention(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	u8 sense_key, asc, ascq;
	पूर्णांक sense_len;

	अगर (c->err_info->SenseLen > माप(c->err_info->SenseInfo))
		sense_len = माप(c->err_info->SenseInfo);
	अन्यथा
		sense_len = c->err_info->SenseLen;

	decode_sense_data(c->err_info->SenseInfo, sense_len,
				&sense_key, &asc, &ascq);
	अगर (sense_key != UNIT_ATTENTION || asc == 0xff)
		वापस 0;

	चयन (asc) अणु
	हाल STATE_CHANGED:
		dev_warn(&h->pdev->dev,
			"%s: a state change detected, command retried\n",
			h->devname);
		अवरोध;
	हाल LUN_FAILED:
		dev_warn(&h->pdev->dev,
			"%s: LUN failure detected\n", h->devname);
		अवरोध;
	हाल REPORT_LUNS_CHANGED:
		dev_warn(&h->pdev->dev,
			"%s: report LUN data changed\n", h->devname);
	/*
	 * Note: this REPORT_LUNS_CHANGED condition only occurs on the बाह्यal
	 * target (array) devices.
	 */
		अवरोध;
	हाल POWER_OR_RESET:
		dev_warn(&h->pdev->dev,
			"%s: a power on or device reset detected\n",
			h->devname);
		अवरोध;
	हाल UNIT_ATTENTION_CLEARED:
		dev_warn(&h->pdev->dev,
			"%s: unit attention cleared by another initiator\n",
			h->devname);
		अवरोध;
	शेष:
		dev_warn(&h->pdev->dev,
			"%s: unknown unit attention detected\n",
			h->devname);
		अवरोध;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक check_क्रम_busy(काष्ठा ctlr_info *h, काष्ठा CommandList *c)
अणु
	अगर (c->err_info->CommandStatus != CMD_TARGET_STATUS ||
		(c->err_info->ScsiStatus != SAM_STAT_BUSY &&
		 c->err_info->ScsiStatus != SAM_STAT_TASK_SET_FULL))
		वापस 0;
	dev_warn(&h->pdev->dev, HPSA "device busy");
	वापस 1;
पूर्ण

अटल u32 lockup_detected(काष्ठा ctlr_info *h);
अटल sमाप_प्रकार host_show_lockup_detected(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ld;
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	h = shost_to_hba(shost);
	ld = lockup_detected(h);

	वापस प्र_लिखो(buf, "ld=%d\n", ld);
पूर्ण

अटल sमाप_प्रकार host_store_hp_ssd_smart_path_status(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक status, len;
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	अक्षर पंचांगpbuf[10];

	अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		वापस -EACCES;
	len = count > माप(पंचांगpbuf) - 1 ? माप(पंचांगpbuf) - 1 : count;
	म_नकलन(पंचांगpbuf, buf, len);
	पंचांगpbuf[len] = '\0';
	अगर (माला_पूछो(पंचांगpbuf, "%d", &status) != 1)
		वापस -EINVAL;
	h = shost_to_hba(shost);
	h->acciopath_status = !!status;
	dev_warn(&h->pdev->dev,
		"hpsa: HP SSD Smart Path %s via sysfs update.\n",
		h->acciopath_status ? "enabled" : "disabled");
	वापस count;
पूर्ण

अटल sमाप_प्रकार host_store_raid_offload_debug(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक debug_level, len;
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	अक्षर पंचांगpbuf[10];

	अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		वापस -EACCES;
	len = count > माप(पंचांगpbuf) - 1 ? माप(पंचांगpbuf) - 1 : count;
	म_नकलन(पंचांगpbuf, buf, len);
	पंचांगpbuf[len] = '\0';
	अगर (माला_पूछो(पंचांगpbuf, "%d", &debug_level) != 1)
		वापस -EINVAL;
	अगर (debug_level < 0)
		debug_level = 0;
	h = shost_to_hba(shost);
	h->raid_offload_debug = debug_level;
	dev_warn(&h->pdev->dev, "hpsa: Set raid_offload_debug level = %d\n",
		h->raid_offload_debug);
	वापस count;
पूर्ण

अटल sमाप_प्रकार host_store_rescan(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	h = shost_to_hba(shost);
	hpsa_scan_start(h->scsi_host);
	वापस count;
पूर्ण

अटल व्योम hpsa_turn_off_ioaccel_क्रम_device(काष्ठा hpsa_scsi_dev_t *device)
अणु
	device->offload_enabled = 0;
	device->offload_to_be_enabled = 0;
पूर्ण

अटल sमाप_प्रकार host_show_firmware_revision(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	अचिन्हित अक्षर *fwrev;

	h = shost_to_hba(shost);
	अगर (!h->hba_inquiry_data)
		वापस 0;
	fwrev = &h->hba_inquiry_data[32];
	वापस snम_लिखो(buf, 20, "%c%c%c%c\n",
		fwrev[0], fwrev[1], fwrev[2], fwrev[3]);
पूर्ण

अटल sमाप_प्रकार host_show_commands_outstanding(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ctlr_info *h = shost_to_hba(shost);

	वापस snम_लिखो(buf, 20, "%d\n",
			atomic_पढ़ो(&h->commands_outstanding));
पूर्ण

अटल sमाप_प्रकार host_show_transport_mode(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	h = shost_to_hba(shost);
	वापस snम_लिखो(buf, 20, "%s\n",
		h->transMethod & CFGTBL_Trans_Perक्रमmant ?
			"performant" : "simple");
पूर्ण

अटल sमाप_प्रकार host_show_hp_ssd_smart_path_status(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	h = shost_to_hba(shost);
	वापस snम_लिखो(buf, 30, "HP SSD Smart Path %s\n",
		(h->acciopath_status == 1) ?  "enabled" : "disabled");
पूर्ण

/* List of controllers which cannot be hard reset on kexec with reset_devices */
अटल u32 unresettable_controller[] = अणु
	0x324a103C, /* Smart Array P712m */
	0x324b103C, /* Smart Array P711m */
	0x3223103C, /* Smart Array P800 */
	0x3234103C, /* Smart Array P400 */
	0x3235103C, /* Smart Array P400i */
	0x3211103C, /* Smart Array E200i */
	0x3212103C, /* Smart Array E200 */
	0x3213103C, /* Smart Array E200i */
	0x3214103C, /* Smart Array E200i */
	0x3215103C, /* Smart Array E200i */
	0x3237103C, /* Smart Array E500 */
	0x323D103C, /* Smart Array P700m */
	0x40800E11, /* Smart Array 5i */
	0x409C0E11, /* Smart Array 6400 */
	0x409D0E11, /* Smart Array 6400 EM */
	0x40700E11, /* Smart Array 5300 */
	0x40820E11, /* Smart Array 532 */
	0x40830E11, /* Smart Array 5312 */
	0x409A0E11, /* Smart Array 641 */
	0x409B0E11, /* Smart Array 642 */
	0x40910E11, /* Smart Array 6i */
पूर्ण;

/* List of controllers which cannot even be soft reset */
अटल u32 soft_unresettable_controller[] = अणु
	0x40800E11, /* Smart Array 5i */
	0x40700E11, /* Smart Array 5300 */
	0x40820E11, /* Smart Array 532 */
	0x40830E11, /* Smart Array 5312 */
	0x409A0E11, /* Smart Array 641 */
	0x409B0E11, /* Smart Array 642 */
	0x40910E11, /* Smart Array 6i */
	/* Exclude 640x boards.  These are two pci devices in one slot
	 * which share a battery backed cache module.  One controls the
	 * cache, the other accesses the cache through the one that controls
	 * it.  If we reset the one controlling the cache, the other will
	 * likely not be happy.  Just क्रमbid resetting this conjoined mess.
	 * The 640x isn't really supported by hpsa anyway.
	 */
	0x409C0E11, /* Smart Array 6400 */
	0x409D0E11, /* Smart Array 6400 EM */
पूर्ण;

अटल पूर्णांक board_id_in_array(u32 a[], पूर्णांक nelems, u32 board_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nelems; i++)
		अगर (a[i] == board_id)
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ctlr_is_hard_resettable(u32 board_id)
अणु
	वापस !board_id_in_array(unresettable_controller,
			ARRAY_SIZE(unresettable_controller), board_id);
पूर्ण

अटल पूर्णांक ctlr_is_soft_resettable(u32 board_id)
अणु
	वापस !board_id_in_array(soft_unresettable_controller,
			ARRAY_SIZE(soft_unresettable_controller), board_id);
पूर्ण

अटल पूर्णांक ctlr_is_resettable(u32 board_id)
अणु
	वापस ctlr_is_hard_resettable(board_id) ||
		ctlr_is_soft_resettable(board_id);
पूर्ण

अटल sमाप_प्रकार host_show_resettable(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	h = shost_to_hba(shost);
	वापस snम_लिखो(buf, 20, "%d\n", ctlr_is_resettable(h->board_id));
पूर्ण

अटल अंतरभूत पूर्णांक is_logical_dev_addr_mode(अचिन्हित अक्षर scsi3addr[])
अणु
	वापस (scsi3addr[3] & 0xC0) == 0x40;
पूर्ण

अटल स्थिर अक्षर * स्थिर raid_label[] = अणु "0", "4", "1(+0)", "5", "5+1", "6",
	"1(+0)ADM", "UNKNOWN", "PHYS DRV"
पूर्ण;
#घोषणा HPSA_RAID_0	0
#घोषणा HPSA_RAID_4	1
#घोषणा HPSA_RAID_1	2	/* also used क्रम RAID 10 */
#घोषणा HPSA_RAID_5	3	/* also used क्रम RAID 50 */
#घोषणा HPSA_RAID_51	4
#घोषणा HPSA_RAID_6	5	/* also used क्रम RAID 60 */
#घोषणा HPSA_RAID_ADM	6	/* also used क्रम RAID 1+0 ADM */
#घोषणा RAID_UNKNOWN (ARRAY_SIZE(raid_label) - 2)
#घोषणा PHYSICAL_DRIVE (ARRAY_SIZE(raid_label) - 1)

अटल अंतरभूत bool is_logical_device(काष्ठा hpsa_scsi_dev_t *device)
अणु
	वापस !device->physical_device;
पूर्ण

अटल sमाप_प्रकार raid_level_show(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार l = 0;
	अचिन्हित अक्षर rlevel;
	काष्ठा ctlr_info *h;
	काष्ठा scsi_device *sdev;
	काष्ठा hpsa_scsi_dev_t *hdev;
	अचिन्हित दीर्घ flags;

	sdev = to_scsi_device(dev);
	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->lock, flags);
	hdev = sdev->hostdata;
	अगर (!hdev) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		वापस -ENODEV;
	पूर्ण

	/* Is this even a logical drive? */
	अगर (!is_logical_device(hdev)) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		l = snम_लिखो(buf, PAGE_SIZE, "N/A\n");
		वापस l;
	पूर्ण

	rlevel = hdev->raid_level;
	spin_unlock_irqrestore(&h->lock, flags);
	अगर (rlevel > RAID_UNKNOWN)
		rlevel = RAID_UNKNOWN;
	l = snम_लिखो(buf, PAGE_SIZE, "RAID %s\n", raid_label[rlevel]);
	वापस l;
पूर्ण

अटल sमाप_प्रकार lunid_show(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा scsi_device *sdev;
	काष्ठा hpsa_scsi_dev_t *hdev;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर lunid[8];

	sdev = to_scsi_device(dev);
	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->lock, flags);
	hdev = sdev->hostdata;
	अगर (!hdev) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		वापस -ENODEV;
	पूर्ण
	स_नकल(lunid, hdev->scsi3addr, माप(lunid));
	spin_unlock_irqrestore(&h->lock, flags);
	वापस snम_लिखो(buf, 20, "0x%8phN\n", lunid);
पूर्ण

अटल sमाप_प्रकार unique_id_show(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा scsi_device *sdev;
	काष्ठा hpsa_scsi_dev_t *hdev;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर sn[16];

	sdev = to_scsi_device(dev);
	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->lock, flags);
	hdev = sdev->hostdata;
	अगर (!hdev) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		वापस -ENODEV;
	पूर्ण
	स_नकल(sn, hdev->device_id, माप(sn));
	spin_unlock_irqrestore(&h->lock, flags);
	वापस snम_लिखो(buf, 16 * 2 + 2,
			"%02X%02X%02X%02X%02X%02X%02X%02X"
			"%02X%02X%02X%02X%02X%02X%02X%02X\n",
			sn[0], sn[1], sn[2], sn[3],
			sn[4], sn[5], sn[6], sn[7],
			sn[8], sn[9], sn[10], sn[11],
			sn[12], sn[13], sn[14], sn[15]);
पूर्ण

अटल sमाप_प्रकार sas_address_show(काष्ठा device *dev,
	      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा scsi_device *sdev;
	काष्ठा hpsa_scsi_dev_t *hdev;
	अचिन्हित दीर्घ flags;
	u64 sas_address;

	sdev = to_scsi_device(dev);
	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->lock, flags);
	hdev = sdev->hostdata;
	अगर (!hdev || is_logical_device(hdev) || !hdev->expose_device) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		वापस -ENODEV;
	पूर्ण
	sas_address = hdev->sas_address;
	spin_unlock_irqrestore(&h->lock, flags);

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%016llx\n", sas_address);
पूर्ण

अटल sमाप_प्रकार host_show_hp_ssd_smart_path_enabled(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा scsi_device *sdev;
	काष्ठा hpsa_scsi_dev_t *hdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक offload_enabled;

	sdev = to_scsi_device(dev);
	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->lock, flags);
	hdev = sdev->hostdata;
	अगर (!hdev) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		वापस -ENODEV;
	पूर्ण
	offload_enabled = hdev->offload_enabled;
	spin_unlock_irqrestore(&h->lock, flags);

	अगर (hdev->devtype == TYPE_DISK || hdev->devtype == TYPE_ZBC)
		वापस snम_लिखो(buf, 20, "%d\n", offload_enabled);
	अन्यथा
		वापस snम_लिखो(buf, 40, "%s\n",
				"Not applicable for a controller");
पूर्ण

#घोषणा MAX_PATHS 8
अटल sमाप_प्रकार path_info_show(काष्ठा device *dev,
	     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा scsi_device *sdev;
	काष्ठा hpsa_scsi_dev_t *hdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक output_len = 0;
	u8 box;
	u8 bay;
	u8 path_map_index = 0;
	अक्षर *active;
	अचिन्हित अक्षर phys_connector[2];

	sdev = to_scsi_device(dev);
	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->devlock, flags);
	hdev = sdev->hostdata;
	अगर (!hdev) अणु
		spin_unlock_irqrestore(&h->devlock, flags);
		वापस -ENODEV;
	पूर्ण

	bay = hdev->bay;
	क्रम (i = 0; i < MAX_PATHS; i++) अणु
		path_map_index = 1<<i;
		अगर (i == hdev->active_path_index)
			active = "Active";
		अन्यथा अगर (hdev->path_map & path_map_index)
			active = "Inactive";
		अन्यथा
			जारी;

		output_len += scnम_लिखो(buf + output_len,
				PAGE_SIZE - output_len,
				"[%d:%d:%d:%d] %20.20s ",
				h->scsi_host->host_no,
				hdev->bus, hdev->target, hdev->lun,
				scsi_device_type(hdev->devtype));

		अगर (hdev->devtype == TYPE_RAID || is_logical_device(hdev)) अणु
			output_len += scnम_लिखो(buf + output_len,
						PAGE_SIZE - output_len,
						"%s\n", active);
			जारी;
		पूर्ण

		box = hdev->box[i];
		स_नकल(&phys_connector, &hdev->phys_connector[i],
			माप(phys_connector));
		अगर (phys_connector[0] < '0')
			phys_connector[0] = '0';
		अगर (phys_connector[1] < '0')
			phys_connector[1] = '0';
		output_len += scnम_लिखो(buf + output_len,
				PAGE_SIZE - output_len,
				"PORT: %.2s ",
				phys_connector);
		अगर ((hdev->devtype == TYPE_DISK || hdev->devtype == TYPE_ZBC) &&
			hdev->expose_device) अणु
			अगर (box == 0 || box == 0xFF) अणु
				output_len += scnम_लिखो(buf + output_len,
					PAGE_SIZE - output_len,
					"BAY: %hhu %s\n",
					bay, active);
			पूर्ण अन्यथा अणु
				output_len += scnम_लिखो(buf + output_len,
					PAGE_SIZE - output_len,
					"BOX: %hhu BAY: %hhu %s\n",
					box, bay, active);
			पूर्ण
		पूर्ण अन्यथा अगर (box != 0 && box != 0xFF) अणु
			output_len += scnम_लिखो(buf + output_len,
				PAGE_SIZE - output_len, "BOX: %hhu %s\n",
				box, active);
		पूर्ण अन्यथा
			output_len += scnम_लिखो(buf + output_len,
				PAGE_SIZE - output_len, "%s\n", active);
	पूर्ण

	spin_unlock_irqrestore(&h->devlock, flags);
	वापस output_len;
पूर्ण

अटल sमाप_प्रकार host_show_ctlr_num(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	h = shost_to_hba(shost);
	वापस snम_लिखो(buf, 20, "%d\n", h->ctlr);
पूर्ण

अटल sमाप_प्रकार host_show_legacy_board(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा Scsi_Host *shost = class_to_shost(dev);

	h = shost_to_hba(shost);
	वापस snम_लिखो(buf, 20, "%d\n", h->legacy_board ? 1 : 0);
पूर्ण

अटल DEVICE_ATTR_RO(raid_level);
अटल DEVICE_ATTR_RO(lunid);
अटल DEVICE_ATTR_RO(unique_id);
अटल DEVICE_ATTR(rescan, S_IWUSR, शून्य, host_store_rescan);
अटल DEVICE_ATTR_RO(sas_address);
अटल DEVICE_ATTR(hp_ssd_smart_path_enabled, S_IRUGO,
			host_show_hp_ssd_smart_path_enabled, शून्य);
अटल DEVICE_ATTR_RO(path_info);
अटल DEVICE_ATTR(hp_ssd_smart_path_status, S_IWUSR|S_IRUGO|S_IROTH,
		host_show_hp_ssd_smart_path_status,
		host_store_hp_ssd_smart_path_status);
अटल DEVICE_ATTR(raid_offload_debug, S_IWUSR, शून्य,
			host_store_raid_offload_debug);
अटल DEVICE_ATTR(firmware_revision, S_IRUGO,
	host_show_firmware_revision, शून्य);
अटल DEVICE_ATTR(commands_outstanding, S_IRUGO,
	host_show_commands_outstanding, शून्य);
अटल DEVICE_ATTR(transport_mode, S_IRUGO,
	host_show_transport_mode, शून्य);
अटल DEVICE_ATTR(resettable, S_IRUGO,
	host_show_resettable, शून्य);
अटल DEVICE_ATTR(lockup_detected, S_IRUGO,
	host_show_lockup_detected, शून्य);
अटल DEVICE_ATTR(ctlr_num, S_IRUGO,
	host_show_ctlr_num, शून्य);
अटल DEVICE_ATTR(legacy_board, S_IRUGO,
	host_show_legacy_board, शून्य);

अटल काष्ठा device_attribute *hpsa_sdev_attrs[] = अणु
	&dev_attr_raid_level,
	&dev_attr_lunid,
	&dev_attr_unique_id,
	&dev_attr_hp_ssd_smart_path_enabled,
	&dev_attr_path_info,
	&dev_attr_sas_address,
	शून्य,
पूर्ण;

अटल काष्ठा device_attribute *hpsa_shost_attrs[] = अणु
	&dev_attr_rescan,
	&dev_attr_firmware_revision,
	&dev_attr_commands_outstanding,
	&dev_attr_transport_mode,
	&dev_attr_resettable,
	&dev_attr_hp_ssd_smart_path_status,
	&dev_attr_raid_offload_debug,
	&dev_attr_lockup_detected,
	&dev_attr_ctlr_num,
	&dev_attr_legacy_board,
	शून्य,
पूर्ण;

#घोषणा HPSA_NRESERVED_CMDS	(HPSA_CMDS_RESERVED_FOR_DRIVER +\
				 HPSA_MAX_CONCURRENT_PASSTHRUS)

अटल काष्ठा scsi_host_ढाँचा hpsa_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= HPSA,
	.proc_name		= HPSA,
	.queuecommand		= hpsa_scsi_queue_command,
	.scan_start		= hpsa_scan_start,
	.scan_finished		= hpsa_scan_finished,
	.change_queue_depth	= hpsa_change_queue_depth,
	.this_id		= -1,
	.eh_device_reset_handler = hpsa_eh_device_reset_handler,
	.ioctl			= hpsa_ioctl,
	.slave_alloc		= hpsa_slave_alloc,
	.slave_configure	= hpsa_slave_configure,
	.slave_destroy		= hpsa_slave_destroy,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= hpsa_compat_ioctl,
#पूर्ण_अगर
	.sdev_attrs = hpsa_sdev_attrs,
	.shost_attrs = hpsa_shost_attrs,
	.max_sectors = 2048,
	.no_ग_लिखो_same = 1,
पूर्ण;

अटल अंतरभूत u32 next_command(काष्ठा ctlr_info *h, u8 q)
अणु
	u32 a;
	काष्ठा reply_queue_buffer *rq = &h->reply_queue[q];

	अगर (h->transMethod & CFGTBL_Trans_io_accel1)
		वापस h->access.command_completed(h, q);

	अगर (unlikely(!(h->transMethod & CFGTBL_Trans_Perक्रमmant)))
		वापस h->access.command_completed(h, q);

	अगर ((rq->head[rq->current_entry] & 1) == rq->wraparound) अणु
		a = rq->head[rq->current_entry];
		rq->current_entry++;
		atomic_dec(&h->commands_outstanding);
	पूर्ण अन्यथा अणु
		a = FIFO_EMPTY;
	पूर्ण
	/* Check क्रम wraparound */
	अगर (rq->current_entry == h->max_commands) अणु
		rq->current_entry = 0;
		rq->wraparound ^= 1;
	पूर्ण
	वापस a;
पूर्ण

/*
 * There are some special bits in the bus address of the
 * command that we have to set क्रम the controller to know
 * how to process the command:
 *
 * Normal perक्रमmant mode:
 * bit 0: 1 means perक्रमmant mode, 0 means simple mode.
 * bits 1-3 = block fetch table entry
 * bits 4-6 = command type (== 0)
 *
 * ioaccel1 mode:
 * bit 0 = "performant mode" bit.
 * bits 1-3 = block fetch table entry
 * bits 4-6 = command type (== 110)
 * (command type is needed because ioaccel1 mode
 * commands are submitted through the same रेजिस्टर as normal
 * mode commands, so this is how the controller knows whether
 * the command is normal mode or ioaccel1 mode.)
 *
 * ioaccel2 mode:
 * bit 0 = "performant mode" bit.
 * bits 1-4 = block fetch table entry (note extra bit)
 * bits 4-6 = not needed, because ioaccel2 mode has
 * a separate special रेजिस्टर क्रम submitting commands.
 */

/*
 * set_perक्रमmant_mode: Modअगरy the tag क्रम cciss perक्रमmant
 * set bit 0 क्रम pull model, bits 3-1 क्रम block fetch
 * रेजिस्टर number
 */
#घोषणा DEFAULT_REPLY_QUEUE (-1)
अटल व्योम set_perक्रमmant_mode(काष्ठा ctlr_info *h, काष्ठा CommandList *c,
					पूर्णांक reply_queue)
अणु
	अगर (likely(h->transMethod & CFGTBL_Trans_Perक्रमmant)) अणु
		c->busaddr |= 1 | (h->blockFetchTable[c->Header.SGList] << 1);
		अगर (unlikely(!h->msix_vectors))
			वापस;
		c->Header.ReplyQueue = reply_queue;
	पूर्ण
पूर्ण

अटल व्योम set_ioaccel1_perक्रमmant_mode(काष्ठा ctlr_info *h,
						काष्ठा CommandList *c,
						पूर्णांक reply_queue)
अणु
	काष्ठा io_accel1_cmd *cp = &h->ioaccel_cmd_pool[c->cmdindex];

	/*
	 * Tell the controller to post the reply to the queue क्रम this
	 * processor.  This seems to give the best I/O throughput.
	 */
	cp->ReplyQueue = reply_queue;
	/*
	 * Set the bits in the address sent करोwn to include:
	 *  - perक्रमmant mode bit (bit 0)
	 *  - pull count (bits 1-3)
	 *  - command type (bits 4-6)
	 */
	c->busaddr |= 1 | (h->ioaccel1_blockFetchTable[c->Header.SGList] << 1) |
					IOACCEL1_BUSADDR_CMDTYPE;
पूर्ण

अटल व्योम set_ioaccel2_पंचांगf_perक्रमmant_mode(काष्ठा ctlr_info *h,
						काष्ठा CommandList *c,
						पूर्णांक reply_queue)
अणु
	काष्ठा hpsa_पंचांगf_काष्ठा *cp = (काष्ठा hpsa_पंचांगf_काष्ठा *)
		&h->ioaccel2_cmd_pool[c->cmdindex];

	/* Tell the controller to post the reply to the queue क्रम this
	 * processor.  This seems to give the best I/O throughput.
	 */
	cp->reply_queue = reply_queue;
	/* Set the bits in the address sent करोwn to include:
	 *  - perक्रमmant mode bit not used in ioaccel mode 2
	 *  - pull count (bits 0-3)
	 *  - command type isn't needed क्रम ioaccel2
	 */
	c->busaddr |= h->ioaccel2_blockFetchTable[0];
पूर्ण

अटल व्योम set_ioaccel2_perक्रमmant_mode(काष्ठा ctlr_info *h,
						काष्ठा CommandList *c,
						पूर्णांक reply_queue)
अणु
	काष्ठा io_accel2_cmd *cp = &h->ioaccel2_cmd_pool[c->cmdindex];

	/*
	 * Tell the controller to post the reply to the queue क्रम this
	 * processor.  This seems to give the best I/O throughput.
	 */
	cp->reply_queue = reply_queue;
	/*
	 * Set the bits in the address sent करोwn to include:
	 *  - perक्रमmant mode bit not used in ioaccel mode 2
	 *  - pull count (bits 0-3)
	 *  - command type isn't needed क्रम ioaccel2
	 */
	c->busaddr |= (h->ioaccel2_blockFetchTable[cp->sg_count]);
पूर्ण

अटल पूर्णांक is_firmware_flash_cmd(u8 *cdb)
अणु
	वापस cdb[0] == BMIC_WRITE && cdb[6] == BMIC_FLASH_FIRMWARE;
पूर्ण

/*
 * During firmware flash, the heartbeat रेजिस्टर may not update as frequently
 * as it should.  So we dial करोwn lockup detection during firmware flash. and
 * dial it back up when firmware flash completes.
 */
#घोषणा HEARTBEAT_SAMPLE_INTERVAL_DURING_FLASH (240 * HZ)
#घोषणा HEARTBEAT_SAMPLE_INTERVAL (30 * HZ)
#घोषणा HPSA_EVENT_MONITOR_INTERVAL (15 * HZ)
अटल व्योम dial_करोwn_lockup_detection_during_fw_flash(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c)
अणु
	अगर (!is_firmware_flash_cmd(c->Request.CDB))
		वापस;
	atomic_inc(&h->firmware_flash_in_progress);
	h->heartbeat_sample_पूर्णांकerval = HEARTBEAT_SAMPLE_INTERVAL_DURING_FLASH;
पूर्ण

अटल व्योम dial_up_lockup_detection_on_fw_flash_complete(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c)
अणु
	अगर (is_firmware_flash_cmd(c->Request.CDB) &&
		atomic_dec_and_test(&h->firmware_flash_in_progress))
		h->heartbeat_sample_पूर्णांकerval = HEARTBEAT_SAMPLE_INTERVAL;
पूर्ण

अटल व्योम __enqueue_cmd_and_start_io(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, पूर्णांक reply_queue)
अणु
	dial_करोwn_lockup_detection_during_fw_flash(h, c);
	atomic_inc(&h->commands_outstanding);
	/*
	 * Check to see अगर the command is being retried.
	 */
	अगर (c->device && !c->retry_pending)
		atomic_inc(&c->device->commands_outstanding);

	reply_queue = h->reply_map[raw_smp_processor_id()];
	चयन (c->cmd_type) अणु
	हाल CMD_IOACCEL1:
		set_ioaccel1_perक्रमmant_mode(h, c, reply_queue);
		ग_लिखोl(c->busaddr, h->vaddr + SA5_REQUEST_PORT_OFFSET);
		अवरोध;
	हाल CMD_IOACCEL2:
		set_ioaccel2_perक्रमmant_mode(h, c, reply_queue);
		ग_लिखोl(c->busaddr, h->vaddr + IOACCEL2_INBOUND_POSTQ_32);
		अवरोध;
	हाल IOACCEL2_TMF:
		set_ioaccel2_पंचांगf_perक्रमmant_mode(h, c, reply_queue);
		ग_लिखोl(c->busaddr, h->vaddr + IOACCEL2_INBOUND_POSTQ_32);
		अवरोध;
	शेष:
		set_perक्रमmant_mode(h, c, reply_queue);
		h->access.submit_command(h, c);
	पूर्ण
पूर्ण

अटल व्योम enqueue_cmd_and_start_io(काष्ठा ctlr_info *h, काष्ठा CommandList *c)
अणु
	__enqueue_cmd_and_start_io(h, c, DEFAULT_REPLY_QUEUE);
पूर्ण

अटल अंतरभूत पूर्णांक is_hba_lunid(अचिन्हित अक्षर scsi3addr[])
अणु
	वापस स_भेद(scsi3addr, RAID_CTLR_LUNID, 8) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_scsi_rev_5(काष्ठा ctlr_info *h)
अणु
	अगर (!h->hba_inquiry_data)
		वापस 0;
	अगर ((h->hba_inquiry_data[2] & 0x07) == 5)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_find_target_lun(काष्ठा ctlr_info *h,
	अचिन्हित अक्षर scsi3addr[], पूर्णांक bus, पूर्णांक *target, पूर्णांक *lun)
अणु
	/* finds an unused bus, target, lun क्रम a new physical device
	 * assumes h->devlock is held
	 */
	पूर्णांक i, found = 0;
	DECLARE_BITMAP(lun_taken, HPSA_MAX_DEVICES);

	biपंचांगap_zero(lun_taken, HPSA_MAX_DEVICES);

	क्रम (i = 0; i < h->ndevices; i++) अणु
		अगर (h->dev[i]->bus == bus && h->dev[i]->target != -1)
			__set_bit(h->dev[i]->target, lun_taken);
	पूर्ण

	i = find_first_zero_bit(lun_taken, HPSA_MAX_DEVICES);
	अगर (i < HPSA_MAX_DEVICES) अणु
		/* *bus = 1; */
		*target = i;
		*lun = 0;
		found = 1;
	पूर्ण
	वापस !found;
पूर्ण

अटल व्योम hpsa_show_dev_msg(स्थिर अक्षर *level, काष्ठा ctlr_info *h,
	काष्ठा hpsa_scsi_dev_t *dev, अक्षर *description)
अणु
#घोषणा LABEL_SIZE 25
	अक्षर label[LABEL_SIZE];

	अगर (h == शून्य || h->pdev == शून्य || h->scsi_host == शून्य)
		वापस;

	चयन (dev->devtype) अणु
	हाल TYPE_RAID:
		snम_लिखो(label, LABEL_SIZE, "controller");
		अवरोध;
	हाल TYPE_ENCLOSURE:
		snम_लिखो(label, LABEL_SIZE, "enclosure");
		अवरोध;
	हाल TYPE_DISK:
	हाल TYPE_ZBC:
		अगर (dev->बाह्यal)
			snम_लिखो(label, LABEL_SIZE, "external");
		अन्यथा अगर (!is_logical_dev_addr_mode(dev->scsi3addr))
			snम_लिखो(label, LABEL_SIZE, "%s",
				raid_label[PHYSICAL_DRIVE]);
		अन्यथा
			snम_लिखो(label, LABEL_SIZE, "RAID-%s",
				dev->raid_level > RAID_UNKNOWN ? "?" :
				raid_label[dev->raid_level]);
		अवरोध;
	हाल TYPE_ROM:
		snम_लिखो(label, LABEL_SIZE, "rom");
		अवरोध;
	हाल TYPE_TAPE:
		snम_लिखो(label, LABEL_SIZE, "tape");
		अवरोध;
	हाल TYPE_MEDIUM_CHANGER:
		snम_लिखो(label, LABEL_SIZE, "changer");
		अवरोध;
	शेष:
		snम_लिखो(label, LABEL_SIZE, "UNKNOWN");
		अवरोध;
	पूर्ण

	dev_prपूर्णांकk(level, &h->pdev->dev,
			"scsi %d:%d:%d:%d: %s %s %.8s %.16s %s SSDSmartPathCap%c En%c Exp=%d\n",
			h->scsi_host->host_no, dev->bus, dev->target, dev->lun,
			description,
			scsi_device_type(dev->devtype),
			dev->venकरोr,
			dev->model,
			label,
			dev->offload_config ? '+' : '-',
			dev->offload_to_be_enabled ? '+' : '-',
			dev->expose_device);
पूर्ण

/* Add an entry पूर्णांकo h->dev[] array. */
अटल पूर्णांक hpsa_scsi_add_entry(काष्ठा ctlr_info *h,
		काष्ठा hpsa_scsi_dev_t *device,
		काष्ठा hpsa_scsi_dev_t *added[], पूर्णांक *nadded)
अणु
	/* assumes h->devlock is held */
	पूर्णांक n = h->ndevices;
	पूर्णांक i;
	अचिन्हित अक्षर addr1[8], addr2[8];
	काष्ठा hpsa_scsi_dev_t *sd;

	अगर (n >= HPSA_MAX_DEVICES) अणु
		dev_err(&h->pdev->dev, "too many devices, some will be "
			"inaccessible.\n");
		वापस -1;
	पूर्ण

	/* physical devices करो not have lun or target asचिन्हित until now. */
	अगर (device->lun != -1)
		/* Logical device, lun is alपढ़ोy asचिन्हित. */
		जाओ lun_asचिन्हित;

	/* If this device a non-zero lun of a multi-lun device
	 * byte 4 of the 8-byte LUN addr will contain the logical
	 * unit no, zero otherwise.
	 */
	अगर (device->scsi3addr[4] == 0) अणु
		/* This is not a non-zero lun of a multi-lun device */
		अगर (hpsa_find_target_lun(h, device->scsi3addr,
			device->bus, &device->target, &device->lun) != 0)
			वापस -1;
		जाओ lun_asचिन्हित;
	पूर्ण

	/* This is a non-zero lun of a multi-lun device.
	 * Search through our list and find the device which
	 * has the same 8 byte LUN address, excepting byte 4 and 5.
	 * Assign the same bus and target क्रम this new LUN.
	 * Use the logical unit number from the firmware.
	 */
	स_नकल(addr1, device->scsi3addr, 8);
	addr1[4] = 0;
	addr1[5] = 0;
	क्रम (i = 0; i < n; i++) अणु
		sd = h->dev[i];
		स_नकल(addr2, sd->scsi3addr, 8);
		addr2[4] = 0;
		addr2[5] = 0;
		/* dअगरfer only in byte 4 and 5? */
		अगर (स_भेद(addr1, addr2, 8) == 0) अणु
			device->bus = sd->bus;
			device->target = sd->target;
			device->lun = device->scsi3addr[4];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (device->lun == -1) अणु
		dev_warn(&h->pdev->dev, "physical device with no LUN=0,"
			" suspect firmware bug or unsupported hardware "
			"configuration.\n");
		वापस -1;
	पूर्ण

lun_asचिन्हित:

	h->dev[n] = device;
	h->ndevices++;
	added[*nadded] = device;
	(*nadded)++;
	hpsa_show_dev_msg(KERN_INFO, h, device,
		device->expose_device ? "added" : "masked");
	वापस 0;
पूर्ण

/*
 * Called during a scan operation.
 *
 * Update an entry in h->dev[] array.
 */
अटल व्योम hpsa_scsi_update_entry(काष्ठा ctlr_info *h,
	पूर्णांक entry, काष्ठा hpsa_scsi_dev_t *new_entry)
अणु
	/* assumes h->devlock is held */
	BUG_ON(entry < 0 || entry >= HPSA_MAX_DEVICES);

	/* Raid level changed. */
	h->dev[entry]->raid_level = new_entry->raid_level;

	/*
	 * ioacccel_handle may have changed क्रम a dual करोमुख्य disk
	 */
	h->dev[entry]->ioaccel_handle = new_entry->ioaccel_handle;

	/* Raid offload parameters changed.  Careful about the ordering. */
	अगर (new_entry->offload_config && new_entry->offload_to_be_enabled) अणु
		/*
		 * अगर drive is newly offload_enabled, we want to copy the
		 * raid map data first.  If previously offload_enabled and
		 * offload_config were set, raid map data had better be
		 * the same as it was beक्रमe. If raid map data has changed
		 * then it had better be the हाल that
		 * h->dev[entry]->offload_enabled is currently 0.
		 */
		h->dev[entry]->raid_map = new_entry->raid_map;
		h->dev[entry]->ioaccel_handle = new_entry->ioaccel_handle;
	पूर्ण
	अगर (new_entry->offload_to_be_enabled) अणु
		h->dev[entry]->ioaccel_handle = new_entry->ioaccel_handle;
		wmb(); /* set ioaccel_handle *beक्रमe* hba_ioaccel_enabled */
	पूर्ण
	h->dev[entry]->hba_ioaccel_enabled = new_entry->hba_ioaccel_enabled;
	h->dev[entry]->offload_config = new_entry->offload_config;
	h->dev[entry]->offload_to_mirror = new_entry->offload_to_mirror;
	h->dev[entry]->queue_depth = new_entry->queue_depth;

	/*
	 * We can turn off ioaccel offload now, but need to delay turning
	 * ioaccel on until we can update h->dev[entry]->phys_disk[], but we
	 * can't करो that until all the devices are updated.
	 */
	h->dev[entry]->offload_to_be_enabled = new_entry->offload_to_be_enabled;

	/*
	 * turn ioaccel off immediately अगर told to करो so.
	 */
	अगर (!new_entry->offload_to_be_enabled)
		h->dev[entry]->offload_enabled = 0;

	hpsa_show_dev_msg(KERN_INFO, h, h->dev[entry], "updated");
पूर्ण

/* Replace an entry from h->dev[] array. */
अटल व्योम hpsa_scsi_replace_entry(काष्ठा ctlr_info *h,
	पूर्णांक entry, काष्ठा hpsa_scsi_dev_t *new_entry,
	काष्ठा hpsa_scsi_dev_t *added[], पूर्णांक *nadded,
	काष्ठा hpsa_scsi_dev_t *हटाओd[], पूर्णांक *nहटाओd)
अणु
	/* assumes h->devlock is held */
	BUG_ON(entry < 0 || entry >= HPSA_MAX_DEVICES);
	हटाओd[*nहटाओd] = h->dev[entry];
	(*nहटाओd)++;

	/*
	 * New physical devices won't have target/lun asचिन्हित yet
	 * so we need to preserve the values in the slot we are replacing.
	 */
	अगर (new_entry->target == -1) अणु
		new_entry->target = h->dev[entry]->target;
		new_entry->lun = h->dev[entry]->lun;
	पूर्ण

	h->dev[entry] = new_entry;
	added[*nadded] = new_entry;
	(*nadded)++;

	hpsa_show_dev_msg(KERN_INFO, h, new_entry, "replaced");
पूर्ण

/* Remove an entry from h->dev[] array. */
अटल व्योम hpsa_scsi_हटाओ_entry(काष्ठा ctlr_info *h, पूर्णांक entry,
	काष्ठा hpsa_scsi_dev_t *हटाओd[], पूर्णांक *nहटाओd)
अणु
	/* assumes h->devlock is held */
	पूर्णांक i;
	काष्ठा hpsa_scsi_dev_t *sd;

	BUG_ON(entry < 0 || entry >= HPSA_MAX_DEVICES);

	sd = h->dev[entry];
	हटाओd[*nहटाओd] = h->dev[entry];
	(*nहटाओd)++;

	क्रम (i = entry; i < h->ndevices-1; i++)
		h->dev[i] = h->dev[i+1];
	h->ndevices--;
	hpsa_show_dev_msg(KERN_INFO, h, sd, "removed");
पूर्ण

#घोषणा SCSI3ADDR_EQ(a, b) ( \
	(a)[7] == (b)[7] && \
	(a)[6] == (b)[6] && \
	(a)[5] == (b)[5] && \
	(a)[4] == (b)[4] && \
	(a)[3] == (b)[3] && \
	(a)[2] == (b)[2] && \
	(a)[1] == (b)[1] && \
	(a)[0] == (b)[0])

अटल व्योम fixup_botched_add(काष्ठा ctlr_info *h,
	काष्ठा hpsa_scsi_dev_t *added)
अणु
	/* called when scsi_add_device fails in order to re-adjust
	 * h->dev[] to match the mid layer's view.
	 */
	अचिन्हित दीर्घ flags;
	पूर्णांक i, j;

	spin_lock_irqsave(&h->lock, flags);
	क्रम (i = 0; i < h->ndevices; i++) अणु
		अगर (h->dev[i] == added) अणु
			क्रम (j = i; j < h->ndevices-1; j++)
				h->dev[j] = h->dev[j+1];
			h->ndevices--;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&h->lock, flags);
	kमुक्त(added);
पूर्ण

अटल अंतरभूत पूर्णांक device_is_the_same(काष्ठा hpsa_scsi_dev_t *dev1,
	काष्ठा hpsa_scsi_dev_t *dev2)
अणु
	/* we compare everything except lun and target as these
	 * are not yet asचिन्हित.  Compare parts likely
	 * to dअगरfer first
	 */
	अगर (स_भेद(dev1->scsi3addr, dev2->scsi3addr,
		माप(dev1->scsi3addr)) != 0)
		वापस 0;
	अगर (स_भेद(dev1->device_id, dev2->device_id,
		माप(dev1->device_id)) != 0)
		वापस 0;
	अगर (स_भेद(dev1->model, dev2->model, माप(dev1->model)) != 0)
		वापस 0;
	अगर (स_भेद(dev1->venकरोr, dev2->venकरोr, माप(dev1->venकरोr)) != 0)
		वापस 0;
	अगर (dev1->devtype != dev2->devtype)
		वापस 0;
	अगर (dev1->bus != dev2->bus)
		वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक device_updated(काष्ठा hpsa_scsi_dev_t *dev1,
	काष्ठा hpsa_scsi_dev_t *dev2)
अणु
	/* Device attributes that can change, but करोn't mean
	 * that the device is a dअगरferent device, nor that the OS
	 * needs to be told anything about the change.
	 */
	अगर (dev1->raid_level != dev2->raid_level)
		वापस 1;
	अगर (dev1->offload_config != dev2->offload_config)
		वापस 1;
	अगर (dev1->offload_to_be_enabled != dev2->offload_to_be_enabled)
		वापस 1;
	अगर (!is_logical_dev_addr_mode(dev1->scsi3addr))
		अगर (dev1->queue_depth != dev2->queue_depth)
			वापस 1;
	/*
	 * This can happen क्रम dual करोमुख्य devices. An active
	 * path change causes the ioaccel handle to change
	 *
	 * क्रम example note the handle dअगरferences between p0 and p1
	 * Device                    WWN               ,WWN hash,Handle
	 * D016 p0|0x3 [02]P2E:01:01,0x5000C5005FC4DACA,0x9B5616,0x01030003
	 *	p1                   0x5000C5005FC4DAC9,0x6798C0,0x00040004
	 */
	अगर (dev1->ioaccel_handle != dev2->ioaccel_handle)
		वापस 1;
	वापस 0;
पूर्ण

/* Find needle in haystack.  If exact match found, वापस DEVICE_SAME,
 * and वापस needle location in *index.  If scsi3addr matches, but not
 * venकरोr, model, serial num, etc. वापस DEVICE_CHANGED, and वापस needle
 * location in *index.
 * In the हाल of a minor device attribute change, such as RAID level, just
 * वापस DEVICE_UPDATED, aदीर्घ with the updated device's location in index.
 * If needle not found, वापस DEVICE_NOT_FOUND.
 */
अटल पूर्णांक hpsa_scsi_find_entry(काष्ठा hpsa_scsi_dev_t *needle,
	काष्ठा hpsa_scsi_dev_t *haystack[], पूर्णांक haystack_size,
	पूर्णांक *index)
अणु
	पूर्णांक i;
#घोषणा DEVICE_NOT_FOUND 0
#घोषणा DEVICE_CHANGED 1
#घोषणा DEVICE_SAME 2
#घोषणा DEVICE_UPDATED 3
	अगर (needle == शून्य)
		वापस DEVICE_NOT_FOUND;

	क्रम (i = 0; i < haystack_size; i++) अणु
		अगर (haystack[i] == शून्य) /* previously हटाओd. */
			जारी;
		अगर (SCSI3ADDR_EQ(needle->scsi3addr, haystack[i]->scsi3addr)) अणु
			*index = i;
			अगर (device_is_the_same(needle, haystack[i])) अणु
				अगर (device_updated(needle, haystack[i]))
					वापस DEVICE_UPDATED;
				वापस DEVICE_SAME;
			पूर्ण अन्यथा अणु
				/* Keep offline devices offline */
				अगर (needle->volume_offline)
					वापस DEVICE_NOT_FOUND;
				वापस DEVICE_CHANGED;
			पूर्ण
		पूर्ण
	पूर्ण
	*index = -1;
	वापस DEVICE_NOT_FOUND;
पूर्ण

अटल व्योम hpsa_monitor_offline_device(काष्ठा ctlr_info *h,
					अचिन्हित अक्षर scsi3addr[])
अणु
	काष्ठा offline_device_entry *device;
	अचिन्हित दीर्घ flags;

	/* Check to see अगर device is alपढ़ोy on the list */
	spin_lock_irqsave(&h->offline_device_lock, flags);
	list_क्रम_each_entry(device, &h->offline_device_list, offline_list) अणु
		अगर (स_भेद(device->scsi3addr, scsi3addr,
			माप(device->scsi3addr)) == 0) अणु
			spin_unlock_irqrestore(&h->offline_device_lock, flags);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&h->offline_device_lock, flags);

	/* Device is not on the list, add it. */
	device = kदो_स्मृति(माप(*device), GFP_KERNEL);
	अगर (!device)
		वापस;

	स_नकल(device->scsi3addr, scsi3addr, माप(device->scsi3addr));
	spin_lock_irqsave(&h->offline_device_lock, flags);
	list_add_tail(&device->offline_list, &h->offline_device_list);
	spin_unlock_irqrestore(&h->offline_device_lock, flags);
पूर्ण

/* Prपूर्णांक a message explaining various offline volume states */
अटल व्योम hpsa_show_volume_status(काष्ठा ctlr_info *h,
	काष्ठा hpsa_scsi_dev_t *sd)
अणु
	अगर (sd->volume_offline == HPSA_VPD_LV_STATUS_UNSUPPORTED)
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume status is not available through vital product data pages.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
	चयन (sd->volume_offline) अणु
	हाल HPSA_LV_OK:
		अवरोध;
	हाल HPSA_LV_UNDERGOING_ERASE:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing background erase process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_NOT_AVAILABLE:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is waiting for transforming volume.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_UNDERGOING_RPI:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing rapid parity init.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_PENDING_RPI:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is queued for rapid parity initialization process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_ENCRYPTED_NO_KEY:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is encrypted and cannot be accessed because key is not present.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is not encrypted and cannot be accessed because controller is in encryption-only mode.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_UNDERGOING_ENCRYPTION:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing encryption process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_UNDERGOING_ENCRYPTION_REKEYING:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing encryption re-keying process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is encrypted and cannot be accessed because controller does not have encryption enabled.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_PENDING_ENCRYPTION:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is pending migration to encrypted state, but process has not started.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	हाल HPSA_LV_PENDING_ENCRYPTION_REKEYING:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is encrypted and is pending encryption rekeying.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Figure the list of physical drive poपूर्णांकers क्रम a logical drive with
 * raid offload configured.
 */
अटल व्योम hpsa_figure_phys_disk_ptrs(काष्ठा ctlr_info *h,
				काष्ठा hpsa_scsi_dev_t *dev[], पूर्णांक ndevices,
				काष्ठा hpsa_scsi_dev_t *logical_drive)
अणु
	काष्ठा raid_map_data *map = &logical_drive->raid_map;
	काष्ठा raid_map_disk_data *dd = &map->data[0];
	पूर्णांक i, j;
	पूर्णांक total_disks_per_row = le16_to_cpu(map->data_disks_per_row) +
				le16_to_cpu(map->metadata_disks_per_row);
	पूर्णांक nraid_map_entries = le16_to_cpu(map->row_cnt) *
				le16_to_cpu(map->layout_map_count) *
				total_disks_per_row;
	पूर्णांक nphys_disk = le16_to_cpu(map->layout_map_count) *
				total_disks_per_row;
	पूर्णांक qdepth;

	अगर (nraid_map_entries > RAID_MAP_MAX_ENTRIES)
		nraid_map_entries = RAID_MAP_MAX_ENTRIES;

	logical_drive->nphysical_disks = nraid_map_entries;

	qdepth = 0;
	क्रम (i = 0; i < nraid_map_entries; i++) अणु
		logical_drive->phys_disk[i] = शून्य;
		अगर (!logical_drive->offload_config)
			जारी;
		क्रम (j = 0; j < ndevices; j++) अणु
			अगर (dev[j] == शून्य)
				जारी;
			अगर (dev[j]->devtype != TYPE_DISK &&
			    dev[j]->devtype != TYPE_ZBC)
				जारी;
			अगर (is_logical_device(dev[j]))
				जारी;
			अगर (dev[j]->ioaccel_handle != dd[i].ioaccel_handle)
				जारी;

			logical_drive->phys_disk[i] = dev[j];
			अगर (i < nphys_disk)
				qdepth = min(h->nr_cmds, qdepth +
				    logical_drive->phys_disk[i]->queue_depth);
			अवरोध;
		पूर्ण

		/*
		 * This can happen अगर a physical drive is हटाओd and
		 * the logical drive is degraded.  In that हाल, the RAID
		 * map data will refer to a physical disk which isn't actually
		 * present.  And in that हाल offload_enabled should alपढ़ोy
		 * be 0, but we'll turn it off here just in हाल
		 */
		अगर (!logical_drive->phys_disk[i]) अणु
			dev_warn(&h->pdev->dev,
				"%s: [%d:%d:%d:%d] A phys disk component of LV is missing, turning off offload_enabled for LV.\n",
				__func__,
				h->scsi_host->host_no, logical_drive->bus,
				logical_drive->target, logical_drive->lun);
			hpsa_turn_off_ioaccel_क्रम_device(logical_drive);
			logical_drive->queue_depth = 8;
		पूर्ण
	पूर्ण
	अगर (nraid_map_entries)
		/*
		 * This is correct क्रम पढ़ोs, too high क्रम full stripe ग_लिखोs,
		 * way too high क्रम partial stripe ग_लिखोs
		 */
		logical_drive->queue_depth = qdepth;
	अन्यथा अणु
		अगर (logical_drive->बाह्यal)
			logical_drive->queue_depth = EXTERNAL_QD;
		अन्यथा
			logical_drive->queue_depth = h->nr_cmds;
	पूर्ण
पूर्ण

अटल व्योम hpsa_update_log_drive_phys_drive_ptrs(काष्ठा ctlr_info *h,
				काष्ठा hpsa_scsi_dev_t *dev[], पूर्णांक ndevices)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndevices; i++) अणु
		अगर (dev[i] == शून्य)
			जारी;
		अगर (dev[i]->devtype != TYPE_DISK &&
		    dev[i]->devtype != TYPE_ZBC)
			जारी;
		अगर (!is_logical_device(dev[i]))
			जारी;

		/*
		 * If offload is currently enabled, the RAID map and
		 * phys_disk[] assignment *better* not be changing
		 * because we would be changing ioaccel phsy_disk[] poपूर्णांकers
		 * on a ioaccel volume processing I/O requests.
		 *
		 * If an ioaccel volume status changed, initially because it was
		 * re-configured and thus underwent a transक्रमmation, or
		 * a drive failed, we would have received a state change
		 * request and ioaccel should have been turned off. When the
		 * transक्रमmation completes, we get another state change
		 * request to turn ioaccel back on. In this हाल, we need
		 * to update the ioaccel inक्रमmation.
		 *
		 * Thus: If it is not currently enabled, but will be after
		 * the scan completes, make sure the ioaccel poपूर्णांकers
		 * are up to date.
		 */

		अगर (!dev[i]->offload_enabled && dev[i]->offload_to_be_enabled)
			hpsa_figure_phys_disk_ptrs(h, dev, ndevices, dev[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक hpsa_add_device(काष्ठा ctlr_info *h, काष्ठा hpsa_scsi_dev_t *device)
अणु
	पूर्णांक rc = 0;

	अगर (!h->scsi_host)
		वापस 1;

	अगर (is_logical_device(device)) /* RAID */
		rc = scsi_add_device(h->scsi_host, device->bus,
					device->target, device->lun);
	अन्यथा /* HBA */
		rc = hpsa_add_sas_device(h->sas_host, device);

	वापस rc;
पूर्ण

अटल पूर्णांक hpsa_find_outstanding_commands_क्रम_dev(काष्ठा ctlr_info *h,
						काष्ठा hpsa_scsi_dev_t *dev)
अणु
	पूर्णांक i;
	पूर्णांक count = 0;

	क्रम (i = 0; i < h->nr_cmds; i++) अणु
		काष्ठा CommandList *c = h->cmd_pool + i;
		पूर्णांक refcount = atomic_inc_वापस(&c->refcount);

		अगर (refcount > 1 && hpsa_cmd_dev_match(h, c, dev,
				dev->scsi3addr)) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&h->lock, flags);	/* Implied MB */
			अगर (!hpsa_is_cmd_idle(c))
				++count;
			spin_unlock_irqrestore(&h->lock, flags);
		पूर्ण

		cmd_मुक्त(h, c);
	पूर्ण

	वापस count;
पूर्ण

#घोषणा NUM_WAIT 20
अटल व्योम hpsa_रुको_क्रम_outstanding_commands_क्रम_dev(काष्ठा ctlr_info *h,
						काष्ठा hpsa_scsi_dev_t *device)
अणु
	पूर्णांक cmds = 0;
	पूर्णांक रुकोs = 0;
	पूर्णांक num_रुको = NUM_WAIT;

	अगर (device->बाह्यal)
		num_रुको = HPSA_EH_PTRAID_TIMEOUT;

	जबतक (1) अणु
		cmds = hpsa_find_outstanding_commands_क्रम_dev(h, device);
		अगर (cmds == 0)
			अवरोध;
		अगर (++रुकोs > num_रुको)
			अवरोध;
		msleep(1000);
	पूर्ण

	अगर (रुकोs > num_रुको) अणु
		dev_warn(&h->pdev->dev,
			"%s: removing device [%d:%d:%d:%d] with %d outstanding commands!\n",
			__func__,
			h->scsi_host->host_no,
			device->bus, device->target, device->lun, cmds);
	पूर्ण
पूर्ण

अटल व्योम hpsa_हटाओ_device(काष्ठा ctlr_info *h,
			काष्ठा hpsa_scsi_dev_t *device)
अणु
	काष्ठा scsi_device *sdev = शून्य;

	अगर (!h->scsi_host)
		वापस;

	/*
	 * Allow क्रम commands to drain
	 */
	device->हटाओd = 1;
	hpsa_रुको_क्रम_outstanding_commands_क्रम_dev(h, device);

	अगर (is_logical_device(device)) अणु /* RAID */
		sdev = scsi_device_lookup(h->scsi_host, device->bus,
						device->target, device->lun);
		अगर (sdev) अणु
			scsi_हटाओ_device(sdev);
			scsi_device_put(sdev);
		पूर्ण अन्यथा अणु
			/*
			 * We करोn't expect to get here.  Future commands
			 * to this device will get a selection समयout as
			 * अगर the device were gone.
			 */
			hpsa_show_dev_msg(KERN_WARNING, h, device,
					"didn't find device for removal.");
		पूर्ण
	पूर्ण अन्यथा अणु /* HBA */

		hpsa_हटाओ_sas_device(device);
	पूर्ण
पूर्ण

अटल व्योम adjust_hpsa_scsi_table(काष्ठा ctlr_info *h,
	काष्ठा hpsa_scsi_dev_t *sd[], पूर्णांक nsds)
अणु
	/* sd contains scsi3 addresses and devtypes, and inquiry
	 * data.  This function takes what's in sd to be the current
	 * reality and updates h->dev[] to reflect that reality.
	 */
	पूर्णांक i, entry, device_change, changes = 0;
	काष्ठा hpsa_scsi_dev_t *csd;
	अचिन्हित दीर्घ flags;
	काष्ठा hpsa_scsi_dev_t **added, **हटाओd;
	पूर्णांक nadded, nहटाओd;

	/*
	 * A reset can cause a device status to change
	 * re-schedule the scan to see what happened.
	 */
	spin_lock_irqsave(&h->reset_lock, flags);
	अगर (h->reset_in_progress) अणु
		h->drv_req_rescan = 1;
		spin_unlock_irqrestore(&h->reset_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&h->reset_lock, flags);

	added = kसुस्मृति(HPSA_MAX_DEVICES, माप(*added), GFP_KERNEL);
	हटाओd = kसुस्मृति(HPSA_MAX_DEVICES, माप(*हटाओd), GFP_KERNEL);

	अगर (!added || !हटाओd) अणु
		dev_warn(&h->pdev->dev, "out of memory in "
			"adjust_hpsa_scsi_table\n");
		जाओ मुक्त_and_out;
	पूर्ण

	spin_lock_irqsave(&h->devlock, flags);

	/* find any devices in h->dev[] that are not in
	 * sd[] and हटाओ them from h->dev[], and क्रम any
	 * devices which have changed, हटाओ the old device
	 * info and add the new device info.
	 * If minor device attributes change, just update
	 * the existing device काष्ठाure.
	 */
	i = 0;
	nहटाओd = 0;
	nadded = 0;
	जबतक (i < h->ndevices) अणु
		csd = h->dev[i];
		device_change = hpsa_scsi_find_entry(csd, sd, nsds, &entry);
		अगर (device_change == DEVICE_NOT_FOUND) अणु
			changes++;
			hpsa_scsi_हटाओ_entry(h, i, हटाओd, &nहटाओd);
			जारी; /* हटाओ ^^^, hence i not incremented */
		पूर्ण अन्यथा अगर (device_change == DEVICE_CHANGED) अणु
			changes++;
			hpsa_scsi_replace_entry(h, i, sd[entry],
				added, &nadded, हटाओd, &nहटाओd);
			/* Set it to शून्य to prevent it from being मुक्तd
			 * at the bottom of hpsa_update_scsi_devices()
			 */
			sd[entry] = शून्य;
		पूर्ण अन्यथा अगर (device_change == DEVICE_UPDATED) अणु
			hpsa_scsi_update_entry(h, i, sd[entry]);
		पूर्ण
		i++;
	पूर्ण

	/* Now, make sure every device listed in sd[] is also
	 * listed in h->dev[], adding them अगर they aren't found
	 */

	क्रम (i = 0; i < nsds; i++) अणु
		अगर (!sd[i]) /* अगर alपढ़ोy added above. */
			जारी;

		/* Don't add devices which are NOT READY, FORMAT IN PROGRESS
		 * as the SCSI mid-layer करोes not handle such devices well.
		 * It relentlessly loops sending TUR at 3Hz, then READ(10)
		 * at 160Hz, and prevents the प्रणाली from coming up.
		 */
		अगर (sd[i]->volume_offline) अणु
			hpsa_show_volume_status(h, sd[i]);
			hpsa_show_dev_msg(KERN_INFO, h, sd[i], "offline");
			जारी;
		पूर्ण

		device_change = hpsa_scsi_find_entry(sd[i], h->dev,
					h->ndevices, &entry);
		अगर (device_change == DEVICE_NOT_FOUND) अणु
			changes++;
			अगर (hpsa_scsi_add_entry(h, sd[i], added, &nadded) != 0)
				अवरोध;
			sd[i] = शून्य; /* prevent from being मुक्तd later. */
		पूर्ण अन्यथा अगर (device_change == DEVICE_CHANGED) अणु
			/* should never happen... */
			changes++;
			dev_warn(&h->pdev->dev,
				"device unexpectedly changed.\n");
			/* but अगर it करोes happen, we just ignore that device */
		पूर्ण
	पूर्ण
	hpsa_update_log_drive_phys_drive_ptrs(h, h->dev, h->ndevices);

	/*
	 * Now that h->dev[]->phys_disk[] is coherent, we can enable
	 * any logical drives that need it enabled.
	 *
	 * The raid map should be current by now.
	 *
	 * We are updating the device list used क्रम I/O requests.
	 */
	क्रम (i = 0; i < h->ndevices; i++) अणु
		अगर (h->dev[i] == शून्य)
			जारी;
		h->dev[i]->offload_enabled = h->dev[i]->offload_to_be_enabled;
	पूर्ण

	spin_unlock_irqrestore(&h->devlock, flags);

	/* Monitor devices which are in one of several NOT READY states to be
	 * brought online later. This must be करोne without holding h->devlock,
	 * so करोn't touch h->dev[]
	 */
	क्रम (i = 0; i < nsds; i++) अणु
		अगर (!sd[i]) /* अगर alपढ़ोy added above. */
			जारी;
		अगर (sd[i]->volume_offline)
			hpsa_monitor_offline_device(h, sd[i]->scsi3addr);
	पूर्ण

	/* Don't notअगरy scsi mid layer of any changes the first समय through
	 * (or अगर there are no changes) scsi_scan_host will करो it later the
	 * first समय through.
	 */
	अगर (!changes)
		जाओ मुक्त_and_out;

	/* Notअगरy scsi mid layer of any हटाओd devices */
	क्रम (i = 0; i < nहटाओd; i++) अणु
		अगर (हटाओd[i] == शून्य)
			जारी;
		अगर (हटाओd[i]->expose_device)
			hpsa_हटाओ_device(h, हटाओd[i]);
		kमुक्त(हटाओd[i]);
		हटाओd[i] = शून्य;
	पूर्ण

	/* Notअगरy scsi mid layer of any added devices */
	क्रम (i = 0; i < nadded; i++) अणु
		पूर्णांक rc = 0;

		अगर (added[i] == शून्य)
			जारी;
		अगर (!(added[i]->expose_device))
			जारी;
		rc = hpsa_add_device(h, added[i]);
		अगर (!rc)
			जारी;
		dev_warn(&h->pdev->dev,
			"addition failed %d, device not added.", rc);
		/* now we have to हटाओ it from h->dev,
		 * since it didn't get added to scsi mid layer
		 */
		fixup_botched_add(h, added[i]);
		h->drv_req_rescan = 1;
	पूर्ण

मुक्त_and_out:
	kमुक्त(added);
	kमुक्त(हटाओd);
पूर्ण

/*
 * Lookup bus/target/lun and वापस corresponding काष्ठा hpsa_scsi_dev_t *
 * Assume's h->devlock is held.
 */
अटल काष्ठा hpsa_scsi_dev_t *lookup_hpsa_scsi_dev(काष्ठा ctlr_info *h,
	पूर्णांक bus, पूर्णांक target, पूर्णांक lun)
अणु
	पूर्णांक i;
	काष्ठा hpsa_scsi_dev_t *sd;

	क्रम (i = 0; i < h->ndevices; i++) अणु
		sd = h->dev[i];
		अगर (sd->bus == bus && sd->target == target && sd->lun == lun)
			वापस sd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक hpsa_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा hpsa_scsi_dev_t *sd = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा ctlr_info *h;

	h = sdev_to_hba(sdev);
	spin_lock_irqsave(&h->devlock, flags);
	अगर (sdev_channel(sdev) == HPSA_PHYSICAL_DEVICE_BUS) अणु
		काष्ठा scsi_target *starget;
		काष्ठा sas_rphy *rphy;

		starget = scsi_target(sdev);
		rphy = target_to_rphy(starget);
		sd = hpsa_find_device_by_sas_rphy(h, rphy);
		अगर (sd) अणु
			sd->target = sdev_id(sdev);
			sd->lun = sdev->lun;
		पूर्ण
	पूर्ण
	अगर (!sd)
		sd = lookup_hpsa_scsi_dev(h, sdev_channel(sdev),
					sdev_id(sdev), sdev->lun);

	अगर (sd && sd->expose_device) अणु
		atomic_set(&sd->ioaccel_cmds_out, 0);
		sdev->hostdata = sd;
	पूर्ण अन्यथा
		sdev->hostdata = शून्य;
	spin_unlock_irqrestore(&h->devlock, flags);
	वापस 0;
पूर्ण

/* configure scsi device based on पूर्णांकernal per-device काष्ठाure */
#घोषणा CTLR_TIMEOUT (120 * HZ)
अटल पूर्णांक hpsa_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा hpsa_scsi_dev_t *sd;
	पूर्णांक queue_depth;

	sd = sdev->hostdata;
	sdev->no_uld_attach = !sd || !sd->expose_device;

	अगर (sd) अणु
		sd->was_हटाओd = 0;
		queue_depth = sd->queue_depth != 0 ?
				sd->queue_depth : sdev->host->can_queue;
		अगर (sd->बाह्यal) अणु
			queue_depth = EXTERNAL_QD;
			sdev->eh_समयout = HPSA_EH_PTRAID_TIMEOUT;
			blk_queue_rq_समयout(sdev->request_queue,
						HPSA_EH_PTRAID_TIMEOUT);
		पूर्ण
		अगर (is_hba_lunid(sd->scsi3addr)) अणु
			sdev->eh_समयout = CTLR_TIMEOUT;
			blk_queue_rq_समयout(sdev->request_queue, CTLR_TIMEOUT);
		पूर्ण
	पूर्ण अन्यथा अणु
		queue_depth = sdev->host->can_queue;
	पूर्ण

	scsi_change_queue_depth(sdev, queue_depth);

	वापस 0;
पूर्ण

अटल व्योम hpsa_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा hpsa_scsi_dev_t *hdev = शून्य;

	hdev = sdev->hostdata;

	अगर (hdev)
		hdev->was_हटाओd = 1;
पूर्ण

अटल व्योम hpsa_मुक्त_ioaccel2_sg_chain_blocks(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;

	अगर (!h->ioaccel2_cmd_sg_list)
		वापस;
	क्रम (i = 0; i < h->nr_cmds; i++) अणु
		kमुक्त(h->ioaccel2_cmd_sg_list[i]);
		h->ioaccel2_cmd_sg_list[i] = शून्य;
	पूर्ण
	kमुक्त(h->ioaccel2_cmd_sg_list);
	h->ioaccel2_cmd_sg_list = शून्य;
पूर्ण

अटल पूर्णांक hpsa_allocate_ioaccel2_sg_chain_blocks(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;

	अगर (h->chainsize <= 0)
		वापस 0;

	h->ioaccel2_cmd_sg_list =
		kसुस्मृति(h->nr_cmds, माप(*h->ioaccel2_cmd_sg_list),
					GFP_KERNEL);
	अगर (!h->ioaccel2_cmd_sg_list)
		वापस -ENOMEM;
	क्रम (i = 0; i < h->nr_cmds; i++) अणु
		h->ioaccel2_cmd_sg_list[i] =
			kदो_स्मृति_array(h->maxsgentries,
				      माप(*h->ioaccel2_cmd_sg_list[i]),
				      GFP_KERNEL);
		अगर (!h->ioaccel2_cmd_sg_list[i])
			जाओ clean;
	पूर्ण
	वापस 0;

clean:
	hpsa_मुक्त_ioaccel2_sg_chain_blocks(h);
	वापस -ENOMEM;
पूर्ण

अटल व्योम hpsa_मुक्त_sg_chain_blocks(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;

	अगर (!h->cmd_sg_list)
		वापस;
	क्रम (i = 0; i < h->nr_cmds; i++) अणु
		kमुक्त(h->cmd_sg_list[i]);
		h->cmd_sg_list[i] = शून्य;
	पूर्ण
	kमुक्त(h->cmd_sg_list);
	h->cmd_sg_list = शून्य;
पूर्ण

अटल पूर्णांक hpsa_alloc_sg_chain_blocks(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;

	अगर (h->chainsize <= 0)
		वापस 0;

	h->cmd_sg_list = kसुस्मृति(h->nr_cmds, माप(*h->cmd_sg_list),
				 GFP_KERNEL);
	अगर (!h->cmd_sg_list)
		वापस -ENOMEM;

	क्रम (i = 0; i < h->nr_cmds; i++) अणु
		h->cmd_sg_list[i] = kदो_स्मृति_array(h->chainsize,
						  माप(*h->cmd_sg_list[i]),
						  GFP_KERNEL);
		अगर (!h->cmd_sg_list[i])
			जाओ clean;

	पूर्ण
	वापस 0;

clean:
	hpsa_मुक्त_sg_chain_blocks(h);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक hpsa_map_ioaccel2_sg_chain_block(काष्ठा ctlr_info *h,
	काष्ठा io_accel2_cmd *cp, काष्ठा CommandList *c)
अणु
	काष्ठा ioaccel2_sg_element *chain_block;
	u64 temp64;
	u32 chain_size;

	chain_block = h->ioaccel2_cmd_sg_list[c->cmdindex];
	chain_size = le32_to_cpu(cp->sg[0].length);
	temp64 = dma_map_single(&h->pdev->dev, chain_block, chain_size,
				DMA_TO_DEVICE);
	अगर (dma_mapping_error(&h->pdev->dev, temp64)) अणु
		/* prevent subsequent unmapping */
		cp->sg->address = 0;
		वापस -1;
	पूर्ण
	cp->sg->address = cpu_to_le64(temp64);
	वापस 0;
पूर्ण

अटल व्योम hpsa_unmap_ioaccel2_sg_chain_block(काष्ठा ctlr_info *h,
	काष्ठा io_accel2_cmd *cp)
अणु
	काष्ठा ioaccel2_sg_element *chain_sg;
	u64 temp64;
	u32 chain_size;

	chain_sg = cp->sg;
	temp64 = le64_to_cpu(chain_sg->address);
	chain_size = le32_to_cpu(cp->sg[0].length);
	dma_unmap_single(&h->pdev->dev, temp64, chain_size, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक hpsa_map_sg_chain_block(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	काष्ठा SGDescriptor *chain_sg, *chain_block;
	u64 temp64;
	u32 chain_len;

	chain_sg = &c->SG[h->max_cmd_sg_entries - 1];
	chain_block = h->cmd_sg_list[c->cmdindex];
	chain_sg->Ext = cpu_to_le32(HPSA_SG_CHAIN);
	chain_len = माप(*chain_sg) *
		(le16_to_cpu(c->Header.SGTotal) - h->max_cmd_sg_entries);
	chain_sg->Len = cpu_to_le32(chain_len);
	temp64 = dma_map_single(&h->pdev->dev, chain_block, chain_len,
				DMA_TO_DEVICE);
	अगर (dma_mapping_error(&h->pdev->dev, temp64)) अणु
		/* prevent subsequent unmapping */
		chain_sg->Addr = cpu_to_le64(0);
		वापस -1;
	पूर्ण
	chain_sg->Addr = cpu_to_le64(temp64);
	वापस 0;
पूर्ण

अटल व्योम hpsa_unmap_sg_chain_block(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	काष्ठा SGDescriptor *chain_sg;

	अगर (le16_to_cpu(c->Header.SGTotal) <= h->max_cmd_sg_entries)
		वापस;

	chain_sg = &c->SG[h->max_cmd_sg_entries - 1];
	dma_unmap_single(&h->pdev->dev, le64_to_cpu(chain_sg->Addr),
			le32_to_cpu(chain_sg->Len), DMA_TO_DEVICE);
पूर्ण


/* Decode the various types of errors on ioaccel2 path.
 * Return 1 क्रम any error that should generate a RAID path retry.
 * Return 0 क्रम errors that करोn't require a RAID path retry.
 */
अटल पूर्णांक handle_ioaccel_mode2_error(काष्ठा ctlr_info *h,
					काष्ठा CommandList *c,
					काष्ठा scsi_cmnd *cmd,
					काष्ठा io_accel2_cmd *c2,
					काष्ठा hpsa_scsi_dev_t *dev)
अणु
	पूर्णांक data_len;
	पूर्णांक retry = 0;
	u32 ioaccel2_resid = 0;

	चयन (c2->error_data.serv_response) अणु
	हाल IOACCEL2_SERV_RESPONSE_COMPLETE:
		चयन (c2->error_data.status) अणु
		हाल IOACCEL2_STATUS_SR_TASK_COMP_GOOD:
			अगर (cmd)
				cmd->result = 0;
			अवरोध;
		हाल IOACCEL2_STATUS_SR_TASK_COMP_CHK_COND:
			cmd->result |= SAM_STAT_CHECK_CONDITION;
			अगर (c2->error_data.data_present !=
					IOACCEL2_SENSE_DATA_PRESENT) अणु
				स_रखो(cmd->sense_buffer, 0,
					SCSI_SENSE_BUFFERSIZE);
				अवरोध;
			पूर्ण
			/* copy the sense data */
			data_len = c2->error_data.sense_data_len;
			अगर (data_len > SCSI_SENSE_BUFFERSIZE)
				data_len = SCSI_SENSE_BUFFERSIZE;
			अगर (data_len > माप(c2->error_data.sense_data_buff))
				data_len =
					माप(c2->error_data.sense_data_buff);
			स_नकल(cmd->sense_buffer,
				c2->error_data.sense_data_buff, data_len);
			retry = 1;
			अवरोध;
		हाल IOACCEL2_STATUS_SR_TASK_COMP_BUSY:
			retry = 1;
			अवरोध;
		हाल IOACCEL2_STATUS_SR_TASK_COMP_RES_CON:
			retry = 1;
			अवरोध;
		हाल IOACCEL2_STATUS_SR_TASK_COMP_SET_FULL:
			retry = 1;
			अवरोध;
		हाल IOACCEL2_STATUS_SR_TASK_COMP_ABORTED:
			retry = 1;
			अवरोध;
		शेष:
			retry = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IOACCEL2_SERV_RESPONSE_FAILURE:
		चयन (c2->error_data.status) अणु
		हाल IOACCEL2_STATUS_SR_IO_ERROR:
		हाल IOACCEL2_STATUS_SR_IO_ABORTED:
		हाल IOACCEL2_STATUS_SR_OVERRUN:
			retry = 1;
			अवरोध;
		हाल IOACCEL2_STATUS_SR_UNDERRUN:
			cmd->result = (DID_OK << 16);		/* host byte */
			ioaccel2_resid = get_unaligned_le32(
						&c2->error_data.resid_cnt[0]);
			scsi_set_resid(cmd, ioaccel2_resid);
			अवरोध;
		हाल IOACCEL2_STATUS_SR_NO_PATH_TO_DEVICE:
		हाल IOACCEL2_STATUS_SR_INVALID_DEVICE:
		हाल IOACCEL2_STATUS_SR_IOACCEL_DISABLED:
			/*
			 * Did an HBA disk disappear? We will eventually
			 * get a state change event from the controller but
			 * in the meanसमय, we need to tell the OS that the
			 * HBA disk is no दीर्घer there and stop I/O
			 * from going करोwn. This allows the potential re-insert
			 * of the disk to get the same device node.
			 */
			अगर (dev->physical_device && dev->expose_device) अणु
				cmd->result = DID_NO_CONNECT << 16;
				dev->हटाओd = 1;
				h->drv_req_rescan = 1;
				dev_warn(&h->pdev->dev,
					"%s: device is gone!\n", __func__);
			पूर्ण अन्यथा
				/*
				 * Retry by sending करोwn the RAID path.
				 * We will get an event from ctlr to
				 * trigger rescan regardless.
				 */
				retry = 1;
			अवरोध;
		शेष:
			retry = 1;
		पूर्ण
		अवरोध;
	हाल IOACCEL2_SERV_RESPONSE_TMF_COMPLETE:
		अवरोध;
	हाल IOACCEL2_SERV_RESPONSE_TMF_SUCCESS:
		अवरोध;
	हाल IOACCEL2_SERV_RESPONSE_TMF_REJECTED:
		retry = 1;
		अवरोध;
	हाल IOACCEL2_SERV_RESPONSE_TMF_WRONG_LUN:
		अवरोध;
	शेष:
		retry = 1;
		अवरोध;
	पूर्ण

	अगर (dev->in_reset)
		retry = 0;

	वापस retry;	/* retry on raid path? */
पूर्ण

अटल व्योम hpsa_cmd_resolve_events(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c)
अणु
	काष्ठा hpsa_scsi_dev_t *dev = c->device;

	/*
	 * Reset c->scsi_cmd here so that the reset handler will know
	 * this command has completed.  Then, check to see अगर the handler is
	 * रुकोing क्रम this command, and, अगर so, wake it.
	 */
	c->scsi_cmd = SCSI_CMD_IDLE;
	mb();	/* Declare command idle beक्रमe checking क्रम pending events. */
	अगर (dev) अणु
		atomic_dec(&dev->commands_outstanding);
		अगर (dev->in_reset &&
			atomic_पढ़ो(&dev->commands_outstanding) <= 0)
			wake_up_all(&h->event_sync_रुको_queue);
	पूर्ण
पूर्ण

अटल व्योम hpsa_cmd_resolve_and_मुक्त(काष्ठा ctlr_info *h,
				      काष्ठा CommandList *c)
अणु
	hpsa_cmd_resolve_events(h, c);
	cmd_tagged_मुक्त(h, c);
पूर्ण

अटल व्योम hpsa_cmd_मुक्त_and_करोne(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c, काष्ठा scsi_cmnd *cmd)
अणु
	hpsa_cmd_resolve_and_मुक्त(h, c);
	अगर (cmd && cmd->scsi_करोne)
		cmd->scsi_करोne(cmd);
पूर्ण

अटल व्योम hpsa_retry_cmd(काष्ठा ctlr_info *h, काष्ठा CommandList *c)
अणु
	INIT_WORK(&c->work, hpsa_command_resubmit_worker);
	queue_work_on(raw_smp_processor_id(), h->resubmit_wq, &c->work);
पूर्ण

अटल व्योम process_ioaccel2_completion(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c, काष्ठा scsi_cmnd *cmd,
		काष्ठा hpsa_scsi_dev_t *dev)
अणु
	काष्ठा io_accel2_cmd *c2 = &h->ioaccel2_cmd_pool[c->cmdindex];

	/* check क्रम good status */
	अगर (likely(c2->error_data.serv_response == 0 &&
			c2->error_data.status == 0)) अणु
		cmd->result = 0;
		वापस hpsa_cmd_मुक्त_and_करोne(h, c, cmd);
	पूर्ण

	/*
	 * Any RAID offload error results in retry which will use
	 * the normal I/O path so the controller can handle whatever is
	 * wrong.
	 */
	अगर (is_logical_device(dev) &&
		c2->error_data.serv_response ==
			IOACCEL2_SERV_RESPONSE_FAILURE) अणु
		अगर (c2->error_data.status ==
			IOACCEL2_STATUS_SR_IOACCEL_DISABLED) अणु
			hpsa_turn_off_ioaccel_क्रम_device(dev);
		पूर्ण

		अगर (dev->in_reset) अणु
			cmd->result = DID_RESET << 16;
			वापस hpsa_cmd_मुक्त_and_करोne(h, c, cmd);
		पूर्ण

		वापस hpsa_retry_cmd(h, c);
	पूर्ण

	अगर (handle_ioaccel_mode2_error(h, c, cmd, c2, dev))
		वापस hpsa_retry_cmd(h, c);

	वापस hpsa_cmd_मुक्त_and_करोne(h, c, cmd);
पूर्ण

/* Returns 0 on success, < 0 otherwise. */
अटल पूर्णांक hpsa_evaluate_पंचांगf_status(काष्ठा ctlr_info *h,
					काष्ठा CommandList *cp)
अणु
	u8 पंचांगf_status = cp->err_info->ScsiStatus;

	चयन (पंचांगf_status) अणु
	हाल CISS_TMF_COMPLETE:
		/*
		 * CISS_TMF_COMPLETE never happens, instead,
		 * ei->CommandStatus == 0 क्रम this हाल.
		 */
	हाल CISS_TMF_SUCCESS:
		वापस 0;
	हाल CISS_TMF_INVALID_FRAME:
	हाल CISS_TMF_NOT_SUPPORTED:
	हाल CISS_TMF_FAILED:
	हाल CISS_TMF_WRONG_LUN:
	हाल CISS_TMF_OVERLAPPED_TAG:
		अवरोध;
	शेष:
		dev_warn(&h->pdev->dev, "Unknown TMF status: 0x%02x\n",
				पंचांगf_status);
		अवरोध;
	पूर्ण
	वापस -पंचांगf_status;
पूर्ण

अटल व्योम complete_scsi_command(काष्ठा CommandList *cp)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा ctlr_info *h;
	काष्ठा ErrorInfo *ei;
	काष्ठा hpsa_scsi_dev_t *dev;
	काष्ठा io_accel2_cmd *c2;

	u8 sense_key;
	u8 asc;      /* additional sense code */
	u8 ascq;     /* additional sense code qualअगरier */
	अचिन्हित दीर्घ sense_data_size;

	ei = cp->err_info;
	cmd = cp->scsi_cmd;
	h = cp->h;

	अगर (!cmd->device) अणु
		cmd->result = DID_NO_CONNECT << 16;
		वापस hpsa_cmd_मुक्त_and_करोne(h, cp, cmd);
	पूर्ण

	dev = cmd->device->hostdata;
	अगर (!dev) अणु
		cmd->result = DID_NO_CONNECT << 16;
		वापस hpsa_cmd_मुक्त_and_करोne(h, cp, cmd);
	पूर्ण
	c2 = &h->ioaccel2_cmd_pool[cp->cmdindex];

	scsi_dma_unmap(cmd); /* unकरो the DMA mappings */
	अगर ((cp->cmd_type == CMD_SCSI) &&
		(le16_to_cpu(cp->Header.SGTotal) > h->max_cmd_sg_entries))
		hpsa_unmap_sg_chain_block(h, cp);

	अगर ((cp->cmd_type == CMD_IOACCEL2) &&
		(c2->sg[0].chain_indicator == IOACCEL2_CHAIN))
		hpsa_unmap_ioaccel2_sg_chain_block(h, c2);

	cmd->result = (DID_OK << 16);		/* host byte */

	/* SCSI command has alपढ़ोy been cleaned up in SML */
	अगर (dev->was_हटाओd) अणु
		hpsa_cmd_resolve_and_मुक्त(h, cp);
		वापस;
	पूर्ण

	अगर (cp->cmd_type == CMD_IOACCEL2 || cp->cmd_type == CMD_IOACCEL1) अणु
		अगर (dev->physical_device && dev->expose_device &&
			dev->हटाओd) अणु
			cmd->result = DID_NO_CONNECT << 16;
			वापस hpsa_cmd_मुक्त_and_करोne(h, cp, cmd);
		पूर्ण
		अगर (likely(cp->phys_disk != शून्य))
			atomic_dec(&cp->phys_disk->ioaccel_cmds_out);
	पूर्ण

	/*
	 * We check क्रम lockup status here as it may be set क्रम
	 * CMD_SCSI, CMD_IOACCEL1 and CMD_IOACCEL2 commands by
	 * fail_all_oustanding_cmds()
	 */
	अगर (unlikely(ei->CommandStatus == CMD_CTLR_LOCKUP)) अणु
		/* DID_NO_CONNECT will prevent a retry */
		cmd->result = DID_NO_CONNECT << 16;
		वापस hpsa_cmd_मुक्त_and_करोne(h, cp, cmd);
	पूर्ण

	अगर (cp->cmd_type == CMD_IOACCEL2)
		वापस process_ioaccel2_completion(h, cp, cmd, dev);

	scsi_set_resid(cmd, ei->ResidualCnt);
	अगर (ei->CommandStatus == 0)
		वापस hpsa_cmd_मुक्त_and_करोne(h, cp, cmd);

	/* For I/O accelerator commands, copy over some fields to the normal
	 * CISS header used below क्रम error handling.
	 */
	अगर (cp->cmd_type == CMD_IOACCEL1) अणु
		काष्ठा io_accel1_cmd *c = &h->ioaccel_cmd_pool[cp->cmdindex];
		cp->Header.SGList = scsi_sg_count(cmd);
		cp->Header.SGTotal = cpu_to_le16(cp->Header.SGList);
		cp->Request.CDBLen = le16_to_cpu(c->io_flags) &
			IOACCEL1_IOFLAGS_CDBLEN_MASK;
		cp->Header.tag = c->tag;
		स_नकल(cp->Header.LUN.LunAddrBytes, c->CISS_LUN, 8);
		स_नकल(cp->Request.CDB, c->CDB, cp->Request.CDBLen);

		/* Any RAID offload error results in retry which will use
		 * the normal I/O path so the controller can handle whatever's
		 * wrong.
		 */
		अगर (is_logical_device(dev)) अणु
			अगर (ei->CommandStatus == CMD_IOACCEL_DISABLED)
				dev->offload_enabled = 0;
			वापस hpsa_retry_cmd(h, cp);
		पूर्ण
	पूर्ण

	/* an error has occurred */
	चयन (ei->CommandStatus) अणु

	हाल CMD_TARGET_STATUS:
		cmd->result |= ei->ScsiStatus;
		/* copy the sense data */
		अगर (SCSI_SENSE_BUFFERSIZE < माप(ei->SenseInfo))
			sense_data_size = SCSI_SENSE_BUFFERSIZE;
		अन्यथा
			sense_data_size = माप(ei->SenseInfo);
		अगर (ei->SenseLen < sense_data_size)
			sense_data_size = ei->SenseLen;
		स_नकल(cmd->sense_buffer, ei->SenseInfo, sense_data_size);
		अगर (ei->ScsiStatus)
			decode_sense_data(ei->SenseInfo, sense_data_size,
				&sense_key, &asc, &ascq);
		अगर (ei->ScsiStatus == SAM_STAT_CHECK_CONDITION) अणु
			चयन (sense_key) अणु
			हाल ABORTED_COMMAND:
				cmd->result |= DID_SOFT_ERROR << 16;
				अवरोध;
			हाल UNIT_ATTENTION:
				अगर (asc == 0x3F && ascq == 0x0E)
					h->drv_req_rescan = 1;
				अवरोध;
			हाल ILLEGAL_REQUEST:
				अगर (asc == 0x25 && ascq == 0x00) अणु
					dev->हटाओd = 1;
					cmd->result = DID_NO_CONNECT << 16;
				पूर्ण
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		/* Problem was not a check condition
		 * Pass it up to the upper layers...
		 */
		अगर (ei->ScsiStatus) अणु
			dev_warn(&h->pdev->dev, "cp %p has status 0x%x "
				"Sense: 0x%x, ASC: 0x%x, ASCQ: 0x%x, "
				"Returning result: 0x%x\n",
				cp, ei->ScsiStatus,
				sense_key, asc, ascq,
				cmd->result);
		पूर्ण अन्यथा अणु  /* scsi status is zero??? How??? */
			dev_warn(&h->pdev->dev, "cp %p SCSI status was 0. "
				"Returning no connection.\n", cp),

			/* Ordinarily, this हाल should never happen,
			 * but there is a bug in some released firmware
			 * revisions that allows it to happen अगर, क्रम
			 * example, a 4100 backplane loses घातer and
			 * the tape drive is in it.  We assume that
			 * it's a fatal error of some kind because we
			 * can't show that it wasn't. We will make it
			 * look like selection समयout since that is
			 * the most common reason क्रम this to occur,
			 * and it's severe enough.
			 */

			cmd->result = DID_NO_CONNECT << 16;
		पूर्ण
		अवरोध;

	हाल CMD_DATA_UNDERRUN: /* let mid layer handle it. */
		अवरोध;
	हाल CMD_DATA_OVERRUN:
		dev_warn(&h->pdev->dev,
			"CDB %16phN data overrun\n", cp->Request.CDB);
		अवरोध;
	हाल CMD_INVALID: अणु
		/* prपूर्णांक_bytes(cp, माप(*cp), 1, 0);
		prपूर्णांक_cmd(cp); */
		/* We get CMD_INVALID अगर you address a non-existent device
		 * instead of a selection समयout (no response).  You will
		 * see this अगर you yank out a drive, then try to access it.
		 * This is kind of a shame because it means that any other
		 * CMD_INVALID (e.g. driver bug) will get पूर्णांकerpreted as a
		 * missing target. */
		cmd->result = DID_NO_CONNECT << 16;
	पूर्ण
		अवरोध;
	हाल CMD_PROTOCOL_ERR:
		cmd->result = DID_ERROR << 16;
		dev_warn(&h->pdev->dev, "CDB %16phN : protocol error\n",
				cp->Request.CDB);
		अवरोध;
	हाल CMD_HARDWARE_ERR:
		cmd->result = DID_ERROR << 16;
		dev_warn(&h->pdev->dev, "CDB %16phN : hardware error\n",
			cp->Request.CDB);
		अवरोध;
	हाल CMD_CONNECTION_LOST:
		cmd->result = DID_ERROR << 16;
		dev_warn(&h->pdev->dev, "CDB %16phN : connection lost\n",
			cp->Request.CDB);
		अवरोध;
	हाल CMD_ABORTED:
		cmd->result = DID_ABORT << 16;
		अवरोध;
	हाल CMD_ABORT_FAILED:
		cmd->result = DID_ERROR << 16;
		dev_warn(&h->pdev->dev, "CDB %16phN : abort failed\n",
			cp->Request.CDB);
		अवरोध;
	हाल CMD_UNSOLICITED_ABORT:
		cmd->result = DID_SOFT_ERROR << 16; /* retry the command */
		dev_warn(&h->pdev->dev, "CDB %16phN : unsolicited abort\n",
			cp->Request.CDB);
		अवरोध;
	हाल CMD_TIMEOUT:
		cmd->result = DID_TIME_OUT << 16;
		dev_warn(&h->pdev->dev, "CDB %16phN timed out\n",
			cp->Request.CDB);
		अवरोध;
	हाल CMD_UNABORTABLE:
		cmd->result = DID_ERROR << 16;
		dev_warn(&h->pdev->dev, "Command unabortable\n");
		अवरोध;
	हाल CMD_TMF_STATUS:
		अगर (hpsa_evaluate_पंचांगf_status(h, cp)) /* TMF failed? */
			cmd->result = DID_ERROR << 16;
		अवरोध;
	हाल CMD_IOACCEL_DISABLED:
		/* This only handles the direct pass-through हाल since RAID
		 * offload is handled above.  Just attempt a retry.
		 */
		cmd->result = DID_SOFT_ERROR << 16;
		dev_warn(&h->pdev->dev,
				"cp %p had HP SSD Smart Path error\n", cp);
		अवरोध;
	शेष:
		cmd->result = DID_ERROR << 16;
		dev_warn(&h->pdev->dev, "cp %p returned unknown status %x\n",
				cp, ei->CommandStatus);
	पूर्ण

	वापस hpsa_cmd_मुक्त_and_करोne(h, cp, cmd);
पूर्ण

अटल व्योम hpsa_pci_unmap(काष्ठा pci_dev *pdev, काष्ठा CommandList *c,
		पूर्णांक sg_used, क्रमागत dma_data_direction data_direction)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sg_used; i++)
		dma_unmap_single(&pdev->dev, le64_to_cpu(c->SG[i].Addr),
				le32_to_cpu(c->SG[i].Len),
				data_direction);
पूर्ण

अटल पूर्णांक hpsa_map_one(काष्ठा pci_dev *pdev,
		काष्ठा CommandList *cp,
		अचिन्हित अक्षर *buf,
		माप_प्रकार buflen,
		क्रमागत dma_data_direction data_direction)
अणु
	u64 addr64;

	अगर (buflen == 0 || data_direction == DMA_NONE) अणु
		cp->Header.SGList = 0;
		cp->Header.SGTotal = cpu_to_le16(0);
		वापस 0;
	पूर्ण

	addr64 = dma_map_single(&pdev->dev, buf, buflen, data_direction);
	अगर (dma_mapping_error(&pdev->dev, addr64)) अणु
		/* Prevent subsequent unmap of something never mapped */
		cp->Header.SGList = 0;
		cp->Header.SGTotal = cpu_to_le16(0);
		वापस -1;
	पूर्ण
	cp->SG[0].Addr = cpu_to_le64(addr64);
	cp->SG[0].Len = cpu_to_le32(buflen);
	cp->SG[0].Ext = cpu_to_le32(HPSA_SG_LAST); /* we are not chaining */
	cp->Header.SGList = 1;   /* no. SGs contig in this cmd */
	cp->Header.SGTotal = cpu_to_le16(1); /* total sgs in cmd list */
	वापस 0;
पूर्ण

#घोषणा NO_TIMEOUT ((अचिन्हित दीर्घ) -1)
#घोषणा DEFAULT_TIMEOUT 30000 /* milliseconds */
अटल पूर्णांक hpsa_scsi_करो_simple_cmd_core(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, पूर्णांक reply_queue, अचिन्हित दीर्घ समयout_msecs)
अणु
	DECLARE_COMPLETION_ONSTACK(रुको);

	c->रुकोing = &रुको;
	__enqueue_cmd_and_start_io(h, c, reply_queue);
	अगर (समयout_msecs == NO_TIMEOUT) अणु
		/* TODO: get rid of this no-समयout thing */
		रुको_क्रम_completion_io(&रुको);
		वापस IO_OK;
	पूर्ण
	अगर (!रुको_क्रम_completion_io_समयout(&रुको,
					msecs_to_jअगरfies(समयout_msecs))) अणु
		dev_warn(&h->pdev->dev, "Command timed out.\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस IO_OK;
पूर्ण

अटल पूर्णांक hpsa_scsi_करो_simple_cmd(काष्ठा ctlr_info *h, काष्ठा CommandList *c,
				   पूर्णांक reply_queue, अचिन्हित दीर्घ समयout_msecs)
अणु
	अगर (unlikely(lockup_detected(h))) अणु
		c->err_info->CommandStatus = CMD_CTLR_LOCKUP;
		वापस IO_OK;
	पूर्ण
	वापस hpsa_scsi_करो_simple_cmd_core(h, c, reply_queue, समयout_msecs);
पूर्ण

अटल u32 lockup_detected(काष्ठा ctlr_info *h)
अणु
	पूर्णांक cpu;
	u32 rc, *lockup_detected;

	cpu = get_cpu();
	lockup_detected = per_cpu_ptr(h->lockup_detected, cpu);
	rc = *lockup_detected;
	put_cpu();
	वापस rc;
पूर्ण

#घोषणा MAX_DRIVER_CMD_RETRIES 25
अटल पूर्णांक hpsa_scsi_करो_simple_cmd_with_retry(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c, क्रमागत dma_data_direction data_direction,
		अचिन्हित दीर्घ समयout_msecs)
अणु
	पूर्णांक backoff_समय = 10, retry_count = 0;
	पूर्णांक rc;

	करो अणु
		स_रखो(c->err_info, 0, माप(*c->err_info));
		rc = hpsa_scsi_करो_simple_cmd(h, c, DEFAULT_REPLY_QUEUE,
						  समयout_msecs);
		अगर (rc)
			अवरोध;
		retry_count++;
		अगर (retry_count > 3) अणु
			msleep(backoff_समय);
			अगर (backoff_समय < 1000)
				backoff_समय *= 2;
		पूर्ण
	पूर्ण जबतक ((check_क्रम_unit_attention(h, c) ||
			check_क्रम_busy(h, c)) &&
			retry_count <= MAX_DRIVER_CMD_RETRIES);
	hpsa_pci_unmap(h->pdev, c, 1, data_direction);
	अगर (retry_count > MAX_DRIVER_CMD_RETRIES)
		rc = -EIO;
	वापस rc;
पूर्ण

अटल व्योम hpsa_prपूर्णांक_cmd(काष्ठा ctlr_info *h, अक्षर *txt,
				काष्ठा CommandList *c)
अणु
	स्थिर u8 *cdb = c->Request.CDB;
	स्थिर u8 *lun = c->Header.LUN.LunAddrBytes;

	dev_warn(&h->pdev->dev, "%s: LUN:%8phN CDB:%16phN\n",
		 txt, lun, cdb);
पूर्ण

अटल व्योम hpsa_scsi_पूर्णांकerpret_error(काष्ठा ctlr_info *h,
			काष्ठा CommandList *cp)
अणु
	स्थिर काष्ठा ErrorInfo *ei = cp->err_info;
	काष्ठा device *d = &cp->h->pdev->dev;
	u8 sense_key, asc, ascq;
	पूर्णांक sense_len;

	चयन (ei->CommandStatus) अणु
	हाल CMD_TARGET_STATUS:
		अगर (ei->SenseLen > माप(ei->SenseInfo))
			sense_len = माप(ei->SenseInfo);
		अन्यथा
			sense_len = ei->SenseLen;
		decode_sense_data(ei->SenseInfo, sense_len,
					&sense_key, &asc, &ascq);
		hpsa_prपूर्णांक_cmd(h, "SCSI status", cp);
		अगर (ei->ScsiStatus == SAM_STAT_CHECK_CONDITION)
			dev_warn(d, "SCSI Status = 02, Sense key = 0x%02x, ASC = 0x%02x, ASCQ = 0x%02x\n",
				sense_key, asc, ascq);
		अन्यथा
			dev_warn(d, "SCSI Status = 0x%02x\n", ei->ScsiStatus);
		अगर (ei->ScsiStatus == 0)
			dev_warn(d, "SCSI status is abnormally zero.  "
			"(probably indicates selection timeout "
			"reported incorrectly due to a known "
			"firmware bug, circa July, 2001.)\n");
		अवरोध;
	हाल CMD_DATA_UNDERRUN: /* let mid layer handle it. */
		अवरोध;
	हाल CMD_DATA_OVERRUN:
		hpsa_prपूर्णांक_cmd(h, "overrun condition", cp);
		अवरोध;
	हाल CMD_INVALID: अणु
		/* controller unक्रमtunately reports SCSI passthru's
		 * to non-existent tarमाला_लो as invalid commands.
		 */
		hpsa_prपूर्णांक_cmd(h, "invalid command", cp);
		dev_warn(d, "probably means device no longer present\n");
		पूर्ण
		अवरोध;
	हाल CMD_PROTOCOL_ERR:
		hpsa_prपूर्णांक_cmd(h, "protocol error", cp);
		अवरोध;
	हाल CMD_HARDWARE_ERR:
		hpsa_prपूर्णांक_cmd(h, "hardware error", cp);
		अवरोध;
	हाल CMD_CONNECTION_LOST:
		hpsa_prपूर्णांक_cmd(h, "connection lost", cp);
		अवरोध;
	हाल CMD_ABORTED:
		hpsa_prपूर्णांक_cmd(h, "aborted", cp);
		अवरोध;
	हाल CMD_ABORT_FAILED:
		hpsa_prपूर्णांक_cmd(h, "abort failed", cp);
		अवरोध;
	हाल CMD_UNSOLICITED_ABORT:
		hpsa_prपूर्णांक_cmd(h, "unsolicited abort", cp);
		अवरोध;
	हाल CMD_TIMEOUT:
		hpsa_prपूर्णांक_cmd(h, "timed out", cp);
		अवरोध;
	हाल CMD_UNABORTABLE:
		hpsa_prपूर्णांक_cmd(h, "unabortable", cp);
		अवरोध;
	हाल CMD_CTLR_LOCKUP:
		hpsa_prपूर्णांक_cmd(h, "controller lockup detected", cp);
		अवरोध;
	शेष:
		hpsa_prपूर्णांक_cmd(h, "unknown status", cp);
		dev_warn(d, "Unknown command status %x\n",
				ei->CommandStatus);
	पूर्ण
पूर्ण

अटल पूर्णांक hpsa_करो_receive_diagnostic(काष्ठा ctlr_info *h, u8 *scsi3addr,
					u8 page, u8 *buf, माप_प्रकार bufsize)
अणु
	पूर्णांक rc = IO_OK;
	काष्ठा CommandList *c;
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);
	अगर (fill_cmd(c, RECEIVE_DIAGNOSTIC, h, buf, bufsize,
			page, scsi3addr, TYPE_CMD)) अणु
		rc = -1;
		जाओ out;
	पूर्ण
	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर (rc)
		जाओ out;
	ei = c->err_info;
	अगर (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -1;
	पूर्ण
out:
	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

अटल u64 hpsa_get_enclosure_logical_identअगरier(काष्ठा ctlr_info *h,
						u8 *scsi3addr)
अणु
	u8 *buf;
	u64 sa = 0;
	पूर्णांक rc = 0;

	buf = kzalloc(1024, GFP_KERNEL);
	अगर (!buf)
		वापस 0;

	rc = hpsa_करो_receive_diagnostic(h, scsi3addr, RECEIVE_DIAGNOSTIC,
					buf, 1024);

	अगर (rc)
		जाओ out;

	sa = get_unaligned_be64(buf+12);

out:
	kमुक्त(buf);
	वापस sa;
पूर्ण

अटल पूर्णांक hpsa_scsi_करो_inquiry(काष्ठा ctlr_info *h, अचिन्हित अक्षर *scsi3addr,
			u16 page, अचिन्हित अक्षर *buf,
			अचिन्हित अक्षर bufsize)
अणु
	पूर्णांक rc = IO_OK;
	काष्ठा CommandList *c;
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);

	अगर (fill_cmd(c, HPSA_INQUIRY, h, buf, bufsize,
			page, scsi3addr, TYPE_CMD)) अणु
		rc = -1;
		जाओ out;
	पूर्ण
	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर (rc)
		जाओ out;
	ei = c->err_info;
	अगर (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -1;
	पूर्ण
out:
	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

अटल पूर्णांक hpsa_send_reset(काष्ठा ctlr_info *h, काष्ठा hpsa_scsi_dev_t *dev,
	u8 reset_type, पूर्णांक reply_queue)
अणु
	पूर्णांक rc = IO_OK;
	काष्ठा CommandList *c;
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);
	c->device = dev;

	/* fill_cmd can't fail here, no data buffer to map. */
	(व्योम) fill_cmd(c, reset_type, h, शून्य, 0, 0, dev->scsi3addr, TYPE_MSG);
	rc = hpsa_scsi_करो_simple_cmd(h, c, reply_queue, NO_TIMEOUT);
	अगर (rc) अणु
		dev_warn(&h->pdev->dev, "Failed to send reset command\n");
		जाओ out;
	पूर्ण
	/* no unmap needed here because no data xfer. */

	ei = c->err_info;
	अगर (ei->CommandStatus != 0) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -1;
	पूर्ण
out:
	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

अटल bool hpsa_cmd_dev_match(काष्ठा ctlr_info *h, काष्ठा CommandList *c,
			       काष्ठा hpsa_scsi_dev_t *dev,
			       अचिन्हित अक्षर *scsi3addr)
अणु
	पूर्णांक i;
	bool match = false;
	काष्ठा io_accel2_cmd *c2 = &h->ioaccel2_cmd_pool[c->cmdindex];
	काष्ठा hpsa_पंचांगf_काष्ठा *ac = (काष्ठा hpsa_पंचांगf_काष्ठा *) c2;

	अगर (hpsa_is_cmd_idle(c))
		वापस false;

	चयन (c->cmd_type) अणु
	हाल CMD_SCSI:
	हाल CMD_IOCTL_PEND:
		match = !स_भेद(scsi3addr, &c->Header.LUN.LunAddrBytes,
				माप(c->Header.LUN.LunAddrBytes));
		अवरोध;

	हाल CMD_IOACCEL1:
	हाल CMD_IOACCEL2:
		अगर (c->phys_disk == dev) अणु
			/* HBA mode match */
			match = true;
		पूर्ण अन्यथा अणु
			/* Possible RAID mode -- check each phys dev. */
			/* FIXME:  Do we need to take out a lock here?  If
			 * so, we could just call hpsa_get_pdisk_of_ioaccel2()
			 * instead. */
			क्रम (i = 0; i < dev->nphysical_disks && !match; i++) अणु
				/* FIXME: an alternate test might be
				 *
				 * match = dev->phys_disk[i]->ioaccel_handle
				 *              == c2->scsi_nexus;      */
				match = dev->phys_disk[i] == c->phys_disk;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IOACCEL2_TMF:
		क्रम (i = 0; i < dev->nphysical_disks && !match; i++) अणु
			match = dev->phys_disk[i]->ioaccel_handle ==
					le32_to_cpu(ac->it_nexus);
		पूर्ण
		अवरोध;

	हाल 0:		/* The command is in the middle of being initialized. */
		match = false;
		अवरोध;

	शेष:
		dev_err(&h->pdev->dev, "unexpected cmd_type: %d\n",
			c->cmd_type);
		BUG();
	पूर्ण

	वापस match;
पूर्ण

अटल पूर्णांक hpsa_करो_reset(काष्ठा ctlr_info *h, काष्ठा hpsa_scsi_dev_t *dev,
	u8 reset_type, पूर्णांक reply_queue)
अणु
	पूर्णांक rc = 0;

	/* We can really only handle one reset at a समय */
	अगर (mutex_lock_पूर्णांकerruptible(&h->reset_mutex) == -EINTR) अणु
		dev_warn(&h->pdev->dev, "concurrent reset wait interrupted.\n");
		वापस -EINTR;
	पूर्ण

	rc = hpsa_send_reset(h, dev, reset_type, reply_queue);
	अगर (!rc) अणु
		/* incremented by sending the reset request */
		atomic_dec(&dev->commands_outstanding);
		रुको_event(h->event_sync_रुको_queue,
			atomic_पढ़ो(&dev->commands_outstanding) <= 0 ||
			lockup_detected(h));
	पूर्ण

	अगर (unlikely(lockup_detected(h))) अणु
		dev_warn(&h->pdev->dev,
			 "Controller lockup detected during reset wait\n");
		rc = -ENODEV;
	पूर्ण

	अगर (!rc)
		rc = रुको_क्रम_device_to_become_पढ़ोy(h, dev->scsi3addr, 0);

	mutex_unlock(&h->reset_mutex);
	वापस rc;
पूर्ण

अटल व्योम hpsa_get_raid_level(काष्ठा ctlr_info *h,
	अचिन्हित अक्षर *scsi3addr, अचिन्हित अक्षर *raid_level)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर *buf;

	*raid_level = RAID_UNKNOWN;
	buf = kzalloc(64, GFP_KERNEL);
	अगर (!buf)
		वापस;

	अगर (!hpsa_vpd_page_supported(h, scsi3addr,
		HPSA_VPD_LV_DEVICE_GEOMETRY))
		जाओ निकास;

	rc = hpsa_scsi_करो_inquiry(h, scsi3addr, VPD_PAGE |
		HPSA_VPD_LV_DEVICE_GEOMETRY, buf, 64);

	अगर (rc == 0)
		*raid_level = buf[8];
	अगर (*raid_level > RAID_UNKNOWN)
		*raid_level = RAID_UNKNOWN;
निकास:
	kमुक्त(buf);
	वापस;
पूर्ण

#घोषणा HPSA_MAP_DEBUG
#अगर_घोषित HPSA_MAP_DEBUG
अटल व्योम hpsa_debug_map_buff(काष्ठा ctlr_info *h, पूर्णांक rc,
				काष्ठा raid_map_data *map_buff)
अणु
	काष्ठा raid_map_disk_data *dd = &map_buff->data[0];
	पूर्णांक map, row, col;
	u16 map_cnt, row_cnt, disks_per_row;

	अगर (rc != 0)
		वापस;

	/* Show details only अगर debugging has been activated. */
	अगर (h->raid_offload_debug < 2)
		वापस;

	dev_info(&h->pdev->dev, "structure_size = %u\n",
				le32_to_cpu(map_buff->काष्ठाure_size));
	dev_info(&h->pdev->dev, "volume_blk_size = %u\n",
			le32_to_cpu(map_buff->volume_blk_size));
	dev_info(&h->pdev->dev, "volume_blk_cnt = 0x%llx\n",
			le64_to_cpu(map_buff->volume_blk_cnt));
	dev_info(&h->pdev->dev, "physicalBlockShift = %u\n",
			map_buff->phys_blk_shअगरt);
	dev_info(&h->pdev->dev, "parity_rotation_shift = %u\n",
			map_buff->parity_rotation_shअगरt);
	dev_info(&h->pdev->dev, "strip_size = %u\n",
			le16_to_cpu(map_buff->strip_size));
	dev_info(&h->pdev->dev, "disk_starting_blk = 0x%llx\n",
			le64_to_cpu(map_buff->disk_starting_blk));
	dev_info(&h->pdev->dev, "disk_blk_cnt = 0x%llx\n",
			le64_to_cpu(map_buff->disk_blk_cnt));
	dev_info(&h->pdev->dev, "data_disks_per_row = %u\n",
			le16_to_cpu(map_buff->data_disks_per_row));
	dev_info(&h->pdev->dev, "metadata_disks_per_row = %u\n",
			le16_to_cpu(map_buff->metadata_disks_per_row));
	dev_info(&h->pdev->dev, "row_cnt = %u\n",
			le16_to_cpu(map_buff->row_cnt));
	dev_info(&h->pdev->dev, "layout_map_count = %u\n",
			le16_to_cpu(map_buff->layout_map_count));
	dev_info(&h->pdev->dev, "flags = 0x%x\n",
			le16_to_cpu(map_buff->flags));
	dev_info(&h->pdev->dev, "encryption = %s\n",
			le16_to_cpu(map_buff->flags) &
			RAID_MAP_FLAG_ENCRYPT_ON ?  "ON" : "OFF");
	dev_info(&h->pdev->dev, "dekindex = %u\n",
			le16_to_cpu(map_buff->dekindex));
	map_cnt = le16_to_cpu(map_buff->layout_map_count);
	क्रम (map = 0; map < map_cnt; map++) अणु
		dev_info(&h->pdev->dev, "Map%u:\n", map);
		row_cnt = le16_to_cpu(map_buff->row_cnt);
		क्रम (row = 0; row < row_cnt; row++) अणु
			dev_info(&h->pdev->dev, "  Row%u:\n", row);
			disks_per_row =
				le16_to_cpu(map_buff->data_disks_per_row);
			क्रम (col = 0; col < disks_per_row; col++, dd++)
				dev_info(&h->pdev->dev,
					"    D%02u: h=0x%04x xor=%u,%u\n",
					col, dd->ioaccel_handle,
					dd->xor_mult[0], dd->xor_mult[1]);
			disks_per_row =
				le16_to_cpu(map_buff->metadata_disks_per_row);
			क्रम (col = 0; col < disks_per_row; col++, dd++)
				dev_info(&h->pdev->dev,
					"    M%02u: h=0x%04x xor=%u,%u\n",
					col, dd->ioaccel_handle,
					dd->xor_mult[0], dd->xor_mult[1]);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम hpsa_debug_map_buff(__attribute__((unused)) काष्ठा ctlr_info *h,
			__attribute__((unused)) पूर्णांक rc,
			__attribute__((unused)) काष्ठा raid_map_data *map_buff)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hpsa_get_raid_map(काष्ठा ctlr_info *h,
	अचिन्हित अक्षर *scsi3addr, काष्ठा hpsa_scsi_dev_t *this_device)
अणु
	पूर्णांक rc = 0;
	काष्ठा CommandList *c;
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);

	अगर (fill_cmd(c, HPSA_GET_RAID_MAP, h, &this_device->raid_map,
			माप(this_device->raid_map), 0,
			scsi3addr, TYPE_CMD)) अणु
		dev_warn(&h->pdev->dev, "hpsa_get_raid_map fill_cmd failed\n");
		cmd_मुक्त(h, c);
		वापस -1;
	पूर्ण
	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर (rc)
		जाओ out;
	ei = c->err_info;
	अगर (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -1;
		जाओ out;
	पूर्ण
	cmd_मुक्त(h, c);

	/* @toकरो in the future, dynamically allocate RAID map memory */
	अगर (le32_to_cpu(this_device->raid_map.काष्ठाure_size) >
				माप(this_device->raid_map)) अणु
		dev_warn(&h->pdev->dev, "RAID map size is too large!\n");
		rc = -1;
	पूर्ण
	hpsa_debug_map_buff(h, rc, &this_device->raid_map);
	वापस rc;
out:
	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

अटल पूर्णांक hpsa_bmic_sense_subप्रणाली_inक्रमmation(काष्ठा ctlr_info *h,
		अचिन्हित अक्षर scsi3addr[], u16 bmic_device_index,
		काष्ठा bmic_sense_subप्रणाली_info *buf, माप_प्रकार bufsize)
अणु
	पूर्णांक rc = IO_OK;
	काष्ठा CommandList *c;
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);

	rc = fill_cmd(c, BMIC_SENSE_SUBSYSTEM_INFORMATION, h, buf, bufsize,
		0, RAID_CTLR_LUNID, TYPE_CMD);
	अगर (rc)
		जाओ out;

	c->Request.CDB[2] = bmic_device_index & 0xff;
	c->Request.CDB[9] = (bmic_device_index >> 8) & 0xff;

	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर (rc)
		जाओ out;
	ei = c->err_info;
	अगर (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -1;
	पूर्ण
out:
	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

अटल पूर्णांक hpsa_bmic_id_controller(काष्ठा ctlr_info *h,
	काष्ठा bmic_identअगरy_controller *buf, माप_प्रकार bufsize)
अणु
	पूर्णांक rc = IO_OK;
	काष्ठा CommandList *c;
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);

	rc = fill_cmd(c, BMIC_IDENTIFY_CONTROLLER, h, buf, bufsize,
		0, RAID_CTLR_LUNID, TYPE_CMD);
	अगर (rc)
		जाओ out;

	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर (rc)
		जाओ out;
	ei = c->err_info;
	अगर (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -1;
	पूर्ण
out:
	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

अटल पूर्णांक hpsa_bmic_id_physical_device(काष्ठा ctlr_info *h,
		अचिन्हित अक्षर scsi3addr[], u16 bmic_device_index,
		काष्ठा bmic_identअगरy_physical_device *buf, माप_प्रकार bufsize)
अणु
	पूर्णांक rc = IO_OK;
	काष्ठा CommandList *c;
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);
	rc = fill_cmd(c, BMIC_IDENTIFY_PHYSICAL_DEVICE, h, buf, bufsize,
		0, RAID_CTLR_LUNID, TYPE_CMD);
	अगर (rc)
		जाओ out;

	c->Request.CDB[2] = bmic_device_index & 0xff;
	c->Request.CDB[9] = (bmic_device_index >> 8) & 0xff;

	hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
						NO_TIMEOUT);
	ei = c->err_info;
	अगर (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -1;
	पूर्ण
out:
	cmd_मुक्त(h, c);

	वापस rc;
पूर्ण

/*
 * get enclosure inक्रमmation
 * काष्ठा ReportExtendedLUNdata *rlep - Used क्रम BMIC drive number
 * काष्ठा hpsa_scsi_dev_t *encl_dev - device entry क्रम enclosure
 * Uses id_physical_device to determine the box_index.
 */
अटल व्योम hpsa_get_enclosure_info(काष्ठा ctlr_info *h,
			अचिन्हित अक्षर *scsi3addr,
			काष्ठा ReportExtendedLUNdata *rlep, पूर्णांक rle_index,
			काष्ठा hpsa_scsi_dev_t *encl_dev)
अणु
	पूर्णांक rc = -1;
	काष्ठा CommandList *c = शून्य;
	काष्ठा ErrorInfo *ei = शून्य;
	काष्ठा bmic_sense_storage_box_params *bssbp = शून्य;
	काष्ठा bmic_identअगरy_physical_device *id_phys = शून्य;
	काष्ठा ext_report_lun_entry *rle;
	u16 bmic_device_index = 0;

	अगर (rle_index < 0 || rle_index >= HPSA_MAX_PHYS_LUN)
		वापस;

	rle = &rlep->LUN[rle_index];

	encl_dev->eli =
		hpsa_get_enclosure_logical_identअगरier(h, scsi3addr);

	bmic_device_index = GET_BMIC_DRIVE_NUMBER(&rle->lunid[0]);

	अगर (encl_dev->target == -1 || encl_dev->lun == -1) अणु
		rc = IO_OK;
		जाओ out;
	पूर्ण

	अगर (bmic_device_index == 0xFF00 || MASKED_DEVICE(&rle->lunid[0])) अणु
		rc = IO_OK;
		जाओ out;
	पूर्ण

	bssbp = kzalloc(माप(*bssbp), GFP_KERNEL);
	अगर (!bssbp)
		जाओ out;

	id_phys = kzalloc(माप(*id_phys), GFP_KERNEL);
	अगर (!id_phys)
		जाओ out;

	rc = hpsa_bmic_id_physical_device(h, scsi3addr, bmic_device_index,
						id_phys, माप(*id_phys));
	अगर (rc) अणु
		dev_warn(&h->pdev->dev, "%s: id_phys failed %d bdi[0x%x]\n",
			__func__, encl_dev->बाह्यal, bmic_device_index);
		जाओ out;
	पूर्ण

	c = cmd_alloc(h);

	rc = fill_cmd(c, BMIC_SENSE_STORAGE_BOX_PARAMS, h, bssbp,
			माप(*bssbp), 0, RAID_CTLR_LUNID, TYPE_CMD);

	अगर (rc)
		जाओ out;

	अगर (id_phys->phys_connector[1] == 'E')
		c->Request.CDB[5] = id_phys->box_index;
	अन्यथा
		c->Request.CDB[5] = 0;

	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
						NO_TIMEOUT);
	अगर (rc)
		जाओ out;

	ei = c->err_info;
	अगर (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		rc = -1;
		जाओ out;
	पूर्ण

	encl_dev->box[id_phys->active_path_number] = bssbp->phys_box_on_port;
	स_नकल(&encl_dev->phys_connector[id_phys->active_path_number],
		bssbp->phys_connector, माप(bssbp->phys_connector));

	rc = IO_OK;
out:
	kमुक्त(bssbp);
	kमुक्त(id_phys);

	अगर (c)
		cmd_मुक्त(h, c);

	अगर (rc != IO_OK)
		hpsa_show_dev_msg(KERN_INFO, h, encl_dev,
			"Error, could not get enclosure information");
पूर्ण

अटल u64 hpsa_get_sas_address_from_report_physical(काष्ठा ctlr_info *h,
						अचिन्हित अक्षर *scsi3addr)
अणु
	काष्ठा ReportExtendedLUNdata *physdev;
	u32 nphysicals;
	u64 sa = 0;
	पूर्णांक i;

	physdev = kzalloc(माप(*physdev), GFP_KERNEL);
	अगर (!physdev)
		वापस 0;

	अगर (hpsa_scsi_करो_report_phys_luns(h, physdev, माप(*physdev))) अणु
		dev_err(&h->pdev->dev, "report physical LUNs failed.\n");
		kमुक्त(physdev);
		वापस 0;
	पूर्ण
	nphysicals = get_unaligned_be32(physdev->LUNListLength) / 24;

	क्रम (i = 0; i < nphysicals; i++)
		अगर (!स_भेद(&physdev->LUN[i].lunid[0], scsi3addr, 8)) अणु
			sa = get_unaligned_be64(&physdev->LUN[i].wwid[0]);
			अवरोध;
		पूर्ण

	kमुक्त(physdev);

	वापस sa;
पूर्ण

अटल व्योम hpsa_get_sas_address(काष्ठा ctlr_info *h, अचिन्हित अक्षर *scsi3addr,
					काष्ठा hpsa_scsi_dev_t *dev)
अणु
	पूर्णांक rc;
	u64 sa = 0;

	अगर (is_hba_lunid(scsi3addr)) अणु
		काष्ठा bmic_sense_subप्रणाली_info *ssi;

		ssi = kzalloc(माप(*ssi), GFP_KERNEL);
		अगर (!ssi)
			वापस;

		rc = hpsa_bmic_sense_subप्रणाली_inक्रमmation(h,
					scsi3addr, 0, ssi, माप(*ssi));
		अगर (rc == 0) अणु
			sa = get_unaligned_be64(ssi->primary_world_wide_id);
			h->sas_address = sa;
		पूर्ण

		kमुक्त(ssi);
	पूर्ण अन्यथा
		sa = hpsa_get_sas_address_from_report_physical(h, scsi3addr);

	dev->sas_address = sa;
पूर्ण

अटल व्योम hpsa_ext_ctrl_present(काष्ठा ctlr_info *h,
	काष्ठा ReportExtendedLUNdata *physdev)
अणु
	u32 nphysicals;
	पूर्णांक i;

	अगर (h->discovery_polling)
		वापस;

	nphysicals = (get_unaligned_be32(physdev->LUNListLength) / 24) + 1;

	क्रम (i = 0; i < nphysicals; i++) अणु
		अगर (physdev->LUN[i].device_type ==
			BMIC_DEVICE_TYPE_CONTROLLER
			&& !is_hba_lunid(physdev->LUN[i].lunid)) अणु
			dev_info(&h->pdev->dev,
				"External controller present, activate discovery polling and disable rld caching\n");
			hpsa_disable_rld_caching(h);
			h->discovery_polling = 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Get a device id from inquiry page 0x83 */
अटल bool hpsa_vpd_page_supported(काष्ठा ctlr_info *h,
	अचिन्हित अक्षर scsi3addr[], u8 page)
अणु
	पूर्णांक rc;
	पूर्णांक i;
	पूर्णांक pages;
	अचिन्हित अक्षर *buf, bufsize;

	buf = kzalloc(256, GFP_KERNEL);
	अगर (!buf)
		वापस false;

	/* Get the size of the page list first */
	rc = hpsa_scsi_करो_inquiry(h, scsi3addr,
				VPD_PAGE | HPSA_VPD_SUPPORTED_PAGES,
				buf, HPSA_VPD_HEADER_SZ);
	अगर (rc != 0)
		जाओ निकास_unsupported;
	pages = buf[3];
	अगर ((pages + HPSA_VPD_HEADER_SZ) <= 255)
		bufsize = pages + HPSA_VPD_HEADER_SZ;
	अन्यथा
		bufsize = 255;

	/* Get the whole VPD page list */
	rc = hpsa_scsi_करो_inquiry(h, scsi3addr,
				VPD_PAGE | HPSA_VPD_SUPPORTED_PAGES,
				buf, bufsize);
	अगर (rc != 0)
		जाओ निकास_unsupported;

	pages = buf[3];
	क्रम (i = 1; i <= pages; i++)
		अगर (buf[3 + i] == page)
			जाओ निकास_supported;
निकास_unsupported:
	kमुक्त(buf);
	वापस false;
निकास_supported:
	kमुक्त(buf);
	वापस true;
पूर्ण

/*
 * Called during a scan operation.
 * Sets ioaccel status on the new device list, not the existing device list
 *
 * The device list used during I/O will be updated later in
 * adjust_hpsa_scsi_table.
 */
अटल व्योम hpsa_get_ioaccel_status(काष्ठा ctlr_info *h,
	अचिन्हित अक्षर *scsi3addr, काष्ठा hpsa_scsi_dev_t *this_device)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर *buf;
	u8 ioaccel_status;

	this_device->offload_config = 0;
	this_device->offload_enabled = 0;
	this_device->offload_to_be_enabled = 0;

	buf = kzalloc(64, GFP_KERNEL);
	अगर (!buf)
		वापस;
	अगर (!hpsa_vpd_page_supported(h, scsi3addr, HPSA_VPD_LV_IOACCEL_STATUS))
		जाओ out;
	rc = hpsa_scsi_करो_inquiry(h, scsi3addr,
			VPD_PAGE | HPSA_VPD_LV_IOACCEL_STATUS, buf, 64);
	अगर (rc != 0)
		जाओ out;

#घोषणा IOACCEL_STATUS_BYTE 4
#घोषणा OFFLOAD_CONFIGURED_BIT 0x01
#घोषणा OFFLOAD_ENABLED_BIT 0x02
	ioaccel_status = buf[IOACCEL_STATUS_BYTE];
	this_device->offload_config =
		!!(ioaccel_status & OFFLOAD_CONFIGURED_BIT);
	अगर (this_device->offload_config) अणु
		bool offload_enabled =
			!!(ioaccel_status & OFFLOAD_ENABLED_BIT);
		/*
		 * Check to see अगर offload can be enabled.
		 */
		अगर (offload_enabled) अणु
			rc = hpsa_get_raid_map(h, scsi3addr, this_device);
			अगर (rc) /* could not load raid_map */
				जाओ out;
			this_device->offload_to_be_enabled = 1;
		पूर्ण
	पूर्ण

out:
	kमुक्त(buf);
	वापस;
पूर्ण

/* Get the device id from inquiry page 0x83 */
अटल पूर्णांक hpsa_get_device_id(काष्ठा ctlr_info *h, अचिन्हित अक्षर *scsi3addr,
	अचिन्हित अक्षर *device_id, पूर्णांक index, पूर्णांक buflen)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर *buf;

	/* Does controller have VPD क्रम device id? */
	अगर (!hpsa_vpd_page_supported(h, scsi3addr, HPSA_VPD_LV_DEVICE_ID))
		वापस 1; /* not supported */

	buf = kzalloc(64, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	rc = hpsa_scsi_करो_inquiry(h, scsi3addr, VPD_PAGE |
					HPSA_VPD_LV_DEVICE_ID, buf, 64);
	अगर (rc == 0) अणु
		अगर (buflen > 16)
			buflen = 16;
		स_नकल(device_id, &buf[8], buflen);
	पूर्ण

	kमुक्त(buf);

	वापस rc; /*0 - got id,  otherwise, didn't */
पूर्ण

अटल पूर्णांक hpsa_scsi_करो_report_luns(काष्ठा ctlr_info *h, पूर्णांक logical,
		व्योम *buf, पूर्णांक bufsize,
		पूर्णांक extended_response)
अणु
	पूर्णांक rc = IO_OK;
	काष्ठा CommandList *c;
	अचिन्हित अक्षर scsi3addr[8];
	काष्ठा ErrorInfo *ei;

	c = cmd_alloc(h);

	/* address the controller */
	स_रखो(scsi3addr, 0, माप(scsi3addr));
	अगर (fill_cmd(c, logical ? HPSA_REPORT_LOG : HPSA_REPORT_PHYS, h,
		buf, bufsize, 0, scsi3addr, TYPE_CMD)) अणु
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	अगर (extended_response)
		c->Request.CDB[1] = extended_response;
	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर (rc)
		जाओ out;
	ei = c->err_info;
	अगर (ei->CommandStatus != 0 &&
	    ei->CommandStatus != CMD_DATA_UNDERRUN) अणु
		hpsa_scsi_पूर्णांकerpret_error(h, c);
		rc = -EIO;
	पूर्ण अन्यथा अणु
		काष्ठा ReportLUNdata *rld = buf;

		अगर (rld->extended_response_flag != extended_response) अणु
			अगर (!h->legacy_board) अणु
				dev_err(&h->pdev->dev,
					"report luns requested format %u, got %u\n",
					extended_response,
					rld->extended_response_flag);
				rc = -EINVAL;
			पूर्ण अन्यथा
				rc = -EOPNOTSUPP;
		पूर्ण
	पूर्ण
out:
	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक hpsa_scsi_करो_report_phys_luns(काष्ठा ctlr_info *h,
		काष्ठा ReportExtendedLUNdata *buf, पूर्णांक bufsize)
अणु
	पूर्णांक rc;
	काष्ठा ReportLUNdata *lbuf;

	rc = hpsa_scsi_करो_report_luns(h, 0, buf, bufsize,
				      HPSA_REPORT_PHYS_EXTENDED);
	अगर (!rc || rc != -EOPNOTSUPP)
		वापस rc;

	/* REPORT PHYS EXTENDED is not supported */
	lbuf = kzalloc(माप(*lbuf), GFP_KERNEL);
	अगर (!lbuf)
		वापस -ENOMEM;

	rc = hpsa_scsi_करो_report_luns(h, 0, lbuf, माप(*lbuf), 0);
	अगर (!rc) अणु
		पूर्णांक i;
		u32 nphys;

		/* Copy ReportLUNdata header */
		स_नकल(buf, lbuf, 8);
		nphys = be32_to_cpu(*((__be32 *)lbuf->LUNListLength)) / 8;
		क्रम (i = 0; i < nphys; i++)
			स_नकल(buf->LUN[i].lunid, lbuf->LUN[i], 8);
	पूर्ण
	kमुक्त(lbuf);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक hpsa_scsi_करो_report_log_luns(काष्ठा ctlr_info *h,
		काष्ठा ReportLUNdata *buf, पूर्णांक bufsize)
अणु
	वापस hpsa_scsi_करो_report_luns(h, 1, buf, bufsize, 0);
पूर्ण

अटल अंतरभूत व्योम hpsa_set_bus_target_lun(काष्ठा hpsa_scsi_dev_t *device,
	पूर्णांक bus, पूर्णांक target, पूर्णांक lun)
अणु
	device->bus = bus;
	device->target = target;
	device->lun = lun;
पूर्ण

/* Use VPD inquiry to get details of volume status */
अटल पूर्णांक hpsa_get_volume_status(काष्ठा ctlr_info *h,
					अचिन्हित अक्षर scsi3addr[])
अणु
	पूर्णांक rc;
	पूर्णांक status;
	पूर्णांक size;
	अचिन्हित अक्षर *buf;

	buf = kzalloc(64, GFP_KERNEL);
	अगर (!buf)
		वापस HPSA_VPD_LV_STATUS_UNSUPPORTED;

	/* Does controller have VPD क्रम logical volume status? */
	अगर (!hpsa_vpd_page_supported(h, scsi3addr, HPSA_VPD_LV_STATUS))
		जाओ निकास_failed;

	/* Get the size of the VPD वापस buffer */
	rc = hpsa_scsi_करो_inquiry(h, scsi3addr, VPD_PAGE | HPSA_VPD_LV_STATUS,
					buf, HPSA_VPD_HEADER_SZ);
	अगर (rc != 0)
		जाओ निकास_failed;
	size = buf[3];

	/* Now get the whole VPD buffer */
	rc = hpsa_scsi_करो_inquiry(h, scsi3addr, VPD_PAGE | HPSA_VPD_LV_STATUS,
					buf, size + HPSA_VPD_HEADER_SZ);
	अगर (rc != 0)
		जाओ निकास_failed;
	status = buf[4]; /* status byte */

	kमुक्त(buf);
	वापस status;
निकास_failed:
	kमुक्त(buf);
	वापस HPSA_VPD_LV_STATUS_UNSUPPORTED;
पूर्ण

/* Determine offline status of a volume.
 * Return either:
 *  0 (not offline)
 *  0xff (offline क्रम unknown reasons)
 *  # (पूर्णांकeger code indicating one of several NOT READY states
 *     describing why a volume is to be kept offline)
 */
अटल अचिन्हित अक्षर hpsa_volume_offline(काष्ठा ctlr_info *h,
					अचिन्हित अक्षर scsi3addr[])
अणु
	काष्ठा CommandList *c;
	अचिन्हित अक्षर *sense;
	u8 sense_key, asc, ascq;
	पूर्णांक sense_len;
	पूर्णांक rc, ldstat = 0;
#घोषणा ASC_LUN_NOT_READY 0x04
#घोषणा ASCQ_LUN_NOT_READY_FORMAT_IN_PROGRESS 0x04
#घोषणा ASCQ_LUN_NOT_READY_INITIALIZING_CMD_REQ 0x02

	c = cmd_alloc(h);

	(व्योम) fill_cmd(c, TEST_UNIT_READY, h, शून्य, 0, 0, scsi3addr, TYPE_CMD);
	rc = hpsa_scsi_करो_simple_cmd(h, c, DEFAULT_REPLY_QUEUE,
					NO_TIMEOUT);
	अगर (rc) अणु
		cmd_मुक्त(h, c);
		वापस HPSA_VPD_LV_STATUS_UNSUPPORTED;
	पूर्ण
	sense = c->err_info->SenseInfo;
	अगर (c->err_info->SenseLen > माप(c->err_info->SenseInfo))
		sense_len = माप(c->err_info->SenseInfo);
	अन्यथा
		sense_len = c->err_info->SenseLen;
	decode_sense_data(sense, sense_len, &sense_key, &asc, &ascq);
	cmd_मुक्त(h, c);

	/* Determine the reason क्रम not पढ़ोy state */
	ldstat = hpsa_get_volume_status(h, scsi3addr);

	/* Keep volume offline in certain हालs: */
	चयन (ldstat) अणु
	हाल HPSA_LV_FAILED:
	हाल HPSA_LV_UNDERGOING_ERASE:
	हाल HPSA_LV_NOT_AVAILABLE:
	हाल HPSA_LV_UNDERGOING_RPI:
	हाल HPSA_LV_PENDING_RPI:
	हाल HPSA_LV_ENCRYPTED_NO_KEY:
	हाल HPSA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER:
	हाल HPSA_LV_UNDERGOING_ENCRYPTION:
	हाल HPSA_LV_UNDERGOING_ENCRYPTION_REKEYING:
	हाल HPSA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER:
		वापस ldstat;
	हाल HPSA_VPD_LV_STATUS_UNSUPPORTED:
		/* If VPD status page isn't available,
		 * use ASC/ASCQ to determine state
		 */
		अगर ((ascq == ASCQ_LUN_NOT_READY_FORMAT_IN_PROGRESS) ||
			(ascq == ASCQ_LUN_NOT_READY_INITIALIZING_CMD_REQ))
			वापस ldstat;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस HPSA_LV_OK;
पूर्ण

अटल पूर्णांक hpsa_update_device_info(काष्ठा ctlr_info *h,
	अचिन्हित अक्षर scsi3addr[], काष्ठा hpsa_scsi_dev_t *this_device,
	अचिन्हित अक्षर *is_OBDR_device)
अणु

#घोषणा OBDR_SIG_OFFSET 43
#घोषणा OBDR_TAPE_SIG "$DR-10"
#घोषणा OBDR_SIG_LEN (माप(OBDR_TAPE_SIG) - 1)
#घोषणा OBDR_TAPE_INQ_SIZE (OBDR_SIG_OFFSET + OBDR_SIG_LEN)

	अचिन्हित अक्षर *inq_buff;
	अचिन्हित अक्षर *obdr_sig;
	पूर्णांक rc = 0;

	inq_buff = kzalloc(OBDR_TAPE_INQ_SIZE, GFP_KERNEL);
	अगर (!inq_buff) अणु
		rc = -ENOMEM;
		जाओ bail_out;
	पूर्ण

	/* Do an inquiry to the device to see what it is. */
	अगर (hpsa_scsi_करो_inquiry(h, scsi3addr, 0, inq_buff,
		(अचिन्हित अक्षर) OBDR_TAPE_INQ_SIZE) != 0) अणु
		dev_err(&h->pdev->dev,
			"%s: inquiry failed, device will be skipped.\n",
			__func__);
		rc = HPSA_INQUIRY_FAILED;
		जाओ bail_out;
	पूर्ण

	scsi_sanitize_inquiry_string(&inq_buff[8], 8);
	scsi_sanitize_inquiry_string(&inq_buff[16], 16);

	this_device->devtype = (inq_buff[0] & 0x1f);
	स_नकल(this_device->scsi3addr, scsi3addr, 8);
	स_नकल(this_device->venकरोr, &inq_buff[8],
		माप(this_device->venकरोr));
	स_नकल(this_device->model, &inq_buff[16],
		माप(this_device->model));
	this_device->rev = inq_buff[2];
	स_रखो(this_device->device_id, 0,
		माप(this_device->device_id));
	अगर (hpsa_get_device_id(h, scsi3addr, this_device->device_id, 8,
		माप(this_device->device_id)) < 0) अणु
		dev_err(&h->pdev->dev,
			"hpsa%d: %s: can't get device id for [%d:%d:%d:%d]\t%s\t%.16s\n",
			h->ctlr, __func__,
			h->scsi_host->host_no,
			this_device->bus, this_device->target,
			this_device->lun,
			scsi_device_type(this_device->devtype),
			this_device->model);
		rc = HPSA_LV_FAILED;
		जाओ bail_out;
	पूर्ण

	अगर ((this_device->devtype == TYPE_DISK ||
		this_device->devtype == TYPE_ZBC) &&
		is_logical_dev_addr_mode(scsi3addr)) अणु
		अचिन्हित अक्षर volume_offline;

		hpsa_get_raid_level(h, scsi3addr, &this_device->raid_level);
		अगर (h->fw_support & MISC_FW_RAID_OFFLOAD_BASIC)
			hpsa_get_ioaccel_status(h, scsi3addr, this_device);
		volume_offline = hpsa_volume_offline(h, scsi3addr);
		अगर (volume_offline == HPSA_VPD_LV_STATUS_UNSUPPORTED &&
		    h->legacy_board) अणु
			/*
			 * Legacy boards might not support volume status
			 */
			dev_info(&h->pdev->dev,
				 "C0:T%d:L%d Volume status not available, assuming online.\n",
				 this_device->target, this_device->lun);
			volume_offline = 0;
		पूर्ण
		this_device->volume_offline = volume_offline;
		अगर (volume_offline == HPSA_LV_FAILED) अणु
			rc = HPSA_LV_FAILED;
			dev_err(&h->pdev->dev,
				"%s: LV failed, device will be skipped.\n",
				__func__);
			जाओ bail_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		this_device->raid_level = RAID_UNKNOWN;
		this_device->offload_config = 0;
		hpsa_turn_off_ioaccel_क्रम_device(this_device);
		this_device->hba_ioaccel_enabled = 0;
		this_device->volume_offline = 0;
		this_device->queue_depth = h->nr_cmds;
	पूर्ण

	अगर (this_device->बाह्यal)
		this_device->queue_depth = EXTERNAL_QD;

	अगर (is_OBDR_device) अणु
		/* See अगर this is a One-Button-Disaster-Recovery device
		 * by looking क्रम "$DR-10" at offset 43 in inquiry data.
		 */
		obdr_sig = &inq_buff[OBDR_SIG_OFFSET];
		*is_OBDR_device = (this_device->devtype == TYPE_ROM &&
					म_भेदन(obdr_sig, OBDR_TAPE_SIG,
						OBDR_SIG_LEN) == 0);
	पूर्ण
	kमुक्त(inq_buff);
	वापस 0;

bail_out:
	kमुक्त(inq_buff);
	वापस rc;
पूर्ण

/*
 * Helper function to assign bus, target, lun mapping of devices.
 * Logical drive target and lun are asचिन्हित at this समय, but
 * physical device lun and target assignment are deferred (asचिन्हित
 * in hpsa_find_target_lun, called by hpsa_scsi_add_entry.)
*/
अटल व्योम figure_bus_target_lun(काष्ठा ctlr_info *h,
	u8 *lunaddrbytes, काष्ठा hpsa_scsi_dev_t *device)
अणु
	u32 lunid = get_unaligned_le32(lunaddrbytes);

	अगर (!is_logical_dev_addr_mode(lunaddrbytes)) अणु
		/* physical device, target and lun filled in later */
		अगर (is_hba_lunid(lunaddrbytes)) अणु
			पूर्णांक bus = HPSA_HBA_BUS;

			अगर (!device->rev)
				bus = HPSA_LEGACY_HBA_BUS;
			hpsa_set_bus_target_lun(device,
					bus, 0, lunid & 0x3fff);
		पूर्ण अन्यथा
			/* defer target, lun assignment क्रम physical devices */
			hpsa_set_bus_target_lun(device,
					HPSA_PHYSICAL_DEVICE_BUS, -1, -1);
		वापस;
	पूर्ण
	/* It's a logical device */
	अगर (device->बाह्यal) अणु
		hpsa_set_bus_target_lun(device,
			HPSA_EXTERNAL_RAID_VOLUME_BUS, (lunid >> 16) & 0x3fff,
			lunid & 0x00ff);
		वापस;
	पूर्ण
	hpsa_set_bus_target_lun(device, HPSA_RAID_VOLUME_BUS,
				0, lunid & 0x3fff);
पूर्ण

अटल पूर्णांक  figure_बाह्यal_status(काष्ठा ctlr_info *h, पूर्णांक raid_ctlr_position,
	पूर्णांक i, पूर्णांक nphysicals, पूर्णांक nlocal_logicals)
अणु
	/* In report logicals, local logicals are listed first,
	* then any बाह्यals.
	*/
	पूर्णांक logicals_start = nphysicals + (raid_ctlr_position == 0);

	अगर (i == raid_ctlr_position)
		वापस 0;

	अगर (i < logicals_start)
		वापस 0;

	/* i is in logicals range, but still within local logicals */
	अगर ((i - nphysicals - (raid_ctlr_position == 0)) < nlocal_logicals)
		वापस 0;

	वापस 1; /* it's an बाह्यal lun */
पूर्ण

/*
 * Do CISS_REPORT_PHYS and CISS_REPORT_LOG.  Data is वापसed in physdev,
 * logdev.  The number of luns in physdev and logdev are वापसed in
 * *nphysicals and *nlogicals, respectively.
 * Returns 0 on success, -1 otherwise.
 */
अटल पूर्णांक hpsa_gather_lun_info(काष्ठा ctlr_info *h,
	काष्ठा ReportExtendedLUNdata *physdev, u32 *nphysicals,
	काष्ठा ReportLUNdata *logdev, u32 *nlogicals)
अणु
	अगर (hpsa_scsi_करो_report_phys_luns(h, physdev, माप(*physdev))) अणु
		dev_err(&h->pdev->dev, "report physical LUNs failed.\n");
		वापस -1;
	पूर्ण
	*nphysicals = be32_to_cpu(*((__be32 *)physdev->LUNListLength)) / 24;
	अगर (*nphysicals > HPSA_MAX_PHYS_LUN) अणु
		dev_warn(&h->pdev->dev, "maximum physical LUNs (%d) exceeded. %d LUNs ignored.\n",
			HPSA_MAX_PHYS_LUN, *nphysicals - HPSA_MAX_PHYS_LUN);
		*nphysicals = HPSA_MAX_PHYS_LUN;
	पूर्ण
	अगर (hpsa_scsi_करो_report_log_luns(h, logdev, माप(*logdev))) अणु
		dev_err(&h->pdev->dev, "report logical LUNs failed.\n");
		वापस -1;
	पूर्ण
	*nlogicals = be32_to_cpu(*((__be32 *) logdev->LUNListLength)) / 8;
	/* Reject Logicals in excess of our max capability. */
	अगर (*nlogicals > HPSA_MAX_LUN) अणु
		dev_warn(&h->pdev->dev,
			"maximum logical LUNs (%d) exceeded.  "
			"%d LUNs ignored.\n", HPSA_MAX_LUN,
			*nlogicals - HPSA_MAX_LUN);
		*nlogicals = HPSA_MAX_LUN;
	पूर्ण
	अगर (*nlogicals + *nphysicals > HPSA_MAX_PHYS_LUN) अणु
		dev_warn(&h->pdev->dev,
			"maximum logical + physical LUNs (%d) exceeded. "
			"%d LUNs ignored.\n", HPSA_MAX_PHYS_LUN,
			*nphysicals + *nlogicals - HPSA_MAX_PHYS_LUN);
		*nlogicals = HPSA_MAX_PHYS_LUN - *nphysicals;
	पूर्ण
	वापस 0;
पूर्ण

अटल u8 *figure_lunaddrbytes(काष्ठा ctlr_info *h, पूर्णांक raid_ctlr_position,
	पूर्णांक i, पूर्णांक nphysicals, पूर्णांक nlogicals,
	काष्ठा ReportExtendedLUNdata *physdev_list,
	काष्ठा ReportLUNdata *logdev_list)
अणु
	/* Helper function, figure out where the LUN ID info is coming from
	 * given index i, lists of physical and logical devices, where in
	 * the list the raid controller is supposed to appear (first or last)
	 */

	पूर्णांक logicals_start = nphysicals + (raid_ctlr_position == 0);
	पूर्णांक last_device = nphysicals + nlogicals + (raid_ctlr_position == 0);

	अगर (i == raid_ctlr_position)
		वापस RAID_CTLR_LUNID;

	अगर (i < logicals_start)
		वापस &physdev_list->LUN[i -
				(raid_ctlr_position == 0)].lunid[0];

	अगर (i < last_device)
		वापस &logdev_list->LUN[i - nphysicals -
			(raid_ctlr_position == 0)][0];
	BUG();
	वापस शून्य;
पूर्ण

/* get physical drive ioaccel handle and queue depth */
अटल व्योम hpsa_get_ioaccel_drive_info(काष्ठा ctlr_info *h,
		काष्ठा hpsa_scsi_dev_t *dev,
		काष्ठा ReportExtendedLUNdata *rlep, पूर्णांक rle_index,
		काष्ठा bmic_identअगरy_physical_device *id_phys)
अणु
	पूर्णांक rc;
	काष्ठा ext_report_lun_entry *rle;

	अगर (rle_index < 0 || rle_index >= HPSA_MAX_PHYS_LUN)
		वापस;

	rle = &rlep->LUN[rle_index];

	dev->ioaccel_handle = rle->ioaccel_handle;
	अगर ((rle->device_flags & 0x08) && dev->ioaccel_handle)
		dev->hba_ioaccel_enabled = 1;
	स_रखो(id_phys, 0, माप(*id_phys));
	rc = hpsa_bmic_id_physical_device(h, &rle->lunid[0],
			GET_BMIC_DRIVE_NUMBER(&rle->lunid[0]), id_phys,
			माप(*id_phys));
	अगर (!rc)
		/* Reserve space क्रम FW operations */
#घोषणा DRIVE_CMDS_RESERVED_FOR_FW 2
#घोषणा DRIVE_QUEUE_DEPTH 7
		dev->queue_depth =
			le16_to_cpu(id_phys->current_queue_depth_limit) -
				DRIVE_CMDS_RESERVED_FOR_FW;
	अन्यथा
		dev->queue_depth = DRIVE_QUEUE_DEPTH; /* conservative */
पूर्ण

अटल व्योम hpsa_get_path_info(काष्ठा hpsa_scsi_dev_t *this_device,
	काष्ठा ReportExtendedLUNdata *rlep, पूर्णांक rle_index,
	काष्ठा bmic_identअगरy_physical_device *id_phys)
अणु
	काष्ठा ext_report_lun_entry *rle;

	अगर (rle_index < 0 || rle_index >= HPSA_MAX_PHYS_LUN)
		वापस;

	rle = &rlep->LUN[rle_index];

	अगर ((rle->device_flags & 0x08) && this_device->ioaccel_handle)
		this_device->hba_ioaccel_enabled = 1;

	स_नकल(&this_device->active_path_index,
		&id_phys->active_path_number,
		माप(this_device->active_path_index));
	स_नकल(&this_device->path_map,
		&id_phys->redundant_path_present_map,
		माप(this_device->path_map));
	स_नकल(&this_device->box,
		&id_phys->alternate_paths_phys_box_on_port,
		माप(this_device->box));
	स_नकल(&this_device->phys_connector,
		&id_phys->alternate_paths_phys_connector,
		माप(this_device->phys_connector));
	स_नकल(&this_device->bay,
		&id_phys->phys_bay_in_box,
		माप(this_device->bay));
पूर्ण

/* get number of local logical disks. */
अटल पूर्णांक hpsa_set_local_logical_count(काष्ठा ctlr_info *h,
	काष्ठा bmic_identअगरy_controller *id_ctlr,
	u32 *nlocals)
अणु
	पूर्णांक rc;

	अगर (!id_ctlr) अणु
		dev_warn(&h->pdev->dev, "%s: id_ctlr buffer is NULL.\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(id_ctlr, 0, माप(*id_ctlr));
	rc = hpsa_bmic_id_controller(h, id_ctlr, माप(*id_ctlr));
	अगर (!rc)
		अगर (id_ctlr->configured_logical_drive_count < 255)
			*nlocals = id_ctlr->configured_logical_drive_count;
		अन्यथा
			*nlocals = le16_to_cpu(
					id_ctlr->extended_logical_unit_count);
	अन्यथा
		*nlocals = -1;
	वापस rc;
पूर्ण

अटल bool hpsa_is_disk_spare(काष्ठा ctlr_info *h, u8 *lunaddrbytes)
अणु
	काष्ठा bmic_identअगरy_physical_device *id_phys;
	bool is_spare = false;
	पूर्णांक rc;

	id_phys = kzalloc(माप(*id_phys), GFP_KERNEL);
	अगर (!id_phys)
		वापस false;

	rc = hpsa_bmic_id_physical_device(h,
					lunaddrbytes,
					GET_BMIC_DRIVE_NUMBER(lunaddrbytes),
					id_phys, माप(*id_phys));
	अगर (rc == 0)
		is_spare = (id_phys->more_flags >> 6) & 0x01;

	kमुक्त(id_phys);
	वापस is_spare;
पूर्ण

#घोषणा RPL_DEV_FLAG_NON_DISK                           0x1
#घोषणा RPL_DEV_FLAG_UNCONFIG_DISK_REPORTING_SUPPORTED  0x2
#घोषणा RPL_DEV_FLAG_UNCONFIG_DISK                      0x4

#घोषणा BMIC_DEVICE_TYPE_ENCLOSURE  6

अटल bool hpsa_skip_device(काष्ठा ctlr_info *h, u8 *lunaddrbytes,
				काष्ठा ext_report_lun_entry *rle)
अणु
	u8 device_flags;
	u8 device_type;

	अगर (!MASKED_DEVICE(lunaddrbytes))
		वापस false;

	device_flags = rle->device_flags;
	device_type = rle->device_type;

	अगर (device_flags & RPL_DEV_FLAG_NON_DISK) अणु
		अगर (device_type == BMIC_DEVICE_TYPE_ENCLOSURE)
			वापस false;
		वापस true;
	पूर्ण

	अगर (!(device_flags & RPL_DEV_FLAG_UNCONFIG_DISK_REPORTING_SUPPORTED))
		वापस false;

	अगर (device_flags & RPL_DEV_FLAG_UNCONFIG_DISK)
		वापस false;

	/*
	 * Spares may be spun करोwn, we करो not want to
	 * करो an Inquiry to a RAID set spare drive as
	 * that would have them spun up, that is a
	 * perक्रमmance hit because I/O to the RAID device
	 * stops जबतक the spin up occurs which can take
	 * over 50 seconds.
	 */
	अगर (hpsa_is_disk_spare(h, lunaddrbytes))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम hpsa_update_scsi_devices(काष्ठा ctlr_info *h)
अणु
	/* the idea here is we could get notअगरied
	 * that some devices have changed, so we करो a report
	 * physical luns and report logical luns cmd, and adjust
	 * our list of devices accordingly.
	 *
	 * The scsi3addr's of devices won't change so दीर्घ as the
	 * adapter is not reset.  That means we can rescan and
	 * tell which devices we alपढ़ोy know about, vs. new
	 * devices, vs.  disappearing devices.
	 */
	काष्ठा ReportExtendedLUNdata *physdev_list = शून्य;
	काष्ठा ReportLUNdata *logdev_list = शून्य;
	काष्ठा bmic_identअगरy_physical_device *id_phys = शून्य;
	काष्ठा bmic_identअगरy_controller *id_ctlr = शून्य;
	u32 nphysicals = 0;
	u32 nlogicals = 0;
	u32 nlocal_logicals = 0;
	u32 ndev_allocated = 0;
	काष्ठा hpsa_scsi_dev_t **currentsd, *this_device, *पंचांगpdevice;
	पूर्णांक ncurrent = 0;
	पूर्णांक i, ndevs_to_allocate;
	पूर्णांक raid_ctlr_position;
	bool physical_device;
	DECLARE_BITMAP(lunzerobits, MAX_EXT_TARGETS);

	currentsd = kसुस्मृति(HPSA_MAX_DEVICES, माप(*currentsd), GFP_KERNEL);
	physdev_list = kzalloc(माप(*physdev_list), GFP_KERNEL);
	logdev_list = kzalloc(माप(*logdev_list), GFP_KERNEL);
	पंचांगpdevice = kzalloc(माप(*पंचांगpdevice), GFP_KERNEL);
	id_phys = kzalloc(माप(*id_phys), GFP_KERNEL);
	id_ctlr = kzalloc(माप(*id_ctlr), GFP_KERNEL);

	अगर (!currentsd || !physdev_list || !logdev_list ||
		!पंचांगpdevice || !id_phys || !id_ctlr) अणु
		dev_err(&h->pdev->dev, "out of memory\n");
		जाओ out;
	पूर्ण
	स_रखो(lunzerobits, 0, माप(lunzerobits));

	h->drv_req_rescan = 0; /* cancel scheduled rescan - we're करोing it. */

	अगर (hpsa_gather_lun_info(h, physdev_list, &nphysicals,
			logdev_list, &nlogicals)) अणु
		h->drv_req_rescan = 1;
		जाओ out;
	पूर्ण

	/* Set number of local logicals (non PTRAID) */
	अगर (hpsa_set_local_logical_count(h, id_ctlr, &nlocal_logicals)) अणु
		dev_warn(&h->pdev->dev,
			"%s: Can't determine number of local logical devices.\n",
			__func__);
	पूर्ण

	/* We might see up to the maximum number of logical and physical disks
	 * plus बाह्यal target devices, and a device क्रम the local RAID
	 * controller.
	 */
	ndevs_to_allocate = nphysicals + nlogicals + MAX_EXT_TARGETS + 1;

	hpsa_ext_ctrl_present(h, physdev_list);

	/* Allocate the per device काष्ठाures */
	क्रम (i = 0; i < ndevs_to_allocate; i++) अणु
		अगर (i >= HPSA_MAX_DEVICES) अणु
			dev_warn(&h->pdev->dev, "maximum devices (%d) exceeded."
				"  %d devices ignored.\n", HPSA_MAX_DEVICES,
				ndevs_to_allocate - HPSA_MAX_DEVICES);
			अवरोध;
		पूर्ण

		currentsd[i] = kzalloc(माप(*currentsd[i]), GFP_KERNEL);
		अगर (!currentsd[i]) अणु
			h->drv_req_rescan = 1;
			जाओ out;
		पूर्ण
		ndev_allocated++;
	पूर्ण

	अगर (is_scsi_rev_5(h))
		raid_ctlr_position = 0;
	अन्यथा
		raid_ctlr_position = nphysicals + nlogicals;

	/* adjust our table of devices */
	क्रम (i = 0; i < nphysicals + nlogicals + 1; i++) अणु
		u8 *lunaddrbytes, is_OBDR = 0;
		पूर्णांक rc = 0;
		पूर्णांक phys_dev_index = i - (raid_ctlr_position == 0);
		bool skip_device = false;

		स_रखो(पंचांगpdevice, 0, माप(*पंचांगpdevice));

		physical_device = i < nphysicals + (raid_ctlr_position == 0);

		/* Figure out where the LUN ID info is coming from */
		lunaddrbytes = figure_lunaddrbytes(h, raid_ctlr_position,
			i, nphysicals, nlogicals, physdev_list, logdev_list);

		/* Determine अगर this is a lun from an बाह्यal target array */
		पंचांगpdevice->बाह्यal =
			figure_बाह्यal_status(h, raid_ctlr_position, i,
						nphysicals, nlocal_logicals);

		/*
		 * Skip over some devices such as a spare.
		 */
		अगर (phys_dev_index >= 0 && !पंचांगpdevice->बाह्यal &&
			physical_device) अणु
			skip_device = hpsa_skip_device(h, lunaddrbytes,
					&physdev_list->LUN[phys_dev_index]);
			अगर (skip_device)
				जारी;
		पूर्ण

		/* Get device type, venकरोr, model, device id, raid_map */
		rc = hpsa_update_device_info(h, lunaddrbytes, पंचांगpdevice,
							&is_OBDR);
		अगर (rc == -ENOMEM) अणु
			dev_warn(&h->pdev->dev,
				"Out of memory, rescan deferred.\n");
			h->drv_req_rescan = 1;
			जाओ out;
		पूर्ण
		अगर (rc) अणु
			h->drv_req_rescan = 1;
			जारी;
		पूर्ण

		figure_bus_target_lun(h, lunaddrbytes, पंचांगpdevice);
		this_device = currentsd[ncurrent];

		*this_device = *पंचांगpdevice;
		this_device->physical_device = physical_device;

		/*
		 * Expose all devices except क्रम physical devices that
		 * are masked.
		 */
		अगर (MASKED_DEVICE(lunaddrbytes) && this_device->physical_device)
			this_device->expose_device = 0;
		अन्यथा
			this_device->expose_device = 1;


		/*
		 * Get the SAS address क्रम physical devices that are exposed.
		 */
		अगर (this_device->physical_device && this_device->expose_device)
			hpsa_get_sas_address(h, lunaddrbytes, this_device);

		चयन (this_device->devtype) अणु
		हाल TYPE_ROM:
			/* We करोn't *really* support actual CD-ROM devices,
			 * just "One Button Disaster Recovery" tape drive
			 * which temporarily pretends to be a CD-ROM drive.
			 * So we check that the device is really an OBDR tape
			 * device by checking क्रम "$DR-10" in bytes 43-48 of
			 * the inquiry data.
			 */
			अगर (is_OBDR)
				ncurrent++;
			अवरोध;
		हाल TYPE_DISK:
		हाल TYPE_ZBC:
			अगर (this_device->physical_device) अणु
				/* The disk is in HBA mode. */
				/* Never use RAID mapper in HBA mode. */
				this_device->offload_enabled = 0;
				hpsa_get_ioaccel_drive_info(h, this_device,
					physdev_list, phys_dev_index, id_phys);
				hpsa_get_path_info(this_device,
					physdev_list, phys_dev_index, id_phys);
			पूर्ण
			ncurrent++;
			अवरोध;
		हाल TYPE_TAPE:
		हाल TYPE_MEDIUM_CHANGER:
			ncurrent++;
			अवरोध;
		हाल TYPE_ENCLOSURE:
			अगर (!this_device->बाह्यal)
				hpsa_get_enclosure_info(h, lunaddrbytes,
						physdev_list, phys_dev_index,
						this_device);
			ncurrent++;
			अवरोध;
		हाल TYPE_RAID:
			/* Only present the Smartarray HBA as a RAID controller.
			 * If it's a RAID controller other than the HBA itself
			 * (an बाह्यal RAID controller, MSA500 or similar)
			 * करोn't present it.
			 */
			अगर (!is_hba_lunid(lunaddrbytes))
				अवरोध;
			ncurrent++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (ncurrent >= HPSA_MAX_DEVICES)
			अवरोध;
	पूर्ण

	अगर (h->sas_host == शून्य) अणु
		पूर्णांक rc = 0;

		rc = hpsa_add_sas_host(h);
		अगर (rc) अणु
			dev_warn(&h->pdev->dev,
				"Could not add sas host %d\n", rc);
			जाओ out;
		पूर्ण
	पूर्ण

	adjust_hpsa_scsi_table(h, currentsd, ncurrent);
out:
	kमुक्त(पंचांगpdevice);
	क्रम (i = 0; i < ndev_allocated; i++)
		kमुक्त(currentsd[i]);
	kमुक्त(currentsd);
	kमुक्त(physdev_list);
	kमुक्त(logdev_list);
	kमुक्त(id_ctlr);
	kमुक्त(id_phys);
पूर्ण

अटल व्योम hpsa_set_sg_descriptor(काष्ठा SGDescriptor *desc,
				   काष्ठा scatterlist *sg)
अणु
	u64 addr64 = (u64) sg_dma_address(sg);
	अचिन्हित पूर्णांक len = sg_dma_len(sg);

	desc->Addr = cpu_to_le64(addr64);
	desc->Len = cpu_to_le32(len);
	desc->Ext = 0;
पूर्ण

/*
 * hpsa_scatter_gather takes a काष्ठा scsi_cmnd, (cmd), and करोes the pci
 * dma mapping  and fills in the scatter gather entries of the
 * hpsa command, cp.
 */
अटल पूर्णांक hpsa_scatter_gather(काष्ठा ctlr_info *h,
		काष्ठा CommandList *cp,
		काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक use_sg, i, sg_limit, chained;
	काष्ठा SGDescriptor *curr_sg;

	BUG_ON(scsi_sg_count(cmd) > h->maxsgentries);

	use_sg = scsi_dma_map(cmd);
	अगर (use_sg < 0)
		वापस use_sg;

	अगर (!use_sg)
		जाओ sglist_finished;

	/*
	 * If the number of entries is greater than the max क्रम a single list,
	 * then we have a chained list; we will set up all but one entry in the
	 * first list (the last entry is saved क्रम link inक्रमmation);
	 * otherwise, we करोn't have a chained list and we'll set up at each of
	 * the entries in the one list.
	 */
	curr_sg = cp->SG;
	chained = use_sg > h->max_cmd_sg_entries;
	sg_limit = chained ? h->max_cmd_sg_entries - 1 : use_sg;
	scsi_क्रम_each_sg(cmd, sg, sg_limit, i) अणु
		hpsa_set_sg_descriptor(curr_sg, sg);
		curr_sg++;
	पूर्ण

	अगर (chained) अणु
		/*
		 * Continue with the chained list.  Set curr_sg to the chained
		 * list.  Modअगरy the limit to the total count less the entries
		 * we've alपढ़ोy set up.  Resume the scan at the list entry
		 * where the previous loop left off.
		 */
		curr_sg = h->cmd_sg_list[cp->cmdindex];
		sg_limit = use_sg - sg_limit;
		क्रम_each_sg(sg, sg, sg_limit, i) अणु
			hpsa_set_sg_descriptor(curr_sg, sg);
			curr_sg++;
		पूर्ण
	पूर्ण

	/* Back the poपूर्णांकer up to the last entry and mark it as "last". */
	(curr_sg - 1)->Ext = cpu_to_le32(HPSA_SG_LAST);

	अगर (use_sg + chained > h->maxSG)
		h->maxSG = use_sg + chained;

	अगर (chained) अणु
		cp->Header.SGList = h->max_cmd_sg_entries;
		cp->Header.SGTotal = cpu_to_le16(use_sg + 1);
		अगर (hpsa_map_sg_chain_block(h, cp)) अणु
			scsi_dma_unmap(cmd);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण

sglist_finished:

	cp->Header.SGList = (u8) use_sg;   /* no. SGs contig in this cmd */
	cp->Header.SGTotal = cpu_to_le16(use_sg); /* total sgs in cmd list */
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम warn_zero_length_transfer(काष्ठा ctlr_info *h,
						u8 *cdb, पूर्णांक cdb_len,
						स्थिर अक्षर *func)
अणु
	dev_warn(&h->pdev->dev,
		 "%s: Blocking zero-length request: CDB:%*phN\n",
		 func, cdb_len, cdb);
पूर्ण

#घोषणा IO_ACCEL_INELIGIBLE 1
/* zero-length transfers trigger hardware errors. */
अटल bool is_zero_length_transfer(u8 *cdb)
अणु
	u32 block_cnt;

	/* Block zero-length transfer sizes on certain commands. */
	चयन (cdb[0]) अणु
	हाल READ_10:
	हाल WRITE_10:
	हाल VERIFY:		/* 0x2F */
	हाल WRITE_VERIFY:	/* 0x2E */
		block_cnt = get_unaligned_be16(&cdb[7]);
		अवरोध;
	हाल READ_12:
	हाल WRITE_12:
	हाल VERIFY_12: /* 0xAF */
	हाल WRITE_VERIFY_12:	/* 0xAE */
		block_cnt = get_unaligned_be32(&cdb[6]);
		अवरोध;
	हाल READ_16:
	हाल WRITE_16:
	हाल VERIFY_16:		/* 0x8F */
		block_cnt = get_unaligned_be32(&cdb[10]);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस block_cnt == 0;
पूर्ण

अटल पूर्णांक fixup_ioaccel_cdb(u8 *cdb, पूर्णांक *cdb_len)
अणु
	पूर्णांक is_ग_लिखो = 0;
	u32 block;
	u32 block_cnt;

	/* Perक्रमm some CDB fixups अगर needed using 10 byte पढ़ोs/ग_लिखोs only */
	चयन (cdb[0]) अणु
	हाल WRITE_6:
	हाल WRITE_12:
		is_ग_लिखो = 1;
		fallthrough;
	हाल READ_6:
	हाल READ_12:
		अगर (*cdb_len == 6) अणु
			block = (((cdb[1] & 0x1F) << 16) |
				(cdb[2] << 8) |
				cdb[3]);
			block_cnt = cdb[4];
			अगर (block_cnt == 0)
				block_cnt = 256;
		पूर्ण अन्यथा अणु
			BUG_ON(*cdb_len != 12);
			block = get_unaligned_be32(&cdb[2]);
			block_cnt = get_unaligned_be32(&cdb[6]);
		पूर्ण
		अगर (block_cnt > 0xffff)
			वापस IO_ACCEL_INELIGIBLE;

		cdb[0] = is_ग_लिखो ? WRITE_10 : READ_10;
		cdb[1] = 0;
		cdb[2] = (u8) (block >> 24);
		cdb[3] = (u8) (block >> 16);
		cdb[4] = (u8) (block >> 8);
		cdb[5] = (u8) (block);
		cdb[6] = 0;
		cdb[7] = (u8) (block_cnt >> 8);
		cdb[8] = (u8) (block_cnt);
		cdb[9] = 0;
		*cdb_len = 10;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_scsi_ioaccel1_queue_command(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, u32 ioaccel_handle, u8 *cdb, पूर्णांक cdb_len,
	u8 *scsi3addr, काष्ठा hpsa_scsi_dev_t *phys_disk)
अणु
	काष्ठा scsi_cmnd *cmd = c->scsi_cmd;
	काष्ठा io_accel1_cmd *cp = &h->ioaccel_cmd_pool[c->cmdindex];
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक total_len = 0;
	काष्ठा scatterlist *sg;
	u64 addr64;
	पूर्णांक use_sg, i;
	काष्ठा SGDescriptor *curr_sg;
	u32 control = IOACCEL1_CONTROL_SIMPLEQUEUE;

	/* TODO: implement chaining support */
	अगर (scsi_sg_count(cmd) > h->ioaccel_maxsg) अणु
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस IO_ACCEL_INELIGIBLE;
	पूर्ण

	BUG_ON(cmd->cmd_len > IOACCEL1_IOFLAGS_CDBLEN_MAX);

	अगर (is_zero_length_transfer(cdb)) अणु
		warn_zero_length_transfer(h, cdb, cdb_len, __func__);
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस IO_ACCEL_INELIGIBLE;
	पूर्ण

	अगर (fixup_ioaccel_cdb(cdb, &cdb_len)) अणु
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस IO_ACCEL_INELIGIBLE;
	पूर्ण

	c->cmd_type = CMD_IOACCEL1;

	/* Adjust the DMA address to poपूर्णांक to the accelerated command buffer */
	c->busaddr = (u32) h->ioaccel_cmd_pool_dhandle +
				(c->cmdindex * माप(*cp));
	BUG_ON(c->busaddr & 0x0000007F);

	use_sg = scsi_dma_map(cmd);
	अगर (use_sg < 0) अणु
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस use_sg;
	पूर्ण

	अगर (use_sg) अणु
		curr_sg = cp->SG;
		scsi_क्रम_each_sg(cmd, sg, use_sg, i) अणु
			addr64 = (u64) sg_dma_address(sg);
			len  = sg_dma_len(sg);
			total_len += len;
			curr_sg->Addr = cpu_to_le64(addr64);
			curr_sg->Len = cpu_to_le32(len);
			curr_sg->Ext = cpu_to_le32(0);
			curr_sg++;
		पूर्ण
		(--curr_sg)->Ext = cpu_to_le32(HPSA_SG_LAST);

		चयन (cmd->sc_data_direction) अणु
		हाल DMA_TO_DEVICE:
			control |= IOACCEL1_CONTROL_DATA_OUT;
			अवरोध;
		हाल DMA_FROM_DEVICE:
			control |= IOACCEL1_CONTROL_DATA_IN;
			अवरोध;
		हाल DMA_NONE:
			control |= IOACCEL1_CONTROL_NODATAXFER;
			अवरोध;
		शेष:
			dev_err(&h->pdev->dev, "unknown data direction: %d\n",
			cmd->sc_data_direction);
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		control |= IOACCEL1_CONTROL_NODATAXFER;
	पूर्ण

	c->Header.SGList = use_sg;
	/* Fill out the command काष्ठाure to submit */
	cp->dev_handle = cpu_to_le16(ioaccel_handle & 0xFFFF);
	cp->transfer_len = cpu_to_le32(total_len);
	cp->io_flags = cpu_to_le16(IOACCEL1_IOFLAGS_IO_REQ |
			(cdb_len & IOACCEL1_IOFLAGS_CDBLEN_MASK));
	cp->control = cpu_to_le32(control);
	स_नकल(cp->CDB, cdb, cdb_len);
	स_नकल(cp->CISS_LUN, scsi3addr, 8);
	/* Tag was alपढ़ोy set at init समय. */
	enqueue_cmd_and_start_io(h, c);
	वापस 0;
पूर्ण

/*
 * Queue a command directly to a device behind the controller using the
 * I/O accelerator path.
 */
अटल पूर्णांक hpsa_scsi_ioaccel_direct_map(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	काष्ठा scsi_cmnd *cmd = c->scsi_cmd;
	काष्ठा hpsa_scsi_dev_t *dev = cmd->device->hostdata;

	अगर (!dev)
		वापस -1;

	c->phys_disk = dev;

	अगर (dev->in_reset)
		वापस -1;

	वापस hpsa_scsi_ioaccel_queue_command(h, c, dev->ioaccel_handle,
		cmd->cmnd, cmd->cmd_len, dev->scsi3addr, dev);
पूर्ण

/*
 * Set encryption parameters क्रम the ioaccel2 request
 */
अटल व्योम set_encrypt_ioaccel2(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, काष्ठा io_accel2_cmd *cp)
अणु
	काष्ठा scsi_cmnd *cmd = c->scsi_cmd;
	काष्ठा hpsa_scsi_dev_t *dev = cmd->device->hostdata;
	काष्ठा raid_map_data *map = &dev->raid_map;
	u64 first_block;

	/* Are we करोing encryption on this device */
	अगर (!(le16_to_cpu(map->flags) & RAID_MAP_FLAG_ENCRYPT_ON))
		वापस;
	/* Set the data encryption key index. */
	cp->dekindex = map->dekindex;

	/* Set the encryption enable flag, encoded पूर्णांकo direction field. */
	cp->direction |= IOACCEL2_सूचीECTION_ENCRYPT_MASK;

	/* Set encryption tweak values based on logical block address
	 * If block size is 512, tweak value is LBA.
	 * For other block sizes, tweak is (LBA * block size)/ 512)
	 */
	चयन (cmd->cmnd[0]) अणु
	/* Required? 6-byte cdbs eliminated by fixup_ioaccel_cdb */
	हाल READ_6:
	हाल WRITE_6:
		first_block = (((cmd->cmnd[1] & 0x1F) << 16) |
				(cmd->cmnd[2] << 8) |
				cmd->cmnd[3]);
		अवरोध;
	हाल WRITE_10:
	हाल READ_10:
	/* Required? 12-byte cdbs eliminated by fixup_ioaccel_cdb */
	हाल WRITE_12:
	हाल READ_12:
		first_block = get_unaligned_be32(&cmd->cmnd[2]);
		अवरोध;
	हाल WRITE_16:
	हाल READ_16:
		first_block = get_unaligned_be64(&cmd->cmnd[2]);
		अवरोध;
	शेष:
		dev_err(&h->pdev->dev,
			"ERROR: %s: size (0x%x) not supported for encryption\n",
			__func__, cmd->cmnd[0]);
		BUG();
		अवरोध;
	पूर्ण

	अगर (le32_to_cpu(map->volume_blk_size) != 512)
		first_block = first_block *
				le32_to_cpu(map->volume_blk_size)/512;

	cp->tweak_lower = cpu_to_le32(first_block);
	cp->tweak_upper = cpu_to_le32(first_block >> 32);
पूर्ण

अटल पूर्णांक hpsa_scsi_ioaccel2_queue_command(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, u32 ioaccel_handle, u8 *cdb, पूर्णांक cdb_len,
	u8 *scsi3addr, काष्ठा hpsa_scsi_dev_t *phys_disk)
अणु
	काष्ठा scsi_cmnd *cmd = c->scsi_cmd;
	काष्ठा io_accel2_cmd *cp = &h->ioaccel2_cmd_pool[c->cmdindex];
	काष्ठा ioaccel2_sg_element *curr_sg;
	पूर्णांक use_sg, i;
	काष्ठा scatterlist *sg;
	u64 addr64;
	u32 len;
	u32 total_len = 0;

	अगर (!cmd->device)
		वापस -1;

	अगर (!cmd->device->hostdata)
		वापस -1;

	BUG_ON(scsi_sg_count(cmd) > h->maxsgentries);

	अगर (is_zero_length_transfer(cdb)) अणु
		warn_zero_length_transfer(h, cdb, cdb_len, __func__);
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस IO_ACCEL_INELIGIBLE;
	पूर्ण

	अगर (fixup_ioaccel_cdb(cdb, &cdb_len)) अणु
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस IO_ACCEL_INELIGIBLE;
	पूर्ण

	c->cmd_type = CMD_IOACCEL2;
	/* Adjust the DMA address to poपूर्णांक to the accelerated command buffer */
	c->busaddr = (u32) h->ioaccel2_cmd_pool_dhandle +
				(c->cmdindex * माप(*cp));
	BUG_ON(c->busaddr & 0x0000007F);

	स_रखो(cp, 0, माप(*cp));
	cp->IU_type = IOACCEL2_IU_TYPE;

	use_sg = scsi_dma_map(cmd);
	अगर (use_sg < 0) अणु
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस use_sg;
	पूर्ण

	अगर (use_sg) अणु
		curr_sg = cp->sg;
		अगर (use_sg > h->ioaccel_maxsg) अणु
			addr64 = le64_to_cpu(
				h->ioaccel2_cmd_sg_list[c->cmdindex]->address);
			curr_sg->address = cpu_to_le64(addr64);
			curr_sg->length = 0;
			curr_sg->reserved[0] = 0;
			curr_sg->reserved[1] = 0;
			curr_sg->reserved[2] = 0;
			curr_sg->chain_indicator = IOACCEL2_CHAIN;

			curr_sg = h->ioaccel2_cmd_sg_list[c->cmdindex];
		पूर्ण
		scsi_क्रम_each_sg(cmd, sg, use_sg, i) अणु
			addr64 = (u64) sg_dma_address(sg);
			len  = sg_dma_len(sg);
			total_len += len;
			curr_sg->address = cpu_to_le64(addr64);
			curr_sg->length = cpu_to_le32(len);
			curr_sg->reserved[0] = 0;
			curr_sg->reserved[1] = 0;
			curr_sg->reserved[2] = 0;
			curr_sg->chain_indicator = 0;
			curr_sg++;
		पूर्ण

		/*
		 * Set the last s/g element bit
		 */
		(curr_sg - 1)->chain_indicator = IOACCEL2_LAST_SG;

		चयन (cmd->sc_data_direction) अणु
		हाल DMA_TO_DEVICE:
			cp->direction &= ~IOACCEL2_सूचीECTION_MASK;
			cp->direction |= IOACCEL2_सूची_DATA_OUT;
			अवरोध;
		हाल DMA_FROM_DEVICE:
			cp->direction &= ~IOACCEL2_सूचीECTION_MASK;
			cp->direction |= IOACCEL2_सूची_DATA_IN;
			अवरोध;
		हाल DMA_NONE:
			cp->direction &= ~IOACCEL2_सूचीECTION_MASK;
			cp->direction |= IOACCEL2_सूची_NO_DATA;
			अवरोध;
		शेष:
			dev_err(&h->pdev->dev, "unknown data direction: %d\n",
				cmd->sc_data_direction);
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		cp->direction &= ~IOACCEL2_सूचीECTION_MASK;
		cp->direction |= IOACCEL2_सूची_NO_DATA;
	पूर्ण

	/* Set encryption parameters, अगर necessary */
	set_encrypt_ioaccel2(h, c, cp);

	cp->scsi_nexus = cpu_to_le32(ioaccel_handle);
	cp->Tag = cpu_to_le32(c->cmdindex << सूचीECT_LOOKUP_SHIFT);
	स_नकल(cp->cdb, cdb, माप(cp->cdb));

	cp->data_len = cpu_to_le32(total_len);
	cp->err_ptr = cpu_to_le64(c->busaddr +
			दुरत्व(काष्ठा io_accel2_cmd, error_data));
	cp->err_len = cpu_to_le32(माप(cp->error_data));

	/* fill in sg elements */
	अगर (use_sg > h->ioaccel_maxsg) अणु
		cp->sg_count = 1;
		cp->sg[0].length = cpu_to_le32(use_sg * माप(cp->sg[0]));
		अगर (hpsa_map_ioaccel2_sg_chain_block(h, cp, c)) अणु
			atomic_dec(&phys_disk->ioaccel_cmds_out);
			scsi_dma_unmap(cmd);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा
		cp->sg_count = (u8) use_sg;

	अगर (phys_disk->in_reset) अणु
		cmd->result = DID_RESET << 16;
		वापस -1;
	पूर्ण

	enqueue_cmd_and_start_io(h, c);
	वापस 0;
पूर्ण

/*
 * Queue a command to the correct I/O accelerator path.
 */
अटल पूर्णांक hpsa_scsi_ioaccel_queue_command(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, u32 ioaccel_handle, u8 *cdb, पूर्णांक cdb_len,
	u8 *scsi3addr, काष्ठा hpsa_scsi_dev_t *phys_disk)
अणु
	अगर (!c->scsi_cmd->device)
		वापस -1;

	अगर (!c->scsi_cmd->device->hostdata)
		वापस -1;

	अगर (phys_disk->in_reset)
		वापस -1;

	/* Try to honor the device's queue depth */
	अगर (atomic_inc_वापस(&phys_disk->ioaccel_cmds_out) >
					phys_disk->queue_depth) अणु
		atomic_dec(&phys_disk->ioaccel_cmds_out);
		वापस IO_ACCEL_INELIGIBLE;
	पूर्ण
	अगर (h->transMethod & CFGTBL_Trans_io_accel1)
		वापस hpsa_scsi_ioaccel1_queue_command(h, c, ioaccel_handle,
						cdb, cdb_len, scsi3addr,
						phys_disk);
	अन्यथा
		वापस hpsa_scsi_ioaccel2_queue_command(h, c, ioaccel_handle,
						cdb, cdb_len, scsi3addr,
						phys_disk);
पूर्ण

अटल व्योम raid_map_helper(काष्ठा raid_map_data *map,
		पूर्णांक offload_to_mirror, u32 *map_index, u32 *current_group)
अणु
	अगर (offload_to_mirror == 0)  अणु
		/* use physical disk in the first mirrored group. */
		*map_index %= le16_to_cpu(map->data_disks_per_row);
		वापस;
	पूर्ण
	करो अणु
		/* determine mirror group that *map_index indicates */
		*current_group = *map_index /
			le16_to_cpu(map->data_disks_per_row);
		अगर (offload_to_mirror == *current_group)
			जारी;
		अगर (*current_group < le16_to_cpu(map->layout_map_count) - 1) अणु
			/* select map index from next group */
			*map_index += le16_to_cpu(map->data_disks_per_row);
			(*current_group)++;
		पूर्ण अन्यथा अणु
			/* select map index from first group */
			*map_index %= le16_to_cpu(map->data_disks_per_row);
			*current_group = 0;
		पूर्ण
	पूर्ण जबतक (offload_to_mirror != *current_group);
पूर्ण

/*
 * Attempt to perक्रमm offload RAID mapping क्रम a logical volume I/O.
 */
अटल पूर्णांक hpsa_scsi_ioaccel_raid_map(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	काष्ठा scsi_cmnd *cmd = c->scsi_cmd;
	काष्ठा hpsa_scsi_dev_t *dev = cmd->device->hostdata;
	काष्ठा raid_map_data *map = &dev->raid_map;
	काष्ठा raid_map_disk_data *dd = &map->data[0];
	पूर्णांक is_ग_लिखो = 0;
	u32 map_index;
	u64 first_block, last_block;
	u32 block_cnt;
	u32 blocks_per_row;
	u64 first_row, last_row;
	u32 first_row_offset, last_row_offset;
	u32 first_column, last_column;
	u64 r0_first_row, r0_last_row;
	u32 r5or6_blocks_per_row;
	u64 r5or6_first_row, r5or6_last_row;
	u32 r5or6_first_row_offset, r5or6_last_row_offset;
	u32 r5or6_first_column, r5or6_last_column;
	u32 total_disks_per_row;
	u32 stripesize;
	u32 first_group, last_group, current_group;
	u32 map_row;
	u32 disk_handle;
	u64 disk_block;
	u32 disk_block_cnt;
	u8 cdb[16];
	u8 cdb_len;
	u16 strip_size;
#अगर BITS_PER_LONG == 32
	u64 पंचांगpभाग;
#पूर्ण_अगर
	पूर्णांक offload_to_mirror;

	अगर (!dev)
		वापस -1;

	अगर (dev->in_reset)
		वापस -1;

	/* check क्रम valid opcode, get LBA and block count */
	चयन (cmd->cmnd[0]) अणु
	हाल WRITE_6:
		is_ग_लिखो = 1;
		fallthrough;
	हाल READ_6:
		first_block = (((cmd->cmnd[1] & 0x1F) << 16) |
				(cmd->cmnd[2] << 8) |
				cmd->cmnd[3]);
		block_cnt = cmd->cmnd[4];
		अगर (block_cnt == 0)
			block_cnt = 256;
		अवरोध;
	हाल WRITE_10:
		is_ग_लिखो = 1;
		fallthrough;
	हाल READ_10:
		first_block =
			(((u64) cmd->cmnd[2]) << 24) |
			(((u64) cmd->cmnd[3]) << 16) |
			(((u64) cmd->cmnd[4]) << 8) |
			cmd->cmnd[5];
		block_cnt =
			(((u32) cmd->cmnd[7]) << 8) |
			cmd->cmnd[8];
		अवरोध;
	हाल WRITE_12:
		is_ग_लिखो = 1;
		fallthrough;
	हाल READ_12:
		first_block =
			(((u64) cmd->cmnd[2]) << 24) |
			(((u64) cmd->cmnd[3]) << 16) |
			(((u64) cmd->cmnd[4]) << 8) |
			cmd->cmnd[5];
		block_cnt =
			(((u32) cmd->cmnd[6]) << 24) |
			(((u32) cmd->cmnd[7]) << 16) |
			(((u32) cmd->cmnd[8]) << 8) |
		cmd->cmnd[9];
		अवरोध;
	हाल WRITE_16:
		is_ग_लिखो = 1;
		fallthrough;
	हाल READ_16:
		first_block =
			(((u64) cmd->cmnd[2]) << 56) |
			(((u64) cmd->cmnd[3]) << 48) |
			(((u64) cmd->cmnd[4]) << 40) |
			(((u64) cmd->cmnd[5]) << 32) |
			(((u64) cmd->cmnd[6]) << 24) |
			(((u64) cmd->cmnd[7]) << 16) |
			(((u64) cmd->cmnd[8]) << 8) |
			cmd->cmnd[9];
		block_cnt =
			(((u32) cmd->cmnd[10]) << 24) |
			(((u32) cmd->cmnd[11]) << 16) |
			(((u32) cmd->cmnd[12]) << 8) |
			cmd->cmnd[13];
		अवरोध;
	शेष:
		वापस IO_ACCEL_INELIGIBLE; /* process via normal I/O path */
	पूर्ण
	last_block = first_block + block_cnt - 1;

	/* check क्रम ग_लिखो to non-RAID-0 */
	अगर (is_ग_लिखो && dev->raid_level != 0)
		वापस IO_ACCEL_INELIGIBLE;

	/* check क्रम invalid block or wraparound */
	अगर (last_block >= le64_to_cpu(map->volume_blk_cnt) ||
		last_block < first_block)
		वापस IO_ACCEL_INELIGIBLE;

	/* calculate stripe inक्रमmation क्रम the request */
	blocks_per_row = le16_to_cpu(map->data_disks_per_row) *
				le16_to_cpu(map->strip_size);
	strip_size = le16_to_cpu(map->strip_size);
#अगर BITS_PER_LONG == 32
	पंचांगpभाग = first_block;
	(व्योम) करो_भाग(पंचांगpभाग, blocks_per_row);
	first_row = पंचांगpभाग;
	पंचांगpभाग = last_block;
	(व्योम) करो_भाग(पंचांगpभाग, blocks_per_row);
	last_row = पंचांगpभाग;
	first_row_offset = (u32) (first_block - (first_row * blocks_per_row));
	last_row_offset = (u32) (last_block - (last_row * blocks_per_row));
	पंचांगpभाग = first_row_offset;
	(व्योम) करो_भाग(पंचांगpभाग, strip_size);
	first_column = पंचांगpभाग;
	पंचांगpभाग = last_row_offset;
	(व्योम) करो_भाग(पंचांगpभाग, strip_size);
	last_column = पंचांगpभाग;
#अन्यथा
	first_row = first_block / blocks_per_row;
	last_row = last_block / blocks_per_row;
	first_row_offset = (u32) (first_block - (first_row * blocks_per_row));
	last_row_offset = (u32) (last_block - (last_row * blocks_per_row));
	first_column = first_row_offset / strip_size;
	last_column = last_row_offset / strip_size;
#पूर्ण_अगर

	/* अगर this isn't a single row/column then give to the controller */
	अगर ((first_row != last_row) || (first_column != last_column))
		वापस IO_ACCEL_INELIGIBLE;

	/* proceeding with driver mapping */
	total_disks_per_row = le16_to_cpu(map->data_disks_per_row) +
				le16_to_cpu(map->metadata_disks_per_row);
	map_row = ((u32)(first_row >> map->parity_rotation_shअगरt)) %
				le16_to_cpu(map->row_cnt);
	map_index = (map_row * total_disks_per_row) + first_column;

	चयन (dev->raid_level) अणु
	हाल HPSA_RAID_0:
		अवरोध; /* nothing special to करो */
	हाल HPSA_RAID_1:
		/* Handles load balance across RAID 1 members.
		 * (2-drive R1 and R10 with even # of drives.)
		 * Appropriate क्रम SSDs, not optimal क्रम HDDs
		 * Ensure we have the correct raid_map.
		 */
		अगर (le16_to_cpu(map->layout_map_count) != 2) अणु
			hpsa_turn_off_ioaccel_क्रम_device(dev);
			वापस IO_ACCEL_INELIGIBLE;
		पूर्ण
		अगर (dev->offload_to_mirror)
			map_index += le16_to_cpu(map->data_disks_per_row);
		dev->offload_to_mirror = !dev->offload_to_mirror;
		अवरोध;
	हाल HPSA_RAID_ADM:
		/* Handles N-way mirrors  (R1-ADM)
		 * and R10 with # of drives भागisible by 3.)
		 * Ensure we have the correct raid_map.
		 */
		अगर (le16_to_cpu(map->layout_map_count) != 3) अणु
			hpsa_turn_off_ioaccel_क्रम_device(dev);
			वापस IO_ACCEL_INELIGIBLE;
		पूर्ण

		offload_to_mirror = dev->offload_to_mirror;
		raid_map_helper(map, offload_to_mirror,
				&map_index, &current_group);
		/* set mirror group to use next समय */
		offload_to_mirror =
			(offload_to_mirror >=
			le16_to_cpu(map->layout_map_count) - 1)
			? 0 : offload_to_mirror + 1;
		dev->offload_to_mirror = offload_to_mirror;
		/* Aव्योम direct use of dev->offload_to_mirror within this
		 * function since multiple thपढ़ोs might simultaneously
		 * increment it beyond the range of dev->layout_map_count -1.
		 */
		अवरोध;
	हाल HPSA_RAID_5:
	हाल HPSA_RAID_6:
		अगर (le16_to_cpu(map->layout_map_count) <= 1)
			अवरोध;

		/* Verअगरy first and last block are in same RAID group */
		r5or6_blocks_per_row =
			le16_to_cpu(map->strip_size) *
			le16_to_cpu(map->data_disks_per_row);
		अगर (r5or6_blocks_per_row == 0) अणु
			hpsa_turn_off_ioaccel_क्रम_device(dev);
			वापस IO_ACCEL_INELIGIBLE;
		पूर्ण
		stripesize = r5or6_blocks_per_row *
			le16_to_cpu(map->layout_map_count);
#अगर BITS_PER_LONG == 32
		पंचांगpभाग = first_block;
		first_group = करो_भाग(पंचांगpभाग, stripesize);
		पंचांगpभाग = first_group;
		(व्योम) करो_भाग(पंचांगpभाग, r5or6_blocks_per_row);
		first_group = पंचांगpभाग;
		पंचांगpभाग = last_block;
		last_group = करो_भाग(पंचांगpभाग, stripesize);
		पंचांगpभाग = last_group;
		(व्योम) करो_भाग(पंचांगpभाग, r5or6_blocks_per_row);
		last_group = पंचांगpभाग;
#अन्यथा
		first_group = (first_block % stripesize) / r5or6_blocks_per_row;
		last_group = (last_block % stripesize) / r5or6_blocks_per_row;
#पूर्ण_अगर
		अगर (first_group != last_group)
			वापस IO_ACCEL_INELIGIBLE;

		/* Verअगरy request is in a single row of RAID 5/6 */
#अगर BITS_PER_LONG == 32
		पंचांगpभाग = first_block;
		(व्योम) करो_भाग(पंचांगpभाग, stripesize);
		first_row = r5or6_first_row = r0_first_row = पंचांगpभाग;
		पंचांगpभाग = last_block;
		(व्योम) करो_भाग(पंचांगpभाग, stripesize);
		r5or6_last_row = r0_last_row = पंचांगpभाग;
#अन्यथा
		first_row = r5or6_first_row = r0_first_row =
						first_block / stripesize;
		r5or6_last_row = r0_last_row = last_block / stripesize;
#पूर्ण_अगर
		अगर (r5or6_first_row != r5or6_last_row)
			वापस IO_ACCEL_INELIGIBLE;


		/* Verअगरy request is in a single column */
#अगर BITS_PER_LONG == 32
		पंचांगpभाग = first_block;
		first_row_offset = करो_भाग(पंचांगpभाग, stripesize);
		पंचांगpभाग = first_row_offset;
		first_row_offset = (u32) करो_भाग(पंचांगpभाग, r5or6_blocks_per_row);
		r5or6_first_row_offset = first_row_offset;
		पंचांगpभाग = last_block;
		r5or6_last_row_offset = करो_भाग(पंचांगpभाग, stripesize);
		पंचांगpभाग = r5or6_last_row_offset;
		r5or6_last_row_offset = करो_भाग(पंचांगpभाग, r5or6_blocks_per_row);
		पंचांगpभाग = r5or6_first_row_offset;
		(व्योम) करो_भाग(पंचांगpभाग, map->strip_size);
		first_column = r5or6_first_column = पंचांगpभाग;
		पंचांगpभाग = r5or6_last_row_offset;
		(व्योम) करो_भाग(पंचांगpभाग, map->strip_size);
		r5or6_last_column = पंचांगpभाग;
#अन्यथा
		first_row_offset = r5or6_first_row_offset =
			(u32)((first_block % stripesize) %
						r5or6_blocks_per_row);

		r5or6_last_row_offset =
			(u32)((last_block % stripesize) %
						r5or6_blocks_per_row);

		first_column = r5or6_first_column =
			r5or6_first_row_offset / le16_to_cpu(map->strip_size);
		r5or6_last_column =
			r5or6_last_row_offset / le16_to_cpu(map->strip_size);
#पूर्ण_अगर
		अगर (r5or6_first_column != r5or6_last_column)
			वापस IO_ACCEL_INELIGIBLE;

		/* Request is eligible */
		map_row = ((u32)(first_row >> map->parity_rotation_shअगरt)) %
			le16_to_cpu(map->row_cnt);

		map_index = (first_group *
			(le16_to_cpu(map->row_cnt) * total_disks_per_row)) +
			(map_row * total_disks_per_row) + first_column;
		अवरोध;
	शेष:
		वापस IO_ACCEL_INELIGIBLE;
	पूर्ण

	अगर (unlikely(map_index >= RAID_MAP_MAX_ENTRIES))
		वापस IO_ACCEL_INELIGIBLE;

	c->phys_disk = dev->phys_disk[map_index];
	अगर (!c->phys_disk)
		वापस IO_ACCEL_INELIGIBLE;

	disk_handle = dd[map_index].ioaccel_handle;
	disk_block = le64_to_cpu(map->disk_starting_blk) +
			first_row * le16_to_cpu(map->strip_size) +
			(first_row_offset - first_column *
			le16_to_cpu(map->strip_size));
	disk_block_cnt = block_cnt;

	/* handle dअगरfering logical/physical block sizes */
	अगर (map->phys_blk_shअगरt) अणु
		disk_block <<= map->phys_blk_shअगरt;
		disk_block_cnt <<= map->phys_blk_shअगरt;
	पूर्ण
	BUG_ON(disk_block_cnt > 0xffff);

	/* build the new CDB क्रम the physical disk I/O */
	अगर (disk_block > 0xffffffff) अणु
		cdb[0] = is_ग_लिखो ? WRITE_16 : READ_16;
		cdb[1] = 0;
		cdb[2] = (u8) (disk_block >> 56);
		cdb[3] = (u8) (disk_block >> 48);
		cdb[4] = (u8) (disk_block >> 40);
		cdb[5] = (u8) (disk_block >> 32);
		cdb[6] = (u8) (disk_block >> 24);
		cdb[7] = (u8) (disk_block >> 16);
		cdb[8] = (u8) (disk_block >> 8);
		cdb[9] = (u8) (disk_block);
		cdb[10] = (u8) (disk_block_cnt >> 24);
		cdb[11] = (u8) (disk_block_cnt >> 16);
		cdb[12] = (u8) (disk_block_cnt >> 8);
		cdb[13] = (u8) (disk_block_cnt);
		cdb[14] = 0;
		cdb[15] = 0;
		cdb_len = 16;
	पूर्ण अन्यथा अणु
		cdb[0] = is_ग_लिखो ? WRITE_10 : READ_10;
		cdb[1] = 0;
		cdb[2] = (u8) (disk_block >> 24);
		cdb[3] = (u8) (disk_block >> 16);
		cdb[4] = (u8) (disk_block >> 8);
		cdb[5] = (u8) (disk_block);
		cdb[6] = 0;
		cdb[7] = (u8) (disk_block_cnt >> 8);
		cdb[8] = (u8) (disk_block_cnt);
		cdb[9] = 0;
		cdb_len = 10;
	पूर्ण
	वापस hpsa_scsi_ioaccel_queue_command(h, c, disk_handle, cdb, cdb_len,
						dev->scsi3addr,
						dev->phys_disk[map_index]);
पूर्ण

/*
 * Submit commands करोwn the "normal" RAID stack path
 * All callers to hpsa_ciss_submit must check lockup_detected
 * beक्रमehand, beक्रमe (opt.) and after calling cmd_alloc
 */
अटल पूर्णांक hpsa_ciss_submit(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c, काष्ठा scsi_cmnd *cmd,
	काष्ठा hpsa_scsi_dev_t *dev)
अणु
	cmd->host_scribble = (अचिन्हित अक्षर *) c;
	c->cmd_type = CMD_SCSI;
	c->scsi_cmd = cmd;
	c->Header.ReplyQueue = 0;  /* unused in simple mode */
	स_नकल(&c->Header.LUN.LunAddrBytes[0], &dev->scsi3addr[0], 8);
	c->Header.tag = cpu_to_le64((c->cmdindex << सूचीECT_LOOKUP_SHIFT));

	/* Fill in the request block... */

	c->Request.Timeout = 0;
	BUG_ON(cmd->cmd_len > माप(c->Request.CDB));
	c->Request.CDBLen = cmd->cmd_len;
	स_नकल(c->Request.CDB, cmd->cmnd, cmd->cmd_len);
	चयन (cmd->sc_data_direction) अणु
	हाल DMA_TO_DEVICE:
		c->Request.type_attr_dir =
			TYPE_ATTR_सूची(TYPE_CMD, ATTR_SIMPLE, XFER_WRITE);
		अवरोध;
	हाल DMA_FROM_DEVICE:
		c->Request.type_attr_dir =
			TYPE_ATTR_सूची(TYPE_CMD, ATTR_SIMPLE, XFER_READ);
		अवरोध;
	हाल DMA_NONE:
		c->Request.type_attr_dir =
			TYPE_ATTR_सूची(TYPE_CMD, ATTR_SIMPLE, XFER_NONE);
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		/* This can happen अगर a buggy application करोes a scsi passthru
		 * and sets both inlen and outlen to non-zero. ( see
		 * ../scsi/scsi_ioctl.c:scsi_ioctl_send_command() )
		 */

		c->Request.type_attr_dir =
			TYPE_ATTR_सूची(TYPE_CMD, ATTR_SIMPLE, XFER_RSVD);
		/* This is technically wrong, and hpsa controllers should
		 * reject it with CMD_INVALID, which is the most correct
		 * response, but non-fibre backends appear to let it
		 * slide by, and give the same results as अगर this field
		 * were set correctly.  Either way is acceptable क्रम
		 * our purposes here.
		 */

		अवरोध;

	शेष:
		dev_err(&h->pdev->dev, "unknown data direction: %d\n",
			cmd->sc_data_direction);
		BUG();
		अवरोध;
	पूर्ण

	अगर (hpsa_scatter_gather(h, c, cmd) < 0) अणु /* Fill SG list */
		hpsa_cmd_resolve_and_मुक्त(h, c);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	अगर (dev->in_reset) अणु
		hpsa_cmd_resolve_and_मुक्त(h, c);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	c->device = dev;

	enqueue_cmd_and_start_io(h, c);
	/* the cmd'll come back via पूर्णांकr handler in complete_scsi_command()  */
	वापस 0;
पूर्ण

अटल व्योम hpsa_cmd_init(काष्ठा ctlr_info *h, पूर्णांक index,
				काष्ठा CommandList *c)
अणु
	dma_addr_t cmd_dma_handle, err_dma_handle;

	/* Zero out all of commandlist except the last field, refcount */
	स_रखो(c, 0, दुरत्व(काष्ठा CommandList, refcount));
	c->Header.tag = cpu_to_le64((u64) (index << सूचीECT_LOOKUP_SHIFT));
	cmd_dma_handle = h->cmd_pool_dhandle + index * माप(*c);
	c->err_info = h->errinfo_pool + index;
	स_रखो(c->err_info, 0, माप(*c->err_info));
	err_dma_handle = h->errinfo_pool_dhandle
	    + index * माप(*c->err_info);
	c->cmdindex = index;
	c->busaddr = (u32) cmd_dma_handle;
	c->ErrDesc.Addr = cpu_to_le64((u64) err_dma_handle);
	c->ErrDesc.Len = cpu_to_le32((u32) माप(*c->err_info));
	c->h = h;
	c->scsi_cmd = SCSI_CMD_IDLE;
पूर्ण

अटल व्योम hpsa_preinitialize_commands(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < h->nr_cmds; i++) अणु
		काष्ठा CommandList *c = h->cmd_pool + i;

		hpsa_cmd_init(h, i, c);
		atomic_set(&c->refcount, 0);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hpsa_cmd_partial_init(काष्ठा ctlr_info *h, पूर्णांक index,
				काष्ठा CommandList *c)
अणु
	dma_addr_t cmd_dma_handle = h->cmd_pool_dhandle + index * माप(*c);

	BUG_ON(c->cmdindex != index);

	स_रखो(c->Request.CDB, 0, माप(c->Request.CDB));
	स_रखो(c->err_info, 0, माप(*c->err_info));
	c->busaddr = (u32) cmd_dma_handle;
पूर्ण

अटल पूर्णांक hpsa_ioaccel_submit(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c, काष्ठा scsi_cmnd *cmd,
		bool retry)
अणु
	काष्ठा hpsa_scsi_dev_t *dev = cmd->device->hostdata;
	पूर्णांक rc = IO_ACCEL_INELIGIBLE;

	अगर (!dev)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	अगर (dev->in_reset)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	अगर (hpsa_simple_mode)
		वापस IO_ACCEL_INELIGIBLE;

	cmd->host_scribble = (अचिन्हित अक्षर *) c;

	अगर (dev->offload_enabled) अणु
		hpsa_cmd_init(h, c->cmdindex, c); /* Zeroes out all fields */
		c->cmd_type = CMD_SCSI;
		c->scsi_cmd = cmd;
		c->device = dev;
		अगर (retry) /* Resubmit but करो not increment device->commands_outstanding. */
			c->retry_pending = true;
		rc = hpsa_scsi_ioaccel_raid_map(h, c);
		अगर (rc < 0)     /* scsi_dma_map failed. */
			rc = SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण अन्यथा अगर (dev->hba_ioaccel_enabled) अणु
		hpsa_cmd_init(h, c->cmdindex, c); /* Zeroes out all fields */
		c->cmd_type = CMD_SCSI;
		c->scsi_cmd = cmd;
		c->device = dev;
		अगर (retry) /* Resubmit but करो not increment device->commands_outstanding. */
			c->retry_pending = true;
		rc = hpsa_scsi_ioaccel_direct_map(h, c);
		अगर (rc < 0)     /* scsi_dma_map failed. */
			rc = SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम hpsa_command_resubmit_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा hpsa_scsi_dev_t *dev;
	काष्ठा CommandList *c = container_of(work, काष्ठा CommandList, work);

	cmd = c->scsi_cmd;
	dev = cmd->device->hostdata;
	अगर (!dev) अणु
		cmd->result = DID_NO_CONNECT << 16;
		वापस hpsa_cmd_मुक्त_and_करोne(c->h, c, cmd);
	पूर्ण

	अगर (dev->in_reset) अणु
		cmd->result = DID_RESET << 16;
		वापस hpsa_cmd_मुक्त_and_करोne(c->h, c, cmd);
	पूर्ण

	अगर (c->cmd_type == CMD_IOACCEL2) अणु
		काष्ठा ctlr_info *h = c->h;
		काष्ठा io_accel2_cmd *c2 = &h->ioaccel2_cmd_pool[c->cmdindex];
		पूर्णांक rc;

		अगर (c2->error_data.serv_response ==
				IOACCEL2_STATUS_SR_TASK_COMP_SET_FULL) अणु
			/* Resubmit with the retry_pending flag set. */
			rc = hpsa_ioaccel_submit(h, c, cmd, true);
			अगर (rc == 0)
				वापस;
			अगर (rc == SCSI_MLQUEUE_HOST_BUSY) अणु
				/*
				 * If we get here, it means dma mapping failed.
				 * Try again via scsi mid layer, which will
				 * then get SCSI_MLQUEUE_HOST_BUSY.
				 */
				cmd->result = DID_IMM_RETRY << 16;
				वापस hpsa_cmd_मुक्त_and_करोne(h, c, cmd);
			पूर्ण
			/* अन्यथा, fall thru and resubmit करोwn CISS path */
		पूर्ण
	पूर्ण
	hpsa_cmd_partial_init(c->h, c->cmdindex, c);
	/*
	 * Here we have not come in though queue_command, so we
	 * can set the retry_pending flag to true क्रम a driver initiated
	 * retry attempt (I.E. not a SML retry).
	 * I.E. We are submitting a driver initiated retry.
	 * Note: hpsa_ciss_submit करोes not zero out the command fields like
	 *       ioaccel submit करोes.
	 */
	c->retry_pending = true;
	अगर (hpsa_ciss_submit(c->h, c, cmd, dev)) अणु
		/*
		 * If we get here, it means dma mapping failed. Try
		 * again via scsi mid layer, which will then get
		 * SCSI_MLQUEUE_HOST_BUSY.
		 *
		 * hpsa_ciss_submit will have alपढ़ोy मुक्तd c
		 * अगर it encountered a dma mapping failure.
		 */
		cmd->result = DID_IMM_RETRY << 16;
		cmd->scsi_करोne(cmd);
	पूर्ण
पूर्ण

/* Running in काष्ठा Scsi_Host->host_lock less mode */
अटल पूर्णांक hpsa_scsi_queue_command(काष्ठा Scsi_Host *sh, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ctlr_info *h;
	काष्ठा hpsa_scsi_dev_t *dev;
	काष्ठा CommandList *c;
	पूर्णांक rc = 0;

	/* Get the ptr to our adapter काष्ठाure out of cmd->host. */
	h = sdev_to_hba(cmd->device);

	BUG_ON(cmd->request->tag < 0);

	dev = cmd->device->hostdata;
	अगर (!dev) अणु
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण

	अगर (dev->हटाओd) अणु
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण

	अगर (unlikely(lockup_detected(h))) अणु
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण

	अगर (dev->in_reset)
		वापस SCSI_MLQUEUE_DEVICE_BUSY;

	c = cmd_tagged_alloc(h, cmd);
	अगर (c == शून्य)
		वापस SCSI_MLQUEUE_DEVICE_BUSY;

	/*
	 * This is necessary because the SML करोesn't zero out this field during
	 * error recovery.
	 */
	cmd->result = 0;

	/*
	 * Call alternate submit routine क्रम I/O accelerated commands.
	 * Retries always go करोwn the normal I/O path.
	 * Note: If cmd->retries is non-zero, then this is a SML
	 *       initiated retry and not a driver initiated retry.
	 *       This command has been obtained from cmd_tagged_alloc
	 *       and is thereक्रमe a bअक्रम-new command.
	 */
	अगर (likely(cmd->retries == 0 &&
			!blk_rq_is_passthrough(cmd->request) &&
			h->acciopath_status)) अणु
		/* Submit with the retry_pending flag unset. */
		rc = hpsa_ioaccel_submit(h, c, cmd, false);
		अगर (rc == 0)
			वापस 0;
		अगर (rc == SCSI_MLQUEUE_HOST_BUSY) अणु
			hpsa_cmd_resolve_and_मुक्त(h, c);
			वापस SCSI_MLQUEUE_HOST_BUSY;
		पूर्ण
	पूर्ण
	वापस hpsa_ciss_submit(h, c, cmd, dev);
पूर्ण

अटल व्योम hpsa_scan_complete(काष्ठा ctlr_info *h)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&h->scan_lock, flags);
	h->scan_finished = 1;
	wake_up(&h->scan_रुको_queue);
	spin_unlock_irqrestore(&h->scan_lock, flags);
पूर्ण

अटल व्योम hpsa_scan_start(काष्ठा Scsi_Host *sh)
अणु
	काष्ठा ctlr_info *h = shost_to_hba(sh);
	अचिन्हित दीर्घ flags;

	/*
	 * Don't let rescans be initiated on a controller known to be locked
	 * up.  If the controller locks up *during* a rescan, that thपढ़ो is
	 * probably hosed, but at least we can prevent new rescan thपढ़ोs from
	 * piling up on a locked up controller.
	 */
	अगर (unlikely(lockup_detected(h)))
		वापस hpsa_scan_complete(h);

	/*
	 * If a scan is alपढ़ोy रुकोing to run, no need to add another
	 */
	spin_lock_irqsave(&h->scan_lock, flags);
	अगर (h->scan_रुकोing) अणु
		spin_unlock_irqrestore(&h->scan_lock, flags);
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&h->scan_lock, flags);

	/* रुको until any scan alपढ़ोy in progress is finished. */
	जबतक (1) अणु
		spin_lock_irqsave(&h->scan_lock, flags);
		अगर (h->scan_finished)
			अवरोध;
		h->scan_रुकोing = 1;
		spin_unlock_irqrestore(&h->scan_lock, flags);
		रुको_event(h->scan_रुको_queue, h->scan_finished);
		/* Note: We करोn't need to worry about a race between this
		 * thपढ़ो and driver unload because the midlayer will
		 * have incremented the reference count, so unload won't
		 * happen अगर we're in here.
		 */
	पूर्ण
	h->scan_finished = 0; /* mark scan as in progress */
	h->scan_रुकोing = 0;
	spin_unlock_irqrestore(&h->scan_lock, flags);

	अगर (unlikely(lockup_detected(h)))
		वापस hpsa_scan_complete(h);

	/*
	 * Do the scan after a reset completion
	 */
	spin_lock_irqsave(&h->reset_lock, flags);
	अगर (h->reset_in_progress) अणु
		h->drv_req_rescan = 1;
		spin_unlock_irqrestore(&h->reset_lock, flags);
		hpsa_scan_complete(h);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&h->reset_lock, flags);

	hpsa_update_scsi_devices(h);

	hpsa_scan_complete(h);
पूर्ण

अटल पूर्णांक hpsa_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	काष्ठा hpsa_scsi_dev_t *logical_drive = sdev->hostdata;

	अगर (!logical_drive)
		वापस -ENODEV;

	अगर (qdepth < 1)
		qdepth = 1;
	अन्यथा अगर (qdepth > logical_drive->queue_depth)
		qdepth = logical_drive->queue_depth;

	वापस scsi_change_queue_depth(sdev, qdepth);
पूर्ण

अटल पूर्णांक hpsa_scan_finished(काष्ठा Scsi_Host *sh,
	अचिन्हित दीर्घ elapsed_समय)
अणु
	काष्ठा ctlr_info *h = shost_to_hba(sh);
	अचिन्हित दीर्घ flags;
	पूर्णांक finished;

	spin_lock_irqsave(&h->scan_lock, flags);
	finished = h->scan_finished;
	spin_unlock_irqrestore(&h->scan_lock, flags);
	वापस finished;
पूर्ण

अटल पूर्णांक hpsa_scsi_host_alloc(काष्ठा ctlr_info *h)
अणु
	काष्ठा Scsi_Host *sh;

	sh = scsi_host_alloc(&hpsa_driver_ढाँचा, माप(h));
	अगर (sh == शून्य) अणु
		dev_err(&h->pdev->dev, "scsi_host_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	sh->io_port = 0;
	sh->n_io_port = 0;
	sh->this_id = -1;
	sh->max_channel = 3;
	sh->max_cmd_len = MAX_COMMAND_SIZE;
	sh->max_lun = HPSA_MAX_LUN;
	sh->max_id = HPSA_MAX_LUN;
	sh->can_queue = h->nr_cmds - HPSA_NRESERVED_CMDS;
	sh->cmd_per_lun = sh->can_queue;
	sh->sg_tablesize = h->maxsgentries;
	sh->transportt = hpsa_sas_transport_ढाँचा;
	sh->hostdata[0] = (अचिन्हित दीर्घ) h;
	sh->irq = pci_irq_vector(h->pdev, 0);
	sh->unique_id = sh->irq;

	h->scsi_host = sh;
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_scsi_add_host(काष्ठा ctlr_info *h)
अणु
	पूर्णांक rv;

	rv = scsi_add_host(h->scsi_host, &h->pdev->dev);
	अगर (rv) अणु
		dev_err(&h->pdev->dev, "scsi_add_host failed\n");
		वापस rv;
	पूर्ण
	scsi_scan_host(h->scsi_host);
	वापस 0;
पूर्ण

/*
 * The block layer has alपढ़ोy gone to the trouble of picking out a unique,
 * small-पूर्णांकeger tag क्रम this request.  We use an offset from that value as
 * an index to select our command block.  (The offset allows us to reserve the
 * low-numbered entries क्रम our own uses.)
 */
अटल पूर्णांक hpsa_get_cmd_index(काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक idx = scmd->request->tag;

	अगर (idx < 0)
		वापस idx;

	/* Offset to leave space क्रम पूर्णांकernal cmds. */
	वापस idx += HPSA_NRESERVED_CMDS;
पूर्ण

/*
 * Send a TEST_UNIT_READY command to the specअगरied LUN using the specअगरied
 * reply queue; वापसs zero अगर the unit is पढ़ोy, and non-zero otherwise.
 */
अटल पूर्णांक hpsa_send_test_unit_पढ़ोy(काष्ठा ctlr_info *h,
				काष्ठा CommandList *c, अचिन्हित अक्षर lunaddr[],
				पूर्णांक reply_queue)
अणु
	पूर्णांक rc;

	/* Send the Test Unit Ready, fill_cmd can't fail, no mapping */
	(व्योम) fill_cmd(c, TEST_UNIT_READY, h,
			शून्य, 0, 0, lunaddr, TYPE_CMD);
	rc = hpsa_scsi_करो_simple_cmd(h, c, reply_queue, NO_TIMEOUT);
	अगर (rc)
		वापस rc;
	/* no unmap needed here because no data xfer. */

	/* Check अगर the unit is alपढ़ोy पढ़ोy. */
	अगर (c->err_info->CommandStatus == CMD_SUCCESS)
		वापस 0;

	/*
	 * The first command sent after reset will receive "unit attention" to
	 * indicate that the LUN has been reset...this is actually what we're
	 * looking क्रम (but, success is good too).
	 */
	अगर (c->err_info->CommandStatus == CMD_TARGET_STATUS &&
		c->err_info->ScsiStatus == SAM_STAT_CHECK_CONDITION &&
			(c->err_info->SenseInfo[2] == NO_SENSE ||
			 c->err_info->SenseInfo[2] == UNIT_ATTENTION))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Wait क्रम a TEST_UNIT_READY command to complete, retrying as necessary;
 * वापसs zero when the unit is पढ़ोy, and non-zero when giving up.
 */
अटल पूर्णांक hpsa_रुको_क्रम_test_unit_पढ़ोy(काष्ठा ctlr_info *h,
				काष्ठा CommandList *c,
				अचिन्हित अक्षर lunaddr[], पूर्णांक reply_queue)
अणु
	पूर्णांक rc;
	पूर्णांक count = 0;
	पूर्णांक रुकोसमय = 1; /* seconds */

	/* Send test unit पढ़ोy until device पढ़ोy, or give up. */
	क्रम (count = 0; count < HPSA_TUR_RETRY_LIMIT; count++) अणु

		/*
		 * Wait क्रम a bit.  करो this first, because अगर we send
		 * the TUR right away, the reset will just पात it.
		 */
		msleep(1000 * रुकोसमय);

		rc = hpsa_send_test_unit_पढ़ोy(h, c, lunaddr, reply_queue);
		अगर (!rc)
			अवरोध;

		/* Increase रुको समय with each try, up to a poपूर्णांक. */
		अगर (रुकोसमय < HPSA_MAX_WAIT_INTERVAL_SECS)
			रुकोसमय *= 2;

		dev_warn(&h->pdev->dev,
			 "waiting %d secs for device to become ready.\n",
			 रुकोसमय);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक रुको_क्रम_device_to_become_पढ़ोy(काष्ठा ctlr_info *h,
					   अचिन्हित अक्षर lunaddr[],
					   पूर्णांक reply_queue)
अणु
	पूर्णांक first_queue;
	पूर्णांक last_queue;
	पूर्णांक rq;
	पूर्णांक rc = 0;
	काष्ठा CommandList *c;

	c = cmd_alloc(h);

	/*
	 * If no specअगरic reply queue was requested, then send the TUR
	 * repeatedly, requesting a reply on each reply queue; otherwise execute
	 * the loop exactly once using only the specअगरied queue.
	 */
	अगर (reply_queue == DEFAULT_REPLY_QUEUE) अणु
		first_queue = 0;
		last_queue = h->nreply_queues - 1;
	पूर्ण अन्यथा अणु
		first_queue = reply_queue;
		last_queue = reply_queue;
	पूर्ण

	क्रम (rq = first_queue; rq <= last_queue; rq++) अणु
		rc = hpsa_रुको_क्रम_test_unit_पढ़ोy(h, c, lunaddr, rq);
		अगर (rc)
			अवरोध;
	पूर्ण

	अगर (rc)
		dev_warn(&h->pdev->dev, "giving up on device.\n");
	अन्यथा
		dev_warn(&h->pdev->dev, "device is ready.\n");

	cmd_मुक्त(h, c);
	वापस rc;
पूर्ण

/* Need at least one of these error handlers to keep ../scsi/hosts.c from
 * complaining.  Doing a host- or bus-reset can't करो anything good here.
 */
अटल पूर्णांक hpsa_eh_device_reset_handler(काष्ठा scsi_cmnd *scsicmd)
अणु
	पूर्णांक rc = SUCCESS;
	पूर्णांक i;
	काष्ठा ctlr_info *h;
	काष्ठा hpsa_scsi_dev_t *dev = शून्य;
	u8 reset_type;
	अक्षर msg[48];
	अचिन्हित दीर्घ flags;

	/* find the controller to which the command to be पातed was sent */
	h = sdev_to_hba(scsicmd->device);
	अगर (h == शून्य) /* paranoia */
		वापस FAILED;

	spin_lock_irqsave(&h->reset_lock, flags);
	h->reset_in_progress = 1;
	spin_unlock_irqrestore(&h->reset_lock, flags);

	अगर (lockup_detected(h)) अणु
		rc = FAILED;
		जाओ वापस_reset_status;
	पूर्ण

	dev = scsicmd->device->hostdata;
	अगर (!dev) अणु
		dev_err(&h->pdev->dev, "%s: device lookup failed\n", __func__);
		rc = FAILED;
		जाओ वापस_reset_status;
	पूर्ण

	अगर (dev->devtype == TYPE_ENCLOSURE) अणु
		rc = SUCCESS;
		जाओ वापस_reset_status;
	पूर्ण

	/* अगर controller locked up, we can guarantee command won't complete */
	अगर (lockup_detected(h)) अणु
		snम_लिखो(msg, माप(msg),
			 "cmd %d RESET FAILED, lockup detected",
			 hpsa_get_cmd_index(scsicmd));
		hpsa_show_dev_msg(KERN_WARNING, h, dev, msg);
		rc = FAILED;
		जाओ वापस_reset_status;
	पूर्ण

	/* this reset request might be the result of a lockup; check */
	अगर (detect_controller_lockup(h)) अणु
		snम_लिखो(msg, माप(msg),
			 "cmd %d RESET FAILED, new lockup detected",
			 hpsa_get_cmd_index(scsicmd));
		hpsa_show_dev_msg(KERN_WARNING, h, dev, msg);
		rc = FAILED;
		जाओ वापस_reset_status;
	पूर्ण

	/* Do not attempt on controller */
	अगर (is_hba_lunid(dev->scsi3addr)) अणु
		rc = SUCCESS;
		जाओ वापस_reset_status;
	पूर्ण

	अगर (is_logical_dev_addr_mode(dev->scsi3addr))
		reset_type = HPSA_DEVICE_RESET_MSG;
	अन्यथा
		reset_type = HPSA_PHYS_TARGET_RESET;

	प्र_लिखो(msg, "resetting %s",
		reset_type == HPSA_DEVICE_RESET_MSG ? "logical " : "physical ");
	hpsa_show_dev_msg(KERN_WARNING, h, dev, msg);

	/*
	 * रुको to see अगर any commands will complete beक्रमe sending reset
	 */
	dev->in_reset = true; /* block any new cmds from OS क्रम this device */
	क्रम (i = 0; i < 10; i++) अणु
		अगर (atomic_पढ़ो(&dev->commands_outstanding) > 0)
			msleep(1000);
		अन्यथा
			अवरोध;
	पूर्ण

	/* send a reset to the SCSI LUN which the command was sent to */
	rc = hpsa_करो_reset(h, dev, reset_type, DEFAULT_REPLY_QUEUE);
	अगर (rc == 0)
		rc = SUCCESS;
	अन्यथा
		rc = FAILED;

	प्र_लिखो(msg, "reset %s %s",
		reset_type == HPSA_DEVICE_RESET_MSG ? "logical " : "physical ",
		rc == SUCCESS ? "completed successfully" : "failed");
	hpsa_show_dev_msg(KERN_WARNING, h, dev, msg);

वापस_reset_status:
	spin_lock_irqsave(&h->reset_lock, flags);
	h->reset_in_progress = 0;
	अगर (dev)
		dev->in_reset = false;
	spin_unlock_irqrestore(&h->reset_lock, flags);
	वापस rc;
पूर्ण

/*
 * For operations with an associated SCSI command, a command block is allocated
 * at init, and managed by cmd_tagged_alloc() and cmd_tagged_मुक्त() using the
 * block request tag as an index पूर्णांकo a table of entries.  cmd_tagged_मुक्त() is
 * the complement, although cmd_मुक्त() may be called instead.
 * This function is only called क्रम new requests from queue_command.
 */
अटल काष्ठा CommandList *cmd_tagged_alloc(काष्ठा ctlr_info *h,
					    काष्ठा scsi_cmnd *scmd)
अणु
	पूर्णांक idx = hpsa_get_cmd_index(scmd);
	काष्ठा CommandList *c = h->cmd_pool + idx;

	अगर (idx < HPSA_NRESERVED_CMDS || idx >= h->nr_cmds) अणु
		dev_err(&h->pdev->dev, "Bad block tag: %d not in [%d..%d]\n",
			idx, HPSA_NRESERVED_CMDS, h->nr_cmds - 1);
		/* The index value comes from the block layer, so अगर it's out of
		 * bounds, it's probably not our bug.
		 */
		BUG();
	पूर्ण

	अगर (unlikely(!hpsa_is_cmd_idle(c))) अणु
		/*
		 * We expect that the SCSI layer will hand us a unique tag
		 * value.  Thus, there should never be a collision here between
		 * two requests...because अगर the selected command isn't idle
		 * then someone is going to be very disappoपूर्णांकed.
		 */
		अगर (idx != h->last_collision_tag) अणु /* Prपूर्णांक once per tag */
			dev_warn(&h->pdev->dev,
				"%s: tag collision (tag=%d)\n", __func__, idx);
			अगर (scmd)
				scsi_prपूर्णांक_command(scmd);
			h->last_collision_tag = idx;
		पूर्ण
		वापस शून्य;
	पूर्ण

	atomic_inc(&c->refcount);
	hpsa_cmd_partial_init(h, idx, c);

	/*
	 * This is a new command obtained from queue_command so
	 * there have not been any driver initiated retry attempts.
	 */
	c->retry_pending = false;

	वापस c;
पूर्ण

अटल व्योम cmd_tagged_मुक्त(काष्ठा ctlr_info *h, काष्ठा CommandList *c)
अणु
	/*
	 * Release our reference to the block.  We करोn't need to करो anything
	 * अन्यथा to मुक्त it, because it is accessed by index.
	 */
	(व्योम)atomic_dec(&c->refcount);
पूर्ण

/*
 * For operations that cannot sleep, a command block is allocated at init,
 * and managed by cmd_alloc() and cmd_मुक्त() using a simple biपंचांगap to track
 * which ones are मुक्त or in use.  Lock must be held when calling this.
 * cmd_मुक्त() is the complement.
 * This function never gives up and वापसs शून्य.  If it hangs,
 * another thपढ़ो must call cmd_मुक्त() to मुक्त some tags.
 */

अटल काष्ठा CommandList *cmd_alloc(काष्ठा ctlr_info *h)
अणु
	काष्ठा CommandList *c;
	पूर्णांक refcount, i;
	पूर्णांक offset = 0;

	/*
	 * There is some *extremely* small but non-zero chance that that
	 * multiple thपढ़ोs could get in here, and one thपढ़ो could
	 * be scanning through the list of bits looking क्रम a मुक्त
	 * one, but the मुक्त ones are always behind him, and other
	 * thपढ़ोs sneak in behind him and eat them beक्रमe he can
	 * get to them, so that जबतक there is always a मुक्त one, a
	 * very unlucky thपढ़ो might be starved anyway, never able to
	 * beat the other thपढ़ोs.  In reality, this happens so
	 * infrequently as to be indistinguishable from never.
	 *
	 * Note that we start allocating commands beक्रमe the SCSI host काष्ठाure
	 * is initialized.  Since the search starts at bit zero, this
	 * all works, since we have at least one command काष्ठाure available;
	 * however, it means that the काष्ठाures with the low indexes have to be
	 * reserved क्रम driver-initiated requests, जबतक requests from the block
	 * layer will use the higher indexes.
	 */

	क्रम (;;) अणु
		i = find_next_zero_bit(h->cmd_pool_bits,
					HPSA_NRESERVED_CMDS,
					offset);
		अगर (unlikely(i >= HPSA_NRESERVED_CMDS)) अणु
			offset = 0;
			जारी;
		पूर्ण
		c = h->cmd_pool + i;
		refcount = atomic_inc_वापस(&c->refcount);
		अगर (unlikely(refcount > 1)) अणु
			cmd_मुक्त(h, c); /* alपढ़ोy in use */
			offset = (i + 1) % HPSA_NRESERVED_CMDS;
			जारी;
		पूर्ण
		set_bit(i & (BITS_PER_LONG - 1),
			h->cmd_pool_bits + (i / BITS_PER_LONG));
		अवरोध; /* it's ours now. */
	पूर्ण
	hpsa_cmd_partial_init(h, i, c);
	c->device = शून्य;

	/*
	 * cmd_alloc is क्रम "internal" commands and they are never
	 * retried.
	 */
	c->retry_pending = false;

	वापस c;
पूर्ण

/*
 * This is the complementary operation to cmd_alloc().  Note, however, in some
 * corner हालs it may also be used to मुक्त blocks allocated by
 * cmd_tagged_alloc() in which हाल the ref-count decrement करोes the trick and
 * the clear-bit is harmless.
 */
अटल व्योम cmd_मुक्त(काष्ठा ctlr_info *h, काष्ठा CommandList *c)
अणु
	अगर (atomic_dec_and_test(&c->refcount)) अणु
		पूर्णांक i;

		i = c - h->cmd_pool;
		clear_bit(i & (BITS_PER_LONG - 1),
			  h->cmd_pool_bits + (i / BITS_PER_LONG));
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT

अटल पूर्णांक hpsa_ioctl32_passthru(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
	व्योम __user *arg)
अणु
	काष्ठा ctlr_info *h = sdev_to_hba(dev);
	IOCTL32_Command_काष्ठा __user *arg32 = arg;
	IOCTL_Command_काष्ठा arg64;
	पूर्णांक err;
	u32 cp;

	अगर (!arg)
		वापस -EINVAL;

	स_रखो(&arg64, 0, माप(arg64));
	अगर (copy_from_user(&arg64, arg32, दुरत्व(IOCTL_Command_काष्ठा, buf)))
		वापस -EFAULT;
	अगर (get_user(cp, &arg32->buf))
		वापस -EFAULT;
	arg64.buf = compat_ptr(cp);

	अगर (atomic_dec_अगर_positive(&h->passthru_cmds_avail) < 0)
		वापस -EAGAIN;
	err = hpsa_passthru_ioctl(h, &arg64);
	atomic_inc(&h->passthru_cmds_avail);
	अगर (err)
		वापस err;
	अगर (copy_to_user(&arg32->error_info, &arg64.error_info,
			 माप(arg32->error_info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_ioctl32_big_passthru(काष्ठा scsi_device *dev,
	अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा ctlr_info *h = sdev_to_hba(dev);
	BIG_IOCTL32_Command_काष्ठा __user *arg32 = arg;
	BIG_IOCTL_Command_काष्ठा arg64;
	पूर्णांक err;
	u32 cp;

	अगर (!arg)
		वापस -EINVAL;
	स_रखो(&arg64, 0, माप(arg64));
	अगर (copy_from_user(&arg64, arg32,
			   दुरत्व(BIG_IOCTL32_Command_काष्ठा, buf)))
		वापस -EFAULT;
	अगर (get_user(cp, &arg32->buf))
		वापस -EFAULT;
	arg64.buf = compat_ptr(cp);

	अगर (atomic_dec_अगर_positive(&h->passthru_cmds_avail) < 0)
		वापस -EAGAIN;
	err = hpsa_big_passthru_ioctl(h, &arg64);
	atomic_inc(&h->passthru_cmds_avail);
	अगर (err)
		वापस err;
	अगर (copy_to_user(&arg32->error_info, &arg64.error_info,
			 माप(arg32->error_info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_compat_ioctl(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
			     व्योम __user *arg)
अणु
	चयन (cmd) अणु
	हाल CCISS_GETPCIINFO:
	हाल CCISS_GETINTINFO:
	हाल CCISS_SETINTINFO:
	हाल CCISS_GETNODENAME:
	हाल CCISS_SETNODENAME:
	हाल CCISS_GETHEARTBEAT:
	हाल CCISS_GETBUSTYPES:
	हाल CCISS_GETFIRMVER:
	हाल CCISS_GETDRIVVER:
	हाल CCISS_REVALIDVOLS:
	हाल CCISS_DEREGDISK:
	हाल CCISS_REGNEWDISK:
	हाल CCISS_REGNEWD:
	हाल CCISS_RESCANDISK:
	हाल CCISS_GETLUNINFO:
		वापस hpsa_ioctl(dev, cmd, arg);

	हाल CCISS_PASSTHRU32:
		वापस hpsa_ioctl32_passthru(dev, cmd, arg);
	हाल CCISS_BIG_PASSTHRU32:
		वापस hpsa_ioctl32_big_passthru(dev, cmd, arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hpsa_getpciinfo_ioctl(काष्ठा ctlr_info *h, व्योम __user *argp)
अणु
	काष्ठा hpsa_pci_info pciinfo;

	अगर (!argp)
		वापस -EINVAL;
	pciinfo.करोमुख्य = pci_करोमुख्य_nr(h->pdev->bus);
	pciinfo.bus = h->pdev->bus->number;
	pciinfo.dev_fn = h->pdev->devfn;
	pciinfo.board_id = h->board_id;
	अगर (copy_to_user(argp, &pciinfo, माप(pciinfo)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_getdrivver_ioctl(काष्ठा ctlr_info *h, व्योम __user *argp)
अणु
	DriverVer_type DriverVer;
	अचिन्हित अक्षर vmaj, vmin, vsubmin;
	पूर्णांक rc;

	rc = माला_पूछो(HPSA_DRIVER_VERSION, "%hhu.%hhu.%hhu",
		&vmaj, &vmin, &vsubmin);
	अगर (rc != 3) अणु
		dev_info(&h->pdev->dev, "driver version string '%s' "
			"unrecognized.", HPSA_DRIVER_VERSION);
		vmaj = 0;
		vmin = 0;
		vsubmin = 0;
	पूर्ण
	DriverVer = (vmaj << 16) | (vmin << 8) | vsubmin;
	अगर (!argp)
		वापस -EINVAL;
	अगर (copy_to_user(argp, &DriverVer, माप(DriverVer_type)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_passthru_ioctl(काष्ठा ctlr_info *h,
			       IOCTL_Command_काष्ठा *iocommand)
अणु
	काष्ठा CommandList *c;
	अक्षर *buff = शून्य;
	u64 temp64;
	पूर्णांक rc = 0;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;
	अगर ((iocommand->buf_size < 1) &&
	    (iocommand->Request.Type.Direction != XFER_NONE)) अणु
		वापस -EINVAL;
	पूर्ण
	अगर (iocommand->buf_size > 0) अणु
		buff = kदो_स्मृति(iocommand->buf_size, GFP_KERNEL);
		अगर (buff == शून्य)
			वापस -ENOMEM;
		अगर (iocommand->Request.Type.Direction & XFER_WRITE) अणु
			/* Copy the data पूर्णांकo the buffer we created */
			अगर (copy_from_user(buff, iocommand->buf,
				iocommand->buf_size)) अणु
				rc = -EFAULT;
				जाओ out_kमुक्त;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_रखो(buff, 0, iocommand->buf_size);
		पूर्ण
	पूर्ण
	c = cmd_alloc(h);

	/* Fill in the command type */
	c->cmd_type = CMD_IOCTL_PEND;
	c->scsi_cmd = SCSI_CMD_BUSY;
	/* Fill in Command Header */
	c->Header.ReplyQueue = 0; /* unused in simple mode */
	अगर (iocommand->buf_size > 0) अणु	/* buffer to fill */
		c->Header.SGList = 1;
		c->Header.SGTotal = cpu_to_le16(1);
	पूर्ण अन्यथा	अणु /* no buffers to fill */
		c->Header.SGList = 0;
		c->Header.SGTotal = cpu_to_le16(0);
	पूर्ण
	स_नकल(&c->Header.LUN, &iocommand->LUN_info, माप(c->Header.LUN));

	/* Fill in Request block */
	स_नकल(&c->Request, &iocommand->Request,
		माप(c->Request));

	/* Fill in the scatter gather inक्रमmation */
	अगर (iocommand->buf_size > 0) अणु
		temp64 = dma_map_single(&h->pdev->dev, buff,
			iocommand->buf_size, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(&h->pdev->dev, (dma_addr_t) temp64)) अणु
			c->SG[0].Addr = cpu_to_le64(0);
			c->SG[0].Len = cpu_to_le32(0);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		c->SG[0].Addr = cpu_to_le64(temp64);
		c->SG[0].Len = cpu_to_le32(iocommand->buf_size);
		c->SG[0].Ext = cpu_to_le32(HPSA_SG_LAST); /* not chaining */
	पूर्ण
	rc = hpsa_scsi_करो_simple_cmd(h, c, DEFAULT_REPLY_QUEUE,
					NO_TIMEOUT);
	अगर (iocommand->buf_size > 0)
		hpsa_pci_unmap(h->pdev, c, 1, DMA_BIसूचीECTIONAL);
	check_ioctl_unit_attention(h, c);
	अगर (rc) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* Copy the error inक्रमmation out */
	स_नकल(&iocommand->error_info, c->err_info,
		माप(iocommand->error_info));
	अगर ((iocommand->Request.Type.Direction & XFER_READ) &&
		iocommand->buf_size > 0) अणु
		/* Copy the data out of the buffer we created */
		अगर (copy_to_user(iocommand->buf, buff, iocommand->buf_size)) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	cmd_मुक्त(h, c);
out_kमुक्त:
	kमुक्त(buff);
	वापस rc;
पूर्ण

अटल पूर्णांक hpsa_big_passthru_ioctl(काष्ठा ctlr_info *h,
				   BIG_IOCTL_Command_काष्ठा *ioc)
अणु
	काष्ठा CommandList *c;
	अचिन्हित अक्षर **buff = शून्य;
	पूर्णांक *buff_size = शून्य;
	u64 temp64;
	BYTE sg_used = 0;
	पूर्णांक status = 0;
	u32 left;
	u32 sz;
	BYTE __user *data_ptr;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	अगर ((ioc->buf_size < 1) &&
	    (ioc->Request.Type.Direction != XFER_NONE))
		वापस -EINVAL;
	/* Check kदो_स्मृति limits  using all SGs */
	अगर (ioc->दो_स्मृति_size > MAX_KMALLOC_SIZE)
		वापस -EINVAL;
	अगर (ioc->buf_size > ioc->दो_स्मृति_size * SG_ENTRIES_IN_CMD)
		वापस -EINVAL;
	buff = kसुस्मृति(SG_ENTRIES_IN_CMD, माप(अक्षर *), GFP_KERNEL);
	अगर (!buff) अणु
		status = -ENOMEM;
		जाओ cleanup1;
	पूर्ण
	buff_size = kदो_स्मृति_array(SG_ENTRIES_IN_CMD, माप(पूर्णांक), GFP_KERNEL);
	अगर (!buff_size) अणु
		status = -ENOMEM;
		जाओ cleanup1;
	पूर्ण
	left = ioc->buf_size;
	data_ptr = ioc->buf;
	जबतक (left) अणु
		sz = (left > ioc->दो_स्मृति_size) ? ioc->दो_स्मृति_size : left;
		buff_size[sg_used] = sz;
		buff[sg_used] = kदो_स्मृति(sz, GFP_KERNEL);
		अगर (buff[sg_used] == शून्य) अणु
			status = -ENOMEM;
			जाओ cleanup1;
		पूर्ण
		अगर (ioc->Request.Type.Direction & XFER_WRITE) अणु
			अगर (copy_from_user(buff[sg_used], data_ptr, sz)) अणु
				status = -EFAULT;
				जाओ cleanup1;
			पूर्ण
		पूर्ण अन्यथा
			स_रखो(buff[sg_used], 0, sz);
		left -= sz;
		data_ptr += sz;
		sg_used++;
	पूर्ण
	c = cmd_alloc(h);

	c->cmd_type = CMD_IOCTL_PEND;
	c->scsi_cmd = SCSI_CMD_BUSY;
	c->Header.ReplyQueue = 0;
	c->Header.SGList = (u8) sg_used;
	c->Header.SGTotal = cpu_to_le16(sg_used);
	स_नकल(&c->Header.LUN, &ioc->LUN_info, माप(c->Header.LUN));
	स_नकल(&c->Request, &ioc->Request, माप(c->Request));
	अगर (ioc->buf_size > 0) अणु
		पूर्णांक i;
		क्रम (i = 0; i < sg_used; i++) अणु
			temp64 = dma_map_single(&h->pdev->dev, buff[i],
				    buff_size[i], DMA_BIसूचीECTIONAL);
			अगर (dma_mapping_error(&h->pdev->dev,
							(dma_addr_t) temp64)) अणु
				c->SG[i].Addr = cpu_to_le64(0);
				c->SG[i].Len = cpu_to_le32(0);
				hpsa_pci_unmap(h->pdev, c, i,
					DMA_BIसूचीECTIONAL);
				status = -ENOMEM;
				जाओ cleanup0;
			पूर्ण
			c->SG[i].Addr = cpu_to_le64(temp64);
			c->SG[i].Len = cpu_to_le32(buff_size[i]);
			c->SG[i].Ext = cpu_to_le32(0);
		पूर्ण
		c->SG[--i].Ext = cpu_to_le32(HPSA_SG_LAST);
	पूर्ण
	status = hpsa_scsi_करो_simple_cmd(h, c, DEFAULT_REPLY_QUEUE,
						NO_TIMEOUT);
	अगर (sg_used)
		hpsa_pci_unmap(h->pdev, c, sg_used, DMA_BIसूचीECTIONAL);
	check_ioctl_unit_attention(h, c);
	अगर (status) अणु
		status = -EIO;
		जाओ cleanup0;
	पूर्ण

	/* Copy the error inक्रमmation out */
	स_नकल(&ioc->error_info, c->err_info, माप(ioc->error_info));
	अगर ((ioc->Request.Type.Direction & XFER_READ) && ioc->buf_size > 0) अणु
		पूर्णांक i;

		/* Copy the data out of the buffer we created */
		BYTE __user *ptr = ioc->buf;
		क्रम (i = 0; i < sg_used; i++) अणु
			अगर (copy_to_user(ptr, buff[i], buff_size[i])) अणु
				status = -EFAULT;
				जाओ cleanup0;
			पूर्ण
			ptr += buff_size[i];
		पूर्ण
	पूर्ण
	status = 0;
cleanup0:
	cmd_मुक्त(h, c);
cleanup1:
	अगर (buff) अणु
		पूर्णांक i;

		क्रम (i = 0; i < sg_used; i++)
			kमुक्त(buff[i]);
		kमुक्त(buff);
	पूर्ण
	kमुक्त(buff_size);
	वापस status;
पूर्ण

अटल व्योम check_ioctl_unit_attention(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	अगर (c->err_info->CommandStatus == CMD_TARGET_STATUS &&
			c->err_info->ScsiStatus != SAM_STAT_CHECK_CONDITION)
		(व्योम) check_क्रम_unit_attention(h, c);
पूर्ण

/*
 * ioctl
 */
अटल पूर्णांक hpsa_ioctl(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
		      व्योम __user *argp)
अणु
	काष्ठा ctlr_info *h = sdev_to_hba(dev);
	पूर्णांक rc;

	चयन (cmd) अणु
	हाल CCISS_DEREGDISK:
	हाल CCISS_REGNEWDISK:
	हाल CCISS_REGNEWD:
		hpsa_scan_start(h->scsi_host);
		वापस 0;
	हाल CCISS_GETPCIINFO:
		वापस hpsa_getpciinfo_ioctl(h, argp);
	हाल CCISS_GETDRIVVER:
		वापस hpsa_getdrivver_ioctl(h, argp);
	हाल CCISS_PASSTHRU: अणु
		IOCTL_Command_काष्ठा iocommand;

		अगर (!argp)
			वापस -EINVAL;
		अगर (copy_from_user(&iocommand, argp, माप(iocommand)))
			वापस -EFAULT;
		अगर (atomic_dec_अगर_positive(&h->passthru_cmds_avail) < 0)
			वापस -EAGAIN;
		rc = hpsa_passthru_ioctl(h, &iocommand);
		atomic_inc(&h->passthru_cmds_avail);
		अगर (!rc && copy_to_user(argp, &iocommand, माप(iocommand)))
			rc = -EFAULT;
		वापस rc;
	पूर्ण
	हाल CCISS_BIG_PASSTHRU: अणु
		BIG_IOCTL_Command_काष्ठा ioc;
		अगर (!argp)
			वापस -EINVAL;
		अगर (copy_from_user(&ioc, argp, माप(ioc)))
			वापस -EFAULT;
		अगर (atomic_dec_अगर_positive(&h->passthru_cmds_avail) < 0)
			वापस -EAGAIN;
		rc = hpsa_big_passthru_ioctl(h, &ioc);
		atomic_inc(&h->passthru_cmds_avail);
		अगर (!rc && copy_to_user(argp, &ioc, माप(ioc)))
			rc = -EFAULT;
		वापस rc;
	पूर्ण
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल व्योम hpsa_send_host_reset(काष्ठा ctlr_info *h, u8 reset_type)
अणु
	काष्ठा CommandList *c;

	c = cmd_alloc(h);

	/* fill_cmd can't fail here, no data buffer to map */
	(व्योम) fill_cmd(c, HPSA_DEVICE_RESET_MSG, h, शून्य, 0, 0,
		RAID_CTLR_LUNID, TYPE_MSG);
	c->Request.CDB[1] = reset_type; /* fill_cmd शेषs to target reset */
	c->रुकोing = शून्य;
	enqueue_cmd_and_start_io(h, c);
	/* Don't wait for completion, the reset won't complete.  Don't मुक्त
	 * the command either.  This is the last command we will send beक्रमe
	 * re-initializing everything, so it करोesn't matter and won't leak.
	 */
	वापस;
पूर्ण

अटल पूर्णांक fill_cmd(काष्ठा CommandList *c, u8 cmd, काष्ठा ctlr_info *h,
	व्योम *buff, माप_प्रकार size, u16 page_code, अचिन्हित अक्षर *scsi3addr,
	पूर्णांक cmd_type)
अणु
	क्रमागत dma_data_direction dir = DMA_NONE;

	c->cmd_type = CMD_IOCTL_PEND;
	c->scsi_cmd = SCSI_CMD_BUSY;
	c->Header.ReplyQueue = 0;
	अगर (buff != शून्य && size > 0) अणु
		c->Header.SGList = 1;
		c->Header.SGTotal = cpu_to_le16(1);
	पूर्ण अन्यथा अणु
		c->Header.SGList = 0;
		c->Header.SGTotal = cpu_to_le16(0);
	पूर्ण
	स_नकल(c->Header.LUN.LunAddrBytes, scsi3addr, 8);

	अगर (cmd_type == TYPE_CMD) अणु
		चयन (cmd) अणु
		हाल HPSA_INQUIRY:
			/* are we trying to पढ़ो a vital product page */
			अगर (page_code & VPD_PAGE) अणु
				c->Request.CDB[1] = 0x01;
				c->Request.CDB[2] = (page_code & 0xff);
			पूर्ण
			c->Request.CDBLen = 6;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = HPSA_INQUIRY;
			c->Request.CDB[4] = size & 0xFF;
			अवरोध;
		हाल RECEIVE_DIAGNOSTIC:
			c->Request.CDBLen = 6;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = cmd;
			c->Request.CDB[1] = 1;
			c->Request.CDB[2] = 1;
			c->Request.CDB[3] = (size >> 8) & 0xFF;
			c->Request.CDB[4] = size & 0xFF;
			अवरोध;
		हाल HPSA_REPORT_LOG:
		हाल HPSA_REPORT_PHYS:
			/* Talking to controller so It's a physical command
			   mode = 00 target = 0.  Nothing to ग_लिखो.
			 */
			c->Request.CDBLen = 12;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = cmd;
			c->Request.CDB[6] = (size >> 24) & 0xFF; /* MSB */
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0xFF;
			c->Request.CDB[9] = size & 0xFF;
			अवरोध;
		हाल BMIC_SENSE_DIAG_OPTIONS:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			/* Spec says this should be BMIC_WRITE */
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_DIAG_OPTIONS;
			अवरोध;
		हाल BMIC_SET_DIAG_OPTIONS:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
					TYPE_ATTR_सूची(cmd_type,
						ATTR_SIMPLE, XFER_WRITE);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_WRITE;
			c->Request.CDB[6] = BMIC_SET_DIAG_OPTIONS;
			अवरोध;
		हाल HPSA_CACHE_FLUSH:
			c->Request.CDBLen = 12;
			c->Request.type_attr_dir =
					TYPE_ATTR_सूची(cmd_type,
						ATTR_SIMPLE, XFER_WRITE);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_WRITE;
			c->Request.CDB[6] = BMIC_CACHE_FLUSH;
			c->Request.CDB[7] = (size >> 8) & 0xFF;
			c->Request.CDB[8] = size & 0xFF;
			अवरोध;
		हाल TEST_UNIT_READY:
			c->Request.CDBLen = 6;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_NONE);
			c->Request.Timeout = 0;
			अवरोध;
		हाल HPSA_GET_RAID_MAP:
			c->Request.CDBLen = 12;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = HPSA_CISS_READ;
			c->Request.CDB[1] = cmd;
			c->Request.CDB[6] = (size >> 24) & 0xFF; /* MSB */
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0xFF;
			c->Request.CDB[9] = size & 0xFF;
			अवरोध;
		हाल BMIC_SENSE_CONTROLLER_PARAMETERS:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_CONTROLLER_PARAMETERS;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0xFF;
			अवरोध;
		हाल BMIC_IDENTIFY_PHYSICAL_DEVICE:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_IDENTIFY_PHYSICAL_DEVICE;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			अवरोध;
		हाल BMIC_SENSE_SUBSYSTEM_INFORMATION:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_SUBSYSTEM_INFORMATION;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			अवरोध;
		हाल BMIC_SENSE_STORAGE_BOX_PARAMS:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_STORAGE_BOX_PARAMS;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			अवरोध;
		हाल BMIC_IDENTIFY_CONTROLLER:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[1] = 0;
			c->Request.CDB[2] = 0;
			c->Request.CDB[3] = 0;
			c->Request.CDB[4] = 0;
			c->Request.CDB[5] = 0;
			c->Request.CDB[6] = BMIC_IDENTIFY_CONTROLLER;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			c->Request.CDB[9] = 0;
			अवरोध;
		शेष:
			dev_warn(&h->pdev->dev, "unknown command 0x%c\n", cmd);
			BUG();
		पूर्ण
	पूर्ण अन्यथा अगर (cmd_type == TYPE_MSG) अणु
		चयन (cmd) अणु

		हाल  HPSA_PHYS_TARGET_RESET:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_NONE);
			c->Request.Timeout = 0; /* Don't समय out */
			स_रखो(&c->Request.CDB[0], 0, माप(c->Request.CDB));
			c->Request.CDB[0] = HPSA_RESET;
			c->Request.CDB[1] = HPSA_TARGET_RESET_TYPE;
			/* Physical target reset needs no control bytes 4-7*/
			c->Request.CDB[4] = 0x00;
			c->Request.CDB[5] = 0x00;
			c->Request.CDB[6] = 0x00;
			c->Request.CDB[7] = 0x00;
			अवरोध;
		हाल  HPSA_DEVICE_RESET_MSG:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
				TYPE_ATTR_सूची(cmd_type, ATTR_SIMPLE, XFER_NONE);
			c->Request.Timeout = 0; /* Don't समय out */
			स_रखो(&c->Request.CDB[0], 0, माप(c->Request.CDB));
			c->Request.CDB[0] =  cmd;
			c->Request.CDB[1] = HPSA_RESET_TYPE_LUN;
			/* If bytes 4-7 are zero, it means reset the */
			/* LunID device */
			c->Request.CDB[4] = 0x00;
			c->Request.CDB[5] = 0x00;
			c->Request.CDB[6] = 0x00;
			c->Request.CDB[7] = 0x00;
			अवरोध;
		शेष:
			dev_warn(&h->pdev->dev, "unknown message type %d\n",
				cmd);
			BUG();
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(&h->pdev->dev, "unknown command type %d\n", cmd_type);
		BUG();
	पूर्ण

	चयन (GET_सूची(c->Request.type_attr_dir)) अणु
	हाल XFER_READ:
		dir = DMA_FROM_DEVICE;
		अवरोध;
	हाल XFER_WRITE:
		dir = DMA_TO_DEVICE;
		अवरोध;
	हाल XFER_NONE:
		dir = DMA_NONE;
		अवरोध;
	शेष:
		dir = DMA_BIसूचीECTIONAL;
	पूर्ण
	अगर (hpsa_map_one(h->pdev, c, buff, size, dir))
		वापस -1;
	वापस 0;
पूर्ण

/*
 * Map (physical) PCI mem पूर्णांकo (भव) kernel space
 */
अटल व्योम __iomem *remap_pci_mem(uदीर्घ base, uदीर्घ size)
अणु
	uदीर्घ page_base = ((uदीर्घ) base) & PAGE_MASK;
	uदीर्घ page_offs = ((uदीर्घ) base) - page_base;
	व्योम __iomem *page_remapped = ioremap(page_base,
		page_offs + size);

	वापस page_remapped ? (page_remapped + page_offs) : शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_next_completion(काष्ठा ctlr_info *h, u8 q)
अणु
	वापस h->access.command_completed(h, q);
पूर्ण

अटल अंतरभूत bool पूर्णांकerrupt_pending(काष्ठा ctlr_info *h)
अणु
	वापस h->access.पूर्णांकr_pending(h);
पूर्ण

अटल अंतरभूत दीर्घ पूर्णांकerrupt_not_क्रम_us(काष्ठा ctlr_info *h)
अणु
	वापस (h->access.पूर्णांकr_pending(h) == 0) ||
		(h->पूर्णांकerrupts_enabled == 0);
पूर्ण

अटल अंतरभूत पूर्णांक bad_tag(काष्ठा ctlr_info *h, u32 tag_index,
	u32 raw_tag)
अणु
	अगर (unlikely(tag_index >= h->nr_cmds)) अणु
		dev_warn(&h->pdev->dev, "bad tag 0x%08x ignored.\n", raw_tag);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम finish_cmd(काष्ठा CommandList *c)
अणु
	dial_up_lockup_detection_on_fw_flash_complete(c->h, c);
	अगर (likely(c->cmd_type == CMD_IOACCEL1 || c->cmd_type == CMD_SCSI
			|| c->cmd_type == CMD_IOACCEL2))
		complete_scsi_command(c);
	अन्यथा अगर (c->cmd_type == CMD_IOCTL_PEND || c->cmd_type == IOACCEL2_TMF)
		complete(c->रुकोing);
पूर्ण

/* process completion of an indexed ("direct lookup") command */
अटल अंतरभूत व्योम process_indexed_cmd(काष्ठा ctlr_info *h,
	u32 raw_tag)
अणु
	u32 tag_index;
	काष्ठा CommandList *c;

	tag_index = raw_tag >> सूचीECT_LOOKUP_SHIFT;
	अगर (!bad_tag(h, tag_index, raw_tag)) अणु
		c = h->cmd_pool + tag_index;
		finish_cmd(c);
	पूर्ण
पूर्ण

/* Some controllers, like p400, will give us one पूर्णांकerrupt
 * after a soft reset, even अगर we turned पूर्णांकerrupts off.
 * Only need to check क्रम this in the hpsa_xxx_discard_completions
 * functions.
 */
अटल पूर्णांक ignore_bogus_पूर्णांकerrupt(काष्ठा ctlr_info *h)
अणु
	अगर (likely(!reset_devices))
		वापस 0;

	अगर (likely(h->पूर्णांकerrupts_enabled))
		वापस 0;

	dev_info(&h->pdev->dev, "Received interrupt while interrupts disabled "
		"(known firmware bug.)  Ignoring.\n");

	वापस 1;
पूर्ण

/*
 * Convert &h->q[x] (passed to पूर्णांकerrupt handlers) back to h.
 * Relies on (h-q[x] == x) being true क्रम x such that
 * 0 <= x < MAX_REPLY_QUEUES.
 */
अटल काष्ठा ctlr_info *queue_to_hba(u8 *queue)
अणु
	वापस container_of((queue - *queue), काष्ठा ctlr_info, q[0]);
पूर्ण

अटल irqवापस_t hpsa_पूर्णांकx_discard_completions(पूर्णांक irq, व्योम *queue)
अणु
	काष्ठा ctlr_info *h = queue_to_hba(queue);
	u8 q = *(u8 *) queue;
	u32 raw_tag;

	अगर (ignore_bogus_पूर्णांकerrupt(h))
		वापस IRQ_NONE;

	अगर (पूर्णांकerrupt_not_क्रम_us(h))
		वापस IRQ_NONE;
	h->last_पूर्णांकr_बारtamp = get_jअगरfies_64();
	जबतक (पूर्णांकerrupt_pending(h)) अणु
		raw_tag = get_next_completion(h, q);
		जबतक (raw_tag != FIFO_EMPTY)
			raw_tag = next_command(h, q);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t hpsa_msix_discard_completions(पूर्णांक irq, व्योम *queue)
अणु
	काष्ठा ctlr_info *h = queue_to_hba(queue);
	u32 raw_tag;
	u8 q = *(u8 *) queue;

	अगर (ignore_bogus_पूर्णांकerrupt(h))
		वापस IRQ_NONE;

	h->last_पूर्णांकr_बारtamp = get_jअगरfies_64();
	raw_tag = get_next_completion(h, q);
	जबतक (raw_tag != FIFO_EMPTY)
		raw_tag = next_command(h, q);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t करो_hpsa_पूर्णांकr_पूर्णांकx(पूर्णांक irq, व्योम *queue)
अणु
	काष्ठा ctlr_info *h = queue_to_hba((u8 *) queue);
	u32 raw_tag;
	u8 q = *(u8 *) queue;

	अगर (पूर्णांकerrupt_not_क्रम_us(h))
		वापस IRQ_NONE;
	h->last_पूर्णांकr_बारtamp = get_jअगरfies_64();
	जबतक (पूर्णांकerrupt_pending(h)) अणु
		raw_tag = get_next_completion(h, q);
		जबतक (raw_tag != FIFO_EMPTY) अणु
			process_indexed_cmd(h, raw_tag);
			raw_tag = next_command(h, q);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t करो_hpsa_पूर्णांकr_msi(पूर्णांक irq, व्योम *queue)
अणु
	काष्ठा ctlr_info *h = queue_to_hba(queue);
	u32 raw_tag;
	u8 q = *(u8 *) queue;

	h->last_पूर्णांकr_बारtamp = get_jअगरfies_64();
	raw_tag = get_next_completion(h, q);
	जबतक (raw_tag != FIFO_EMPTY) अणु
		process_indexed_cmd(h, raw_tag);
		raw_tag = next_command(h, q);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/* Send a message CDB to the firmware. Careful, this only works
 * in simple mode, not perक्रमmant mode due to the tag lookup.
 * We only ever use this immediately after a controller reset.
 */
अटल पूर्णांक hpsa_message(काष्ठा pci_dev *pdev, अचिन्हित अक्षर opcode,
			अचिन्हित अक्षर type)
अणु
	काष्ठा Command अणु
		काष्ठा CommandListHeader CommandHeader;
		काष्ठा RequestBlock Request;
		काष्ठा ErrDescriptor ErrorDescriptor;
	पूर्ण;
	काष्ठा Command *cmd;
	अटल स्थिर माप_प्रकार cmd_sz = माप(*cmd) +
					माप(cmd->ErrorDescriptor);
	dma_addr_t paddr64;
	__le32 paddr32;
	u32 tag;
	व्योम __iomem *vaddr;
	पूर्णांक i, err;

	vaddr = pci_ioremap_bar(pdev, 0);
	अगर (vaddr == शून्य)
		वापस -ENOMEM;

	/* The Inbound Post Queue only accepts 32-bit physical addresses क्रम the
	 * CCISS commands, so they must be allocated from the lower 4GiB of
	 * memory.
	 */
	err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		iounmap(vaddr);
		वापस err;
	पूर्ण

	cmd = dma_alloc_coherent(&pdev->dev, cmd_sz, &paddr64, GFP_KERNEL);
	अगर (cmd == शून्य) अणु
		iounmap(vaddr);
		वापस -ENOMEM;
	पूर्ण

	/* This must fit, because of the 32-bit consistent DMA mask.  Also,
	 * although there's no guarantee, we assume that the address is at
	 * least 4-byte aligned (most likely, it's page-aligned).
	 */
	paddr32 = cpu_to_le32(paddr64);

	cmd->CommandHeader.ReplyQueue = 0;
	cmd->CommandHeader.SGList = 0;
	cmd->CommandHeader.SGTotal = cpu_to_le16(0);
	cmd->CommandHeader.tag = cpu_to_le64(paddr64);
	स_रखो(&cmd->CommandHeader.LUN.LunAddrBytes, 0, 8);

	cmd->Request.CDBLen = 16;
	cmd->Request.type_attr_dir =
			TYPE_ATTR_सूची(TYPE_MSG, ATTR_HEADOFQUEUE, XFER_NONE);
	cmd->Request.Timeout = 0; /* Don't समय out */
	cmd->Request.CDB[0] = opcode;
	cmd->Request.CDB[1] = type;
	स_रखो(&cmd->Request.CDB[2], 0, 14); /* rest of the CDB is reserved */
	cmd->ErrorDescriptor.Addr =
			cpu_to_le64((le32_to_cpu(paddr32) + माप(*cmd)));
	cmd->ErrorDescriptor.Len = cpu_to_le32(माप(काष्ठा ErrorInfo));

	ग_लिखोl(le32_to_cpu(paddr32), vaddr + SA5_REQUEST_PORT_OFFSET);

	क्रम (i = 0; i < HPSA_MSG_SEND_RETRY_LIMIT; i++) अणु
		tag = पढ़ोl(vaddr + SA5_REPLY_PORT_OFFSET);
		अगर ((tag & ~HPSA_SIMPLE_ERROR_BITS) == paddr64)
			अवरोध;
		msleep(HPSA_MSG_SEND_RETRY_INTERVAL_MSECS);
	पूर्ण

	iounmap(vaddr);

	/* we leak the DMA buffer here ... no choice since the controller could
	 *  still complete the command.
	 */
	अगर (i == HPSA_MSG_SEND_RETRY_LIMIT) अणु
		dev_err(&pdev->dev, "controller message %02x:%02x timed out\n",
			opcode, type);
		वापस -ETIMEDOUT;
	पूर्ण

	dma_मुक्त_coherent(&pdev->dev, cmd_sz, cmd, paddr64);

	अगर (tag & HPSA_ERROR_BIT) अणु
		dev_err(&pdev->dev, "controller message %02x:%02x failed\n",
			opcode, type);
		वापस -EIO;
	पूर्ण

	dev_info(&pdev->dev, "controller message %02x:%02x succeeded\n",
		opcode, type);
	वापस 0;
पूर्ण

#घोषणा hpsa_noop(p) hpsa_message(p, 3, 0)

अटल पूर्णांक hpsa_controller_hard_reset(काष्ठा pci_dev *pdev,
	व्योम __iomem *vaddr, u32 use_करोorbell)
अणु

	अगर (use_करोorbell) अणु
		/* For everything after the P600, the PCI घातer state method
		 * of resetting the controller करोesn't work, so we have this
		 * other way using the करोorbell रेजिस्टर.
		 */
		dev_info(&pdev->dev, "using doorbell to reset controller\n");
		ग_लिखोl(use_करोorbell, vaddr + SA5_DOORBELL);

		/* PMC hardware guys tell us we need a 10 second delay after
		 * करोorbell reset and beक्रमe any attempt to talk to the board
		 * at all to ensure that this actually works and करोesn't fall
		 * over in some weird corner हालs.
		 */
		msleep(10000);
	पूर्ण अन्यथा अणु /* Try to करो it the PCI घातer state way */

		/* Quoting from the Open CISS Specअगरication: "The Power
		 * Management Control/Status Register (CSR) controls the घातer
		 * state of the device.  The normal operating state is D0,
		 * CSR=00h.  The software off state is D3, CSR=03h.  To reset
		 * the controller, place the पूर्णांकerface device in D3 then to D0,
		 * this causes a secondary PCI reset which will reset the
		 * controller." */

		पूर्णांक rc = 0;

		dev_info(&pdev->dev, "using PCI PM to reset controller\n");

		/* enter the D3hot घातer management state */
		rc = pci_set_घातer_state(pdev, PCI_D3hot);
		अगर (rc)
			वापस rc;

		msleep(500);

		/* enter the D0 घातer management state */
		rc = pci_set_घातer_state(pdev, PCI_D0);
		अगर (rc)
			वापस rc;

		/*
		 * The P600 requires a small delay when changing states.
		 * Otherwise we may think the board did not reset and we bail.
		 * This क्रम kdump only and is particular to the P600.
		 */
		msleep(500);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम init_driver_version(अक्षर *driver_version, पूर्णांक len)
अणु
	स_रखो(driver_version, 0, len);
	म_नकलन(driver_version, HPSA " " HPSA_DRIVER_VERSION, len - 1);
पूर्ण

अटल पूर्णांक ग_लिखो_driver_ver_to_cfgtable(काष्ठा CfgTable __iomem *cfgtable)
अणु
	अक्षर *driver_version;
	पूर्णांक i, size = माप(cfgtable->driver_version);

	driver_version = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!driver_version)
		वापस -ENOMEM;

	init_driver_version(driver_version, size);
	क्रम (i = 0; i < size; i++)
		ग_लिखोb(driver_version[i], &cfgtable->driver_version[i]);
	kमुक्त(driver_version);
	वापस 0;
पूर्ण

अटल व्योम पढ़ो_driver_ver_from_cfgtable(काष्ठा CfgTable __iomem *cfgtable,
					  अचिन्हित अक्षर *driver_ver)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(cfgtable->driver_version); i++)
		driver_ver[i] = पढ़ोb(&cfgtable->driver_version[i]);
पूर्ण

अटल पूर्णांक controller_reset_failed(काष्ठा CfgTable __iomem *cfgtable)
अणु

	अक्षर *driver_ver, *old_driver_ver;
	पूर्णांक rc, size = माप(cfgtable->driver_version);

	old_driver_ver = kदो_स्मृति_array(2, size, GFP_KERNEL);
	अगर (!old_driver_ver)
		वापस -ENOMEM;
	driver_ver = old_driver_ver + size;

	/* After a reset, the 32 bytes of "driver version" in the cfgtable
	 * should have been changed, otherwise we know the reset failed.
	 */
	init_driver_version(old_driver_ver, size);
	पढ़ो_driver_ver_from_cfgtable(cfgtable, driver_ver);
	rc = !स_भेद(driver_ver, old_driver_ver, size);
	kमुक्त(old_driver_ver);
	वापस rc;
पूर्ण
/* This करोes a hard reset of the controller using PCI घातer management
 * states or the using the करोorbell रेजिस्टर.
 */
अटल पूर्णांक hpsa_kdump_hard_reset_controller(काष्ठा pci_dev *pdev, u32 board_id)
अणु
	u64 cfg_offset;
	u32 cfg_base_addr;
	u64 cfg_base_addr_index;
	व्योम __iomem *vaddr;
	अचिन्हित दीर्घ paddr;
	u32 misc_fw_support;
	पूर्णांक rc;
	काष्ठा CfgTable __iomem *cfgtable;
	u32 use_करोorbell;
	u16 command_रेजिस्टर;

	/* For controllers as old as the P600, this is very nearly
	 * the same thing as
	 *
	 * pci_save_state(pci_dev);
	 * pci_set_घातer_state(pci_dev, PCI_D3hot);
	 * pci_set_घातer_state(pci_dev, PCI_D0);
	 * pci_restore_state(pci_dev);
	 *
	 * For controllers newer than the P600, the pci घातer state
	 * method of resetting करोesn't work so we have another way
	 * using the करोorbell रेजिस्टर.
	 */

	अगर (!ctlr_is_resettable(board_id)) अणु
		dev_warn(&pdev->dev, "Controller not resettable\n");
		वापस -ENODEV;
	पूर्ण

	/* अगर controller is soft- but not hard resettable... */
	अगर (!ctlr_is_hard_resettable(board_id))
		वापस -ENOTSUPP; /* try soft reset later. */

	/* Save the PCI command रेजिस्टर */
	pci_पढ़ो_config_word(pdev, 4, &command_रेजिस्टर);
	pci_save_state(pdev);

	/* find the first memory BAR, so we can find the cfg table */
	rc = hpsa_pci_find_memory_BAR(pdev, &paddr);
	अगर (rc)
		वापस rc;
	vaddr = remap_pci_mem(paddr, 0x250);
	अगर (!vaddr)
		वापस -ENOMEM;

	/* find cfgtable in order to check अगर reset via करोorbell is supported */
	rc = hpsa_find_cfg_addrs(pdev, vaddr, &cfg_base_addr,
					&cfg_base_addr_index, &cfg_offset);
	अगर (rc)
		जाओ unmap_vaddr;
	cfgtable = remap_pci_mem(pci_resource_start(pdev,
		       cfg_base_addr_index) + cfg_offset, माप(*cfgtable));
	अगर (!cfgtable) अणु
		rc = -ENOMEM;
		जाओ unmap_vaddr;
	पूर्ण
	rc = ग_लिखो_driver_ver_to_cfgtable(cfgtable);
	अगर (rc)
		जाओ unmap_cfgtable;

	/* If reset via करोorbell रेजिस्टर is supported, use that.
	 * There are two such methods.  Favor the newest method.
	 */
	misc_fw_support = पढ़ोl(&cfgtable->misc_fw_support);
	use_करोorbell = misc_fw_support & MISC_FW_DOORBELL_RESET2;
	अगर (use_करोorbell) अणु
		use_करोorbell = DOORBELL_CTLR_RESET2;
	पूर्ण अन्यथा अणु
		use_करोorbell = misc_fw_support & MISC_FW_DOORBELL_RESET;
		अगर (use_करोorbell) अणु
			dev_warn(&pdev->dev,
				"Soft reset not supported. Firmware update is required.\n");
			rc = -ENOTSUPP; /* try soft reset */
			जाओ unmap_cfgtable;
		पूर्ण
	पूर्ण

	rc = hpsa_controller_hard_reset(pdev, vaddr, use_करोorbell);
	अगर (rc)
		जाओ unmap_cfgtable;

	pci_restore_state(pdev);
	pci_ग_लिखो_config_word(pdev, 4, command_रेजिस्टर);

	/* Some devices (notably the HP Smart Array 5i Controller)
	   need a little छोड़ो here */
	msleep(HPSA_POST_RESET_PAUSE_MSECS);

	rc = hpsa_रुको_क्रम_board_state(pdev, vaddr, BOARD_READY);
	अगर (rc) अणु
		dev_warn(&pdev->dev,
			"Failed waiting for board to become ready after hard reset\n");
		जाओ unmap_cfgtable;
	पूर्ण

	rc = controller_reset_failed(vaddr);
	अगर (rc < 0)
		जाओ unmap_cfgtable;
	अगर (rc) अणु
		dev_warn(&pdev->dev, "Unable to successfully reset "
			"controller. Will try soft reset.\n");
		rc = -ENOTSUPP;
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "board ready after hard reset.\n");
	पूर्ण

unmap_cfgtable:
	iounmap(cfgtable);

unmap_vaddr:
	iounmap(vaddr);
	वापस rc;
पूर्ण

/*
 *  We cannot पढ़ो the काष्ठाure directly, क्रम portability we must use
 *   the io functions.
 *   This is क्रम debug only.
 */
अटल व्योम prपूर्णांक_cfg_table(काष्ठा device *dev, काष्ठा CfgTable __iomem *tb)
अणु
#अगर_घोषित HPSA_DEBUG
	पूर्णांक i;
	अक्षर temp_name[17];

	dev_info(dev, "Controller Configuration information\n");
	dev_info(dev, "------------------------------------\n");
	क्रम (i = 0; i < 4; i++)
		temp_name[i] = पढ़ोb(&(tb->Signature[i]));
	temp_name[4] = '\0';
	dev_info(dev, "   Signature = %s\n", temp_name);
	dev_info(dev, "   Spec Number = %d\n", पढ़ोl(&(tb->SpecValence)));
	dev_info(dev, "   Transport methods supported = 0x%x\n",
	       पढ़ोl(&(tb->TransportSupport)));
	dev_info(dev, "   Transport methods active = 0x%x\n",
	       पढ़ोl(&(tb->TransportActive)));
	dev_info(dev, "   Requested transport Method = 0x%x\n",
	       पढ़ोl(&(tb->HostWrite.TransportRequest)));
	dev_info(dev, "   Coalesce Interrupt Delay = 0x%x\n",
	       पढ़ोl(&(tb->HostWrite.CoalIntDelay)));
	dev_info(dev, "   Coalesce Interrupt Count = 0x%x\n",
	       पढ़ोl(&(tb->HostWrite.CoalIntCount)));
	dev_info(dev, "   Max outstanding commands = %d\n",
	       पढ़ोl(&(tb->CmdsOutMax)));
	dev_info(dev, "   Bus Types = 0x%x\n", पढ़ोl(&(tb->BusTypes)));
	क्रम (i = 0; i < 16; i++)
		temp_name[i] = पढ़ोb(&(tb->ServerName[i]));
	temp_name[16] = '\0';
	dev_info(dev, "   Server Name = %s\n", temp_name);
	dev_info(dev, "   Heartbeat Counter = 0x%x\n\n\n",
		पढ़ोl(&(tb->HeartBeat)));
#पूर्ण_अगर				/* HPSA_DEBUG */
पूर्ण

अटल पूर्णांक find_PCI_BAR_index(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ pci_bar_addr)
अणु
	पूर्णांक i, offset, mem_type, bar_type;

	अगर (pci_bar_addr == PCI_BASE_ADDRESS_0)	/* looking क्रम BAR zero? */
		वापस 0;
	offset = 0;
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		bar_type = pci_resource_flags(pdev, i) & PCI_BASE_ADDRESS_SPACE;
		अगर (bar_type == PCI_BASE_ADDRESS_SPACE_IO)
			offset += 4;
		अन्यथा अणु
			mem_type = pci_resource_flags(pdev, i) &
			    PCI_BASE_ADDRESS_MEM_TYPE_MASK;
			चयन (mem_type) अणु
			हाल PCI_BASE_ADDRESS_MEM_TYPE_32:
			हाल PCI_BASE_ADDRESS_MEM_TYPE_1M:
				offset += 4;	/* 32 bit */
				अवरोध;
			हाल PCI_BASE_ADDRESS_MEM_TYPE_64:
				offset += 8;
				अवरोध;
			शेष:	/* reserved in PCI 2.2 */
				dev_warn(&pdev->dev,
				       "base address is invalid\n");
				वापस -1;
			पूर्ण
		पूर्ण
		अगर (offset == pci_bar_addr - PCI_BASE_ADDRESS_0)
			वापस i + 1;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम hpsa_disable_पूर्णांकerrupt_mode(काष्ठा ctlr_info *h)
अणु
	pci_मुक्त_irq_vectors(h->pdev);
	h->msix_vectors = 0;
पूर्ण

अटल व्योम hpsa_setup_reply_map(काष्ठा ctlr_info *h)
अणु
	स्थिर काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक queue, cpu;

	क्रम (queue = 0; queue < h->msix_vectors; queue++) अणु
		mask = pci_irq_get_affinity(h->pdev, queue);
		अगर (!mask)
			जाओ fallback;

		क्रम_each_cpu(cpu, mask)
			h->reply_map[cpu] = queue;
	पूर्ण
	वापस;

fallback:
	क्रम_each_possible_cpu(cpu)
		h->reply_map[cpu] = 0;
पूर्ण

/* If MSI/MSI-X is supported by the kernel we will try to enable it on
 * controllers that are capable. If not, we use legacy INTx mode.
 */
अटल पूर्णांक hpsa_पूर्णांकerrupt_mode(काष्ठा ctlr_info *h)
अणु
	अचिन्हित पूर्णांक flags = PCI_IRQ_LEGACY;
	पूर्णांक ret;

	/* Some boards advertise MSI but करोn't really support it */
	चयन (h->board_id) अणु
	हाल 0x40700E11:
	हाल 0x40800E11:
	हाल 0x40820E11:
	हाल 0x40830E11:
		अवरोध;
	शेष:
		ret = pci_alloc_irq_vectors(h->pdev, 1, MAX_REPLY_QUEUES,
				PCI_IRQ_MSIX | PCI_IRQ_AFFINITY);
		अगर (ret > 0) अणु
			h->msix_vectors = ret;
			वापस 0;
		पूर्ण

		flags |= PCI_IRQ_MSI;
		अवरोध;
	पूर्ण

	ret = pci_alloc_irq_vectors(h->pdev, 1, 1, flags);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_lookup_board_id(काष्ठा pci_dev *pdev, u32 *board_id,
				bool *legacy_board)
अणु
	पूर्णांक i;
	u32 subप्रणाली_venकरोr_id, subप्रणाली_device_id;

	subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	subप्रणाली_device_id = pdev->subप्रणाली_device;
	*board_id = ((subप्रणाली_device_id << 16) & 0xffff0000) |
		    subप्रणाली_venकरोr_id;

	अगर (legacy_board)
		*legacy_board = false;
	क्रम (i = 0; i < ARRAY_SIZE(products); i++)
		अगर (*board_id == products[i].board_id) अणु
			अगर (products[i].access != &SA5A_access &&
			    products[i].access != &SA5B_access)
				वापस i;
			dev_warn(&pdev->dev,
				 "legacy board ID: 0x%08x\n",
				 *board_id);
			अगर (legacy_board)
			    *legacy_board = true;
			वापस i;
		पूर्ण

	dev_warn(&pdev->dev, "unrecognized board ID: 0x%08x\n", *board_id);
	अगर (legacy_board)
		*legacy_board = true;
	वापस ARRAY_SIZE(products) - 1; /* generic unknown smart array */
पूर्ण

अटल पूर्णांक hpsa_pci_find_memory_BAR(काष्ठा pci_dev *pdev,
				    अचिन्हित दीर्घ *memory_bar)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++)
		अगर (pci_resource_flags(pdev, i) & IORESOURCE_MEM) अणु
			/* addressing mode bits alपढ़ोy हटाओd */
			*memory_bar = pci_resource_start(pdev, i);
			dev_dbg(&pdev->dev, "memory BAR = %lx\n",
				*memory_bar);
			वापस 0;
		पूर्ण
	dev_warn(&pdev->dev, "no memory BAR found\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक hpsa_रुको_क्रम_board_state(काष्ठा pci_dev *pdev, व्योम __iomem *vaddr,
				     पूर्णांक रुको_क्रम_पढ़ोy)
अणु
	पूर्णांक i, iterations;
	u32 scratchpad;
	अगर (रुको_क्रम_पढ़ोy)
		iterations = HPSA_BOARD_READY_ITERATIONS;
	अन्यथा
		iterations = HPSA_BOARD_NOT_READY_ITERATIONS;

	क्रम (i = 0; i < iterations; i++) अणु
		scratchpad = पढ़ोl(vaddr + SA5_SCRATCHPAD_OFFSET);
		अगर (रुको_क्रम_पढ़ोy) अणु
			अगर (scratchpad == HPSA_FIRMWARE_READY)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (scratchpad != HPSA_FIRMWARE_READY)
				वापस 0;
		पूर्ण
		msleep(HPSA_BOARD_READY_POLL_INTERVAL_MSECS);
	पूर्ण
	dev_warn(&pdev->dev, "board not ready, timed out.\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक hpsa_find_cfg_addrs(काष्ठा pci_dev *pdev, व्योम __iomem *vaddr,
			       u32 *cfg_base_addr, u64 *cfg_base_addr_index,
			       u64 *cfg_offset)
अणु
	*cfg_base_addr = पढ़ोl(vaddr + SA5_CTCFG_OFFSET);
	*cfg_offset = पढ़ोl(vaddr + SA5_CTMEM_OFFSET);
	*cfg_base_addr &= (u32) 0x0000ffff;
	*cfg_base_addr_index = find_PCI_BAR_index(pdev, *cfg_base_addr);
	अगर (*cfg_base_addr_index == -1) अणु
		dev_warn(&pdev->dev, "cannot find cfg_base_addr_index\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hpsa_मुक्त_cfgtables(काष्ठा ctlr_info *h)
अणु
	अगर (h->transtable) अणु
		iounmap(h->transtable);
		h->transtable = शून्य;
	पूर्ण
	अगर (h->cfgtable) अणु
		iounmap(h->cfgtable);
		h->cfgtable = शून्य;
	पूर्ण
पूर्ण

/* Find and map CISS config table and transfer table
+ * several items must be unmapped (मुक्तd) later
+ * */
अटल पूर्णांक hpsa_find_cfgtables(काष्ठा ctlr_info *h)
अणु
	u64 cfg_offset;
	u32 cfg_base_addr;
	u64 cfg_base_addr_index;
	u32 trans_offset;
	पूर्णांक rc;

	rc = hpsa_find_cfg_addrs(h->pdev, h->vaddr, &cfg_base_addr,
		&cfg_base_addr_index, &cfg_offset);
	अगर (rc)
		वापस rc;
	h->cfgtable = remap_pci_mem(pci_resource_start(h->pdev,
		       cfg_base_addr_index) + cfg_offset, माप(*h->cfgtable));
	अगर (!h->cfgtable) अणु
		dev_err(&h->pdev->dev, "Failed mapping cfgtable\n");
		वापस -ENOMEM;
	पूर्ण
	rc = ग_लिखो_driver_ver_to_cfgtable(h->cfgtable);
	अगर (rc)
		वापस rc;
	/* Find perक्रमmant mode table. */
	trans_offset = पढ़ोl(&h->cfgtable->TransMethodOffset);
	h->transtable = remap_pci_mem(pci_resource_start(h->pdev,
				cfg_base_addr_index)+cfg_offset+trans_offset,
				माप(*h->transtable));
	अगर (!h->transtable) अणु
		dev_err(&h->pdev->dev, "Failed mapping transfer table\n");
		hpsa_मुक्त_cfgtables(h);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hpsa_get_max_perf_mode_cmds(काष्ठा ctlr_info *h)
अणु
#घोषणा MIN_MAX_COMMANDS 16
	BUILD_BUG_ON(MIN_MAX_COMMANDS <= HPSA_NRESERVED_CMDS);

	h->max_commands = पढ़ोl(&h->cfgtable->MaxPerक्रमmantModeCommands);

	/* Limit commands in memory limited kdump scenario. */
	अगर (reset_devices && h->max_commands > 32)
		h->max_commands = 32;

	अगर (h->max_commands < MIN_MAX_COMMANDS) अणु
		dev_warn(&h->pdev->dev,
			"Controller reports max supported commands of %d Using %d instead. Ensure that firmware is up to date.\n",
			h->max_commands,
			MIN_MAX_COMMANDS);
		h->max_commands = MIN_MAX_COMMANDS;
	पूर्ण
पूर्ण

/* If the controller reports that the total max sg entries is greater than 512,
 * then we know that chained SG blocks work.  (Original smart arrays did not
 * support chained SG blocks and would वापस zero क्रम max sg entries.)
 */
अटल पूर्णांक hpsa_supports_chained_sg_blocks(काष्ठा ctlr_info *h)
अणु
	वापस h->maxsgentries > 512;
पूर्ण

/* Interrogate the hardware क्रम some limits:
 * max commands, max SG elements without chaining, and with chaining,
 * SG chain block size, etc.
 */
अटल व्योम hpsa_find_board_params(काष्ठा ctlr_info *h)
अणु
	hpsa_get_max_perf_mode_cmds(h);
	h->nr_cmds = h->max_commands;
	h->maxsgentries = पढ़ोl(&(h->cfgtable->MaxScatterGatherElements));
	h->fw_support = पढ़ोl(&(h->cfgtable->misc_fw_support));
	अगर (hpsa_supports_chained_sg_blocks(h)) अणु
		/* Limit in-command s/g elements to 32 save dma'able memory. */
		h->max_cmd_sg_entries = 32;
		h->chainsize = h->maxsgentries - h->max_cmd_sg_entries;
		h->maxsgentries--; /* save one क्रम chain poपूर्णांकer */
	पूर्ण अन्यथा अणु
		/*
		 * Original smart arrays supported at most 31 s/g entries
		 * embedded अंतरभूत in the command (trying to use more
		 * would lock up the controller)
		 */
		h->max_cmd_sg_entries = 31;
		h->maxsgentries = 31; /* शेष to traditional values */
		h->chainsize = 0;
	पूर्ण

	/* Find out what task management functions are supported and cache */
	h->TMFSupportFlags = पढ़ोl(&(h->cfgtable->TMFSupportFlags));
	अगर (!(HPSATMF_PHYS_TASK_ABORT & h->TMFSupportFlags))
		dev_warn(&h->pdev->dev, "Physical aborts not supported\n");
	अगर (!(HPSATMF_LOG_TASK_ABORT & h->TMFSupportFlags))
		dev_warn(&h->pdev->dev, "Logical aborts not supported\n");
	अगर (!(HPSATMF_IOACCEL_ENABLED & h->TMFSupportFlags))
		dev_warn(&h->pdev->dev, "HP SSD Smart Path aborts not supported\n");
पूर्ण

अटल अंतरभूत bool hpsa_CISS_signature_present(काष्ठा ctlr_info *h)
अणु
	अगर (!check_signature(h->cfgtable->Signature, "CISS", 4)) अणु
		dev_err(&h->pdev->dev, "not a valid CISS config table\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत व्योम hpsa_set_driver_support_bits(काष्ठा ctlr_info *h)
अणु
	u32 driver_support;

	driver_support = पढ़ोl(&(h->cfgtable->driver_support));
	/* Need to enable prefetch in the SCSI core क्रम 6400 in x86 */
#अगर_घोषित CONFIG_X86
	driver_support |= ENABLE_SCSI_PREFETCH;
#पूर्ण_अगर
	driver_support |= ENABLE_UNIT_ATTN;
	ग_लिखोl(driver_support, &(h->cfgtable->driver_support));
पूर्ण

/* Disable DMA prefetch क्रम the P600.  Otherwise an ASIC bug may result
 * in a prefetch beyond physical memory.
 */
अटल अंतरभूत व्योम hpsa_p600_dma_prefetch_quirk(काष्ठा ctlr_info *h)
अणु
	u32 dma_prefetch;

	अगर (h->board_id != 0x3225103C)
		वापस;
	dma_prefetch = पढ़ोl(h->vaddr + I2O_DMA1_CFG);
	dma_prefetch |= 0x8000;
	ग_लिखोl(dma_prefetch, h->vaddr + I2O_DMA1_CFG);
पूर्ण

अटल पूर्णांक hpsa_रुको_क्रम_clear_event_notअगरy_ack(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;
	u32 करोorbell_value;
	अचिन्हित दीर्घ flags;
	/* रुको until the clear_event_notअगरy bit 6 is cleared by controller. */
	क्रम (i = 0; i < MAX_CLEAR_EVENT_WAIT; i++) अणु
		spin_lock_irqsave(&h->lock, flags);
		करोorbell_value = पढ़ोl(h->vaddr + SA5_DOORBELL);
		spin_unlock_irqrestore(&h->lock, flags);
		अगर (!(करोorbell_value & DOORBELL_CLEAR_EVENTS))
			जाओ करोne;
		/* delay and try again */
		msleep(CLEAR_EVENT_WAIT_INTERVAL);
	पूर्ण
	वापस -ENODEV;
करोne:
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_रुको_क्रम_mode_change_ack(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;
	u32 करोorbell_value;
	अचिन्हित दीर्घ flags;

	/* under certain very rare conditions, this can take aजबतक.
	 * (e.g.: hot replace a failed 144GB drive in a RAID 5 set right
	 * as we enter this code.)
	 */
	क्रम (i = 0; i < MAX_MODE_CHANGE_WAIT; i++) अणु
		अगर (h->हटाओ_in_progress)
			जाओ करोne;
		spin_lock_irqsave(&h->lock, flags);
		करोorbell_value = पढ़ोl(h->vaddr + SA5_DOORBELL);
		spin_unlock_irqrestore(&h->lock, flags);
		अगर (!(करोorbell_value & CFGTBL_ChangeReq))
			जाओ करोne;
		/* delay and try again */
		msleep(MODE_CHANGE_WAIT_INTERVAL);
	पूर्ण
	वापस -ENODEV;
करोne:
	वापस 0;
पूर्ण

/* वापस -ENODEV or other reason on error, 0 on success */
अटल पूर्णांक hpsa_enter_simple_mode(काष्ठा ctlr_info *h)
अणु
	u32 trans_support;

	trans_support = पढ़ोl(&(h->cfgtable->TransportSupport));
	अगर (!(trans_support & SIMPLE_MODE))
		वापस -ENOTSUPP;

	h->max_commands = पढ़ोl(&(h->cfgtable->CmdsOutMax));

	/* Update the field, and then ring the करोorbell */
	ग_लिखोl(CFGTBL_Trans_Simple, &(h->cfgtable->HostWrite.TransportRequest));
	ग_लिखोl(0, &h->cfgtable->HostWrite.command_pool_addr_hi);
	ग_लिखोl(CFGTBL_ChangeReq, h->vaddr + SA5_DOORBELL);
	अगर (hpsa_रुको_क्रम_mode_change_ack(h))
		जाओ error;
	prपूर्णांक_cfg_table(&h->pdev->dev, h->cfgtable);
	अगर (!(पढ़ोl(&(h->cfgtable->TransportActive)) & CFGTBL_Trans_Simple))
		जाओ error;
	h->transMethod = CFGTBL_Trans_Simple;
	वापस 0;
error:
	dev_err(&h->pdev->dev, "failed to enter simple mode\n");
	वापस -ENODEV;
पूर्ण

/* मुक्त items allocated or mapped by hpsa_pci_init */
अटल व्योम hpsa_मुक्त_pci_init(काष्ठा ctlr_info *h)
अणु
	hpsa_मुक्त_cfgtables(h);			/* pci_init 4 */
	iounmap(h->vaddr);			/* pci_init 3 */
	h->vaddr = शून्य;
	hpsa_disable_पूर्णांकerrupt_mode(h);		/* pci_init 2 */
	/*
	 * call pci_disable_device beक्रमe pci_release_regions per
	 * Documentation/driver-api/pci/pci.rst
	 */
	pci_disable_device(h->pdev);		/* pci_init 1 */
	pci_release_regions(h->pdev);		/* pci_init 2 */
पूर्ण

/* several items must be मुक्तd later */
अटल पूर्णांक hpsa_pci_init(काष्ठा ctlr_info *h)
अणु
	पूर्णांक prod_index, err;
	bool legacy_board;

	prod_index = hpsa_lookup_board_id(h->pdev, &h->board_id, &legacy_board);
	अगर (prod_index < 0)
		वापस prod_index;
	h->product_name = products[prod_index].product_name;
	h->access = *(products[prod_index].access);
	h->legacy_board = legacy_board;
	pci_disable_link_state(h->pdev, PCIE_LINK_STATE_L0S |
			       PCIE_LINK_STATE_L1 | PCIE_LINK_STATE_CLKPM);

	err = pci_enable_device(h->pdev);
	अगर (err) अणु
		dev_err(&h->pdev->dev, "failed to enable PCI device\n");
		pci_disable_device(h->pdev);
		वापस err;
	पूर्ण

	err = pci_request_regions(h->pdev, HPSA);
	अगर (err) अणु
		dev_err(&h->pdev->dev,
			"failed to obtain PCI resources\n");
		pci_disable_device(h->pdev);
		वापस err;
	पूर्ण

	pci_set_master(h->pdev);

	err = hpsa_पूर्णांकerrupt_mode(h);
	अगर (err)
		जाओ clean1;

	/* setup mapping between CPU and reply queue */
	hpsa_setup_reply_map(h);

	err = hpsa_pci_find_memory_BAR(h->pdev, &h->paddr);
	अगर (err)
		जाओ clean2;	/* पूर्णांकmode+region, pci */
	h->vaddr = remap_pci_mem(h->paddr, 0x250);
	अगर (!h->vaddr) अणु
		dev_err(&h->pdev->dev, "failed to remap PCI mem\n");
		err = -ENOMEM;
		जाओ clean2;	/* पूर्णांकmode+region, pci */
	पूर्ण
	err = hpsa_रुको_क्रम_board_state(h->pdev, h->vaddr, BOARD_READY);
	अगर (err)
		जाओ clean3;	/* vaddr, पूर्णांकmode+region, pci */
	err = hpsa_find_cfgtables(h);
	अगर (err)
		जाओ clean3;	/* vaddr, पूर्णांकmode+region, pci */
	hpsa_find_board_params(h);

	अगर (!hpsa_CISS_signature_present(h)) अणु
		err = -ENODEV;
		जाओ clean4;	/* cfgtables, vaddr, पूर्णांकmode+region, pci */
	पूर्ण
	hpsa_set_driver_support_bits(h);
	hpsa_p600_dma_prefetch_quirk(h);
	err = hpsa_enter_simple_mode(h);
	अगर (err)
		जाओ clean4;	/* cfgtables, vaddr, पूर्णांकmode+region, pci */
	वापस 0;

clean4:	/* cfgtables, vaddr, पूर्णांकmode+region, pci */
	hpsa_मुक्त_cfgtables(h);
clean3:	/* vaddr, पूर्णांकmode+region, pci */
	iounmap(h->vaddr);
	h->vaddr = शून्य;
clean2:	/* पूर्णांकmode+region, pci */
	hpsa_disable_पूर्णांकerrupt_mode(h);
clean1:
	/*
	 * call pci_disable_device beक्रमe pci_release_regions per
	 * Documentation/driver-api/pci/pci.rst
	 */
	pci_disable_device(h->pdev);
	pci_release_regions(h->pdev);
	वापस err;
पूर्ण

अटल व्योम hpsa_hba_inquiry(काष्ठा ctlr_info *h)
अणु
	पूर्णांक rc;

#घोषणा HBA_INQUIRY_BYTE_COUNT 64
	h->hba_inquiry_data = kदो_स्मृति(HBA_INQUIRY_BYTE_COUNT, GFP_KERNEL);
	अगर (!h->hba_inquiry_data)
		वापस;
	rc = hpsa_scsi_करो_inquiry(h, RAID_CTLR_LUNID, 0,
		h->hba_inquiry_data, HBA_INQUIRY_BYTE_COUNT);
	अगर (rc != 0) अणु
		kमुक्त(h->hba_inquiry_data);
		h->hba_inquiry_data = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hpsa_init_reset_devices(काष्ठा pci_dev *pdev, u32 board_id)
अणु
	पूर्णांक rc, i;
	व्योम __iomem *vaddr;

	अगर (!reset_devices)
		वापस 0;

	/* kdump kernel is loading, we करोn't know in which state is
	 * the pci पूर्णांकerface. The dev->enable_cnt is equal zero
	 * so we call enable+disable, रुको a जबतक and चयन it on.
	 */
	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		dev_warn(&pdev->dev, "Failed to enable PCI device\n");
		वापस -ENODEV;
	पूर्ण
	pci_disable_device(pdev);
	msleep(260);			/* a अक्रमomly chosen number */
	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		dev_warn(&pdev->dev, "failed to enable device.\n");
		वापस -ENODEV;
	पूर्ण

	pci_set_master(pdev);

	vaddr = pci_ioremap_bar(pdev, 0);
	अगर (vaddr == शून्य) अणु
		rc = -ENOMEM;
		जाओ out_disable;
	पूर्ण
	ग_लिखोl(SA5_INTR_OFF, vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	iounmap(vaddr);

	/* Reset the controller with a PCI घातer-cycle or via करोorbell */
	rc = hpsa_kdump_hard_reset_controller(pdev, board_id);

	/* -ENOTSUPP here means we cannot reset the controller
	 * but it's alपढ़ोy (and still) up and running in
	 * "performant mode".  Or, it might be 640x, which can't reset
	 * due to concerns about shared bbwc between 6402/6404 pair.
	 */
	अगर (rc)
		जाओ out_disable;

	/* Now try to get the controller to respond to a no-op */
	dev_info(&pdev->dev, "Waiting for controller to respond to no-op\n");
	क्रम (i = 0; i < HPSA_POST_RESET_NOOP_RETRIES; i++) अणु
		अगर (hpsa_noop(pdev) == 0)
			अवरोध;
		अन्यथा
			dev_warn(&pdev->dev, "no-op failed%s\n",
					(i < 11 ? "; re-trying" : ""));
	पूर्ण

out_disable:

	pci_disable_device(pdev);
	वापस rc;
पूर्ण

अटल व्योम hpsa_मुक्त_cmd_pool(काष्ठा ctlr_info *h)
अणु
	kमुक्त(h->cmd_pool_bits);
	h->cmd_pool_bits = शून्य;
	अगर (h->cmd_pool) अणु
		dma_मुक्त_coherent(&h->pdev->dev,
				h->nr_cmds * माप(काष्ठा CommandList),
				h->cmd_pool,
				h->cmd_pool_dhandle);
		h->cmd_pool = शून्य;
		h->cmd_pool_dhandle = 0;
	पूर्ण
	अगर (h->errinfo_pool) अणु
		dma_मुक्त_coherent(&h->pdev->dev,
				h->nr_cmds * माप(काष्ठा ErrorInfo),
				h->errinfo_pool,
				h->errinfo_pool_dhandle);
		h->errinfo_pool = शून्य;
		h->errinfo_pool_dhandle = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक hpsa_alloc_cmd_pool(काष्ठा ctlr_info *h)
अणु
	h->cmd_pool_bits = kसुस्मृति(DIV_ROUND_UP(h->nr_cmds, BITS_PER_LONG),
				   माप(अचिन्हित दीर्घ),
				   GFP_KERNEL);
	h->cmd_pool = dma_alloc_coherent(&h->pdev->dev,
		    h->nr_cmds * माप(*h->cmd_pool),
		    &h->cmd_pool_dhandle, GFP_KERNEL);
	h->errinfo_pool = dma_alloc_coherent(&h->pdev->dev,
		    h->nr_cmds * माप(*h->errinfo_pool),
		    &h->errinfo_pool_dhandle, GFP_KERNEL);
	अगर ((h->cmd_pool_bits == शून्य)
	    || (h->cmd_pool == शून्य)
	    || (h->errinfo_pool == शून्य)) अणु
		dev_err(&h->pdev->dev, "out of memory in %s", __func__);
		जाओ clean_up;
	पूर्ण
	hpsa_preinitialize_commands(h);
	वापस 0;
clean_up:
	hpsa_मुक्त_cmd_pool(h);
	वापस -ENOMEM;
पूर्ण

/* clear affinity hपूर्णांकs and मुक्त MSI-X, MSI, or legacy INTx vectors */
अटल व्योम hpsa_मुक्त_irqs(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;
	पूर्णांक irq_vector = 0;

	अगर (hpsa_simple_mode)
		irq_vector = h->पूर्णांकr_mode;

	अगर (!h->msix_vectors || h->पूर्णांकr_mode != PERF_MODE_INT) अणु
		/* Single reply queue, only one irq to मुक्त */
		मुक्त_irq(pci_irq_vector(h->pdev, irq_vector),
				&h->q[h->पूर्णांकr_mode]);
		h->q[h->पूर्णांकr_mode] = 0;
		वापस;
	पूर्ण

	क्रम (i = 0; i < h->msix_vectors; i++) अणु
		मुक्त_irq(pci_irq_vector(h->pdev, i), &h->q[i]);
		h->q[i] = 0;
	पूर्ण
	क्रम (; i < MAX_REPLY_QUEUES; i++)
		h->q[i] = 0;
पूर्ण

/* वापसs 0 on success; cleans up and वापसs -Enn on error */
अटल पूर्णांक hpsa_request_irqs(काष्ठा ctlr_info *h,
	irqवापस_t (*msixhandler)(पूर्णांक, व्योम *),
	irqवापस_t (*पूर्णांकxhandler)(पूर्णांक, व्योम *))
अणु
	पूर्णांक rc, i;
	पूर्णांक irq_vector = 0;

	अगर (hpsa_simple_mode)
		irq_vector = h->पूर्णांकr_mode;

	/*
	 * initialize h->q[x] = x so that पूर्णांकerrupt handlers know which
	 * queue to process.
	 */
	क्रम (i = 0; i < MAX_REPLY_QUEUES; i++)
		h->q[i] = (u8) i;

	अगर (h->पूर्णांकr_mode == PERF_MODE_INT && h->msix_vectors > 0) अणु
		/* If perक्रमmant mode and MSI-X, use multiple reply queues */
		क्रम (i = 0; i < h->msix_vectors; i++) अणु
			प्र_लिखो(h->पूर्णांकrname[i], "%s-msix%d", h->devname, i);
			rc = request_irq(pci_irq_vector(h->pdev, i), msixhandler,
					0, h->पूर्णांकrname[i],
					&h->q[i]);
			अगर (rc) अणु
				पूर्णांक j;

				dev_err(&h->pdev->dev,
					"failed to get irq %d for %s\n",
				       pci_irq_vector(h->pdev, i), h->devname);
				क्रम (j = 0; j < i; j++) अणु
					मुक्त_irq(pci_irq_vector(h->pdev, j), &h->q[j]);
					h->q[j] = 0;
				पूर्ण
				क्रम (; j < MAX_REPLY_QUEUES; j++)
					h->q[j] = 0;
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Use single reply pool */
		अगर (h->msix_vectors > 0 || h->pdev->msi_enabled) अणु
			प्र_लिखो(h->पूर्णांकrname[0], "%s-msi%s", h->devname,
				h->msix_vectors ? "x" : "");
			rc = request_irq(pci_irq_vector(h->pdev, irq_vector),
				msixhandler, 0,
				h->पूर्णांकrname[0],
				&h->q[h->पूर्णांकr_mode]);
		पूर्ण अन्यथा अणु
			प्र_लिखो(h->पूर्णांकrname[h->पूर्णांकr_mode],
				"%s-intx", h->devname);
			rc = request_irq(pci_irq_vector(h->pdev, irq_vector),
				पूर्णांकxhandler, IRQF_SHARED,
				h->पूर्णांकrname[0],
				&h->q[h->पूर्णांकr_mode]);
		पूर्ण
	पूर्ण
	अगर (rc) अणु
		dev_err(&h->pdev->dev, "failed to get irq %d for %s\n",
		       pci_irq_vector(h->pdev, irq_vector), h->devname);
		hpsa_मुक्त_irqs(h);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_kdump_soft_reset(काष्ठा ctlr_info *h)
अणु
	पूर्णांक rc;
	hpsa_send_host_reset(h, HPSA_RESET_TYPE_CONTROLLER);

	dev_info(&h->pdev->dev, "Waiting for board to soft reset.\n");
	rc = hpsa_रुको_क्रम_board_state(h->pdev, h->vaddr, BOARD_NOT_READY);
	अगर (rc) अणु
		dev_warn(&h->pdev->dev, "Soft reset had no effect.\n");
		वापस rc;
	पूर्ण

	dev_info(&h->pdev->dev, "Board reset, awaiting READY status.\n");
	rc = hpsa_रुको_क्रम_board_state(h->pdev, h->vaddr, BOARD_READY);
	अगर (rc) अणु
		dev_warn(&h->pdev->dev, "Board failed to become ready "
			"after soft reset.\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hpsa_मुक्त_reply_queues(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < h->nreply_queues; i++) अणु
		अगर (!h->reply_queue[i].head)
			जारी;
		dma_मुक्त_coherent(&h->pdev->dev,
					h->reply_queue_size,
					h->reply_queue[i].head,
					h->reply_queue[i].busaddr);
		h->reply_queue[i].head = शून्य;
		h->reply_queue[i].busaddr = 0;
	पूर्ण
	h->reply_queue_size = 0;
पूर्ण

अटल व्योम hpsa_unकरो_allocations_after_kdump_soft_reset(काष्ठा ctlr_info *h)
अणु
	hpsa_मुक्त_perक्रमmant_mode(h);		/* init_one 7 */
	hpsa_मुक्त_sg_chain_blocks(h);		/* init_one 6 */
	hpsa_मुक्त_cmd_pool(h);			/* init_one 5 */
	hpsa_मुक्त_irqs(h);			/* init_one 4 */
	scsi_host_put(h->scsi_host);		/* init_one 3 */
	h->scsi_host = शून्य;			/* init_one 3 */
	hpsa_मुक्त_pci_init(h);			/* init_one 2_5 */
	मुक्त_percpu(h->lockup_detected);	/* init_one 2 */
	h->lockup_detected = शून्य;		/* init_one 2 */
	अगर (h->resubmit_wq) अणु
		destroy_workqueue(h->resubmit_wq);	/* init_one 1 */
		h->resubmit_wq = शून्य;
	पूर्ण
	अगर (h->rescan_ctlr_wq) अणु
		destroy_workqueue(h->rescan_ctlr_wq);
		h->rescan_ctlr_wq = शून्य;
	पूर्ण
	अगर (h->monitor_ctlr_wq) अणु
		destroy_workqueue(h->monitor_ctlr_wq);
		h->monitor_ctlr_wq = शून्य;
	पूर्ण

	kमुक्त(h);				/* init_one 1 */
पूर्ण

/* Called when controller lockup detected. */
अटल व्योम fail_all_outstanding_cmds(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i, refcount;
	काष्ठा CommandList *c;
	पूर्णांक failcount = 0;

	flush_workqueue(h->resubmit_wq); /* ensure all cmds are fully built */
	क्रम (i = 0; i < h->nr_cmds; i++) अणु
		c = h->cmd_pool + i;
		refcount = atomic_inc_वापस(&c->refcount);
		अगर (refcount > 1) अणु
			c->err_info->CommandStatus = CMD_CTLR_LOCKUP;
			finish_cmd(c);
			atomic_dec(&h->commands_outstanding);
			failcount++;
		पूर्ण
		cmd_मुक्त(h, c);
	पूर्ण
	dev_warn(&h->pdev->dev,
		"failed %d commands in fail_all\n", failcount);
पूर्ण

अटल व्योम set_lockup_detected_क्रम_all_cpus(काष्ठा ctlr_info *h, u32 value)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		u32 *lockup_detected;
		lockup_detected = per_cpu_ptr(h->lockup_detected, cpu);
		*lockup_detected = value;
	पूर्ण
	wmb(); /* be sure the per-cpu variables are out to memory */
पूर्ण

अटल व्योम controller_lockup_detected(काष्ठा ctlr_info *h)
अणु
	अचिन्हित दीर्घ flags;
	u32 lockup_detected;

	h->access.set_पूर्णांकr_mask(h, HPSA_INTR_OFF);
	spin_lock_irqsave(&h->lock, flags);
	lockup_detected = पढ़ोl(h->vaddr + SA5_SCRATCHPAD_OFFSET);
	अगर (!lockup_detected) अणु
		/* no heartbeat, but controller gave us a zero. */
		dev_warn(&h->pdev->dev,
			"lockup detected after %d but scratchpad register is zero\n",
			h->heartbeat_sample_पूर्णांकerval / HZ);
		lockup_detected = 0xffffffff;
	पूर्ण
	set_lockup_detected_क्रम_all_cpus(h, lockup_detected);
	spin_unlock_irqrestore(&h->lock, flags);
	dev_warn(&h->pdev->dev, "Controller lockup detected: 0x%08x after %d\n",
			lockup_detected, h->heartbeat_sample_पूर्णांकerval / HZ);
	अगर (lockup_detected == 0xffff0000) अणु
		dev_warn(&h->pdev->dev, "Telling controller to do a CHKPT\n");
		ग_लिखोl(DOORBELL_GENERATE_CHKPT, h->vaddr + SA5_DOORBELL);
	पूर्ण
	pci_disable_device(h->pdev);
	fail_all_outstanding_cmds(h);
पूर्ण

अटल पूर्णांक detect_controller_lockup(काष्ठा ctlr_info *h)
अणु
	u64 now;
	u32 heartbeat;
	अचिन्हित दीर्घ flags;

	now = get_jअगरfies_64();
	/* If we've received an interrupt recently, we're ok. */
	अगर (समय_after64(h->last_पूर्णांकr_बारtamp +
				(h->heartbeat_sample_पूर्णांकerval), now))
		वापस false;

	/*
	 * If we've already checked the heartbeat recently, we're ok.
	 * This could happen अगर someone sends us a संकेत. We
	 * otherwise करोn't care about संकेतs in this thपढ़ो.
	 */
	अगर (समय_after64(h->last_heartbeat_बारtamp +
				(h->heartbeat_sample_पूर्णांकerval), now))
		वापस false;

	/* If heartbeat has not changed since we last looked, we're not ok. */
	spin_lock_irqsave(&h->lock, flags);
	heartbeat = पढ़ोl(&h->cfgtable->HeartBeat);
	spin_unlock_irqrestore(&h->lock, flags);
	अगर (h->last_heartbeat == heartbeat) अणु
		controller_lockup_detected(h);
		वापस true;
	पूर्ण

	/* We're ok. */
	h->last_heartbeat = heartbeat;
	h->last_heartbeat_बारtamp = now;
	वापस false;
पूर्ण

/*
 * Set ioaccel status क्रम all ioaccel volumes.
 *
 * Called from monitor controller worker (hpsa_event_monitor_worker)
 *
 * A Volume (or Volumes that comprise an Array set) may be undergoing a
 * transक्रमmation, so we will be turning off ioaccel क्रम all volumes that
 * make up the Array.
 */
अटल व्योम hpsa_set_ioaccel_status(काष्ठा ctlr_info *h)
अणु
	पूर्णांक rc;
	पूर्णांक i;
	u8 ioaccel_status;
	अचिन्हित अक्षर *buf;
	काष्ठा hpsa_scsi_dev_t *device;

	अगर (!h)
		वापस;

	buf = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!buf)
		वापस;

	/*
	 * Run through current device list used during I/O requests.
	 */
	क्रम (i = 0; i < h->ndevices; i++) अणु
		पूर्णांक offload_to_be_enabled = 0;
		पूर्णांक offload_config = 0;

		device = h->dev[i];

		अगर (!device)
			जारी;
		अगर (!hpsa_vpd_page_supported(h, device->scsi3addr,
						HPSA_VPD_LV_IOACCEL_STATUS))
			जारी;

		स_रखो(buf, 0, 64);

		rc = hpsa_scsi_करो_inquiry(h, device->scsi3addr,
					VPD_PAGE | HPSA_VPD_LV_IOACCEL_STATUS,
					buf, 64);
		अगर (rc != 0)
			जारी;

		ioaccel_status = buf[IOACCEL_STATUS_BYTE];

		/*
		 * Check अगर offload is still configured on
		 */
		offload_config =
				!!(ioaccel_status & OFFLOAD_CONFIGURED_BIT);
		/*
		 * If offload is configured on, check to see अगर ioaccel
		 * needs to be enabled.
		 */
		अगर (offload_config)
			offload_to_be_enabled =
				!!(ioaccel_status & OFFLOAD_ENABLED_BIT);

		/*
		 * If ioaccel is to be re-enabled, re-enable later during the
		 * scan operation so the driver can get a fresh raidmap
		 * beक्रमe turning ioaccel back on.
		 */
		अगर (offload_to_be_enabled)
			जारी;

		/*
		 * Immediately turn off ioaccel क्रम any volume the
		 * controller tells us to. Some of the reasons could be:
		 *    transक्रमmation - change to the LVs of an Array.
		 *    degraded volume - component failure
		 */
		hpsa_turn_off_ioaccel_क्रम_device(device);
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल व्योम hpsa_ack_ctlr_events(काष्ठा ctlr_info *h)
अणु
	अक्षर *event_type;

	अगर (!(h->fw_support & MISC_FW_EVENT_NOTIFY))
		वापस;

	/* Ask the controller to clear the events we're handling. */
	अगर ((h->transMethod & (CFGTBL_Trans_io_accel1
			| CFGTBL_Trans_io_accel2)) &&
		(h->events & HPSA_EVENT_NOTIFY_ACCEL_IO_PATH_STATE_CHANGE ||
		 h->events & HPSA_EVENT_NOTIFY_ACCEL_IO_PATH_CONFIG_CHANGE)) अणु

		अगर (h->events & HPSA_EVENT_NOTIFY_ACCEL_IO_PATH_STATE_CHANGE)
			event_type = "state change";
		अगर (h->events & HPSA_EVENT_NOTIFY_ACCEL_IO_PATH_CONFIG_CHANGE)
			event_type = "configuration change";
		/* Stop sending new RAID offload reqs via the IO accelerator */
		scsi_block_requests(h->scsi_host);
		hpsa_set_ioaccel_status(h);
		hpsa_drain_accel_commands(h);
		/* Set 'accelerator path config change' bit */
		dev_warn(&h->pdev->dev,
			"Acknowledging event: 0x%08x (HP SSD Smart Path %s)\n",
			h->events, event_type);
		ग_लिखोl(h->events, &(h->cfgtable->clear_event_notअगरy));
		/* Set the "clear event notify field update" bit 6 */
		ग_लिखोl(DOORBELL_CLEAR_EVENTS, h->vaddr + SA5_DOORBELL);
		/* Wait until ctlr clears 'clear event notify field', bit 6 */
		hpsa_रुको_क्रम_clear_event_notअगरy_ack(h);
		scsi_unblock_requests(h->scsi_host);
	पूर्ण अन्यथा अणु
		/* Acknowledge controller notअगरication events. */
		ग_लिखोl(h->events, &(h->cfgtable->clear_event_notअगरy));
		ग_लिखोl(DOORBELL_CLEAR_EVENTS, h->vaddr + SA5_DOORBELL);
		hpsa_रुको_क्रम_clear_event_notअगरy_ack(h);
	पूर्ण
	वापस;
पूर्ण

/* Check a रेजिस्टर on the controller to see अगर there are configuration
 * changes (added/changed/हटाओd logical drives, etc.) which mean that
 * we should rescan the controller क्रम devices.
 * Also check flag क्रम driver-initiated rescan.
 */
अटल पूर्णांक hpsa_ctlr_needs_rescan(काष्ठा ctlr_info *h)
अणु
	अगर (h->drv_req_rescan) अणु
		h->drv_req_rescan = 0;
		वापस 1;
	पूर्ण

	अगर (!(h->fw_support & MISC_FW_EVENT_NOTIFY))
		वापस 0;

	h->events = पढ़ोl(&(h->cfgtable->event_notअगरy));
	वापस h->events & RESCAN_REQUIRED_EVENT_BITS;
पूर्ण

/*
 * Check अगर any of the offline devices have become पढ़ोy
 */
अटल पूर्णांक hpsa_offline_devices_पढ़ोy(काष्ठा ctlr_info *h)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा offline_device_entry *d;
	काष्ठा list_head *this, *पंचांगp;

	spin_lock_irqsave(&h->offline_device_lock, flags);
	list_क्रम_each_safe(this, पंचांगp, &h->offline_device_list) अणु
		d = list_entry(this, काष्ठा offline_device_entry,
				offline_list);
		spin_unlock_irqrestore(&h->offline_device_lock, flags);
		अगर (!hpsa_volume_offline(h, d->scsi3addr)) अणु
			spin_lock_irqsave(&h->offline_device_lock, flags);
			list_del(&d->offline_list);
			spin_unlock_irqrestore(&h->offline_device_lock, flags);
			वापस 1;
		पूर्ण
		spin_lock_irqsave(&h->offline_device_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&h->offline_device_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक hpsa_luns_changed(काष्ठा ctlr_info *h)
अणु
	पूर्णांक rc = 1; /* assume there are changes */
	काष्ठा ReportLUNdata *logdev = शून्य;

	/* अगर we can't find out अगर lun data has changed,
	 * assume that it has.
	 */

	अगर (!h->lastlogicals)
		वापस rc;

	logdev = kzalloc(माप(*logdev), GFP_KERNEL);
	अगर (!logdev)
		वापस rc;

	अगर (hpsa_scsi_करो_report_luns(h, 1, logdev, माप(*logdev), 0)) अणु
		dev_warn(&h->pdev->dev,
			"report luns failed, can't track lun changes.\n");
		जाओ out;
	पूर्ण
	अगर (स_भेद(logdev, h->lastlogicals, माप(*logdev))) अणु
		dev_info(&h->pdev->dev,
			"Lun changes detected.\n");
		स_नकल(h->lastlogicals, logdev, माप(*logdev));
		जाओ out;
	पूर्ण अन्यथा
		rc = 0; /* no changes detected. */
out:
	kमुक्त(logdev);
	वापस rc;
पूर्ण

अटल व्योम hpsa_perक्रमm_rescan(काष्ठा ctlr_info *h)
अणु
	काष्ठा Scsi_Host *sh = शून्य;
	अचिन्हित दीर्घ flags;

	/*
	 * Do the scan after the reset
	 */
	spin_lock_irqsave(&h->reset_lock, flags);
	अगर (h->reset_in_progress) अणु
		h->drv_req_rescan = 1;
		spin_unlock_irqrestore(&h->reset_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&h->reset_lock, flags);

	sh = scsi_host_get(h->scsi_host);
	अगर (sh != शून्य) अणु
		hpsa_scan_start(sh);
		scsi_host_put(sh);
		h->drv_req_rescan = 0;
	पूर्ण
पूर्ण

/*
 * watch क्रम controller events
 */
अटल व्योम hpsa_event_monitor_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ctlr_info *h = container_of(to_delayed_work(work),
					काष्ठा ctlr_info, event_monitor_work);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&h->lock, flags);
	अगर (h->हटाओ_in_progress) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&h->lock, flags);

	अगर (hpsa_ctlr_needs_rescan(h)) अणु
		hpsa_ack_ctlr_events(h);
		hpsa_perक्रमm_rescan(h);
	पूर्ण

	spin_lock_irqsave(&h->lock, flags);
	अगर (!h->हटाओ_in_progress)
		queue_delayed_work(h->monitor_ctlr_wq, &h->event_monitor_work,
				HPSA_EVENT_MONITOR_INTERVAL);
	spin_unlock_irqrestore(&h->lock, flags);
पूर्ण

अटल व्योम hpsa_rescan_ctlr_worker(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ctlr_info *h = container_of(to_delayed_work(work),
					काष्ठा ctlr_info, rescan_ctlr_work);

	spin_lock_irqsave(&h->lock, flags);
	अगर (h->हटाओ_in_progress) अणु
		spin_unlock_irqrestore(&h->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&h->lock, flags);

	अगर (h->drv_req_rescan || hpsa_offline_devices_पढ़ोy(h)) अणु
		hpsa_perक्रमm_rescan(h);
	पूर्ण अन्यथा अगर (h->discovery_polling) अणु
		अगर (hpsa_luns_changed(h)) अणु
			dev_info(&h->pdev->dev,
				"driver discovery polling rescan.\n");
			hpsa_perक्रमm_rescan(h);
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&h->lock, flags);
	अगर (!h->हटाओ_in_progress)
		queue_delayed_work(h->rescan_ctlr_wq, &h->rescan_ctlr_work,
				h->heartbeat_sample_पूर्णांकerval);
	spin_unlock_irqrestore(&h->lock, flags);
पूर्ण

अटल व्योम hpsa_monitor_ctlr_worker(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ctlr_info *h = container_of(to_delayed_work(work),
					काष्ठा ctlr_info, monitor_ctlr_work);

	detect_controller_lockup(h);
	अगर (lockup_detected(h))
		वापस;

	spin_lock_irqsave(&h->lock, flags);
	अगर (!h->हटाओ_in_progress)
		queue_delayed_work(h->monitor_ctlr_wq, &h->monitor_ctlr_work,
				h->heartbeat_sample_पूर्णांकerval);
	spin_unlock_irqrestore(&h->lock, flags);
पूर्ण

अटल काष्ठा workqueue_काष्ठा *hpsa_create_controller_wq(काष्ठा ctlr_info *h,
						अक्षर *name)
अणु
	काष्ठा workqueue_काष्ठा *wq = शून्य;

	wq = alloc_ordered_workqueue("%s_%d_hpsa", 0, name, h->ctlr);
	अगर (!wq)
		dev_err(&h->pdev->dev, "failed to create %s workqueue\n", name);

	वापस wq;
पूर्ण

अटल व्योम hpda_मुक्त_ctlr_info(काष्ठा ctlr_info *h)
अणु
	kमुक्त(h->reply_map);
	kमुक्त(h);
पूर्ण

अटल काष्ठा ctlr_info *hpda_alloc_ctlr_info(व्योम)
अणु
	काष्ठा ctlr_info *h;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस शून्य;

	h->reply_map = kसुस्मृति(nr_cpu_ids, माप(*h->reply_map), GFP_KERNEL);
	अगर (!h->reply_map) अणु
		kमुक्त(h);
		वापस शून्य;
	पूर्ण
	वापस h;
पूर्ण

अटल पूर्णांक hpsa_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;
	काष्ठा ctlr_info *h;
	पूर्णांक try_soft_reset = 0;
	अचिन्हित दीर्घ flags;
	u32 board_id;

	अगर (number_of_controllers == 0)
		prपूर्णांकk(KERN_INFO DRIVER_NAME "\n");

	rc = hpsa_lookup_board_id(pdev, &board_id, शून्य);
	अगर (rc < 0) अणु
		dev_warn(&pdev->dev, "Board ID not found\n");
		वापस rc;
	पूर्ण

	rc = hpsa_init_reset_devices(pdev, board_id);
	अगर (rc) अणु
		अगर (rc != -ENOTSUPP)
			वापस rc;
		/* If the reset fails in a particular way (it has no way to करो
		 * a proper hard reset, so वापसs -ENOTSUPP) we can try to करो
		 * a soft reset once we get the controller configured up to the
		 * poपूर्णांक that it can accept a command.
		 */
		try_soft_reset = 1;
		rc = 0;
	पूर्ण

reinit_after_soft_reset:

	/* Command काष्ठाures must be aligned on a 32-byte boundary because
	 * the 5 lower bits of the address are used by the hardware. and by
	 * the driver.  See comments in hpsa.h क्रम more info.
	 */
	BUILD_BUG_ON(माप(काष्ठा CommandList) % COMMANDLIST_ALIGNMENT);
	h = hpda_alloc_ctlr_info();
	अगर (!h) अणु
		dev_err(&pdev->dev, "Failed to allocate controller head\n");
		वापस -ENOMEM;
	पूर्ण

	h->pdev = pdev;

	h->पूर्णांकr_mode = hpsa_simple_mode ? SIMPLE_MODE_INT : PERF_MODE_INT;
	INIT_LIST_HEAD(&h->offline_device_list);
	spin_lock_init(&h->lock);
	spin_lock_init(&h->offline_device_lock);
	spin_lock_init(&h->scan_lock);
	spin_lock_init(&h->reset_lock);
	atomic_set(&h->passthru_cmds_avail, HPSA_MAX_CONCURRENT_PASSTHRUS);

	/* Allocate and clear per-cpu variable lockup_detected */
	h->lockup_detected = alloc_percpu(u32);
	अगर (!h->lockup_detected) अणु
		dev_err(&h->pdev->dev, "Failed to allocate lockup detector\n");
		rc = -ENOMEM;
		जाओ clean1;	/* aer/h */
	पूर्ण
	set_lockup_detected_क्रम_all_cpus(h, 0);

	rc = hpsa_pci_init(h);
	अगर (rc)
		जाओ clean2;	/* lu, aer/h */

	/* relies on h-> settings made by hpsa_pci_init, including
	 * पूर्णांकerrupt_mode h->पूर्णांकr */
	rc = hpsa_scsi_host_alloc(h);
	अगर (rc)
		जाओ clean2_5;	/* pci, lu, aer/h */

	प्र_लिखो(h->devname, HPSA "%d", h->scsi_host->host_no);
	h->ctlr = number_of_controllers;
	number_of_controllers++;

	/* configure PCI DMA stuff */
	rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc != 0) अणु
		rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (rc != 0) अणु
			dev_err(&pdev->dev, "no suitable DMA available\n");
			जाओ clean3;	/* shost, pci, lu, aer/h */
		पूर्ण
	पूर्ण

	/* make sure the board पूर्णांकerrupts are off */
	h->access.set_पूर्णांकr_mask(h, HPSA_INTR_OFF);

	rc = hpsa_request_irqs(h, करो_hpsa_पूर्णांकr_msi, करो_hpsa_पूर्णांकr_पूर्णांकx);
	अगर (rc)
		जाओ clean3;	/* shost, pci, lu, aer/h */
	rc = hpsa_alloc_cmd_pool(h);
	अगर (rc)
		जाओ clean4;	/* irq, shost, pci, lu, aer/h */
	rc = hpsa_alloc_sg_chain_blocks(h);
	अगर (rc)
		जाओ clean5;	/* cmd, irq, shost, pci, lu, aer/h */
	init_रुकोqueue_head(&h->scan_रुको_queue);
	init_रुकोqueue_head(&h->event_sync_रुको_queue);
	mutex_init(&h->reset_mutex);
	h->scan_finished = 1; /* no scan currently in progress */
	h->scan_रुकोing = 0;

	pci_set_drvdata(pdev, h);
	h->ndevices = 0;

	spin_lock_init(&h->devlock);
	rc = hpsa_put_ctlr_पूर्णांकo_perक्रमmant_mode(h);
	अगर (rc)
		जाओ clean6; /* sg, cmd, irq, shost, pci, lu, aer/h */

	/* create the resubmit workqueue */
	h->rescan_ctlr_wq = hpsa_create_controller_wq(h, "rescan");
	अगर (!h->rescan_ctlr_wq) अणु
		rc = -ENOMEM;
		जाओ clean7;
	पूर्ण

	h->resubmit_wq = hpsa_create_controller_wq(h, "resubmit");
	अगर (!h->resubmit_wq) अणु
		rc = -ENOMEM;
		जाओ clean7;	/* aer/h */
	पूर्ण

	h->monitor_ctlr_wq = hpsa_create_controller_wq(h, "monitor");
	अगर (!h->monitor_ctlr_wq) अणु
		rc = -ENOMEM;
		जाओ clean7;
	पूर्ण

	/*
	 * At this poपूर्णांक, the controller is पढ़ोy to take commands.
	 * Now, अगर reset_devices and the hard reset didn't work, try
	 * the soft reset and see अगर that works.
	 */
	अगर (try_soft_reset) अणु

		/* This is kind of gross.  We may or may not get a completion
		 * from the soft reset command, and अगर we करो, then the value
		 * from the fअगरo may or may not be valid.  So, we रुको 10 secs
		 * after the reset throwing away any completions we get during
		 * that समय.  Unरेजिस्टर the पूर्णांकerrupt handler and रेजिस्टर
		 * fake ones to scoop up any residual completions.
		 */
		spin_lock_irqsave(&h->lock, flags);
		h->access.set_पूर्णांकr_mask(h, HPSA_INTR_OFF);
		spin_unlock_irqrestore(&h->lock, flags);
		hpsa_मुक्त_irqs(h);
		rc = hpsa_request_irqs(h, hpsa_msix_discard_completions,
					hpsa_पूर्णांकx_discard_completions);
		अगर (rc) अणु
			dev_warn(&h->pdev->dev,
				"Failed to request_irq after soft reset.\n");
			/*
			 * cannot जाओ clean7 or मुक्त_irqs will be called
			 * again. Instead, करो its work
			 */
			hpsa_मुक्त_perक्रमmant_mode(h);	/* clean7 */
			hpsa_मुक्त_sg_chain_blocks(h);	/* clean6 */
			hpsa_मुक्त_cmd_pool(h);		/* clean5 */
			/*
			 * skip hpsa_मुक्त_irqs(h) clean4 since that
			 * was just called beक्रमe request_irqs failed
			 */
			जाओ clean3;
		पूर्ण

		rc = hpsa_kdump_soft_reset(h);
		अगर (rc)
			/* Neither hard nor soft reset worked, we're hosed. */
			जाओ clean7;

		dev_info(&h->pdev->dev, "Board READY.\n");
		dev_info(&h->pdev->dev,
			"Waiting for stale completions to drain.\n");
		h->access.set_पूर्णांकr_mask(h, HPSA_INTR_ON);
		msleep(10000);
		h->access.set_पूर्णांकr_mask(h, HPSA_INTR_OFF);

		rc = controller_reset_failed(h->cfgtable);
		अगर (rc)
			dev_info(&h->pdev->dev,
				"Soft reset appears to have failed.\n");

		/* since the controller's reset, we have to go back and re-init
		 * everything.  Easiest to just क्रमget what we've करोne and करो it
		 * all over again.
		 */
		hpsa_unकरो_allocations_after_kdump_soft_reset(h);
		try_soft_reset = 0;
		अगर (rc)
			/* करोn't जाओ clean, we alपढ़ोy unallocated */
			वापस -ENODEV;

		जाओ reinit_after_soft_reset;
	पूर्ण

	/* Enable Accelerated IO path at driver layer */
	h->acciopath_status = 1;
	/* Disable discovery polling.*/
	h->discovery_polling = 0;


	/* Turn the पूर्णांकerrupts on so we can service requests */
	h->access.set_पूर्णांकr_mask(h, HPSA_INTR_ON);

	hpsa_hba_inquiry(h);

	h->lastlogicals = kzalloc(माप(*(h->lastlogicals)), GFP_KERNEL);
	अगर (!h->lastlogicals)
		dev_info(&h->pdev->dev,
			"Can't track change to report lun data\n");

	/* hook पूर्णांकo SCSI subप्रणाली */
	rc = hpsa_scsi_add_host(h);
	अगर (rc)
		जाओ clean8; /* lastlogicals, perf, sg, cmd, irq, shost, pci, lu, aer/h */

	/* Monitor the controller क्रम firmware lockups */
	h->heartbeat_sample_पूर्णांकerval = HEARTBEAT_SAMPLE_INTERVAL;
	INIT_DELAYED_WORK(&h->monitor_ctlr_work, hpsa_monitor_ctlr_worker);
	schedule_delayed_work(&h->monitor_ctlr_work,
				h->heartbeat_sample_पूर्णांकerval);
	INIT_DELAYED_WORK(&h->rescan_ctlr_work, hpsa_rescan_ctlr_worker);
	queue_delayed_work(h->rescan_ctlr_wq, &h->rescan_ctlr_work,
				h->heartbeat_sample_पूर्णांकerval);
	INIT_DELAYED_WORK(&h->event_monitor_work, hpsa_event_monitor_worker);
	schedule_delayed_work(&h->event_monitor_work,
				HPSA_EVENT_MONITOR_INTERVAL);
	वापस 0;

clean8: /* lastlogicals, perf, sg, cmd, irq, shost, pci, lu, aer/h */
	kमुक्त(h->lastlogicals);
clean7: /* perf, sg, cmd, irq, shost, pci, lu, aer/h */
	hpsa_मुक्त_perक्रमmant_mode(h);
	h->access.set_पूर्णांकr_mask(h, HPSA_INTR_OFF);
clean6: /* sg, cmd, irq, pci, lockup, wq/aer/h */
	hpsa_मुक्त_sg_chain_blocks(h);
clean5: /* cmd, irq, shost, pci, lu, aer/h */
	hpsa_मुक्त_cmd_pool(h);
clean4: /* irq, shost, pci, lu, aer/h */
	hpsa_मुक्त_irqs(h);
clean3: /* shost, pci, lu, aer/h */
	scsi_host_put(h->scsi_host);
	h->scsi_host = शून्य;
clean2_5: /* pci, lu, aer/h */
	hpsa_मुक्त_pci_init(h);
clean2: /* lu, aer/h */
	अगर (h->lockup_detected) अणु
		मुक्त_percpu(h->lockup_detected);
		h->lockup_detected = शून्य;
	पूर्ण
clean1:	/* wq/aer/h */
	अगर (h->resubmit_wq) अणु
		destroy_workqueue(h->resubmit_wq);
		h->resubmit_wq = शून्य;
	पूर्ण
	अगर (h->rescan_ctlr_wq) अणु
		destroy_workqueue(h->rescan_ctlr_wq);
		h->rescan_ctlr_wq = शून्य;
	पूर्ण
	अगर (h->monitor_ctlr_wq) अणु
		destroy_workqueue(h->monitor_ctlr_wq);
		h->monitor_ctlr_wq = शून्य;
	पूर्ण
	kमुक्त(h);
	वापस rc;
पूर्ण

अटल व्योम hpsa_flush_cache(काष्ठा ctlr_info *h)
अणु
	अक्षर *flush_buf;
	काष्ठा CommandList *c;
	पूर्णांक rc;

	अगर (unlikely(lockup_detected(h)))
		वापस;
	flush_buf = kzalloc(4, GFP_KERNEL);
	अगर (!flush_buf)
		वापस;

	c = cmd_alloc(h);

	अगर (fill_cmd(c, HPSA_CACHE_FLUSH, h, flush_buf, 4, 0,
		RAID_CTLR_LUNID, TYPE_CMD)) अणु
		जाओ out;
	पूर्ण
	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_TO_DEVICE,
			DEFAULT_TIMEOUT);
	अगर (rc)
		जाओ out;
	अगर (c->err_info->CommandStatus != 0)
out:
		dev_warn(&h->pdev->dev,
			"error flushing cache on controller\n");
	cmd_मुक्त(h, c);
	kमुक्त(flush_buf);
पूर्ण

/* Make controller gather fresh report lun data each समय we
 * send करोwn a report luns request
 */
अटल व्योम hpsa_disable_rld_caching(काष्ठा ctlr_info *h)
अणु
	u32 *options;
	काष्ठा CommandList *c;
	पूर्णांक rc;

	/* Don't bother trying to set diag options अगर locked up */
	अगर (unlikely(h->lockup_detected))
		वापस;

	options = kzalloc(माप(*options), GFP_KERNEL);
	अगर (!options)
		वापस;

	c = cmd_alloc(h);

	/* first, get the current diag options settings */
	अगर (fill_cmd(c, BMIC_SENSE_DIAG_OPTIONS, h, options, 4, 0,
		RAID_CTLR_LUNID, TYPE_CMD))
		जाओ errout;

	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर ((rc != 0) || (c->err_info->CommandStatus != 0))
		जाओ errout;

	/* Now, set the bit क्रम disabling the RLD caching */
	*options |= HPSA_DIAG_OPTS_DISABLE_RLD_CACHING;

	अगर (fill_cmd(c, BMIC_SET_DIAG_OPTIONS, h, options, 4, 0,
		RAID_CTLR_LUNID, TYPE_CMD))
		जाओ errout;

	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_TO_DEVICE,
			NO_TIMEOUT);
	अगर ((rc != 0)  || (c->err_info->CommandStatus != 0))
		जाओ errout;

	/* Now verअगरy that it got set: */
	अगर (fill_cmd(c, BMIC_SENSE_DIAG_OPTIONS, h, options, 4, 0,
		RAID_CTLR_LUNID, TYPE_CMD))
		जाओ errout;

	rc = hpsa_scsi_करो_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	अगर ((rc != 0)  || (c->err_info->CommandStatus != 0))
		जाओ errout;

	अगर (*options & HPSA_DIAG_OPTS_DISABLE_RLD_CACHING)
		जाओ out;

errout:
	dev_err(&h->pdev->dev,
			"Error: failed to disable report lun data caching.\n");
out:
	cmd_मुक्त(h, c);
	kमुक्त(options);
पूर्ण

अटल व्योम __hpsa_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ctlr_info *h;

	h = pci_get_drvdata(pdev);
	/* Turn board पूर्णांकerrupts off  and send the flush cache command
	 * sendcmd will turn off पूर्णांकerrupt, and send the flush...
	 * To ग_लिखो all data in the battery backed cache to disks
	 */
	hpsa_flush_cache(h);
	h->access.set_पूर्णांकr_mask(h, HPSA_INTR_OFF);
	hpsa_मुक्त_irqs(h);			/* init_one 4 */
	hpsa_disable_पूर्णांकerrupt_mode(h);		/* pci_init 2 */
पूर्ण

अटल व्योम hpsa_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	__hpsa_shutकरोwn(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम hpsa_मुक्त_device_info(काष्ठा ctlr_info *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < h->ndevices; i++) अणु
		kमुक्त(h->dev[i]);
		h->dev[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम hpsa_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ctlr_info *h;
	अचिन्हित दीर्घ flags;

	अगर (pci_get_drvdata(pdev) == शून्य) अणु
		dev_err(&pdev->dev, "unable to remove device\n");
		वापस;
	पूर्ण
	h = pci_get_drvdata(pdev);

	/* Get rid of any controller monitoring work items */
	spin_lock_irqsave(&h->lock, flags);
	h->हटाओ_in_progress = 1;
	spin_unlock_irqrestore(&h->lock, flags);
	cancel_delayed_work_sync(&h->monitor_ctlr_work);
	cancel_delayed_work_sync(&h->rescan_ctlr_work);
	cancel_delayed_work_sync(&h->event_monitor_work);
	destroy_workqueue(h->rescan_ctlr_wq);
	destroy_workqueue(h->resubmit_wq);
	destroy_workqueue(h->monitor_ctlr_wq);

	hpsa_delete_sas_host(h);

	/*
	 * Call beक्रमe disabling पूर्णांकerrupts.
	 * scsi_हटाओ_host can trigger I/O operations especially
	 * when multipath is enabled. There can be SYNCHRONIZE CACHE
	 * operations which cannot complete and will hang the प्रणाली.
	 */
	अगर (h->scsi_host)
		scsi_हटाओ_host(h->scsi_host);		/* init_one 8 */
	/* includes hpsa_मुक्त_irqs - init_one 4 */
	/* includes hpsa_disable_पूर्णांकerrupt_mode - pci_init 2 */
	__hpsa_shutकरोwn(pdev);

	hpsa_मुक्त_device_info(h);		/* scan */

	kमुक्त(h->hba_inquiry_data);			/* init_one 10 */
	h->hba_inquiry_data = शून्य;			/* init_one 10 */
	hpsa_मुक्त_ioaccel2_sg_chain_blocks(h);
	hpsa_मुक्त_perक्रमmant_mode(h);			/* init_one 7 */
	hpsa_मुक्त_sg_chain_blocks(h);			/* init_one 6 */
	hpsa_मुक्त_cmd_pool(h);				/* init_one 5 */
	kमुक्त(h->lastlogicals);

	/* hpsa_मुक्त_irqs alपढ़ोy called via hpsa_shutकरोwn init_one 4 */

	scsi_host_put(h->scsi_host);			/* init_one 3 */
	h->scsi_host = शून्य;				/* init_one 3 */

	/* includes hpsa_disable_पूर्णांकerrupt_mode - pci_init 2 */
	hpsa_मुक्त_pci_init(h);				/* init_one 2.5 */

	मुक्त_percpu(h->lockup_detected);		/* init_one 2 */
	h->lockup_detected = शून्य;			/* init_one 2 */
	/* (व्योम) pci_disable_pcie_error_reporting(pdev); */	/* init_one 1 */

	hpda_मुक्त_ctlr_info(h);				/* init_one 1 */
पूर्ण

अटल पूर्णांक __maybe_unused hpsa_suspend(
	__attribute__((unused)) काष्ठा device *dev)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक __maybe_unused hpsa_resume
	(__attribute__((unused)) काष्ठा device *dev)
अणु
	वापस -ENOSYS;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(hpsa_pm_ops, hpsa_suspend, hpsa_resume);

अटल काष्ठा pci_driver hpsa_pci_driver = अणु
	.name = HPSA,
	.probe = hpsa_init_one,
	.हटाओ = hpsa_हटाओ_one,
	.id_table = hpsa_pci_device_id,	/* id_table */
	.shutकरोwn = hpsa_shutकरोwn,
	.driver.pm = &hpsa_pm_ops,
पूर्ण;

/* Fill in bucket_map[], given nsgs (the max number of
 * scatter gather elements supported) and bucket[],
 * which is an array of 8 पूर्णांकegers.  The bucket[] array
 * contains 8 dअगरferent DMA transfer sizes (in 16
 * byte increments) which the controller uses to fetch
 * commands.  This function fills in bucket_map[], which
 * maps a given number of scatter gather elements to one of
 * the 8 DMA transfer sizes.  The poपूर्णांक of it is to allow the
 * controller to only करो as much DMA as needed to fetch the
 * command, with the DMA transfer size encoded in the lower
 * bits of the command address.
 */
अटल व्योम  calc_bucket_map(पूर्णांक bucket[], पूर्णांक num_buckets,
	पूर्णांक nsgs, पूर्णांक min_blocks, u32 *bucket_map)
अणु
	पूर्णांक i, j, b, size;

	/* Note, bucket_map must have nsgs+1 entries. */
	क्रम (i = 0; i <= nsgs; i++) अणु
		/* Compute size of a command with i SG entries */
		size = i + min_blocks;
		b = num_buckets; /* Assume the biggest bucket */
		/* Find the bucket that is just big enough */
		क्रम (j = 0; j < num_buckets; j++) अणु
			अगर (bucket[j] >= size) अणु
				b = j;
				अवरोध;
			पूर्ण
		पूर्ण
		/* क्रम a command with i SG entries, use bucket b. */
		bucket_map[i] = b;
	पूर्ण
पूर्ण

/*
 * वापस -ENODEV on err, 0 on success (or no action)
 * allocates numerous items that must be मुक्तd later
 */
अटल पूर्णांक hpsa_enter_perक्रमmant_mode(काष्ठा ctlr_info *h, u32 trans_support)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ रेजिस्टर_value;
	अचिन्हित दीर्घ transMethod = CFGTBL_Trans_Perक्रमmant |
			(trans_support & CFGTBL_Trans_use_लघु_tags) |
				CFGTBL_Trans_enable_directed_msix |
			(trans_support & (CFGTBL_Trans_io_accel1 |
				CFGTBL_Trans_io_accel2));
	काष्ठा access_method access = SA5_perक्रमmant_access;

	/* This is a bit complicated.  There are 8 रेजिस्टरs on
	 * the controller which we ग_लिखो to to tell it 8 dअगरferent
	 * sizes of commands which there may be.  It's a way of
	 * reducing the DMA करोne to fetch each command.  Encoded पूर्णांकo
	 * each command's tag are 3 bits which communicate to the controller
	 * which of the eight sizes that command fits within.  The size of
	 * each command depends on how many scatter gather entries there are.
	 * Each SG entry requires 16 bytes.  The eight रेजिस्टरs are programmed
	 * with the number of 16-byte blocks a command of that size requires.
	 * The smallest command possible requires 5 such 16 byte blocks.
	 * the largest command possible requires SG_ENTRIES_IN_CMD + 4 16-byte
	 * blocks.  Note, this only extends to the SG entries contained
	 * within the command block, and करोes not extend to chained blocks
	 * of SG elements.   bft[] contains the eight values we ग_लिखो to
	 * the रेजिस्टरs.  They are not evenly distributed, but have more
	 * sizes क्रम small commands, and fewer sizes क्रम larger commands.
	 */
	पूर्णांक bft[8] = अणु5, 6, 8, 10, 12, 20, 28, SG_ENTRIES_IN_CMD + 4पूर्ण;
#घोषणा MIN_IOACCEL2_BFT_ENTRY 5
#घोषणा HPSA_IOACCEL2_HEADER_SZ 4
	पूर्णांक bft2[16] = अणुMIN_IOACCEL2_BFT_ENTRY, 6, 7, 8, 9, 10, 11, 12,
			13, 14, 15, 16, 17, 18, 19,
			HPSA_IOACCEL2_HEADER_SZ + IOACCEL2_MAXSGENTRIESपूर्ण;
	BUILD_BUG_ON(ARRAY_SIZE(bft2) != 16);
	BUILD_BUG_ON(ARRAY_SIZE(bft) != 8);
	BUILD_BUG_ON(दुरत्व(काष्ठा io_accel2_cmd, sg) >
				 16 * MIN_IOACCEL2_BFT_ENTRY);
	BUILD_BUG_ON(माप(काष्ठा ioaccel2_sg_element) != 16);
	BUILD_BUG_ON(28 > SG_ENTRIES_IN_CMD + 4);
	/*  5 = 1 s/g entry or 4k
	 *  6 = 2 s/g entry or 8k
	 *  8 = 4 s/g entry or 16k
	 * 10 = 6 s/g entry or 24k
	 */

	/* If the controller supports either ioaccel method then
	 * we can also use the RAID stack submit path that करोes not
	 * perक्रमm the superfluous पढ़ोl() after each command submission.
	 */
	अगर (trans_support & (CFGTBL_Trans_io_accel1 | CFGTBL_Trans_io_accel2))
		access = SA5_perक्रमmant_access_no_पढ़ो;

	/* Controller spec: zero out this buffer. */
	क्रम (i = 0; i < h->nreply_queues; i++)
		स_रखो(h->reply_queue[i].head, 0, h->reply_queue_size);

	bft[7] = SG_ENTRIES_IN_CMD + 4;
	calc_bucket_map(bft, ARRAY_SIZE(bft),
				SG_ENTRIES_IN_CMD, 4, h->blockFetchTable);
	क्रम (i = 0; i < 8; i++)
		ग_लिखोl(bft[i], &h->transtable->BlockFetch[i]);

	/* size of controller ring buffer */
	ग_लिखोl(h->max_commands, &h->transtable->RepQSize);
	ग_लिखोl(h->nreply_queues, &h->transtable->RepQCount);
	ग_लिखोl(0, &h->transtable->RepQCtrAddrLow32);
	ग_लिखोl(0, &h->transtable->RepQCtrAddrHigh32);

	क्रम (i = 0; i < h->nreply_queues; i++) अणु
		ग_लिखोl(0, &h->transtable->RepQAddr[i].upper);
		ग_लिखोl(h->reply_queue[i].busaddr,
			&h->transtable->RepQAddr[i].lower);
	पूर्ण

	ग_लिखोl(0, &h->cfgtable->HostWrite.command_pool_addr_hi);
	ग_लिखोl(transMethod, &(h->cfgtable->HostWrite.TransportRequest));
	/*
	 * enable outbound पूर्णांकerrupt coalescing in accelerator mode;
	 */
	अगर (trans_support & CFGTBL_Trans_io_accel1) अणु
		access = SA5_ioaccel_mode1_access;
		ग_लिखोl(10, &h->cfgtable->HostWrite.CoalIntDelay);
		ग_लिखोl(4, &h->cfgtable->HostWrite.CoalIntCount);
	पूर्ण अन्यथा
		अगर (trans_support & CFGTBL_Trans_io_accel2)
			access = SA5_ioaccel_mode2_access;
	ग_लिखोl(CFGTBL_ChangeReq, h->vaddr + SA5_DOORBELL);
	अगर (hpsa_रुको_क्रम_mode_change_ack(h)) अणु
		dev_err(&h->pdev->dev,
			"performant mode problem - doorbell timeout\n");
		वापस -ENODEV;
	पूर्ण
	रेजिस्टर_value = पढ़ोl(&(h->cfgtable->TransportActive));
	अगर (!(रेजिस्टर_value & CFGTBL_Trans_Perक्रमmant)) अणु
		dev_err(&h->pdev->dev,
			"performant mode problem - transport not active\n");
		वापस -ENODEV;
	पूर्ण
	/* Change the access methods to the perक्रमmant access methods */
	h->access = access;
	h->transMethod = transMethod;

	अगर (!((trans_support & CFGTBL_Trans_io_accel1) ||
		(trans_support & CFGTBL_Trans_io_accel2)))
		वापस 0;

	अगर (trans_support & CFGTBL_Trans_io_accel1) अणु
		/* Set up I/O accelerator mode */
		क्रम (i = 0; i < h->nreply_queues; i++) अणु
			ग_लिखोl(i, h->vaddr + IOACCEL_MODE1_REPLY_QUEUE_INDEX);
			h->reply_queue[i].current_entry =
				पढ़ोl(h->vaddr + IOACCEL_MODE1_PRODUCER_INDEX);
		पूर्ण
		bft[7] = h->ioaccel_maxsg + 8;
		calc_bucket_map(bft, ARRAY_SIZE(bft), h->ioaccel_maxsg, 8,
				h->ioaccel1_blockFetchTable);

		/* initialize all reply queue entries to unused */
		क्रम (i = 0; i < h->nreply_queues; i++)
			स_रखो(h->reply_queue[i].head,
				(u8) IOACCEL_MODE1_REPLY_UNUSED,
				h->reply_queue_size);

		/* set all the स्थिरant fields in the accelerator command
		 * frames once at init समय to save CPU cycles later.
		 */
		क्रम (i = 0; i < h->nr_cmds; i++) अणु
			काष्ठा io_accel1_cmd *cp = &h->ioaccel_cmd_pool[i];

			cp->function = IOACCEL1_FUNCTION_SCSIIO;
			cp->err_info = (u32) (h->errinfo_pool_dhandle +
					(i * माप(काष्ठा ErrorInfo)));
			cp->err_info_len = माप(काष्ठा ErrorInfo);
			cp->sgl_offset = IOACCEL1_SGLOFFSET;
			cp->host_context_flags =
				cpu_to_le16(IOACCEL1_HCFLAGS_CISS_FORMAT);
			cp->समयout_sec = 0;
			cp->ReplyQueue = 0;
			cp->tag =
				cpu_to_le64((i << सूचीECT_LOOKUP_SHIFT));
			cp->host_addr =
				cpu_to_le64(h->ioaccel_cmd_pool_dhandle +
					(i * माप(काष्ठा io_accel1_cmd)));
		पूर्ण
	पूर्ण अन्यथा अगर (trans_support & CFGTBL_Trans_io_accel2) अणु
		u64 cfg_offset, cfg_base_addr_index;
		u32 bft2_offset, cfg_base_addr;

		hpsa_find_cfg_addrs(h->pdev, h->vaddr, &cfg_base_addr,
				    &cfg_base_addr_index, &cfg_offset);
		BUILD_BUG_ON(दुरत्व(काष्ठा io_accel2_cmd, sg) != 64);
		bft2[15] = h->ioaccel_maxsg + HPSA_IOACCEL2_HEADER_SZ;
		calc_bucket_map(bft2, ARRAY_SIZE(bft2), h->ioaccel_maxsg,
				4, h->ioaccel2_blockFetchTable);
		bft2_offset = पढ़ोl(&h->cfgtable->io_accel_request_size_offset);
		BUILD_BUG_ON(दुरत्व(काष्ठा CfgTable,
				io_accel_request_size_offset) != 0xb8);
		h->ioaccel2_bft2_regs =
			remap_pci_mem(pci_resource_start(h->pdev,
					cfg_base_addr_index) +
					cfg_offset + bft2_offset,
					ARRAY_SIZE(bft2) *
					माप(*h->ioaccel2_bft2_regs));
		क्रम (i = 0; i < ARRAY_SIZE(bft2); i++)
			ग_लिखोl(bft2[i], &h->ioaccel2_bft2_regs[i]);
	पूर्ण
	ग_लिखोl(CFGTBL_ChangeReq, h->vaddr + SA5_DOORBELL);
	अगर (hpsa_रुको_क्रम_mode_change_ack(h)) अणु
		dev_err(&h->pdev->dev,
			"performant mode problem - enabling ioaccel mode\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/* Free ioaccel1 mode command blocks and block fetch table */
अटल व्योम hpsa_मुक्त_ioaccel1_cmd_and_bft(काष्ठा ctlr_info *h)
अणु
	अगर (h->ioaccel_cmd_pool) अणु
		dma_मुक्त_coherent(&h->pdev->dev,
				  h->nr_cmds * माप(*h->ioaccel_cmd_pool),
				  h->ioaccel_cmd_pool,
				  h->ioaccel_cmd_pool_dhandle);
		h->ioaccel_cmd_pool = शून्य;
		h->ioaccel_cmd_pool_dhandle = 0;
	पूर्ण
	kमुक्त(h->ioaccel1_blockFetchTable);
	h->ioaccel1_blockFetchTable = शून्य;
पूर्ण

/* Allocate ioaccel1 mode command blocks and block fetch table */
अटल पूर्णांक hpsa_alloc_ioaccel1_cmd_and_bft(काष्ठा ctlr_info *h)
अणु
	h->ioaccel_maxsg =
		पढ़ोl(&(h->cfgtable->io_accel_max_embedded_sg_count));
	अगर (h->ioaccel_maxsg > IOACCEL1_MAXSGENTRIES)
		h->ioaccel_maxsg = IOACCEL1_MAXSGENTRIES;

	/* Command काष्ठाures must be aligned on a 128-byte boundary
	 * because the 7 lower bits of the address are used by the
	 * hardware.
	 */
	BUILD_BUG_ON(माप(काष्ठा io_accel1_cmd) %
			IOACCEL1_COMMANDLIST_ALIGNMENT);
	h->ioaccel_cmd_pool =
		dma_alloc_coherent(&h->pdev->dev,
			h->nr_cmds * माप(*h->ioaccel_cmd_pool),
			&h->ioaccel_cmd_pool_dhandle, GFP_KERNEL);

	h->ioaccel1_blockFetchTable =
		kदो_स्मृति(((h->ioaccel_maxsg + 1) *
				माप(u32)), GFP_KERNEL);

	अगर ((h->ioaccel_cmd_pool == शून्य) ||
		(h->ioaccel1_blockFetchTable == शून्य))
		जाओ clean_up;

	स_रखो(h->ioaccel_cmd_pool, 0,
		h->nr_cmds * माप(*h->ioaccel_cmd_pool));
	वापस 0;

clean_up:
	hpsa_मुक्त_ioaccel1_cmd_and_bft(h);
	वापस -ENOMEM;
पूर्ण

/* Free ioaccel2 mode command blocks and block fetch table */
अटल व्योम hpsa_मुक्त_ioaccel2_cmd_and_bft(काष्ठा ctlr_info *h)
अणु
	hpsa_मुक्त_ioaccel2_sg_chain_blocks(h);

	अगर (h->ioaccel2_cmd_pool) अणु
		dma_मुक्त_coherent(&h->pdev->dev,
				  h->nr_cmds * माप(*h->ioaccel2_cmd_pool),
				  h->ioaccel2_cmd_pool,
				  h->ioaccel2_cmd_pool_dhandle);
		h->ioaccel2_cmd_pool = शून्य;
		h->ioaccel2_cmd_pool_dhandle = 0;
	पूर्ण
	kमुक्त(h->ioaccel2_blockFetchTable);
	h->ioaccel2_blockFetchTable = शून्य;
पूर्ण

/* Allocate ioaccel2 mode command blocks and block fetch table */
अटल पूर्णांक hpsa_alloc_ioaccel2_cmd_and_bft(काष्ठा ctlr_info *h)
अणु
	पूर्णांक rc;

	/* Allocate ioaccel2 mode command blocks and block fetch table */

	h->ioaccel_maxsg =
		पढ़ोl(&(h->cfgtable->io_accel_max_embedded_sg_count));
	अगर (h->ioaccel_maxsg > IOACCEL2_MAXSGENTRIES)
		h->ioaccel_maxsg = IOACCEL2_MAXSGENTRIES;

	BUILD_BUG_ON(माप(काष्ठा io_accel2_cmd) %
			IOACCEL2_COMMANDLIST_ALIGNMENT);
	h->ioaccel2_cmd_pool =
		dma_alloc_coherent(&h->pdev->dev,
			h->nr_cmds * माप(*h->ioaccel2_cmd_pool),
			&h->ioaccel2_cmd_pool_dhandle, GFP_KERNEL);

	h->ioaccel2_blockFetchTable =
		kदो_स्मृति(((h->ioaccel_maxsg + 1) *
				माप(u32)), GFP_KERNEL);

	अगर ((h->ioaccel2_cmd_pool == शून्य) ||
		(h->ioaccel2_blockFetchTable == शून्य)) अणु
		rc = -ENOMEM;
		जाओ clean_up;
	पूर्ण

	rc = hpsa_allocate_ioaccel2_sg_chain_blocks(h);
	अगर (rc)
		जाओ clean_up;

	स_रखो(h->ioaccel2_cmd_pool, 0,
		h->nr_cmds * माप(*h->ioaccel2_cmd_pool));
	वापस 0;

clean_up:
	hpsa_मुक्त_ioaccel2_cmd_and_bft(h);
	वापस rc;
पूर्ण

/* Free items allocated by hpsa_put_ctlr_पूर्णांकo_perक्रमmant_mode */
अटल व्योम hpsa_मुक्त_perक्रमmant_mode(काष्ठा ctlr_info *h)
अणु
	kमुक्त(h->blockFetchTable);
	h->blockFetchTable = शून्य;
	hpsa_मुक्त_reply_queues(h);
	hpsa_मुक्त_ioaccel1_cmd_and_bft(h);
	hpsa_मुक्त_ioaccel2_cmd_and_bft(h);
पूर्ण

/* वापस -ENODEV on error, 0 on success (or no action)
 * allocates numerous items that must be मुक्तd later
 */
अटल पूर्णांक hpsa_put_ctlr_पूर्णांकo_perक्रमmant_mode(काष्ठा ctlr_info *h)
अणु
	u32 trans_support;
	अचिन्हित दीर्घ transMethod = CFGTBL_Trans_Perक्रमmant |
					CFGTBL_Trans_use_लघु_tags;
	पूर्णांक i, rc;

	अगर (hpsa_simple_mode)
		वापस 0;

	trans_support = पढ़ोl(&(h->cfgtable->TransportSupport));
	अगर (!(trans_support & PERFORMANT_MODE))
		वापस 0;

	/* Check क्रम I/O accelerator mode support */
	अगर (trans_support & CFGTBL_Trans_io_accel1) अणु
		transMethod |= CFGTBL_Trans_io_accel1 |
				CFGTBL_Trans_enable_directed_msix;
		rc = hpsa_alloc_ioaccel1_cmd_and_bft(h);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अगर (trans_support & CFGTBL_Trans_io_accel2) अणु
		transMethod |= CFGTBL_Trans_io_accel2 |
				CFGTBL_Trans_enable_directed_msix;
		rc = hpsa_alloc_ioaccel2_cmd_and_bft(h);
		अगर (rc)
			वापस rc;
	पूर्ण

	h->nreply_queues = h->msix_vectors > 0 ? h->msix_vectors : 1;
	hpsa_get_max_perf_mode_cmds(h);
	/* Perक्रमmant mode ring buffer and supporting data काष्ठाures */
	h->reply_queue_size = h->max_commands * माप(u64);

	क्रम (i = 0; i < h->nreply_queues; i++) अणु
		h->reply_queue[i].head = dma_alloc_coherent(&h->pdev->dev,
						h->reply_queue_size,
						&h->reply_queue[i].busaddr,
						GFP_KERNEL);
		अगर (!h->reply_queue[i].head) अणु
			rc = -ENOMEM;
			जाओ clean1;	/* rq, ioaccel */
		पूर्ण
		h->reply_queue[i].size = h->max_commands;
		h->reply_queue[i].wraparound = 1;  /* spec: init to 1 */
		h->reply_queue[i].current_entry = 0;
	पूर्ण

	/* Need a block fetch table क्रम perक्रमmant mode */
	h->blockFetchTable = kदो_स्मृति(((SG_ENTRIES_IN_CMD + 1) *
				माप(u32)), GFP_KERNEL);
	अगर (!h->blockFetchTable) अणु
		rc = -ENOMEM;
		जाओ clean1;	/* rq, ioaccel */
	पूर्ण

	rc = hpsa_enter_perक्रमmant_mode(h, trans_support);
	अगर (rc)
		जाओ clean2;	/* bft, rq, ioaccel */
	वापस 0;

clean2:	/* bft, rq, ioaccel */
	kमुक्त(h->blockFetchTable);
	h->blockFetchTable = शून्य;
clean1:	/* rq, ioaccel */
	hpsa_मुक्त_reply_queues(h);
	hpsa_मुक्त_ioaccel1_cmd_and_bft(h);
	hpsa_मुक्त_ioaccel2_cmd_and_bft(h);
	वापस rc;
पूर्ण

अटल पूर्णांक is_accelerated_cmd(काष्ठा CommandList *c)
अणु
	वापस c->cmd_type == CMD_IOACCEL1 || c->cmd_type == CMD_IOACCEL2;
पूर्ण

अटल व्योम hpsa_drain_accel_commands(काष्ठा ctlr_info *h)
अणु
	काष्ठा CommandList *c = शून्य;
	पूर्णांक i, accel_cmds_out;
	पूर्णांक refcount;

	करो अणु /* रुको क्रम all outstanding ioaccel commands to drain out */
		accel_cmds_out = 0;
		क्रम (i = 0; i < h->nr_cmds; i++) अणु
			c = h->cmd_pool + i;
			refcount = atomic_inc_वापस(&c->refcount);
			अगर (refcount > 1) /* Command is allocated */
				accel_cmds_out += is_accelerated_cmd(c);
			cmd_मुक्त(h, c);
		पूर्ण
		अगर (accel_cmds_out <= 0)
			अवरोध;
		msleep(100);
	पूर्ण जबतक (1);
पूर्ण

अटल काष्ठा hpsa_sas_phy *hpsa_alloc_sas_phy(
				काष्ठा hpsa_sas_port *hpsa_sas_port)
अणु
	काष्ठा hpsa_sas_phy *hpsa_sas_phy;
	काष्ठा sas_phy *phy;

	hpsa_sas_phy = kzalloc(माप(*hpsa_sas_phy), GFP_KERNEL);
	अगर (!hpsa_sas_phy)
		वापस शून्य;

	phy = sas_phy_alloc(hpsa_sas_port->parent_node->parent_dev,
		hpsa_sas_port->next_phy_index);
	अगर (!phy) अणु
		kमुक्त(hpsa_sas_phy);
		वापस शून्य;
	पूर्ण

	hpsa_sas_port->next_phy_index++;
	hpsa_sas_phy->phy = phy;
	hpsa_sas_phy->parent_port = hpsa_sas_port;

	वापस hpsa_sas_phy;
पूर्ण

अटल व्योम hpsa_मुक्त_sas_phy(काष्ठा hpsa_sas_phy *hpsa_sas_phy)
अणु
	काष्ठा sas_phy *phy = hpsa_sas_phy->phy;

	sas_port_delete_phy(hpsa_sas_phy->parent_port->port, phy);
	अगर (hpsa_sas_phy->added_to_port)
		list_del(&hpsa_sas_phy->phy_list_entry);
	sas_phy_delete(phy);
	kमुक्त(hpsa_sas_phy);
पूर्ण

अटल पूर्णांक hpsa_sas_port_add_phy(काष्ठा hpsa_sas_phy *hpsa_sas_phy)
अणु
	पूर्णांक rc;
	काष्ठा hpsa_sas_port *hpsa_sas_port;
	काष्ठा sas_phy *phy;
	काष्ठा sas_identअगरy *identअगरy;

	hpsa_sas_port = hpsa_sas_phy->parent_port;
	phy = hpsa_sas_phy->phy;

	identअगरy = &phy->identअगरy;
	स_रखो(identअगरy, 0, माप(*identअगरy));
	identअगरy->sas_address = hpsa_sas_port->sas_address;
	identअगरy->device_type = SAS_END_DEVICE;
	identअगरy->initiator_port_protocols = SAS_PROTOCOL_STP;
	identअगरy->target_port_protocols = SAS_PROTOCOL_STP;
	phy->minimum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
	phy->maximum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
	phy->minimum_linkrate = SAS_LINK_RATE_UNKNOWN;
	phy->maximum_linkrate = SAS_LINK_RATE_UNKNOWN;
	phy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;

	rc = sas_phy_add(hpsa_sas_phy->phy);
	अगर (rc)
		वापस rc;

	sas_port_add_phy(hpsa_sas_port->port, hpsa_sas_phy->phy);
	list_add_tail(&hpsa_sas_phy->phy_list_entry,
			&hpsa_sas_port->phy_list_head);
	hpsa_sas_phy->added_to_port = true;

	वापस 0;
पूर्ण

अटल पूर्णांक
	hpsa_sas_port_add_rphy(काष्ठा hpsa_sas_port *hpsa_sas_port,
				काष्ठा sas_rphy *rphy)
अणु
	काष्ठा sas_identअगरy *identअगरy;

	identअगरy = &rphy->identअगरy;
	identअगरy->sas_address = hpsa_sas_port->sas_address;
	identअगरy->initiator_port_protocols = SAS_PROTOCOL_STP;
	identअगरy->target_port_protocols = SAS_PROTOCOL_STP;

	वापस sas_rphy_add(rphy);
पूर्ण

अटल काष्ठा hpsa_sas_port
	*hpsa_alloc_sas_port(काष्ठा hpsa_sas_node *hpsa_sas_node,
				u64 sas_address)
अणु
	पूर्णांक rc;
	काष्ठा hpsa_sas_port *hpsa_sas_port;
	काष्ठा sas_port *port;

	hpsa_sas_port = kzalloc(माप(*hpsa_sas_port), GFP_KERNEL);
	अगर (!hpsa_sas_port)
		वापस शून्य;

	INIT_LIST_HEAD(&hpsa_sas_port->phy_list_head);
	hpsa_sas_port->parent_node = hpsa_sas_node;

	port = sas_port_alloc_num(hpsa_sas_node->parent_dev);
	अगर (!port)
		जाओ मुक्त_hpsa_port;

	rc = sas_port_add(port);
	अगर (rc)
		जाओ मुक्त_sas_port;

	hpsa_sas_port->port = port;
	hpsa_sas_port->sas_address = sas_address;
	list_add_tail(&hpsa_sas_port->port_list_entry,
			&hpsa_sas_node->port_list_head);

	वापस hpsa_sas_port;

मुक्त_sas_port:
	sas_port_मुक्त(port);
मुक्त_hpsa_port:
	kमुक्त(hpsa_sas_port);

	वापस शून्य;
पूर्ण

अटल व्योम hpsa_मुक्त_sas_port(काष्ठा hpsa_sas_port *hpsa_sas_port)
अणु
	काष्ठा hpsa_sas_phy *hpsa_sas_phy;
	काष्ठा hpsa_sas_phy *next;

	list_क्रम_each_entry_safe(hpsa_sas_phy, next,
			&hpsa_sas_port->phy_list_head, phy_list_entry)
		hpsa_मुक्त_sas_phy(hpsa_sas_phy);

	sas_port_delete(hpsa_sas_port->port);
	list_del(&hpsa_sas_port->port_list_entry);
	kमुक्त(hpsa_sas_port);
पूर्ण

अटल काष्ठा hpsa_sas_node *hpsa_alloc_sas_node(काष्ठा device *parent_dev)
अणु
	काष्ठा hpsa_sas_node *hpsa_sas_node;

	hpsa_sas_node = kzalloc(माप(*hpsa_sas_node), GFP_KERNEL);
	अगर (hpsa_sas_node) अणु
		hpsa_sas_node->parent_dev = parent_dev;
		INIT_LIST_HEAD(&hpsa_sas_node->port_list_head);
	पूर्ण

	वापस hpsa_sas_node;
पूर्ण

अटल व्योम hpsa_मुक्त_sas_node(काष्ठा hpsa_sas_node *hpsa_sas_node)
अणु
	काष्ठा hpsa_sas_port *hpsa_sas_port;
	काष्ठा hpsa_sas_port *next;

	अगर (!hpsa_sas_node)
		वापस;

	list_क्रम_each_entry_safe(hpsa_sas_port, next,
			&hpsa_sas_node->port_list_head, port_list_entry)
		hpsa_मुक्त_sas_port(hpsa_sas_port);

	kमुक्त(hpsa_sas_node);
पूर्ण

अटल काष्ठा hpsa_scsi_dev_t
	*hpsa_find_device_by_sas_rphy(काष्ठा ctlr_info *h,
					काष्ठा sas_rphy *rphy)
अणु
	पूर्णांक i;
	काष्ठा hpsa_scsi_dev_t *device;

	क्रम (i = 0; i < h->ndevices; i++) अणु
		device = h->dev[i];
		अगर (!device->sas_port)
			जारी;
		अगर (device->sas_port->rphy == rphy)
			वापस device;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक hpsa_add_sas_host(काष्ठा ctlr_info *h)
अणु
	पूर्णांक rc;
	काष्ठा device *parent_dev;
	काष्ठा hpsa_sas_node *hpsa_sas_node;
	काष्ठा hpsa_sas_port *hpsa_sas_port;
	काष्ठा hpsa_sas_phy *hpsa_sas_phy;

	parent_dev = &h->scsi_host->shost_dev;

	hpsa_sas_node = hpsa_alloc_sas_node(parent_dev);
	अगर (!hpsa_sas_node)
		वापस -ENOMEM;

	hpsa_sas_port = hpsa_alloc_sas_port(hpsa_sas_node, h->sas_address);
	अगर (!hpsa_sas_port) अणु
		rc = -ENODEV;
		जाओ मुक्त_sas_node;
	पूर्ण

	hpsa_sas_phy = hpsa_alloc_sas_phy(hpsa_sas_port);
	अगर (!hpsa_sas_phy) अणु
		rc = -ENODEV;
		जाओ मुक्त_sas_port;
	पूर्ण

	rc = hpsa_sas_port_add_phy(hpsa_sas_phy);
	अगर (rc)
		जाओ मुक्त_sas_phy;

	h->sas_host = hpsa_sas_node;

	वापस 0;

मुक्त_sas_phy:
	hpsa_मुक्त_sas_phy(hpsa_sas_phy);
मुक्त_sas_port:
	hpsa_मुक्त_sas_port(hpsa_sas_port);
मुक्त_sas_node:
	hpsa_मुक्त_sas_node(hpsa_sas_node);

	वापस rc;
पूर्ण

अटल व्योम hpsa_delete_sas_host(काष्ठा ctlr_info *h)
अणु
	hpsa_मुक्त_sas_node(h->sas_host);
पूर्ण

अटल पूर्णांक hpsa_add_sas_device(काष्ठा hpsa_sas_node *hpsa_sas_node,
				काष्ठा hpsa_scsi_dev_t *device)
अणु
	पूर्णांक rc;
	काष्ठा hpsa_sas_port *hpsa_sas_port;
	काष्ठा sas_rphy *rphy;

	hpsa_sas_port = hpsa_alloc_sas_port(hpsa_sas_node, device->sas_address);
	अगर (!hpsa_sas_port)
		वापस -ENOMEM;

	rphy = sas_end_device_alloc(hpsa_sas_port->port);
	अगर (!rphy) अणु
		rc = -ENODEV;
		जाओ मुक्त_sas_port;
	पूर्ण

	hpsa_sas_port->rphy = rphy;
	device->sas_port = hpsa_sas_port;

	rc = hpsa_sas_port_add_rphy(hpsa_sas_port, rphy);
	अगर (rc)
		जाओ मुक्त_sas_port;

	वापस 0;

मुक्त_sas_port:
	hpsa_मुक्त_sas_port(hpsa_sas_port);
	device->sas_port = शून्य;

	वापस rc;
पूर्ण

अटल व्योम hpsa_हटाओ_sas_device(काष्ठा hpsa_scsi_dev_t *device)
अणु
	अगर (device->sas_port) अणु
		hpsa_मुक्त_sas_port(device->sas_port);
		device->sas_port = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
hpsa_sas_get_linkerrors(काष्ठा sas_phy *phy)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
hpsa_sas_get_enclosure_identअगरier(काष्ठा sas_rphy *rphy, u64 *identअगरier)
अणु
	काष्ठा Scsi_Host *shost = phy_to_shost(rphy);
	काष्ठा ctlr_info *h;
	काष्ठा hpsa_scsi_dev_t *sd;

	अगर (!shost)
		वापस -ENXIO;

	h = shost_to_hba(shost);

	अगर (!h)
		वापस -ENXIO;

	sd = hpsa_find_device_by_sas_rphy(h, rphy);
	अगर (!sd)
		वापस -ENXIO;

	*identअगरier = sd->eli;

	वापस 0;
पूर्ण

अटल पूर्णांक
hpsa_sas_get_bay_identअगरier(काष्ठा sas_rphy *rphy)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक
hpsa_sas_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
hpsa_sas_phy_enable(काष्ठा sas_phy *phy, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
hpsa_sas_phy_setup(काष्ठा sas_phy *phy)
अणु
	वापस 0;
पूर्ण

अटल व्योम
hpsa_sas_phy_release(काष्ठा sas_phy *phy)
अणु
पूर्ण

अटल पूर्णांक
hpsa_sas_phy_speed(काष्ठा sas_phy *phy, काष्ठा sas_phy_linkrates *rates)
अणु
	वापस -EINVAL;
पूर्ण

अटल काष्ठा sas_function_ढाँचा hpsa_sas_transport_functions = अणु
	.get_linkerrors = hpsa_sas_get_linkerrors,
	.get_enclosure_identअगरier = hpsa_sas_get_enclosure_identअगरier,
	.get_bay_identअगरier = hpsa_sas_get_bay_identअगरier,
	.phy_reset = hpsa_sas_phy_reset,
	.phy_enable = hpsa_sas_phy_enable,
	.phy_setup = hpsa_sas_phy_setup,
	.phy_release = hpsa_sas_phy_release,
	.set_phy_speed = hpsa_sas_phy_speed,
पूर्ण;

/*
 *  This is it.  Register the PCI driver inक्रमmation क्रम the cards we control
 *  the OS will call our रेजिस्टरed routines when it finds one of our cards.
 */
अटल पूर्णांक __init hpsa_init(व्योम)
अणु
	पूर्णांक rc;

	hpsa_sas_transport_ढाँचा =
		sas_attach_transport(&hpsa_sas_transport_functions);
	अगर (!hpsa_sas_transport_ढाँचा)
		वापस -ENODEV;

	rc = pci_रेजिस्टर_driver(&hpsa_pci_driver);

	अगर (rc)
		sas_release_transport(hpsa_sas_transport_ढाँचा);

	वापस rc;
पूर्ण

अटल व्योम __निकास hpsa_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hpsa_pci_driver);
	sas_release_transport(hpsa_sas_transport_ढाँचा);
पूर्ण

अटल व्योम __attribute__((unused)) verअगरy_offsets(व्योम)
अणु
#घोषणा VERIFY_OFFSET(member, offset) \
	BUILD_BUG_ON(दुरत्व(काष्ठा raid_map_data, member) != offset)

	VERIFY_OFFSET(काष्ठाure_size, 0);
	VERIFY_OFFSET(volume_blk_size, 4);
	VERIFY_OFFSET(volume_blk_cnt, 8);
	VERIFY_OFFSET(phys_blk_shअगरt, 16);
	VERIFY_OFFSET(parity_rotation_shअगरt, 17);
	VERIFY_OFFSET(strip_size, 18);
	VERIFY_OFFSET(disk_starting_blk, 20);
	VERIFY_OFFSET(disk_blk_cnt, 28);
	VERIFY_OFFSET(data_disks_per_row, 36);
	VERIFY_OFFSET(metadata_disks_per_row, 38);
	VERIFY_OFFSET(row_cnt, 40);
	VERIFY_OFFSET(layout_map_count, 42);
	VERIFY_OFFSET(flags, 44);
	VERIFY_OFFSET(dekindex, 46);
	/* VERIFY_OFFSET(reserved, 48 */
	VERIFY_OFFSET(data, 64);

#अघोषित VERIFY_OFFSET

#घोषणा VERIFY_OFFSET(member, offset) \
	BUILD_BUG_ON(दुरत्व(काष्ठा io_accel2_cmd, member) != offset)

	VERIFY_OFFSET(IU_type, 0);
	VERIFY_OFFSET(direction, 1);
	VERIFY_OFFSET(reply_queue, 2);
	/* VERIFY_OFFSET(reserved1, 3);  */
	VERIFY_OFFSET(scsi_nexus, 4);
	VERIFY_OFFSET(Tag, 8);
	VERIFY_OFFSET(cdb, 16);
	VERIFY_OFFSET(cciss_lun, 32);
	VERIFY_OFFSET(data_len, 40);
	VERIFY_OFFSET(cmd_priority_task_attr, 44);
	VERIFY_OFFSET(sg_count, 45);
	/* VERIFY_OFFSET(reserved3 */
	VERIFY_OFFSET(err_ptr, 48);
	VERIFY_OFFSET(err_len, 56);
	/* VERIFY_OFFSET(reserved4  */
	VERIFY_OFFSET(sg, 64);

#अघोषित VERIFY_OFFSET

#घोषणा VERIFY_OFFSET(member, offset) \
	BUILD_BUG_ON(दुरत्व(काष्ठा io_accel1_cmd, member) != offset)

	VERIFY_OFFSET(dev_handle, 0x00);
	VERIFY_OFFSET(reserved1, 0x02);
	VERIFY_OFFSET(function, 0x03);
	VERIFY_OFFSET(reserved2, 0x04);
	VERIFY_OFFSET(err_info, 0x0C);
	VERIFY_OFFSET(reserved3, 0x10);
	VERIFY_OFFSET(err_info_len, 0x12);
	VERIFY_OFFSET(reserved4, 0x13);
	VERIFY_OFFSET(sgl_offset, 0x14);
	VERIFY_OFFSET(reserved5, 0x15);
	VERIFY_OFFSET(transfer_len, 0x1C);
	VERIFY_OFFSET(reserved6, 0x20);
	VERIFY_OFFSET(io_flags, 0x24);
	VERIFY_OFFSET(reserved7, 0x26);
	VERIFY_OFFSET(LUN, 0x34);
	VERIFY_OFFSET(control, 0x3C);
	VERIFY_OFFSET(CDB, 0x40);
	VERIFY_OFFSET(reserved8, 0x50);
	VERIFY_OFFSET(host_context_flags, 0x60);
	VERIFY_OFFSET(समयout_sec, 0x62);
	VERIFY_OFFSET(ReplyQueue, 0x64);
	VERIFY_OFFSET(reserved9, 0x65);
	VERIFY_OFFSET(tag, 0x68);
	VERIFY_OFFSET(host_addr, 0x70);
	VERIFY_OFFSET(CISS_LUN, 0x78);
	VERIFY_OFFSET(SG, 0x78 + 8);
#अघोषित VERIFY_OFFSET
पूर्ण

module_init(hpsa_init);
module_निकास(hpsa_cleanup);
