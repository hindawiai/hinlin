<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ipr.c -- driver क्रम IBM Power Linux RAID adapters
 *
 * Written By: Brian King <brking@us.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2003, 2004 IBM Corporation
 */

/*
 * Notes:
 *
 * This driver is used to control the following SCSI adapters:
 *
 * IBM iSeries: 5702, 5703, 2780, 5709, 570A, 570B
 *
 * IBM pSeries: PCI-X Dual Channel Ultra 320 SCSI RAID Adapter
 *              PCI-X Dual Channel Ultra 320 SCSI Adapter
 *              PCI-X Dual Channel Ultra 320 SCSI RAID Enablement Card
 *              Embedded SCSI adapter on p615 and p655 प्रणालीs
 *
 * Supported Hardware Features:
 *	- Ultra 320 SCSI controller
 *	- PCI-X host पूर्णांकerface
 *	- Embedded PowerPC RISC Processor and Hardware XOR DMA Engine
 *	- Non-Volatile Write Cache
 *	- Supports attachment of non-RAID disks, tape, and optical devices
 *	- RAID Levels 0, 5, 10
 *	- Hot spare
 *	- Background Parity Checking
 *	- Background Data Scrubbing
 *	- Ability to increase the capacity of an existing RAID 5 disk array
 *		by adding disks
 *
 * Driver Features:
 *	- Tagged command queuing
 *	- Adapter microcode करोwnload
 *	- PCI hot plug
 *	- SCSI device hot plug
 *
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/libata.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/reboot.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/processor.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश "ipr.h"

/*
 *   Global Data
 */
अटल LIST_HEAD(ipr_ioa_head);
अटल अचिन्हित पूर्णांक ipr_log_level = IPR_DEFAULT_LOG_LEVEL;
अटल अचिन्हित पूर्णांक ipr_max_speed = 1;
अटल पूर्णांक ipr_tesपंचांगode = 0;
अटल अचिन्हित पूर्णांक ipr_fastfail = 0;
अटल अचिन्हित पूर्णांक ipr_transop_समयout = 0;
अटल अचिन्हित पूर्णांक ipr_debug = 0;
अटल अचिन्हित पूर्णांक ipr_max_devs = IPR_DEFAULT_SIS64_DEVS;
अटल अचिन्हित पूर्णांक ipr_dual_ioa_raid = 1;
अटल अचिन्हित पूर्णांक ipr_number_of_msix = 16;
अटल अचिन्हित पूर्णांक ipr_fast_reboot;
अटल DEFINE_SPINLOCK(ipr_driver_lock);

/* This table describes the dअगरferences between DMA controller chips */
अटल स्थिर काष्ठा ipr_chip_cfg_t ipr_chip_cfg[] = अणु
	अणु /* Gemstone, Citrine, Obsidian, and Obsidian-E */
		.mailbox = 0x0042C,
		.max_cmds = 100,
		.cache_line_size = 0x20,
		.clear_isr = 1,
		.iopoll_weight = 0,
		अणु
			.set_पूर्णांकerrupt_mask_reg = 0x0022C,
			.clr_पूर्णांकerrupt_mask_reg = 0x00230,
			.clr_पूर्णांकerrupt_mask_reg32 = 0x00230,
			.sense_पूर्णांकerrupt_mask_reg = 0x0022C,
			.sense_पूर्णांकerrupt_mask_reg32 = 0x0022C,
			.clr_पूर्णांकerrupt_reg = 0x00228,
			.clr_पूर्णांकerrupt_reg32 = 0x00228,
			.sense_पूर्णांकerrupt_reg = 0x00224,
			.sense_पूर्णांकerrupt_reg32 = 0x00224,
			.ioarrin_reg = 0x00404,
			.sense_uproc_पूर्णांकerrupt_reg = 0x00214,
			.sense_uproc_पूर्णांकerrupt_reg32 = 0x00214,
			.set_uproc_पूर्णांकerrupt_reg = 0x00214,
			.set_uproc_पूर्णांकerrupt_reg32 = 0x00214,
			.clr_uproc_पूर्णांकerrupt_reg = 0x00218,
			.clr_uproc_पूर्णांकerrupt_reg32 = 0x00218
		पूर्ण
	पूर्ण,
	अणु /* Snipe and Scamp */
		.mailbox = 0x0052C,
		.max_cmds = 100,
		.cache_line_size = 0x20,
		.clear_isr = 1,
		.iopoll_weight = 0,
		अणु
			.set_पूर्णांकerrupt_mask_reg = 0x00288,
			.clr_पूर्णांकerrupt_mask_reg = 0x0028C,
			.clr_पूर्णांकerrupt_mask_reg32 = 0x0028C,
			.sense_पूर्णांकerrupt_mask_reg = 0x00288,
			.sense_पूर्णांकerrupt_mask_reg32 = 0x00288,
			.clr_पूर्णांकerrupt_reg = 0x00284,
			.clr_पूर्णांकerrupt_reg32 = 0x00284,
			.sense_पूर्णांकerrupt_reg = 0x00280,
			.sense_पूर्णांकerrupt_reg32 = 0x00280,
			.ioarrin_reg = 0x00504,
			.sense_uproc_पूर्णांकerrupt_reg = 0x00290,
			.sense_uproc_पूर्णांकerrupt_reg32 = 0x00290,
			.set_uproc_पूर्णांकerrupt_reg = 0x00290,
			.set_uproc_पूर्णांकerrupt_reg32 = 0x00290,
			.clr_uproc_पूर्णांकerrupt_reg = 0x00294,
			.clr_uproc_पूर्णांकerrupt_reg32 = 0x00294
		पूर्ण
	पूर्ण,
	अणु /* CRoC */
		.mailbox = 0x00044,
		.max_cmds = 1000,
		.cache_line_size = 0x20,
		.clear_isr = 0,
		.iopoll_weight = 64,
		अणु
			.set_पूर्णांकerrupt_mask_reg = 0x00010,
			.clr_पूर्णांकerrupt_mask_reg = 0x00018,
			.clr_पूर्णांकerrupt_mask_reg32 = 0x0001C,
			.sense_पूर्णांकerrupt_mask_reg = 0x00010,
			.sense_पूर्णांकerrupt_mask_reg32 = 0x00014,
			.clr_पूर्णांकerrupt_reg = 0x00008,
			.clr_पूर्णांकerrupt_reg32 = 0x0000C,
			.sense_पूर्णांकerrupt_reg = 0x00000,
			.sense_पूर्णांकerrupt_reg32 = 0x00004,
			.ioarrin_reg = 0x00070,
			.sense_uproc_पूर्णांकerrupt_reg = 0x00020,
			.sense_uproc_पूर्णांकerrupt_reg32 = 0x00024,
			.set_uproc_पूर्णांकerrupt_reg = 0x00020,
			.set_uproc_पूर्णांकerrupt_reg32 = 0x00024,
			.clr_uproc_पूर्णांकerrupt_reg = 0x00028,
			.clr_uproc_पूर्णांकerrupt_reg32 = 0x0002C,
			.init_feedback_reg = 0x0005C,
			.dump_addr_reg = 0x00064,
			.dump_data_reg = 0x00068,
			.endian_swap_reg = 0x00084
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ipr_chip_t ipr_chip[] = अणु
	अणु PCI_VENDOR_ID_MYLEX, PCI_DEVICE_ID_IBM_GEMSTONE, false, IPR_SIS32, IPR_PCI_CFG, &ipr_chip_cfg[0] पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CITRINE, false, IPR_SIS32, IPR_PCI_CFG, &ipr_chip_cfg[0] पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_OBSIDIAN, false, IPR_SIS32, IPR_PCI_CFG, &ipr_chip_cfg[0] पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN, false, IPR_SIS32, IPR_PCI_CFG, &ipr_chip_cfg[0] पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN_E, true, IPR_SIS32, IPR_PCI_CFG, &ipr_chip_cfg[0] पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_SNIPE, false, IPR_SIS32, IPR_PCI_CFG, &ipr_chip_cfg[1] पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_SCAMP, false, IPR_SIS32, IPR_PCI_CFG, &ipr_chip_cfg[1] पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROC_FPGA_E2, true, IPR_SIS64, IPR_MMIO, &ipr_chip_cfg[2] पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE, true, IPR_SIS64, IPR_MMIO, &ipr_chip_cfg[2] पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_RATTLESNAKE, true, IPR_SIS64, IPR_MMIO, &ipr_chip_cfg[2] पूर्ण
पूर्ण;

अटल पूर्णांक ipr_max_bus_speeds[] = अणु
	IPR_80MBs_SCSI_RATE, IPR_U160_SCSI_RATE, IPR_U320_SCSI_RATE
पूर्ण;

MODULE_AUTHOR("Brian King <brking@us.ibm.com>");
MODULE_DESCRIPTION("IBM Power RAID SCSI Adapter Driver");
module_param_named(max_speed, ipr_max_speed, uपूर्णांक, 0);
MODULE_PARM_DESC(max_speed, "Maximum bus speed (0-2). Default: 1=U160. Speeds: 0=80 MB/s, 1=U160, 2=U320");
module_param_named(log_level, ipr_log_level, uपूर्णांक, 0);
MODULE_PARM_DESC(log_level, "Set to 0 - 4 for increasing verbosity of device driver");
module_param_named(tesपंचांगode, ipr_tesपंचांगode, पूर्णांक, 0);
MODULE_PARM_DESC(tesपंचांगode, "DANGEROUS!!! Allows unsupported configurations");
module_param_named(fastfail, ipr_fastfail, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(fastfail, "Reduce timeouts and retries");
module_param_named(transop_समयout, ipr_transop_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(transop_समयout, "Time in seconds to wait for adapter to come operational (default: 300)");
module_param_named(debug, ipr_debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Enable device driver debugging logging. Set to 1 to enable. (default: 0)");
module_param_named(dual_ioa_raid, ipr_dual_ioa_raid, पूर्णांक, 0);
MODULE_PARM_DESC(dual_ioa_raid, "Enable dual adapter RAID support. Set to 1 to enable. (default: 1)");
module_param_named(max_devs, ipr_max_devs, पूर्णांक, 0);
MODULE_PARM_DESC(max_devs, "Specify the maximum number of physical devices. "
		 "[Default=" __stringअगरy(IPR_DEFAULT_SIS64_DEVS) "]");
module_param_named(number_of_msix, ipr_number_of_msix, पूर्णांक, 0);
MODULE_PARM_DESC(number_of_msix, "Specify the number of MSIX interrupts to use on capable adapters (1 - 16).  (default:16)");
module_param_named(fast_reboot, ipr_fast_reboot, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(fast_reboot, "Skip adapter shutdown during reboot. Set to 1 to enable. (default: 0)");
MODULE_LICENSE("GPL");
MODULE_VERSION(IPR_DRIVER_VERSION);

/*  A स्थिरant array of IOASCs/URCs/Error Messages */
अटल स्थिर
काष्ठा ipr_error_table_t ipr_error_table[] = अणु
	अणु0x00000000, 1, IPR_DEFAULT_LOG_LEVEL,
	"8155: An unknown error was received"पूर्ण,
	अणु0x00330000, 0, 0,
	"Soft underlength error"पूर्ण,
	अणु0x005A0000, 0, 0,
	"Command to be cancelled not found"पूर्ण,
	अणु0x00808000, 0, 0,
	"Qualified success"पूर्ण,
	अणु0x01080000, 1, IPR_DEFAULT_LOG_LEVEL,
	"FFFE: Soft device bus error recovered by the IOA"पूर्ण,
	अणु0x01088100, 0, IPR_DEFAULT_LOG_LEVEL,
	"4101: Soft device bus fabric error"पूर्ण,
	अणु0x01100100, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFC: Logical block guard error recovered by the device"पूर्ण,
	अणु0x01100300, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFC: Logical block reference tag error recovered by the device"पूर्ण,
	अणु0x01108300, 0, IPR_DEFAULT_LOG_LEVEL,
	"4171: Recovered scatter list tag / sequence number error"पूर्ण,
	अणु0x01109000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FF3D: Recovered logical block CRC error on IOA to Host transfer"पूर्ण,
	अणु0x01109200, 0, IPR_DEFAULT_LOG_LEVEL,
	"4171: Recovered logical block sequence number error on IOA to Host transfer"पूर्ण,
	अणु0x0110A000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFD: Recovered logical block reference tag error detected by the IOA"पूर्ण,
	अणु0x0110A100, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFD: Logical block guard error recovered by the IOA"पूर्ण,
	अणु0x01170600, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF9: Device sector reassign successful"पूर्ण,
	अणु0x01170900, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF7: Media error recovered by device rewrite procedures"पूर्ण,
	अणु0x01180200, 0, IPR_DEFAULT_LOG_LEVEL,
	"7001: IOA sector reassignment successful"पूर्ण,
	अणु0x01180500, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF9: Soft media error. Sector reassignment recommended"पूर्ण,
	अणु0x01180600, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF7: Media error recovered by IOA rewrite procedures"पूर्ण,
	अणु0x01418000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FF3D: Soft PCI bus error recovered by the IOA"पूर्ण,
	अणु0x01440000, 1, IPR_DEFAULT_LOG_LEVEL,
	"FFF6: Device hardware error recovered by the IOA"पूर्ण,
	अणु0x01448100, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF6: Device hardware error recovered by the device"पूर्ण,
	अणु0x01448200, 1, IPR_DEFAULT_LOG_LEVEL,
	"FF3D: Soft IOA error recovered by the IOA"पूर्ण,
	अणु0x01448300, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFA: Undefined device response recovered by the IOA"पूर्ण,
	अणु0x014A0000, 1, IPR_DEFAULT_LOG_LEVEL,
	"FFF6: Device bus error, message or command phase"पूर्ण,
	अणु0x014A8000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFE: Task Management Function failed"पूर्ण,
	अणु0x015D0000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF6: Failure prediction threshold exceeded"पूर्ण,
	अणु0x015D9200, 0, IPR_DEFAULT_LOG_LEVEL,
	"8009: Impending cache battery pack failure"पूर्ण,
	अणु0x02040100, 0, 0,
	"Logical Unit in process of becoming ready"पूर्ण,
	अणु0x02040200, 0, 0,
	"Initializing command required"पूर्ण,
	अणु0x02040400, 0, 0,
	"34FF: Disk device format in progress"पूर्ण,
	अणु0x02040C00, 0, 0,
	"Logical unit not accessible, target port in unavailable state"पूर्ण,
	अणु0x02048000, 0, IPR_DEFAULT_LOG_LEVEL,
	"9070: IOA requested reset"पूर्ण,
	अणु0x023F0000, 0, 0,
	"Synchronization required"पूर्ण,
	अणु0x02408500, 0, 0,
	"IOA microcode download required"पूर्ण,
	अणु0x02408600, 0, 0,
	"Device bus connection is prohibited by host"पूर्ण,
	अणु0x024E0000, 0, 0,
	"No ready, IOA shutdown"पूर्ण,
	अणु0x025A0000, 0, 0,
	"Not ready, IOA has been shutdown"पूर्ण,
	अणु0x02670100, 0, IPR_DEFAULT_LOG_LEVEL,
	"3020: Storage subsystem configuration error"पूर्ण,
	अणु0x03110B00, 0, 0,
	"FFF5: Medium error, data unreadable, recommend reassign"पूर्ण,
	अणु0x03110C00, 0, 0,
	"7000: Medium error, data unreadable, do not reassign"पूर्ण,
	अणु0x03310000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF3: Disk media format bad"पूर्ण,
	अणु0x04050000, 0, IPR_DEFAULT_LOG_LEVEL,
	"3002: Addressed device failed to respond to selection"पूर्ण,
	अणु0x04080000, 1, IPR_DEFAULT_LOG_LEVEL,
	"3100: Device bus error"पूर्ण,
	अणु0x04080100, 0, IPR_DEFAULT_LOG_LEVEL,
	"3109: IOA timed out a device command"पूर्ण,
	अणु0x04088000, 0, 0,
	"3120: SCSI bus is not operational"पूर्ण,
	अणु0x04088100, 0, IPR_DEFAULT_LOG_LEVEL,
	"4100: Hard device bus fabric error"पूर्ण,
	अणु0x04100100, 0, IPR_DEFAULT_LOG_LEVEL,
	"310C: Logical block guard error detected by the device"पूर्ण,
	अणु0x04100300, 0, IPR_DEFAULT_LOG_LEVEL,
	"310C: Logical block reference tag error detected by the device"पूर्ण,
	अणु0x04108300, 1, IPR_DEFAULT_LOG_LEVEL,
	"4170: Scatter list tag / sequence number error"पूर्ण,
	अणु0x04109000, 1, IPR_DEFAULT_LOG_LEVEL,
	"8150: Logical block CRC error on IOA to Host transfer"पूर्ण,
	अणु0x04109200, 1, IPR_DEFAULT_LOG_LEVEL,
	"4170: Logical block sequence number error on IOA to Host transfer"पूर्ण,
	अणु0x0410A000, 0, IPR_DEFAULT_LOG_LEVEL,
	"310D: Logical block reference tag error detected by the IOA"पूर्ण,
	अणु0x0410A100, 0, IPR_DEFAULT_LOG_LEVEL,
	"310D: Logical block guard error detected by the IOA"पूर्ण,
	अणु0x04118000, 0, IPR_DEFAULT_LOG_LEVEL,
	"9000: IOA reserved area data check"पूर्ण,
	अणु0x04118100, 0, IPR_DEFAULT_LOG_LEVEL,
	"9001: IOA reserved area invalid data pattern"पूर्ण,
	अणु0x04118200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9002: IOA reserved area LRC error"पूर्ण,
	अणु0x04118300, 1, IPR_DEFAULT_LOG_LEVEL,
	"Hardware Error, IOA metadata access error"पूर्ण,
	अणु0x04320000, 0, IPR_DEFAULT_LOG_LEVEL,
	"102E: Out of alternate sectors for disk storage"पूर्ण,
	अणु0x04330000, 1, IPR_DEFAULT_LOG_LEVEL,
	"FFF4: Data transfer underlength error"पूर्ण,
	अणु0x04338000, 1, IPR_DEFAULT_LOG_LEVEL,
	"FFF4: Data transfer overlength error"पूर्ण,
	अणु0x043E0100, 0, IPR_DEFAULT_LOG_LEVEL,
	"3400: Logical unit failure"पूर्ण,
	अणु0x04408500, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF4: Device microcode is corrupt"पूर्ण,
	अणु0x04418000, 1, IPR_DEFAULT_LOG_LEVEL,
	"8150: PCI bus error"पूर्ण,
	अणु0x04430000, 1, 0,
	"Unsupported device bus message received"पूर्ण,
	अणु0x04440000, 1, IPR_DEFAULT_LOG_LEVEL,
	"FFF4: Disk device problem"पूर्ण,
	अणु0x04448200, 1, IPR_DEFAULT_LOG_LEVEL,
	"8150: Permanent IOA failure"पूर्ण,
	अणु0x04448300, 0, IPR_DEFAULT_LOG_LEVEL,
	"3010: Disk device returned wrong response to IOA"पूर्ण,
	अणु0x04448400, 0, IPR_DEFAULT_LOG_LEVEL,
	"8151: IOA microcode error"पूर्ण,
	अणु0x04448500, 0, 0,
	"Device bus status error"पूर्ण,
	अणु0x04448600, 0, IPR_DEFAULT_LOG_LEVEL,
	"8157: IOA error requiring IOA reset to recover"पूर्ण,
	अणु0x04448700, 0, 0,
	"ATA device status error"पूर्ण,
	अणु0x04490000, 0, 0,
	"Message reject received from the device"पूर्ण,
	अणु0x04449200, 0, IPR_DEFAULT_LOG_LEVEL,
	"8008: A permanent cache battery pack failure occurred"पूर्ण,
	अणु0x0444A000, 0, IPR_DEFAULT_LOG_LEVEL,
	"9090: Disk unit has been modified after the last known status"पूर्ण,
	अणु0x0444A200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9081: IOA detected device error"पूर्ण,
	अणु0x0444A300, 0, IPR_DEFAULT_LOG_LEVEL,
	"9082: IOA detected device error"पूर्ण,
	अणु0x044A0000, 1, IPR_DEFAULT_LOG_LEVEL,
	"3110: Device bus error, message or command phase"पूर्ण,
	अणु0x044A8000, 1, IPR_DEFAULT_LOG_LEVEL,
	"3110: SAS Command / Task Management Function failed"पूर्ण,
	अणु0x04670400, 0, IPR_DEFAULT_LOG_LEVEL,
	"9091: Incorrect hardware configuration change has been detected"पूर्ण,
	अणु0x04678000, 0, IPR_DEFAULT_LOG_LEVEL,
	"9073: Invalid multi-adapter configuration"पूर्ण,
	अणु0x04678100, 0, IPR_DEFAULT_LOG_LEVEL,
	"4010: Incorrect connection between cascaded expanders"पूर्ण,
	अणु0x04678200, 0, IPR_DEFAULT_LOG_LEVEL,
	"4020: Connections exceed IOA design limits"पूर्ण,
	अणु0x04678300, 0, IPR_DEFAULT_LOG_LEVEL,
	"4030: Incorrect multipath connection"पूर्ण,
	अणु0x04679000, 0, IPR_DEFAULT_LOG_LEVEL,
	"4110: Unsupported enclosure function"पूर्ण,
	अणु0x04679800, 0, IPR_DEFAULT_LOG_LEVEL,
	"4120: SAS cable VPD cannot be read"पूर्ण,
	अणु0x046E0000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFF4: Command to logical unit failed"पूर्ण,
	अणु0x05240000, 1, 0,
	"Illegal request, invalid request type or request packet"पूर्ण,
	अणु0x05250000, 0, 0,
	"Illegal request, invalid resource handle"पूर्ण,
	अणु0x05258000, 0, 0,
	"Illegal request, commands not allowed to this device"पूर्ण,
	अणु0x05258100, 0, 0,
	"Illegal request, command not allowed to a secondary adapter"पूर्ण,
	अणु0x05258200, 0, 0,
	"Illegal request, command not allowed to a non-optimized resource"पूर्ण,
	अणु0x05260000, 0, 0,
	"Illegal request, invalid field in parameter list"पूर्ण,
	अणु0x05260100, 0, 0,
	"Illegal request, parameter not supported"पूर्ण,
	अणु0x05260200, 0, 0,
	"Illegal request, parameter value invalid"पूर्ण,
	अणु0x052C0000, 0, 0,
	"Illegal request, command sequence error"पूर्ण,
	अणु0x052C8000, 1, 0,
	"Illegal request, dual adapter support not enabled"पूर्ण,
	अणु0x052C8100, 1, 0,
	"Illegal request, another cable connector was physically disabled"पूर्ण,
	अणु0x054E8000, 1, 0,
	"Illegal request, inconsistent group id/group count"पूर्ण,
	अणु0x06040500, 0, IPR_DEFAULT_LOG_LEVEL,
	"9031: Array protection temporarily suspended, protection resuming"पूर्ण,
	अणु0x06040600, 0, IPR_DEFAULT_LOG_LEVEL,
	"9040: Array protection temporarily suspended, protection resuming"पूर्ण,
	अणु0x060B0100, 0, IPR_DEFAULT_LOG_LEVEL,
	"4080: IOA exceeded maximum operating temperature"पूर्ण,
	अणु0x060B8000, 0, IPR_DEFAULT_LOG_LEVEL,
	"4085: Service required"पूर्ण,
	अणु0x060B8100, 0, IPR_DEFAULT_LOG_LEVEL,
	"4086: SAS Adapter Hardware Configuration Error"पूर्ण,
	अणु0x06288000, 0, IPR_DEFAULT_LOG_LEVEL,
	"3140: Device bus not ready to ready transition"पूर्ण,
	अणु0x06290000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFB: SCSI bus was reset"पूर्ण,
	अणु0x06290500, 0, 0,
	"FFFE: SCSI bus transition to single ended"पूर्ण,
	अणु0x06290600, 0, 0,
	"FFFE: SCSI bus transition to LVD"पूर्ण,
	अणु0x06298000, 0, IPR_DEFAULT_LOG_LEVEL,
	"FFFB: SCSI bus was reset by another initiator"पूर्ण,
	अणु0x063F0300, 0, IPR_DEFAULT_LOG_LEVEL,
	"3029: A device replacement has occurred"पूर्ण,
	अणु0x063F8300, 0, IPR_DEFAULT_LOG_LEVEL,
	"4102: Device bus fabric performance degradation"पूर्ण,
	अणु0x064C8000, 0, IPR_DEFAULT_LOG_LEVEL,
	"9051: IOA cache data exists for a missing or failed device"पूर्ण,
	अणु0x064C8100, 0, IPR_DEFAULT_LOG_LEVEL,
	"9055: Auxiliary cache IOA contains cache data needed by the primary IOA"पूर्ण,
	अणु0x06670100, 0, IPR_DEFAULT_LOG_LEVEL,
	"9025: Disk unit is not supported at its physical location"पूर्ण,
	अणु0x06670600, 0, IPR_DEFAULT_LOG_LEVEL,
	"3020: IOA detected a SCSI bus configuration error"पूर्ण,
	अणु0x06678000, 0, IPR_DEFAULT_LOG_LEVEL,
	"3150: SCSI bus configuration error"पूर्ण,
	अणु0x06678100, 0, IPR_DEFAULT_LOG_LEVEL,
	"9074: Asymmetric advanced function disk configuration"पूर्ण,
	अणु0x06678300, 0, IPR_DEFAULT_LOG_LEVEL,
	"4040: Incomplete multipath connection between IOA and enclosure"पूर्ण,
	अणु0x06678400, 0, IPR_DEFAULT_LOG_LEVEL,
	"4041: Incomplete multipath connection between enclosure and device"पूर्ण,
	अणु0x06678500, 0, IPR_DEFAULT_LOG_LEVEL,
	"9075: Incomplete multipath connection between IOA and remote IOA"पूर्ण,
	अणु0x06678600, 0, IPR_DEFAULT_LOG_LEVEL,
	"9076: Configuration error, missing remote IOA"पूर्ण,
	अणु0x06679100, 0, IPR_DEFAULT_LOG_LEVEL,
	"4050: Enclosure does not support a required multipath function"पूर्ण,
	अणु0x06679800, 0, IPR_DEFAULT_LOG_LEVEL,
	"4121: Configuration error, required cable is missing"पूर्ण,
	अणु0x06679900, 0, IPR_DEFAULT_LOG_LEVEL,
	"4122: Cable is not plugged into the correct location on remote IOA"पूर्ण,
	अणु0x06679A00, 0, IPR_DEFAULT_LOG_LEVEL,
	"4123: Configuration error, invalid cable vital product data"पूर्ण,
	अणु0x06679B00, 0, IPR_DEFAULT_LOG_LEVEL,
	"4124: Configuration error, both cable ends are plugged into the same IOA"पूर्ण,
	अणु0x06690000, 0, IPR_DEFAULT_LOG_LEVEL,
	"4070: Logically bad block written on device"पूर्ण,
	अणु0x06690200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9041: Array protection temporarily suspended"पूर्ण,
	अणु0x06698200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9042: Corrupt array parity detected on specified device"पूर्ण,
	अणु0x066B0200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9030: Array no longer protected due to missing or failed disk unit"पूर्ण,
	अणु0x066B8000, 0, IPR_DEFAULT_LOG_LEVEL,
	"9071: Link operational transition"पूर्ण,
	अणु0x066B8100, 0, IPR_DEFAULT_LOG_LEVEL,
	"9072: Link not operational transition"पूर्ण,
	अणु0x066B8200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9032: Array exposed but still protected"पूर्ण,
	अणु0x066B8300, 0, IPR_DEBUG_LOG_LEVEL,
	"70DD: Device forced failed by disrupt device command"पूर्ण,
	अणु0x066B9100, 0, IPR_DEFAULT_LOG_LEVEL,
	"4061: Multipath redundancy level got better"पूर्ण,
	अणु0x066B9200, 0, IPR_DEFAULT_LOG_LEVEL,
	"4060: Multipath redundancy level got worse"पूर्ण,
	अणु0x06808100, 0, IPR_DEBUG_LOG_LEVEL,
	"9083: Device raw mode enabled"पूर्ण,
	अणु0x06808200, 0, IPR_DEBUG_LOG_LEVEL,
	"9084: Device raw mode disabled"पूर्ण,
	अणु0x07270000, 0, 0,
	"Failure due to other device"पूर्ण,
	अणु0x07278000, 0, IPR_DEFAULT_LOG_LEVEL,
	"9008: IOA does not support functions expected by devices"पूर्ण,
	अणु0x07278100, 0, IPR_DEFAULT_LOG_LEVEL,
	"9010: Cache data associated with attached devices cannot be found"पूर्ण,
	अणु0x07278200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9011: Cache data belongs to devices other than those attached"पूर्ण,
	अणु0x07278400, 0, IPR_DEFAULT_LOG_LEVEL,
	"9020: Array missing 2 or more devices with only 1 device present"पूर्ण,
	अणु0x07278500, 0, IPR_DEFAULT_LOG_LEVEL,
	"9021: Array missing 2 or more devices with 2 or more devices present"पूर्ण,
	अणु0x07278600, 0, IPR_DEFAULT_LOG_LEVEL,
	"9022: Exposed array is missing a required device"पूर्ण,
	अणु0x07278700, 0, IPR_DEFAULT_LOG_LEVEL,
	"9023: Array member(s) not at required physical locations"पूर्ण,
	अणु0x07278800, 0, IPR_DEFAULT_LOG_LEVEL,
	"9024: Array not functional due to present hardware configuration"पूर्ण,
	अणु0x07278900, 0, IPR_DEFAULT_LOG_LEVEL,
	"9026: Array not functional due to present hardware configuration"पूर्ण,
	अणु0x07278A00, 0, IPR_DEFAULT_LOG_LEVEL,
	"9027: Array is missing a device and parity is out of sync"पूर्ण,
	अणु0x07278B00, 0, IPR_DEFAULT_LOG_LEVEL,
	"9028: Maximum number of arrays already exist"पूर्ण,
	अणु0x07278C00, 0, IPR_DEFAULT_LOG_LEVEL,
	"9050: Required cache data cannot be located for a disk unit"पूर्ण,
	अणु0x07278D00, 0, IPR_DEFAULT_LOG_LEVEL,
	"9052: Cache data exists for a device that has been modified"पूर्ण,
	अणु0x07278F00, 0, IPR_DEFAULT_LOG_LEVEL,
	"9054: IOA resources not available due to previous problems"पूर्ण,
	अणु0x07279100, 0, IPR_DEFAULT_LOG_LEVEL,
	"9092: Disk unit requires initialization before use"पूर्ण,
	अणु0x07279200, 0, IPR_DEFAULT_LOG_LEVEL,
	"9029: Incorrect hardware configuration change has been detected"पूर्ण,
	अणु0x07279600, 0, IPR_DEFAULT_LOG_LEVEL,
	"9060: One or more disk pairs are missing from an array"पूर्ण,
	अणु0x07279700, 0, IPR_DEFAULT_LOG_LEVEL,
	"9061: One or more disks are missing from an array"पूर्ण,
	अणु0x07279800, 0, IPR_DEFAULT_LOG_LEVEL,
	"9062: One or more disks are missing from an array"पूर्ण,
	अणु0x07279900, 0, IPR_DEFAULT_LOG_LEVEL,
	"9063: Maximum number of functional arrays has been exceeded"पूर्ण,
	अणु0x07279A00, 0, 0,
	"Data protect, other volume set problem"पूर्ण,
	अणु0x0B260000, 0, 0,
	"Aborted command, invalid descriptor"पूर्ण,
	अणु0x0B3F9000, 0, 0,
	"Target operating conditions have changed, dual adapter takeover"पूर्ण,
	अणु0x0B530200, 0, 0,
	"Aborted command, medium removal prevented"पूर्ण,
	अणु0x0B5A0000, 0, 0,
	"Command terminated by host"पूर्ण,
	अणु0x0B5B8000, 0, 0,
	"Aborted command, command terminated by host"पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ipr_ses_table_entry ipr_ses_table[] = अणु
	अणु "2104-DL1        ", "XXXXXXXXXXXXXXXX", 80 पूर्ण,
	अणु "2104-TL1        ", "XXXXXXXXXXXXXXXX", 80 पूर्ण,
	अणु "HSBP07M P U2SCSI", "XXXXXXXXXXXXXXXX", 80 पूर्ण, /* Hiभागe 7 slot */
	अणु "HSBP05M P U2SCSI", "XXXXXXXXXXXXXXXX", 80 पूर्ण, /* Hiभागe 5 slot */
	अणु "HSBP05M S U2SCSI", "XXXXXXXXXXXXXXXX", 80 पूर्ण, /* Bowtie */
	अणु "HSBP06E ASU2SCSI", "XXXXXXXXXXXXXXXX", 80 पूर्ण, /* MartinFenning */
	अणु "2104-DU3        ", "XXXXXXXXXXXXXXXX", 160 पूर्ण,
	अणु "2104-TU3        ", "XXXXXXXXXXXXXXXX", 160 पूर्ण,
	अणु "HSBP04C RSU2SCSI", "XXXXXXX*XXXXXXXX", 160 पूर्ण,
	अणु "HSBP06E RSU2SCSI", "XXXXXXX*XXXXXXXX", 160 पूर्ण,
	अणु "St  V1S2        ", "XXXXXXXXXXXXXXXX", 160 पूर्ण,
	अणु "HSBPD4M  PU3SCSI", "XXXXXXX*XXXXXXXX", 160 पूर्ण,
	अणु "VSBPD1H   U3SCSI", "XXXXXXX*XXXXXXXX", 160 पूर्ण
पूर्ण;

/*
 *  Function Prototypes
 */
अटल पूर्णांक ipr_reset_alert(काष्ठा ipr_cmnd *);
अटल व्योम ipr_process_ccn(काष्ठा ipr_cmnd *);
अटल व्योम ipr_process_error(काष्ठा ipr_cmnd *);
अटल व्योम ipr_reset_ioa_job(काष्ठा ipr_cmnd *);
अटल व्योम ipr_initiate_ioa_reset(काष्ठा ipr_ioa_cfg *,
				   क्रमागत ipr_shutकरोwn_type);

#अगर_घोषित CONFIG_SCSI_IPR_TRACE
/**
 * ipr_trc_hook - Add a trace entry to the driver trace
 * @ipr_cmd:	ipr command काष्ठा
 * @type:		trace type
 * @add_data:	additional data
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_trc_hook(काष्ठा ipr_cmnd *ipr_cmd,
			 u8 type, u32 add_data)
अणु
	काष्ठा ipr_trace_entry *trace_entry;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	अचिन्हित पूर्णांक trace_index;

	trace_index = atomic_add_वापस(1, &ioa_cfg->trace_index) & IPR_TRACE_INDEX_MASK;
	trace_entry = &ioa_cfg->trace[trace_index];
	trace_entry->समय = jअगरfies;
	trace_entry->op_code = ipr_cmd->ioarcb.cmd_pkt.cdb[0];
	trace_entry->type = type;
	अगर (ipr_cmd->ioa_cfg->sis64)
		trace_entry->ata_op_code = ipr_cmd->i.ata_ioadl.regs.command;
	अन्यथा
		trace_entry->ata_op_code = ipr_cmd->ioarcb.u.add_data.u.regs.command;
	trace_entry->cmd_index = ipr_cmd->cmd_index & 0xff;
	trace_entry->res_handle = ipr_cmd->ioarcb.res_handle;
	trace_entry->u.add_data = add_data;
	wmb();
पूर्ण
#अन्यथा
#घोषणा ipr_trc_hook(ipr_cmd, type, add_data) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * ipr_lock_and_करोne - Acquire lock and complete command
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 *	none
 **/
अटल व्योम ipr_lock_and_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ipr_cmd->करोne(ipr_cmd);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
पूर्ण

/**
 * ipr_reinit_ipr_cmnd - Re-initialize an IPR Cmnd block क्रम reuse
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_reinit_ipr_cmnd(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	काष्ठा ipr_ioasa64 *ioasa64 = &ipr_cmd->s.ioasa64;
	dma_addr_t dma_addr = ipr_cmd->dma_addr;
	पूर्णांक hrrq_id;

	hrrq_id = ioarcb->cmd_pkt.hrrq_id;
	स_रखो(&ioarcb->cmd_pkt, 0, माप(काष्ठा ipr_cmd_pkt));
	ioarcb->cmd_pkt.hrrq_id = hrrq_id;
	ioarcb->data_transfer_length = 0;
	ioarcb->पढ़ो_data_transfer_length = 0;
	ioarcb->ioadl_len = 0;
	ioarcb->पढ़ो_ioadl_len = 0;

	अगर (ipr_cmd->ioa_cfg->sis64) अणु
		ioarcb->u.sis64_addr_data.data_ioadl_addr =
			cpu_to_be64(dma_addr + दुरत्व(काष्ठा ipr_cmnd, i.ioadl64));
		ioasa64->u.gata.status = 0;
	पूर्ण अन्यथा अणु
		ioarcb->ग_लिखो_ioadl_addr =
			cpu_to_be32(dma_addr + दुरत्व(काष्ठा ipr_cmnd, i.ioadl));
		ioarcb->पढ़ो_ioadl_addr = ioarcb->ग_लिखो_ioadl_addr;
		ioasa->u.gata.status = 0;
	पूर्ण

	ioasa->hdr.ioasc = 0;
	ioasa->hdr.residual_data_len = 0;
	ipr_cmd->scsi_cmd = शून्य;
	ipr_cmd->qc = शून्य;
	ipr_cmd->sense_buffer[0] = 0;
	ipr_cmd->dma_use_sg = 0;
पूर्ण

/**
 * ipr_init_ipr_cmnd - Initialize an IPR Cmnd block
 * @ipr_cmd:	ipr command काष्ठा
 * @fast_करोne:	fast करोne function call-back
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_init_ipr_cmnd(काष्ठा ipr_cmnd *ipr_cmd,
			      व्योम (*fast_करोne) (काष्ठा ipr_cmnd *))
अणु
	ipr_reinit_ipr_cmnd(ipr_cmd);
	ipr_cmd->u.scratch = 0;
	ipr_cmd->sibling = शून्य;
	ipr_cmd->eh_comp = शून्य;
	ipr_cmd->fast_करोne = fast_करोne;
	समयr_setup(&ipr_cmd->समयr, शून्य, 0);
पूर्ण

/**
 * __ipr_get_मुक्त_ipr_cmnd - Get a मुक्त IPR Cmnd block
 * @hrrq:	hrr queue
 *
 * Return value:
 * 	poपूर्णांकer to ipr command काष्ठा
 **/
अटल
काष्ठा ipr_cmnd *__ipr_get_मुक्त_ipr_cmnd(काष्ठा ipr_hrr_queue *hrrq)
अणु
	काष्ठा ipr_cmnd *ipr_cmd = शून्य;

	अगर (likely(!list_empty(&hrrq->hrrq_मुक्त_q))) अणु
		ipr_cmd = list_entry(hrrq->hrrq_मुक्त_q.next,
			काष्ठा ipr_cmnd, queue);
		list_del(&ipr_cmd->queue);
	पूर्ण


	वापस ipr_cmd;
पूर्ण

/**
 * ipr_get_मुक्त_ipr_cmnd - Get a मुक्त IPR Cmnd block and initialize it
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 *	poपूर्णांकer to ipr command काष्ठा
 **/
अटल
काष्ठा ipr_cmnd *ipr_get_मुक्त_ipr_cmnd(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा ipr_cmnd *ipr_cmd =
		__ipr_get_मुक्त_ipr_cmnd(&ioa_cfg->hrrq[IPR_INIT_HRRQ]);
	ipr_init_ipr_cmnd(ipr_cmd, ipr_lock_and_करोne);
	वापस ipr_cmd;
पूर्ण

/**
 * ipr_mask_and_clear_पूर्णांकerrupts - Mask all and clear specअगरied पूर्णांकerrupts
 * @ioa_cfg:	ioa config काष्ठा
 * @clr_पूर्णांकs:     पूर्णांकerrupts to clear
 *
 * This function masks all पूर्णांकerrupts on the adapter, then clears the
 * पूर्णांकerrupts specअगरied in the mask
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_mask_and_clear_पूर्णांकerrupts(काष्ठा ipr_ioa_cfg *ioa_cfg,
					  u32 clr_पूर्णांकs)
अणु
	पूर्णांक i;

	/* Stop new पूर्णांकerrupts */
	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_पूर्णांकerrupts = 0;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	पूर्ण

	/* Set पूर्णांकerrupt mask to stop all new पूर्णांकerrupts */
	अगर (ioa_cfg->sis64)
		ग_लिखोq(~0, ioa_cfg->regs.set_पूर्णांकerrupt_mask_reg);
	अन्यथा
		ग_लिखोl(~0, ioa_cfg->regs.set_पूर्णांकerrupt_mask_reg);

	/* Clear any pending पूर्णांकerrupts */
	अगर (ioa_cfg->sis64)
		ग_लिखोl(~0, ioa_cfg->regs.clr_पूर्णांकerrupt_reg);
	ग_लिखोl(clr_पूर्णांकs, ioa_cfg->regs.clr_पूर्णांकerrupt_reg32);
	पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg);
पूर्ण

/**
 * ipr_save_pcix_cmd_reg - Save PCI-X command रेजिस्टर
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	0 on success / -EIO on failure
 **/
अटल पूर्णांक ipr_save_pcix_cmd_reg(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक pcix_cmd_reg = pci_find_capability(ioa_cfg->pdev, PCI_CAP_ID_PCIX);

	अगर (pcix_cmd_reg == 0)
		वापस 0;

	अगर (pci_पढ़ो_config_word(ioa_cfg->pdev, pcix_cmd_reg + PCI_X_CMD,
				 &ioa_cfg->saved_pcix_cmd_reg) != PCIBIOS_SUCCESSFUL) अणु
		dev_err(&ioa_cfg->pdev->dev, "Failed to save PCI-X command register\n");
		वापस -EIO;
	पूर्ण

	ioa_cfg->saved_pcix_cmd_reg |= PCI_X_CMD_DPERR_E | PCI_X_CMD_ERO;
	वापस 0;
पूर्ण

/**
 * ipr_set_pcix_cmd_reg - Setup PCI-X command रेजिस्टर
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	0 on success / -EIO on failure
 **/
अटल पूर्णांक ipr_set_pcix_cmd_reg(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक pcix_cmd_reg = pci_find_capability(ioa_cfg->pdev, PCI_CAP_ID_PCIX);

	अगर (pcix_cmd_reg) अणु
		अगर (pci_ग_लिखो_config_word(ioa_cfg->pdev, pcix_cmd_reg + PCI_X_CMD,
					  ioa_cfg->saved_pcix_cmd_reg) != PCIBIOS_SUCCESSFUL) अणु
			dev_err(&ioa_cfg->pdev->dev, "Failed to setup PCI-X command register\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __ipr_sata_eh_करोne - करोne function क्रम पातed SATA commands
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is invoked क्रम ops generated to SATA
 * devices which are being पातed.
 *
 * Return value:
 * 	none
 **/
अटल व्योम __ipr_sata_eh_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ata_queued_cmd *qc = ipr_cmd->qc;
	काष्ठा ipr_sata_port *sata_port = qc->ap->निजी_data;

	qc->err_mask |= AC_ERR_OTHER;
	sata_port->ioasa.status |= ATA_BUSY;
	ata_qc_complete(qc);
	अगर (ipr_cmd->eh_comp)
		complete(ipr_cmd->eh_comp);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
पूर्ण

/**
 * ipr_sata_eh_करोne - करोne function क्रम पातed SATA commands
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is invoked क्रम ops generated to SATA
 * devices which are being पातed.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_sata_eh_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_hrr_queue *hrrq = ipr_cmd->hrrq;
	अचिन्हित दीर्घ hrrq_flags;

	spin_lock_irqsave(&hrrq->_lock, hrrq_flags);
	__ipr_sata_eh_करोne(ipr_cmd);
	spin_unlock_irqrestore(&hrrq->_lock, hrrq_flags);
पूर्ण

/**
 * __ipr_scsi_eh_करोne - mid-layer करोne function क्रम पातed ops
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is invoked by the पूर्णांकerrupt handler क्रम
 * ops generated by the SCSI mid-layer which are being पातed.
 *
 * Return value:
 * 	none
 **/
अटल व्योम __ipr_scsi_eh_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;

	scsi_cmd->result |= (DID_ERROR << 16);

	scsi_dma_unmap(ipr_cmd->scsi_cmd);
	scsi_cmd->scsi_करोne(scsi_cmd);
	अगर (ipr_cmd->eh_comp)
		complete(ipr_cmd->eh_comp);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
पूर्ण

/**
 * ipr_scsi_eh_करोne - mid-layer करोne function क्रम पातed ops
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is invoked by the पूर्णांकerrupt handler क्रम
 * ops generated by the SCSI mid-layer which are being पातed.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_scsi_eh_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	अचिन्हित दीर्घ hrrq_flags;
	काष्ठा ipr_hrr_queue *hrrq = ipr_cmd->hrrq;

	spin_lock_irqsave(&hrrq->_lock, hrrq_flags);
	__ipr_scsi_eh_करोne(ipr_cmd);
	spin_unlock_irqrestore(&hrrq->_lock, hrrq_flags);
पूर्ण

/**
 * ipr_fail_all_ops - Fails all outstanding ops.
 * @ioa_cfg:	ioa config काष्ठा
 *
 * This function fails all outstanding ops.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_fail_all_ops(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा ipr_cmnd *ipr_cmd, *temp;
	काष्ठा ipr_hrr_queue *hrrq;

	ENTER;
	क्रम_each_hrrq(hrrq, ioa_cfg) अणु
		spin_lock(&hrrq->_lock);
		list_क्रम_each_entry_safe(ipr_cmd,
					temp, &hrrq->hrrq_pending_q, queue) अणु
			list_del(&ipr_cmd->queue);

			ipr_cmd->s.ioasa.hdr.ioasc =
				cpu_to_be32(IPR_IOASC_IOA_WAS_RESET);
			ipr_cmd->s.ioasa.hdr.ilid =
				cpu_to_be32(IPR_DRIVER_ILID);

			अगर (ipr_cmd->scsi_cmd)
				ipr_cmd->करोne = __ipr_scsi_eh_करोne;
			अन्यथा अगर (ipr_cmd->qc)
				ipr_cmd->करोne = __ipr_sata_eh_करोne;

			ipr_trc_hook(ipr_cmd, IPR_TRACE_FINISH,
				     IPR_IOASC_IOA_WAS_RESET);
			del_समयr(&ipr_cmd->समयr);
			ipr_cmd->करोne(ipr_cmd);
		पूर्ण
		spin_unlock(&hrrq->_lock);
	पूर्ण
	LEAVE;
पूर्ण

/**
 * ipr_send_command -  Send driver initiated requests.
 * @ipr_cmd:		ipr command काष्ठा
 *
 * This function sends a command to the adapter using the correct ग_लिखो call.
 * In the हाल of sis64, calculate the ioarcb size required. Then or in the
 * appropriate bits.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_send_command(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	dma_addr_t send_dma_addr = ipr_cmd->dma_addr;

	अगर (ioa_cfg->sis64) अणु
		/* The शेष size is 256 bytes */
		send_dma_addr |= 0x1;

		/* If the number of ioadls * size of ioadl > 128 bytes,
		   then use a 512 byte ioarcb */
		अगर (ipr_cmd->dma_use_sg * माप(काष्ठा ipr_ioadl64_desc) > 128 )
			send_dma_addr |= 0x4;
		ग_लिखोq(send_dma_addr, ioa_cfg->regs.ioarrin_reg);
	पूर्ण अन्यथा
		ग_लिखोl(send_dma_addr, ioa_cfg->regs.ioarrin_reg);
पूर्ण

/**
 * ipr_करो_req -  Send driver initiated requests.
 * @ipr_cmd:		ipr command काष्ठा
 * @करोne:			करोne function
 * @समयout_func:	समयout function
 * @समयout:		समयout value
 *
 * This function sends the specअगरied command to the adapter with the
 * समयout given. The करोne function is invoked on command completion.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_करो_req(काष्ठा ipr_cmnd *ipr_cmd,
		       व्योम (*करोne) (काष्ठा ipr_cmnd *),
		       व्योम (*समयout_func) (काष्ठा समयr_list *), u32 समयout)
अणु
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);

	ipr_cmd->करोne = करोne;

	ipr_cmd->समयr.expires = jअगरfies + समयout;
	ipr_cmd->समयr.function = समयout_func;

	add_समयr(&ipr_cmd->समयr);

	ipr_trc_hook(ipr_cmd, IPR_TRACE_START, 0);

	ipr_send_command(ipr_cmd);
पूर्ण

/**
 * ipr_पूर्णांकernal_cmd_करोne - Op करोne function क्रम an पूर्णांकernally generated op.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is the op करोne function क्रम an पूर्णांकernally generated,
 * blocking op. It simply wakes the sleeping thपढ़ो.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_पूर्णांकernal_cmd_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	अगर (ipr_cmd->sibling)
		ipr_cmd->sibling = शून्य;
	अन्यथा
		complete(&ipr_cmd->completion);
पूर्ण

/**
 * ipr_init_ioadl - initialize the ioadl क्रम the correct SIS type
 * @ipr_cmd:	ipr command काष्ठा
 * @dma_addr:	dma address
 * @len:	transfer length
 * @flags:	ioadl flag value
 *
 * This function initializes an ioadl in the हाल where there is only a single
 * descriptor.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_init_ioadl(काष्ठा ipr_cmnd *ipr_cmd, dma_addr_t dma_addr,
			   u32 len, पूर्णांक flags)
अणु
	काष्ठा ipr_ioadl_desc *ioadl = ipr_cmd->i.ioadl;
	काष्ठा ipr_ioadl64_desc *ioadl64 = ipr_cmd->i.ioadl64;

	ipr_cmd->dma_use_sg = 1;

	अगर (ipr_cmd->ioa_cfg->sis64) अणु
		ioadl64->flags = cpu_to_be32(flags);
		ioadl64->data_len = cpu_to_be32(len);
		ioadl64->address = cpu_to_be64(dma_addr);

		ipr_cmd->ioarcb.ioadl_len =
		       	cpu_to_be32(माप(काष्ठा ipr_ioadl64_desc));
		ipr_cmd->ioarcb.data_transfer_length = cpu_to_be32(len);
	पूर्ण अन्यथा अणु
		ioadl->flags_and_data_len = cpu_to_be32(flags | len);
		ioadl->address = cpu_to_be32(dma_addr);

		अगर (flags == IPR_IOADL_FLAGS_READ_LAST) अणु
			ipr_cmd->ioarcb.पढ़ो_ioadl_len =
				cpu_to_be32(माप(काष्ठा ipr_ioadl_desc));
			ipr_cmd->ioarcb.पढ़ो_data_transfer_length = cpu_to_be32(len);
		पूर्ण अन्यथा अणु
			ipr_cmd->ioarcb.ioadl_len =
			       	cpu_to_be32(माप(काष्ठा ipr_ioadl_desc));
			ipr_cmd->ioarcb.data_transfer_length = cpu_to_be32(len);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ipr_send_blocking_cmd - Send command and sleep on its completion.
 * @ipr_cmd:	ipr command काष्ठा
 * @समयout_func:	function to invoke अगर command बार out
 * @समयout:	समयout
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_send_blocking_cmd(काष्ठा ipr_cmnd *ipr_cmd,
				  व्योम (*समयout_func) (काष्ठा समयr_list *),
				  u32 समयout)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	init_completion(&ipr_cmd->completion);
	ipr_करो_req(ipr_cmd, ipr_पूर्णांकernal_cmd_करोne, समयout_func, समयout);

	spin_unlock_irq(ioa_cfg->host->host_lock);
	रुको_क्रम_completion(&ipr_cmd->completion);
	spin_lock_irq(ioa_cfg->host->host_lock);
पूर्ण

अटल पूर्णांक ipr_get_hrrq_index(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	अचिन्हित पूर्णांक hrrq;

	अगर (ioa_cfg->hrrq_num == 1)
		hrrq = 0;
	अन्यथा अणु
		hrrq = atomic_add_वापस(1, &ioa_cfg->hrrq_index);
		hrrq = (hrrq % (ioa_cfg->hrrq_num - 1)) + 1;
	पूर्ण
	वापस hrrq;
पूर्ण

/**
 * ipr_send_hcam - Send an HCAM to the adapter.
 * @ioa_cfg:	ioa config काष्ठा
 * @type:		HCAM type
 * @hostrcb:	hostrcb काष्ठा
 *
 * This function will send a Host Controlled Async command to the adapter.
 * If HCAMs are currently not allowed to be issued to the adapter, it will
 * place the hostrcb on the मुक्त queue.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_send_hcam(काष्ठा ipr_ioa_cfg *ioa_cfg, u8 type,
			  काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioarcb *ioarcb;

	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].allow_cmds) अणु
		ipr_cmd = ipr_get_मुक्त_ipr_cmnd(ioa_cfg);
		list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);
		list_add_tail(&hostrcb->queue, &ioa_cfg->hostrcb_pending_q);

		ipr_cmd->u.hostrcb = hostrcb;
		ioarcb = &ipr_cmd->ioarcb;

		ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
		ioarcb->cmd_pkt.request_type = IPR_RQTYPE_HCAM;
		ioarcb->cmd_pkt.cdb[0] = IPR_HOST_CONTROLLED_ASYNC;
		ioarcb->cmd_pkt.cdb[1] = type;
		ioarcb->cmd_pkt.cdb[7] = (माप(hostrcb->hcam) >> 8) & 0xff;
		ioarcb->cmd_pkt.cdb[8] = माप(hostrcb->hcam) & 0xff;

		ipr_init_ioadl(ipr_cmd, hostrcb->hostrcb_dma,
			       माप(hostrcb->hcam), IPR_IOADL_FLAGS_READ_LAST);

		अगर (type == IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE)
			ipr_cmd->करोne = ipr_process_ccn;
		अन्यथा
			ipr_cmd->करोne = ipr_process_error;

		ipr_trc_hook(ipr_cmd, IPR_TRACE_START, IPR_IOA_RES_ADDR);

		ipr_send_command(ipr_cmd);
	पूर्ण अन्यथा अणु
		list_add_tail(&hostrcb->queue, &ioa_cfg->hostrcb_मुक्त_q);
	पूर्ण
पूर्ण

/**
 * ipr_update_ata_class - Update the ata class in the resource entry
 * @res:	resource entry काष्ठा
 * @proto:	cfgte device bus protocol value
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_update_ata_class(काष्ठा ipr_resource_entry *res, अचिन्हित पूर्णांक proto)
अणु
	चयन (proto) अणु
	हाल IPR_PROTO_SATA:
	हाल IPR_PROTO_SAS_STP:
		res->ata_class = ATA_DEV_ATA;
		अवरोध;
	हाल IPR_PROTO_SATA_ATAPI:
	हाल IPR_PROTO_SAS_STP_ATAPI:
		res->ata_class = ATA_DEV_ATAPI;
		अवरोध;
	शेष:
		res->ata_class = ATA_DEV_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ipr_init_res_entry - Initialize a resource entry काष्ठा.
 * @res:	resource entry काष्ठा
 * @cfgtew:	config table entry wrapper काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_init_res_entry(काष्ठा ipr_resource_entry *res,
			       काष्ठा ipr_config_table_entry_wrapper *cfgtew)
अणु
	पूर्णांक found = 0;
	अचिन्हित पूर्णांक proto;
	काष्ठा ipr_ioa_cfg *ioa_cfg = res->ioa_cfg;
	काष्ठा ipr_resource_entry *gscsi_res = शून्य;

	res->needs_sync_complete = 0;
	res->in_erp = 0;
	res->add_to_ml = 0;
	res->del_from_ml = 0;
	res->resetting_device = 0;
	res->reset_occurred = 0;
	res->sdev = शून्य;
	res->sata_port = शून्य;

	अगर (ioa_cfg->sis64) अणु
		proto = cfgtew->u.cfgte64->proto;
		res->flags = be16_to_cpu(cfgtew->u.cfgte64->flags);
		res->res_flags = be16_to_cpu(cfgtew->u.cfgte64->res_flags);
		res->qmodel = IPR_QUEUEING_MODEL64(res);
		res->type = cfgtew->u.cfgte64->res_type;

		स_नकल(res->res_path, &cfgtew->u.cfgte64->res_path,
			माप(res->res_path));

		res->bus = 0;
		स_नकल(&res->dev_lun.scsi_lun, &cfgtew->u.cfgte64->lun,
			माप(res->dev_lun.scsi_lun));
		res->lun = scsilun_to_पूर्णांक(&res->dev_lun);

		अगर (res->type == IPR_RES_TYPE_GENERIC_SCSI) अणु
			list_क्रम_each_entry(gscsi_res, &ioa_cfg->used_res_q, queue) अणु
				अगर (gscsi_res->dev_id == cfgtew->u.cfgte64->dev_id) अणु
					found = 1;
					res->target = gscsi_res->target;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!found) अणु
				res->target = find_first_zero_bit(ioa_cfg->target_ids,
								  ioa_cfg->max_devs_supported);
				set_bit(res->target, ioa_cfg->target_ids);
			पूर्ण
		पूर्ण अन्यथा अगर (res->type == IPR_RES_TYPE_IOAFP) अणु
			res->bus = IPR_IOAFP_VIRTUAL_BUS;
			res->target = 0;
		पूर्ण अन्यथा अगर (res->type == IPR_RES_TYPE_ARRAY) अणु
			res->bus = IPR_ARRAY_VIRTUAL_BUS;
			res->target = find_first_zero_bit(ioa_cfg->array_ids,
							  ioa_cfg->max_devs_supported);
			set_bit(res->target, ioa_cfg->array_ids);
		पूर्ण अन्यथा अगर (res->type == IPR_RES_TYPE_VOLUME_SET) अणु
			res->bus = IPR_VSET_VIRTUAL_BUS;
			res->target = find_first_zero_bit(ioa_cfg->vset_ids,
							  ioa_cfg->max_devs_supported);
			set_bit(res->target, ioa_cfg->vset_ids);
		पूर्ण अन्यथा अणु
			res->target = find_first_zero_bit(ioa_cfg->target_ids,
							  ioa_cfg->max_devs_supported);
			set_bit(res->target, ioa_cfg->target_ids);
		पूर्ण
	पूर्ण अन्यथा अणु
		proto = cfgtew->u.cfgte->proto;
		res->qmodel = IPR_QUEUEING_MODEL(res);
		res->flags = cfgtew->u.cfgte->flags;
		अगर (res->flags & IPR_IS_IOA_RESOURCE)
			res->type = IPR_RES_TYPE_IOAFP;
		अन्यथा
			res->type = cfgtew->u.cfgte->rsvd_subtype & 0x0f;

		res->bus = cfgtew->u.cfgte->res_addr.bus;
		res->target = cfgtew->u.cfgte->res_addr.target;
		res->lun = cfgtew->u.cfgte->res_addr.lun;
		res->lun_wwn = get_unaligned_be64(cfgtew->u.cfgte->lun_wwn);
	पूर्ण

	ipr_update_ata_class(res, proto);
पूर्ण

/**
 * ipr_is_same_device - Determine अगर two devices are the same.
 * @res:	resource entry काष्ठा
 * @cfgtew:	config table entry wrapper काष्ठा
 *
 * Return value:
 * 	1 अगर the devices are the same / 0 otherwise
 **/
अटल पूर्णांक ipr_is_same_device(काष्ठा ipr_resource_entry *res,
			      काष्ठा ipr_config_table_entry_wrapper *cfgtew)
अणु
	अगर (res->ioa_cfg->sis64) अणु
		अगर (!स_भेद(&res->dev_id, &cfgtew->u.cfgte64->dev_id,
					माप(cfgtew->u.cfgte64->dev_id)) &&
			!स_भेद(&res->dev_lun.scsi_lun, &cfgtew->u.cfgte64->lun,
					माप(cfgtew->u.cfgte64->lun))) अणु
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (res->bus == cfgtew->u.cfgte->res_addr.bus &&
		    res->target == cfgtew->u.cfgte->res_addr.target &&
		    res->lun == cfgtew->u.cfgte->res_addr.lun)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __ipr_क्रमmat_res_path - Format the resource path क्रम prपूर्णांकing.
 * @res_path:	resource path
 * @buffer:	buffer
 * @len:	length of buffer provided
 *
 * Return value:
 * 	poपूर्णांकer to buffer
 **/
अटल अक्षर *__ipr_क्रमmat_res_path(u8 *res_path, अक्षर *buffer, पूर्णांक len)
अणु
	पूर्णांक i;
	अक्षर *p = buffer;

	*p = '\0';
	p += scnम_लिखो(p, buffer + len - p, "%02X", res_path[0]);
	क्रम (i = 1; res_path[i] != 0xff && ((i * 3) < len); i++)
		p += scnम_लिखो(p, buffer + len - p, "-%02X", res_path[i]);

	वापस buffer;
पूर्ण

/**
 * ipr_क्रमmat_res_path - Format the resource path क्रम prपूर्णांकing.
 * @ioa_cfg:	ioa config काष्ठा
 * @res_path:	resource path
 * @buffer:	buffer
 * @len:	length of buffer provided
 *
 * Return value:
 *	poपूर्णांकer to buffer
 **/
अटल अक्षर *ipr_क्रमmat_res_path(काष्ठा ipr_ioa_cfg *ioa_cfg,
				 u8 *res_path, अक्षर *buffer, पूर्णांक len)
अणु
	अक्षर *p = buffer;

	*p = '\0';
	p += scnम_लिखो(p, buffer + len - p, "%d/", ioa_cfg->host->host_no);
	__ipr_क्रमmat_res_path(res_path, p, len - (buffer - p));
	वापस buffer;
पूर्ण

/**
 * ipr_update_res_entry - Update the resource entry.
 * @res:	resource entry काष्ठा
 * @cfgtew:	config table entry wrapper काष्ठा
 *
 * Return value:
 *      none
 **/
अटल व्योम ipr_update_res_entry(काष्ठा ipr_resource_entry *res,
				 काष्ठा ipr_config_table_entry_wrapper *cfgtew)
अणु
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];
	अचिन्हित पूर्णांक proto;
	पूर्णांक new_path = 0;

	अगर (res->ioa_cfg->sis64) अणु
		res->flags = be16_to_cpu(cfgtew->u.cfgte64->flags);
		res->res_flags = be16_to_cpu(cfgtew->u.cfgte64->res_flags);
		res->type = cfgtew->u.cfgte64->res_type;

		स_नकल(&res->std_inq_data, &cfgtew->u.cfgte64->std_inq_data,
			माप(काष्ठा ipr_std_inq_data));

		res->qmodel = IPR_QUEUEING_MODEL64(res);
		proto = cfgtew->u.cfgte64->proto;
		res->res_handle = cfgtew->u.cfgte64->res_handle;
		res->dev_id = cfgtew->u.cfgte64->dev_id;

		स_नकल(&res->dev_lun.scsi_lun, &cfgtew->u.cfgte64->lun,
			माप(res->dev_lun.scsi_lun));

		अगर (स_भेद(res->res_path, &cfgtew->u.cfgte64->res_path,
					माप(res->res_path))) अणु
			स_नकल(res->res_path, &cfgtew->u.cfgte64->res_path,
				माप(res->res_path));
			new_path = 1;
		पूर्ण

		अगर (res->sdev && new_path)
			sdev_prपूर्णांकk(KERN_INFO, res->sdev, "Resource path: %s\n",
				    ipr_क्रमmat_res_path(res->ioa_cfg,
					res->res_path, buffer, माप(buffer)));
	पूर्ण अन्यथा अणु
		res->flags = cfgtew->u.cfgte->flags;
		अगर (res->flags & IPR_IS_IOA_RESOURCE)
			res->type = IPR_RES_TYPE_IOAFP;
		अन्यथा
			res->type = cfgtew->u.cfgte->rsvd_subtype & 0x0f;

		स_नकल(&res->std_inq_data, &cfgtew->u.cfgte->std_inq_data,
			माप(काष्ठा ipr_std_inq_data));

		res->qmodel = IPR_QUEUEING_MODEL(res);
		proto = cfgtew->u.cfgte->proto;
		res->res_handle = cfgtew->u.cfgte->res_handle;
	पूर्ण

	ipr_update_ata_class(res, proto);
पूर्ण

/**
 * ipr_clear_res_target - Clear the bit in the bit map representing the target
 * 			  क्रम the resource.
 * @res:	resource entry काष्ठा
 *
 * Return value:
 *      none
 **/
अटल व्योम ipr_clear_res_target(काष्ठा ipr_resource_entry *res)
अणु
	काष्ठा ipr_resource_entry *gscsi_res = शून्य;
	काष्ठा ipr_ioa_cfg *ioa_cfg = res->ioa_cfg;

	अगर (!ioa_cfg->sis64)
		वापस;

	अगर (res->bus == IPR_ARRAY_VIRTUAL_BUS)
		clear_bit(res->target, ioa_cfg->array_ids);
	अन्यथा अगर (res->bus == IPR_VSET_VIRTUAL_BUS)
		clear_bit(res->target, ioa_cfg->vset_ids);
	अन्यथा अगर (res->bus == 0 && res->type == IPR_RES_TYPE_GENERIC_SCSI) अणु
		list_क्रम_each_entry(gscsi_res, &ioa_cfg->used_res_q, queue)
			अगर (gscsi_res->dev_id == res->dev_id && gscsi_res != res)
				वापस;
		clear_bit(res->target, ioa_cfg->target_ids);

	पूर्ण अन्यथा अगर (res->bus == 0)
		clear_bit(res->target, ioa_cfg->target_ids);
पूर्ण

/**
 * ipr_handle_config_change - Handle a config change from the adapter
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_handle_config_change(काष्ठा ipr_ioa_cfg *ioa_cfg,
				     काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_resource_entry *res = शून्य;
	काष्ठा ipr_config_table_entry_wrapper cfgtew;
	__be32 cc_res_handle;

	u32 is_ndn = 1;

	अगर (ioa_cfg->sis64) अणु
		cfgtew.u.cfgte64 = &hostrcb->hcam.u.ccn.u.cfgte64;
		cc_res_handle = cfgtew.u.cfgte64->res_handle;
	पूर्ण अन्यथा अणु
		cfgtew.u.cfgte = &hostrcb->hcam.u.ccn.u.cfgte;
		cc_res_handle = cfgtew.u.cfgte->res_handle;
	पूर्ण

	list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
		अगर (res->res_handle == cc_res_handle) अणु
			is_ndn = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (is_ndn) अणु
		अगर (list_empty(&ioa_cfg->मुक्त_res_q)) अणु
			ipr_send_hcam(ioa_cfg,
				      IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE,
				      hostrcb);
			वापस;
		पूर्ण

		res = list_entry(ioa_cfg->मुक्त_res_q.next,
				 काष्ठा ipr_resource_entry, queue);

		list_del(&res->queue);
		ipr_init_res_entry(res, &cfgtew);
		list_add_tail(&res->queue, &ioa_cfg->used_res_q);
	पूर्ण

	ipr_update_res_entry(res, &cfgtew);

	अगर (hostrcb->hcam.notअगरy_type == IPR_HOST_RCB_NOTIF_TYPE_REM_ENTRY) अणु
		अगर (res->sdev) अणु
			res->del_from_ml = 1;
			res->res_handle = IPR_INVALID_RES_HANDLE;
			schedule_work(&ioa_cfg->work_q);
		पूर्ण अन्यथा अणु
			ipr_clear_res_target(res);
			list_move_tail(&res->queue, &ioa_cfg->मुक्त_res_q);
		पूर्ण
	पूर्ण अन्यथा अगर (!res->sdev || res->del_from_ml) अणु
		res->add_to_ml = 1;
		schedule_work(&ioa_cfg->work_q);
	पूर्ण

	ipr_send_hcam(ioa_cfg, IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE, hostrcb);
पूर्ण

/**
 * ipr_process_ccn - Op करोne function क्रम a CCN.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is the op करोne function क्रम a configuration
 * change notअगरication host controlled async from the adapter.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_process_ccn(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_hostrcb *hostrcb = ipr_cmd->u.hostrcb;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	list_del_init(&hostrcb->queue);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);

	अगर (ioasc) अणु
		अगर (ioasc != IPR_IOASC_IOA_WAS_RESET &&
		    ioasc != IPR_IOASC_ABORTED_CMD_TERM_BY_HOST)
			dev_err(&ioa_cfg->pdev->dev,
				"Host RCB failed with IOASC: 0x%08X\n", ioasc);

		ipr_send_hcam(ioa_cfg, IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE, hostrcb);
	पूर्ण अन्यथा अणु
		ipr_handle_config_change(ioa_cfg, hostrcb);
	पूर्ण
पूर्ण

/**
 * strip_and_pad_whitespace - Strip and pad trailing whitespace.
 * @i:		index पूर्णांकo buffer
 * @buf:		string to modअगरy
 *
 * This function will strip all trailing whitespace, pad the end
 * of the string with a single space, and शून्य terminate the string.
 *
 * Return value:
 * 	new length of string
 **/
अटल पूर्णांक strip_and_pad_whitespace(पूर्णांक i, अक्षर *buf)
अणु
	जबतक (i && buf[i] == ' ')
		i--;
	buf[i+1] = ' ';
	buf[i+2] = '\0';
	वापस i + 2;
पूर्ण

/**
 * ipr_log_vpd_compact - Log the passed extended VPD compactly.
 * @prefix:		string to prपूर्णांक at start of prपूर्णांकk
 * @hostrcb:	hostrcb poपूर्णांकer
 * @vpd:		venकरोr/product id/sn काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_vpd_compact(अक्षर *prefix, काष्ठा ipr_hostrcb *hostrcb,
				काष्ठा ipr_vpd *vpd)
अणु
	अक्षर buffer[IPR_VENDOR_ID_LEN + IPR_PROD_ID_LEN + IPR_SERIAL_NUM_LEN + 3];
	पूर्णांक i = 0;

	स_नकल(buffer, vpd->vpids.venकरोr_id, IPR_VENDOR_ID_LEN);
	i = strip_and_pad_whitespace(IPR_VENDOR_ID_LEN - 1, buffer);

	स_नकल(&buffer[i], vpd->vpids.product_id, IPR_PROD_ID_LEN);
	i = strip_and_pad_whitespace(i + IPR_PROD_ID_LEN - 1, buffer);

	स_नकल(&buffer[i], vpd->sn, IPR_SERIAL_NUM_LEN);
	buffer[IPR_SERIAL_NUM_LEN + i] = '\0';

	ipr_hcam_err(hostrcb, "%s VPID/SN: %s\n", prefix, buffer);
पूर्ण

/**
 * ipr_log_vpd - Log the passed VPD to the error log.
 * @vpd:		venकरोr/product id/sn काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_vpd(काष्ठा ipr_vpd *vpd)
अणु
	अक्षर buffer[IPR_VENDOR_ID_LEN + IPR_PROD_ID_LEN
		    + IPR_SERIAL_NUM_LEN];

	स_नकल(buffer, vpd->vpids.venकरोr_id, IPR_VENDOR_ID_LEN);
	स_नकल(buffer + IPR_VENDOR_ID_LEN, vpd->vpids.product_id,
	       IPR_PROD_ID_LEN);
	buffer[IPR_VENDOR_ID_LEN + IPR_PROD_ID_LEN] = '\0';
	ipr_err("Vendor/Product ID: %s\n", buffer);

	स_नकल(buffer, vpd->sn, IPR_SERIAL_NUM_LEN);
	buffer[IPR_SERIAL_NUM_LEN] = '\0';
	ipr_err("    Serial Number: %s\n", buffer);
पूर्ण

/**
 * ipr_log_ext_vpd_compact - Log the passed extended VPD compactly.
 * @prefix:		string to prपूर्णांक at start of prपूर्णांकk
 * @hostrcb:	hostrcb poपूर्णांकer
 * @vpd:		venकरोr/product id/sn/wwn काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_ext_vpd_compact(अक्षर *prefix, काष्ठा ipr_hostrcb *hostrcb,
				    काष्ठा ipr_ext_vpd *vpd)
अणु
	ipr_log_vpd_compact(prefix, hostrcb, &vpd->vpd);
	ipr_hcam_err(hostrcb, "%s WWN: %08X%08X\n", prefix,
		     be32_to_cpu(vpd->wwid[0]), be32_to_cpu(vpd->wwid[1]));
पूर्ण

/**
 * ipr_log_ext_vpd - Log the passed extended VPD to the error log.
 * @vpd:		venकरोr/product id/sn/wwn काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_ext_vpd(काष्ठा ipr_ext_vpd *vpd)
अणु
	ipr_log_vpd(&vpd->vpd);
	ipr_err("    WWN: %08X%08X\n", be32_to_cpu(vpd->wwid[0]),
		be32_to_cpu(vpd->wwid[1]));
पूर्ण

/**
 * ipr_log_enhanced_cache_error - Log a cache error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_enhanced_cache_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
					 काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_12_error *error;

	अगर (ioa_cfg->sis64)
		error = &hostrcb->hcam.u.error64.u.type_12_error;
	अन्यथा
		error = &hostrcb->hcam.u.error.u.type_12_error;

	ipr_err("-----Current Configuration-----\n");
	ipr_err("Cache Directory Card Information:\n");
	ipr_log_ext_vpd(&error->ioa_vpd);
	ipr_err("Adapter Card Information:\n");
	ipr_log_ext_vpd(&error->cfc_vpd);

	ipr_err("-----Expected Configuration-----\n");
	ipr_err("Cache Directory Card Information:\n");
	ipr_log_ext_vpd(&error->ioa_last_attached_to_cfc_vpd);
	ipr_err("Adapter Card Information:\n");
	ipr_log_ext_vpd(&error->cfc_last_attached_to_ioa_vpd);

	ipr_err("Additional IOA Data: %08X %08X %08X\n",
		     be32_to_cpu(error->ioa_data[0]),
		     be32_to_cpu(error->ioa_data[1]),
		     be32_to_cpu(error->ioa_data[2]));
पूर्ण

/**
 * ipr_log_cache_error - Log a cache error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_cache_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_02_error *error =
		&hostrcb->hcam.u.error.u.type_02_error;

	ipr_err("-----Current Configuration-----\n");
	ipr_err("Cache Directory Card Information:\n");
	ipr_log_vpd(&error->ioa_vpd);
	ipr_err("Adapter Card Information:\n");
	ipr_log_vpd(&error->cfc_vpd);

	ipr_err("-----Expected Configuration-----\n");
	ipr_err("Cache Directory Card Information:\n");
	ipr_log_vpd(&error->ioa_last_attached_to_cfc_vpd);
	ipr_err("Adapter Card Information:\n");
	ipr_log_vpd(&error->cfc_last_attached_to_ioa_vpd);

	ipr_err("Additional IOA Data: %08X %08X %08X\n",
		     be32_to_cpu(error->ioa_data[0]),
		     be32_to_cpu(error->ioa_data[1]),
		     be32_to_cpu(error->ioa_data[2]));
पूर्ण

/**
 * ipr_log_enhanced_config_error - Log a configuration error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_enhanced_config_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
					  काष्ठा ipr_hostrcb *hostrcb)
अणु
	पूर्णांक errors_logged, i;
	काष्ठा ipr_hostrcb_device_data_entry_enhanced *dev_entry;
	काष्ठा ipr_hostrcb_type_13_error *error;

	error = &hostrcb->hcam.u.error.u.type_13_error;
	errors_logged = be32_to_cpu(error->errors_logged);

	ipr_err("Device Errors Detected/Logged: %d/%d\n",
		be32_to_cpu(error->errors_detected), errors_logged);

	dev_entry = error->dev;

	क्रम (i = 0; i < errors_logged; i++, dev_entry++) अणु
		ipr_err_separator;

		ipr_phys_res_err(ioa_cfg, dev_entry->dev_res_addr, "Device %d", i + 1);
		ipr_log_ext_vpd(&dev_entry->vpd);

		ipr_err("-----New Device Information-----\n");
		ipr_log_ext_vpd(&dev_entry->new_vpd);

		ipr_err("Cache Directory Card Information:\n");
		ipr_log_ext_vpd(&dev_entry->ioa_last_with_dev_vpd);

		ipr_err("Adapter Card Information:\n");
		ipr_log_ext_vpd(&dev_entry->cfc_last_with_dev_vpd);
	पूर्ण
पूर्ण

/**
 * ipr_log_sis64_config_error - Log a device error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_sis64_config_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				       काष्ठा ipr_hostrcb *hostrcb)
अणु
	पूर्णांक errors_logged, i;
	काष्ठा ipr_hostrcb64_device_data_entry_enhanced *dev_entry;
	काष्ठा ipr_hostrcb_type_23_error *error;
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];

	error = &hostrcb->hcam.u.error64.u.type_23_error;
	errors_logged = be32_to_cpu(error->errors_logged);

	ipr_err("Device Errors Detected/Logged: %d/%d\n",
		be32_to_cpu(error->errors_detected), errors_logged);

	dev_entry = error->dev;

	क्रम (i = 0; i < errors_logged; i++, dev_entry++) अणु
		ipr_err_separator;

		ipr_err("Device %d : %s", i + 1,
			__ipr_क्रमmat_res_path(dev_entry->res_path,
					      buffer, माप(buffer)));
		ipr_log_ext_vpd(&dev_entry->vpd);

		ipr_err("-----New Device Information-----\n");
		ipr_log_ext_vpd(&dev_entry->new_vpd);

		ipr_err("Cache Directory Card Information:\n");
		ipr_log_ext_vpd(&dev_entry->ioa_last_with_dev_vpd);

		ipr_err("Adapter Card Information:\n");
		ipr_log_ext_vpd(&dev_entry->cfc_last_with_dev_vpd);
	पूर्ण
पूर्ण

/**
 * ipr_log_config_error - Log a configuration error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_config_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				 काष्ठा ipr_hostrcb *hostrcb)
अणु
	पूर्णांक errors_logged, i;
	काष्ठा ipr_hostrcb_device_data_entry *dev_entry;
	काष्ठा ipr_hostrcb_type_03_error *error;

	error = &hostrcb->hcam.u.error.u.type_03_error;
	errors_logged = be32_to_cpu(error->errors_logged);

	ipr_err("Device Errors Detected/Logged: %d/%d\n",
		be32_to_cpu(error->errors_detected), errors_logged);

	dev_entry = error->dev;

	क्रम (i = 0; i < errors_logged; i++, dev_entry++) अणु
		ipr_err_separator;

		ipr_phys_res_err(ioa_cfg, dev_entry->dev_res_addr, "Device %d", i + 1);
		ipr_log_vpd(&dev_entry->vpd);

		ipr_err("-----New Device Information-----\n");
		ipr_log_vpd(&dev_entry->new_vpd);

		ipr_err("Cache Directory Card Information:\n");
		ipr_log_vpd(&dev_entry->ioa_last_with_dev_vpd);

		ipr_err("Adapter Card Information:\n");
		ipr_log_vpd(&dev_entry->cfc_last_with_dev_vpd);

		ipr_err("Additional IOA Data: %08X %08X %08X %08X %08X\n",
			be32_to_cpu(dev_entry->ioa_data[0]),
			be32_to_cpu(dev_entry->ioa_data[1]),
			be32_to_cpu(dev_entry->ioa_data[2]),
			be32_to_cpu(dev_entry->ioa_data[3]),
			be32_to_cpu(dev_entry->ioa_data[4]));
	पूर्ण
पूर्ण

/**
 * ipr_log_enhanced_array_error - Log an array configuration error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_enhanced_array_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
					 काष्ठा ipr_hostrcb *hostrcb)
अणु
	पूर्णांक i, num_entries;
	काष्ठा ipr_hostrcb_type_14_error *error;
	काष्ठा ipr_hostrcb_array_data_entry_enhanced *array_entry;
	स्थिर u8 zero_sn[IPR_SERIAL_NUM_LEN] = अणु [0 ... IPR_SERIAL_NUM_LEN-1] = '0' पूर्ण;

	error = &hostrcb->hcam.u.error.u.type_14_error;

	ipr_err_separator;

	ipr_err("RAID %s Array Configuration: %d:%d:%d:%d\n",
		error->protection_level,
		ioa_cfg->host->host_no,
		error->last_func_vset_res_addr.bus,
		error->last_func_vset_res_addr.target,
		error->last_func_vset_res_addr.lun);

	ipr_err_separator;

	array_entry = error->array_member;
	num_entries = min_t(u32, be32_to_cpu(error->num_entries),
			    ARRAY_SIZE(error->array_member));

	क्रम (i = 0; i < num_entries; i++, array_entry++) अणु
		अगर (!स_भेद(array_entry->vpd.vpd.sn, zero_sn, IPR_SERIAL_NUM_LEN))
			जारी;

		अगर (be32_to_cpu(error->exposed_mode_adn) == i)
			ipr_err("Exposed Array Member %d:\n", i);
		अन्यथा
			ipr_err("Array Member %d:\n", i);

		ipr_log_ext_vpd(&array_entry->vpd);
		ipr_phys_res_err(ioa_cfg, array_entry->dev_res_addr, "Current Location");
		ipr_phys_res_err(ioa_cfg, array_entry->expected_dev_res_addr,
				 "Expected Location");

		ipr_err_separator;
	पूर्ण
पूर्ण

/**
 * ipr_log_array_error - Log an array configuration error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_array_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				काष्ठा ipr_hostrcb *hostrcb)
अणु
	पूर्णांक i;
	काष्ठा ipr_hostrcb_type_04_error *error;
	काष्ठा ipr_hostrcb_array_data_entry *array_entry;
	स्थिर u8 zero_sn[IPR_SERIAL_NUM_LEN] = अणु [0 ... IPR_SERIAL_NUM_LEN-1] = '0' पूर्ण;

	error = &hostrcb->hcam.u.error.u.type_04_error;

	ipr_err_separator;

	ipr_err("RAID %s Array Configuration: %d:%d:%d:%d\n",
		error->protection_level,
		ioa_cfg->host->host_no,
		error->last_func_vset_res_addr.bus,
		error->last_func_vset_res_addr.target,
		error->last_func_vset_res_addr.lun);

	ipr_err_separator;

	array_entry = error->array_member;

	क्रम (i = 0; i < 18; i++) अणु
		अगर (!स_भेद(array_entry->vpd.sn, zero_sn, IPR_SERIAL_NUM_LEN))
			जारी;

		अगर (be32_to_cpu(error->exposed_mode_adn) == i)
			ipr_err("Exposed Array Member %d:\n", i);
		अन्यथा
			ipr_err("Array Member %d:\n", i);

		ipr_log_vpd(&array_entry->vpd);

		ipr_phys_res_err(ioa_cfg, array_entry->dev_res_addr, "Current Location");
		ipr_phys_res_err(ioa_cfg, array_entry->expected_dev_res_addr,
				 "Expected Location");

		ipr_err_separator;

		अगर (i == 9)
			array_entry = error->array_member2;
		अन्यथा
			array_entry++;
	पूर्ण
पूर्ण

/**
 * ipr_log_hex_data - Log additional hex IOA error data.
 * @ioa_cfg:	ioa config काष्ठा
 * @data:		IOA error data
 * @len:		data length
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_hex_data(काष्ठा ipr_ioa_cfg *ioa_cfg, __be32 *data, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (len == 0)
		वापस;

	अगर (ioa_cfg->log_level <= IPR_DEFAULT_LOG_LEVEL)
		len = min_t(पूर्णांक, len, IPR_DEFAULT_MAX_ERROR_DUMP);

	क्रम (i = 0; i < len / 4; i += 4) अणु
		ipr_err("%08X: %08X %08X %08X %08X\n", i*4,
			be32_to_cpu(data[i]),
			be32_to_cpu(data[i+1]),
			be32_to_cpu(data[i+2]),
			be32_to_cpu(data[i+3]));
	पूर्ण
पूर्ण

/**
 * ipr_log_enhanced_dual_ioa_error - Log an enhanced dual adapter error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_enhanced_dual_ioa_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
					    काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_17_error *error;

	अगर (ioa_cfg->sis64)
		error = &hostrcb->hcam.u.error64.u.type_17_error;
	अन्यथा
		error = &hostrcb->hcam.u.error.u.type_17_error;

	error->failure_reason[माप(error->failure_reason) - 1] = '\0';
	strim(error->failure_reason);

	ipr_hcam_err(hostrcb, "%s [PRC: %08X]\n", error->failure_reason,
		     be32_to_cpu(hostrcb->hcam.u.error.prc));
	ipr_log_ext_vpd_compact("Remote IOA", hostrcb, &error->vpd);
	ipr_log_hex_data(ioa_cfg, error->data,
			 be32_to_cpu(hostrcb->hcam.length) -
			 (दुरत्व(काष्ठा ipr_hostrcb_error, u) +
			  दुरत्व(काष्ठा ipr_hostrcb_type_17_error, data)));
पूर्ण

/**
 * ipr_log_dual_ioa_error - Log a dual adapter error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_dual_ioa_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				   काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_07_error *error;

	error = &hostrcb->hcam.u.error.u.type_07_error;
	error->failure_reason[माप(error->failure_reason) - 1] = '\0';
	strim(error->failure_reason);

	ipr_hcam_err(hostrcb, "%s [PRC: %08X]\n", error->failure_reason,
		     be32_to_cpu(hostrcb->hcam.u.error.prc));
	ipr_log_vpd_compact("Remote IOA", hostrcb, &error->vpd);
	ipr_log_hex_data(ioa_cfg, error->data,
			 be32_to_cpu(hostrcb->hcam.length) -
			 (दुरत्व(काष्ठा ipr_hostrcb_error, u) +
			  दुरत्व(काष्ठा ipr_hostrcb_type_07_error, data)));
पूर्ण

अटल स्थिर काष्ठा अणु
	u8 active;
	अक्षर *desc;
पूर्ण path_active_desc[] = अणु
	अणु IPR_PATH_NO_INFO, "Path" पूर्ण,
	अणु IPR_PATH_ACTIVE, "Active path" पूर्ण,
	अणु IPR_PATH_NOT_ACTIVE, "Inactive path" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 state;
	अक्षर *desc;
पूर्ण path_state_desc[] = अणु
	अणु IPR_PATH_STATE_NO_INFO, "has no path state information available" पूर्ण,
	अणु IPR_PATH_HEALTHY, "is healthy" पूर्ण,
	अणु IPR_PATH_DEGRADED, "is degraded" पूर्ण,
	अणु IPR_PATH_FAILED, "is failed" पूर्ण
पूर्ण;

/**
 * ipr_log_fabric_path - Log a fabric path error
 * @hostrcb:	hostrcb काष्ठा
 * @fabric:		fabric descriptor
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_fabric_path(काष्ठा ipr_hostrcb *hostrcb,
				काष्ठा ipr_hostrcb_fabric_desc *fabric)
अणु
	पूर्णांक i, j;
	u8 path_state = fabric->path_state;
	u8 active = path_state & IPR_PATH_ACTIVE_MASK;
	u8 state = path_state & IPR_PATH_STATE_MASK;

	क्रम (i = 0; i < ARRAY_SIZE(path_active_desc); i++) अणु
		अगर (path_active_desc[i].active != active)
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(path_state_desc); j++) अणु
			अगर (path_state_desc[j].state != state)
				जारी;

			अगर (fabric->cascaded_expander == 0xff && fabric->phy == 0xff) अणु
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port);
			पूर्ण अन्यथा अगर (fabric->cascaded_expander == 0xff) अणु
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d, Phy=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port, fabric->phy);
			पूर्ण अन्यथा अगर (fabric->phy == 0xff) अणु
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d, Cascade=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port, fabric->cascaded_expander);
			पूर्ण अन्यथा अणु
				ipr_hcam_err(hostrcb, "%s %s: IOA Port=%d, Cascade=%d, Phy=%d\n",
					     path_active_desc[i].desc, path_state_desc[j].desc,
					     fabric->ioa_port, fabric->cascaded_expander, fabric->phy);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	ipr_err("Path state=%02X IOA Port=%d Cascade=%d Phy=%d\n", path_state,
		fabric->ioa_port, fabric->cascaded_expander, fabric->phy);
पूर्ण

/**
 * ipr_log64_fabric_path - Log a fabric path error
 * @hostrcb:	hostrcb काष्ठा
 * @fabric:		fabric descriptor
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log64_fabric_path(काष्ठा ipr_hostrcb *hostrcb,
				  काष्ठा ipr_hostrcb64_fabric_desc *fabric)
अणु
	पूर्णांक i, j;
	u8 path_state = fabric->path_state;
	u8 active = path_state & IPR_PATH_ACTIVE_MASK;
	u8 state = path_state & IPR_PATH_STATE_MASK;
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];

	क्रम (i = 0; i < ARRAY_SIZE(path_active_desc); i++) अणु
		अगर (path_active_desc[i].active != active)
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(path_state_desc); j++) अणु
			अगर (path_state_desc[j].state != state)
				जारी;

			ipr_hcam_err(hostrcb, "%s %s: Resource Path=%s\n",
				     path_active_desc[i].desc, path_state_desc[j].desc,
				     ipr_क्रमmat_res_path(hostrcb->ioa_cfg,
						fabric->res_path,
						buffer, माप(buffer)));
			वापस;
		पूर्ण
	पूर्ण

	ipr_err("Path state=%02X Resource Path=%s\n", path_state,
		ipr_क्रमmat_res_path(hostrcb->ioa_cfg, fabric->res_path,
				    buffer, माप(buffer)));
पूर्ण

अटल स्थिर काष्ठा अणु
	u8 type;
	अक्षर *desc;
पूर्ण path_type_desc[] = अणु
	अणु IPR_PATH_CFG_IOA_PORT, "IOA port" पूर्ण,
	अणु IPR_PATH_CFG_EXP_PORT, "Expander port" पूर्ण,
	अणु IPR_PATH_CFG_DEVICE_PORT, "Device port" पूर्ण,
	अणु IPR_PATH_CFG_DEVICE_LUN, "Device LUN" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 status;
	अक्षर *desc;
पूर्ण path_status_desc[] = अणु
	अणु IPR_PATH_CFG_NO_PROB, "Functional" पूर्ण,
	अणु IPR_PATH_CFG_DEGRADED, "Degraded" पूर्ण,
	अणु IPR_PATH_CFG_FAILED, "Failed" पूर्ण,
	अणु IPR_PATH_CFG_SUSPECT, "Suspect" पूर्ण,
	अणु IPR_PATH_NOT_DETECTED, "Missing" पूर्ण,
	अणु IPR_PATH_INCORRECT_CONN, "Incorrectly connected" पूर्ण
पूर्ण;

अटल स्थिर अक्षर *link_rate[] = अणु
	"unknown",
	"disabled",
	"phy reset problem",
	"spinup hold",
	"port selector",
	"unknown",
	"unknown",
	"unknown",
	"1.5Gbps",
	"3.0Gbps",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown"
पूर्ण;

/**
 * ipr_log_path_elem - Log a fabric path element.
 * @hostrcb:	hostrcb काष्ठा
 * @cfg:		fabric path element काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_path_elem(काष्ठा ipr_hostrcb *hostrcb,
			      काष्ठा ipr_hostrcb_config_element *cfg)
अणु
	पूर्णांक i, j;
	u8 type = cfg->type_status & IPR_PATH_CFG_TYPE_MASK;
	u8 status = cfg->type_status & IPR_PATH_CFG_STATUS_MASK;

	अगर (type == IPR_PATH_CFG_NOT_EXIST)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(path_type_desc); i++) अणु
		अगर (path_type_desc[i].type != type)
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(path_status_desc); j++) अणु
			अगर (path_status_desc[j].status != status)
				जारी;

			अगर (type == IPR_PATH_CFG_IOA_PORT) अणु
				ipr_hcam_err(hostrcb, "%s %s: Phy=%d, Link rate=%s, WWN=%08X%08X\n",
					     path_status_desc[j].desc, path_type_desc[i].desc,
					     cfg->phy, link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
					     be32_to_cpu(cfg->wwid[0]), be32_to_cpu(cfg->wwid[1]));
			पूर्ण अन्यथा अणु
				अगर (cfg->cascaded_expander == 0xff && cfg->phy == 0xff) अणु
					ipr_hcam_err(hostrcb, "%s %s: Link rate=%s, WWN=%08X%08X\n",
						     path_status_desc[j].desc, path_type_desc[i].desc,
						     link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
						     be32_to_cpu(cfg->wwid[0]), be32_to_cpu(cfg->wwid[1]));
				पूर्ण अन्यथा अगर (cfg->cascaded_expander == 0xff) अणु
					ipr_hcam_err(hostrcb, "%s %s: Phy=%d, Link rate=%s, "
						     "WWN=%08X%08X\n", path_status_desc[j].desc,
						     path_type_desc[i].desc, cfg->phy,
						     link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
						     be32_to_cpu(cfg->wwid[0]), be32_to_cpu(cfg->wwid[1]));
				पूर्ण अन्यथा अगर (cfg->phy == 0xff) अणु
					ipr_hcam_err(hostrcb, "%s %s: Cascade=%d, Link rate=%s, "
						     "WWN=%08X%08X\n", path_status_desc[j].desc,
						     path_type_desc[i].desc, cfg->cascaded_expander,
						     link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
						     be32_to_cpu(cfg->wwid[0]), be32_to_cpu(cfg->wwid[1]));
				पूर्ण अन्यथा अणु
					ipr_hcam_err(hostrcb, "%s %s: Cascade=%d, Phy=%d, Link rate=%s "
						     "WWN=%08X%08X\n", path_status_desc[j].desc,
						     path_type_desc[i].desc, cfg->cascaded_expander, cfg->phy,
						     link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
						     be32_to_cpu(cfg->wwid[0]), be32_to_cpu(cfg->wwid[1]));
				पूर्ण
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	ipr_hcam_err(hostrcb, "Path element=%02X: Cascade=%d Phy=%d Link rate=%s "
		     "WWN=%08X%08X\n", cfg->type_status, cfg->cascaded_expander, cfg->phy,
		     link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
		     be32_to_cpu(cfg->wwid[0]), be32_to_cpu(cfg->wwid[1]));
पूर्ण

/**
 * ipr_log64_path_elem - Log a fabric path element.
 * @hostrcb:	hostrcb काष्ठा
 * @cfg:		fabric path element काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log64_path_elem(काष्ठा ipr_hostrcb *hostrcb,
				काष्ठा ipr_hostrcb64_config_element *cfg)
अणु
	पूर्णांक i, j;
	u8 desc_id = cfg->descriptor_id & IPR_DESCRIPTOR_MASK;
	u8 type = cfg->type_status & IPR_PATH_CFG_TYPE_MASK;
	u8 status = cfg->type_status & IPR_PATH_CFG_STATUS_MASK;
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];

	अगर (type == IPR_PATH_CFG_NOT_EXIST || desc_id != IPR_DESCRIPTOR_SIS64)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(path_type_desc); i++) अणु
		अगर (path_type_desc[i].type != type)
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(path_status_desc); j++) अणु
			अगर (path_status_desc[j].status != status)
				जारी;

			ipr_hcam_err(hostrcb, "%s %s: Resource Path=%s, Link rate=%s, WWN=%08X%08X\n",
				     path_status_desc[j].desc, path_type_desc[i].desc,
				     ipr_क्रमmat_res_path(hostrcb->ioa_cfg,
					cfg->res_path, buffer, माप(buffer)),
					link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
					be32_to_cpu(cfg->wwid[0]),
					be32_to_cpu(cfg->wwid[1]));
			वापस;
		पूर्ण
	पूर्ण
	ipr_hcam_err(hostrcb, "Path element=%02X: Resource Path=%s, Link rate=%s "
		     "WWN=%08X%08X\n", cfg->type_status,
		     ipr_क्रमmat_res_path(hostrcb->ioa_cfg,
			cfg->res_path, buffer, माप(buffer)),
			link_rate[cfg->link_rate & IPR_PHY_LINK_RATE_MASK],
			be32_to_cpu(cfg->wwid[0]), be32_to_cpu(cfg->wwid[1]));
पूर्ण

/**
 * ipr_log_fabric_error - Log a fabric error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_fabric_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				 काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_20_error *error;
	काष्ठा ipr_hostrcb_fabric_desc *fabric;
	काष्ठा ipr_hostrcb_config_element *cfg;
	पूर्णांक i, add_len;

	error = &hostrcb->hcam.u.error.u.type_20_error;
	error->failure_reason[माप(error->failure_reason) - 1] = '\0';
	ipr_hcam_err(hostrcb, "%s\n", error->failure_reason);

	add_len = be32_to_cpu(hostrcb->hcam.length) -
		(दुरत्व(काष्ठा ipr_hostrcb_error, u) +
		 दुरत्व(काष्ठा ipr_hostrcb_type_20_error, desc));

	क्रम (i = 0, fabric = error->desc; i < error->num_entries; i++) अणु
		ipr_log_fabric_path(hostrcb, fabric);
		क्रम_each_fabric_cfg(fabric, cfg)
			ipr_log_path_elem(hostrcb, cfg);

		add_len -= be16_to_cpu(fabric->length);
		fabric = (काष्ठा ipr_hostrcb_fabric_desc *)
			((अचिन्हित दीर्घ)fabric + be16_to_cpu(fabric->length));
	पूर्ण

	ipr_log_hex_data(ioa_cfg, (__be32 *)fabric, add_len);
पूर्ण

/**
 * ipr_log_sis64_array_error - Log a sis64 array error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_sis64_array_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				      काष्ठा ipr_hostrcb *hostrcb)
अणु
	पूर्णांक i, num_entries;
	काष्ठा ipr_hostrcb_type_24_error *error;
	काष्ठा ipr_hostrcb64_array_data_entry *array_entry;
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];
	स्थिर u8 zero_sn[IPR_SERIAL_NUM_LEN] = अणु [0 ... IPR_SERIAL_NUM_LEN-1] = '0' पूर्ण;

	error = &hostrcb->hcam.u.error64.u.type_24_error;

	ipr_err_separator;

	ipr_err("RAID %s Array Configuration: %s\n",
		error->protection_level,
		ipr_क्रमmat_res_path(ioa_cfg, error->last_res_path,
			buffer, माप(buffer)));

	ipr_err_separator;

	array_entry = error->array_member;
	num_entries = min_t(u32, error->num_entries,
			    ARRAY_SIZE(error->array_member));

	क्रम (i = 0; i < num_entries; i++, array_entry++) अणु

		अगर (!स_भेद(array_entry->vpd.vpd.sn, zero_sn, IPR_SERIAL_NUM_LEN))
			जारी;

		अगर (error->exposed_mode_adn == i)
			ipr_err("Exposed Array Member %d:\n", i);
		अन्यथा
			ipr_err("Array Member %d:\n", i);

		ipr_err("Array Member %d:\n", i);
		ipr_log_ext_vpd(&array_entry->vpd);
		ipr_err("Current Location: %s\n",
			 ipr_क्रमmat_res_path(ioa_cfg, array_entry->res_path,
				buffer, माप(buffer)));
		ipr_err("Expected Location: %s\n",
			 ipr_क्रमmat_res_path(ioa_cfg,
				array_entry->expected_res_path,
				buffer, माप(buffer)));

		ipr_err_separator;
	पूर्ण
पूर्ण

/**
 * ipr_log_sis64_fabric_error - Log a sis64 fabric error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_sis64_fabric_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				       काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_30_error *error;
	काष्ठा ipr_hostrcb64_fabric_desc *fabric;
	काष्ठा ipr_hostrcb64_config_element *cfg;
	पूर्णांक i, add_len;

	error = &hostrcb->hcam.u.error64.u.type_30_error;

	error->failure_reason[माप(error->failure_reason) - 1] = '\0';
	ipr_hcam_err(hostrcb, "%s\n", error->failure_reason);

	add_len = be32_to_cpu(hostrcb->hcam.length) -
		(दुरत्व(काष्ठा ipr_hostrcb64_error, u) +
		 दुरत्व(काष्ठा ipr_hostrcb_type_30_error, desc));

	क्रम (i = 0, fabric = error->desc; i < error->num_entries; i++) अणु
		ipr_log64_fabric_path(hostrcb, fabric);
		क्रम_each_fabric_cfg(fabric, cfg)
			ipr_log64_path_elem(hostrcb, cfg);

		add_len -= be16_to_cpu(fabric->length);
		fabric = (काष्ठा ipr_hostrcb64_fabric_desc *)
			((अचिन्हित दीर्घ)fabric + be16_to_cpu(fabric->length));
	पूर्ण

	ipr_log_hex_data(ioa_cfg, (__be32 *)fabric, add_len);
पूर्ण

/**
 * ipr_log_sis64_service_required_error - Log a sis64 service required error.
 * @ioa_cfg:    ioa config काष्ठा
 * @hostrcb:    hostrcb काष्ठा
 *
 * Return value:
 *      none
 **/
अटल व्योम ipr_log_sis64_service_required_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				       काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_41_error *error;

	error = &hostrcb->hcam.u.error64.u.type_41_error;

	error->failure_reason[माप(error->failure_reason) - 1] = '\0';
	ipr_err("Primary Failure Reason: %s\n", error->failure_reason);
	ipr_log_hex_data(ioa_cfg, error->data,
			 be32_to_cpu(hostrcb->hcam.length) -
			 (दुरत्व(काष्ठा ipr_hostrcb_error, u) +
			  दुरत्व(काष्ठा ipr_hostrcb_type_41_error, data)));
पूर्ण
/**
 * ipr_log_generic_error - Log an adapter error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_generic_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
				  काष्ठा ipr_hostrcb *hostrcb)
अणु
	ipr_log_hex_data(ioa_cfg, hostrcb->hcam.u.raw.data,
			 be32_to_cpu(hostrcb->hcam.length));
पूर्ण

/**
 * ipr_log_sis64_device_error - Log a cache error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_log_sis64_device_error(काष्ठा ipr_ioa_cfg *ioa_cfg,
					 काष्ठा ipr_hostrcb *hostrcb)
अणु
	काष्ठा ipr_hostrcb_type_21_error *error;
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];

	error = &hostrcb->hcam.u.error64.u.type_21_error;

	ipr_err("-----Failing Device Information-----\n");
	ipr_err("World Wide Unique ID: %08X%08X%08X%08X\n",
		be32_to_cpu(error->wwn[0]), be32_to_cpu(error->wwn[1]),
		 be32_to_cpu(error->wwn[2]), be32_to_cpu(error->wwn[3]));
	ipr_err("Device Resource Path: %s\n",
		__ipr_क्रमmat_res_path(error->res_path,
				      buffer, माप(buffer)));
	error->primary_problem_desc[माप(error->primary_problem_desc) - 1] = '\0';
	error->second_problem_desc[माप(error->second_problem_desc) - 1] = '\0';
	ipr_err("Primary Problem Description: %s\n", error->primary_problem_desc);
	ipr_err("Secondary Problem Description:  %s\n", error->second_problem_desc);
	ipr_err("SCSI Sense Data:\n");
	ipr_log_hex_data(ioa_cfg, error->sense_data, माप(error->sense_data));
	ipr_err("SCSI Command Descriptor Block: \n");
	ipr_log_hex_data(ioa_cfg, error->cdb, माप(error->cdb));

	ipr_err("Additional IOA Data:\n");
	ipr_log_hex_data(ioa_cfg, error->ioa_data, be32_to_cpu(error->length_of_error));
पूर्ण

/**
 * ipr_get_error - Find the specfied IOASC in the ipr_error_table.
 * @ioasc:	IOASC
 *
 * This function will वापस the index of पूर्णांकo the ipr_error_table
 * क्रम the specअगरied IOASC. If the IOASC is not in the table,
 * 0 will be वापसed, which poपूर्णांकs to the entry used क्रम unknown errors.
 *
 * Return value:
 * 	index पूर्णांकo the ipr_error_table
 **/
अटल u32 ipr_get_error(u32 ioasc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ipr_error_table); i++)
		अगर (ipr_error_table[i].ioasc == (ioasc & IPR_IOASC_IOASC_MASK))
			वापस i;

	वापस 0;
पूर्ण

/**
 * ipr_handle_log_data - Log an adapter error.
 * @ioa_cfg:	ioa config काष्ठा
 * @hostrcb:	hostrcb काष्ठा
 *
 * This function logs an adapter error to the प्रणाली.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_handle_log_data(काष्ठा ipr_ioa_cfg *ioa_cfg,
				काष्ठा ipr_hostrcb *hostrcb)
अणु
	u32 ioasc;
	पूर्णांक error_index;
	काष्ठा ipr_hostrcb_type_21_error *error;

	अगर (hostrcb->hcam.notअगरy_type != IPR_HOST_RCB_NOTIF_TYPE_ERROR_LOG_ENTRY)
		वापस;

	अगर (hostrcb->hcam.notअगरications_lost == IPR_HOST_RCB_NOTIFICATIONS_LOST)
		dev_err(&ioa_cfg->pdev->dev, "Error notifications lost\n");

	अगर (ioa_cfg->sis64)
		ioasc = be32_to_cpu(hostrcb->hcam.u.error64.fd_ioasc);
	अन्यथा
		ioasc = be32_to_cpu(hostrcb->hcam.u.error.fd_ioasc);

	अगर (!ioa_cfg->sis64 && (ioasc == IPR_IOASC_BUS_WAS_RESET ||
	    ioasc == IPR_IOASC_BUS_WAS_RESET_BY_OTHER)) अणु
		/* Tell the midlayer we had a bus reset so it will handle the UA properly */
		scsi_report_bus_reset(ioa_cfg->host,
				      hostrcb->hcam.u.error.fd_res_addr.bus);
	पूर्ण

	error_index = ipr_get_error(ioasc);

	अगर (!ipr_error_table[error_index].log_hcam)
		वापस;

	अगर (ioasc == IPR_IOASC_HW_CMD_FAILED &&
	    hostrcb->hcam.overlay_id == IPR_HOST_RCB_OVERLAY_ID_21) अणु
		error = &hostrcb->hcam.u.error64.u.type_21_error;

		अगर (((be32_to_cpu(error->sense_data[0]) & 0x0000ff00) >> 8) == ILLEGAL_REQUEST &&
			ioa_cfg->log_level <= IPR_DEFAULT_LOG_LEVEL)
				वापस;
	पूर्ण

	ipr_hcam_err(hostrcb, "%s\n", ipr_error_table[error_index].error);

	/* Set indication we have logged an error */
	ioa_cfg->errors_logged++;

	अगर (ioa_cfg->log_level < ipr_error_table[error_index].log_hcam)
		वापस;
	अगर (be32_to_cpu(hostrcb->hcam.length) > माप(hostrcb->hcam.u.raw))
		hostrcb->hcam.length = cpu_to_be32(माप(hostrcb->hcam.u.raw));

	चयन (hostrcb->hcam.overlay_id) अणु
	हाल IPR_HOST_RCB_OVERLAY_ID_2:
		ipr_log_cache_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_3:
		ipr_log_config_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_4:
	हाल IPR_HOST_RCB_OVERLAY_ID_6:
		ipr_log_array_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_7:
		ipr_log_dual_ioa_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_12:
		ipr_log_enhanced_cache_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_13:
		ipr_log_enhanced_config_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_14:
	हाल IPR_HOST_RCB_OVERLAY_ID_16:
		ipr_log_enhanced_array_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_17:
		ipr_log_enhanced_dual_ioa_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_20:
		ipr_log_fabric_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_21:
		ipr_log_sis64_device_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_23:
		ipr_log_sis64_config_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_24:
	हाल IPR_HOST_RCB_OVERLAY_ID_26:
		ipr_log_sis64_array_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_30:
		ipr_log_sis64_fabric_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_41:
		ipr_log_sis64_service_required_error(ioa_cfg, hostrcb);
		अवरोध;
	हाल IPR_HOST_RCB_OVERLAY_ID_1:
	हाल IPR_HOST_RCB_OVERLAY_ID_DEFAULT:
	शेष:
		ipr_log_generic_error(ioa_cfg, hostrcb);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा ipr_hostrcb *ipr_get_मुक्त_hostrcb(काष्ठा ipr_ioa_cfg *ioa)
अणु
	काष्ठा ipr_hostrcb *hostrcb;

	hostrcb = list_first_entry_or_null(&ioa->hostrcb_मुक्त_q,
					काष्ठा ipr_hostrcb, queue);

	अगर (unlikely(!hostrcb)) अणु
		dev_info(&ioa->pdev->dev, "Reclaiming async error buffers.");
		hostrcb = list_first_entry_or_null(&ioa->hostrcb_report_q,
						काष्ठा ipr_hostrcb, queue);
	पूर्ण

	list_del_init(&hostrcb->queue);
	वापस hostrcb;
पूर्ण

/**
 * ipr_process_error - Op करोne function क्रम an adapter error log.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is the op करोne function क्रम an error log host
 * controlled async from the adapter. It will log the error and
 * send the HCAM back to the adapter.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_process_error(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_hostrcb *hostrcb = ipr_cmd->u.hostrcb;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);
	u32 fd_ioasc;

	अगर (ioa_cfg->sis64)
		fd_ioasc = be32_to_cpu(hostrcb->hcam.u.error64.fd_ioasc);
	अन्यथा
		fd_ioasc = be32_to_cpu(hostrcb->hcam.u.error.fd_ioasc);

	list_del_init(&hostrcb->queue);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);

	अगर (!ioasc) अणु
		ipr_handle_log_data(ioa_cfg, hostrcb);
		अगर (fd_ioasc == IPR_IOASC_NR_IOA_RESET_REQUIRED)
			ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_ABBREV);
	पूर्ण अन्यथा अगर (ioasc != IPR_IOASC_IOA_WAS_RESET &&
		   ioasc != IPR_IOASC_ABORTED_CMD_TERM_BY_HOST) अणु
		dev_err(&ioa_cfg->pdev->dev,
			"Host RCB failed with IOASC: 0x%08X\n", ioasc);
	पूर्ण

	list_add_tail(&hostrcb->queue, &ioa_cfg->hostrcb_report_q);
	schedule_work(&ioa_cfg->work_q);
	hostrcb = ipr_get_मुक्त_hostrcb(ioa_cfg);

	ipr_send_hcam(ioa_cfg, IPR_HCAM_CDB_OP_CODE_LOG_DATA, hostrcb);
पूर्ण

/**
 * ipr_समयout -  An पूर्णांकernally generated op has समयd out.
 * @t: Timer context used to fetch ipr command काष्ठा
 *
 * This function blocks host requests and initiates an
 * adapter reset.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ipr_cmnd *ipr_cmd = from_समयr(ipr_cmd, t, समयr);
	अचिन्हित दीर्घ lock_flags = 0;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	ioa_cfg->errors_logged++;
	dev_err(&ioa_cfg->pdev->dev,
		"Adapter being reset due to command timeout.\n");

	अगर (WAIT_FOR_DUMP == ioa_cfg->sdt_state)
		ioa_cfg->sdt_state = GET_DUMP;

	अगर (!ioa_cfg->in_reset_reload || ioa_cfg->reset_cmd == ipr_cmd)
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
पूर्ण

/**
 * ipr_oper_समयout -  Adapter समयd out transitioning to operational
 * @t: Timer context used to fetch ipr command काष्ठा
 *
 * This function blocks host requests and initiates an
 * adapter reset.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_oper_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ipr_cmnd *ipr_cmd = from_समयr(ipr_cmd, t, समयr);
	अचिन्हित दीर्घ lock_flags = 0;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	ioa_cfg->errors_logged++;
	dev_err(&ioa_cfg->pdev->dev,
		"Adapter timed out transitioning to operational.\n");

	अगर (WAIT_FOR_DUMP == ioa_cfg->sdt_state)
		ioa_cfg->sdt_state = GET_DUMP;

	अगर (!ioa_cfg->in_reset_reload || ioa_cfg->reset_cmd == ipr_cmd) अणु
		अगर (ipr_fastfail)
			ioa_cfg->reset_retries += IPR_NUM_RESET_RELOAD_RETRIES;
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	पूर्ण

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
पूर्ण

/**
 * ipr_find_ses_entry - Find matching SES in SES table
 * @res:	resource entry काष्ठा of SES
 *
 * Return value:
 * 	poपूर्णांकer to SES table entry / शून्य on failure
 **/
अटल स्थिर काष्ठा ipr_ses_table_entry *
ipr_find_ses_entry(काष्ठा ipr_resource_entry *res)
अणु
	पूर्णांक i, j, matches;
	काष्ठा ipr_std_inq_vpids *vpids;
	स्थिर काष्ठा ipr_ses_table_entry *ste = ipr_ses_table;

	क्रम (i = 0; i < ARRAY_SIZE(ipr_ses_table); i++, ste++) अणु
		क्रम (j = 0, matches = 0; j < IPR_PROD_ID_LEN; j++) अणु
			अगर (ste->compare_product_id_byte[j] == 'X') अणु
				vpids = &res->std_inq_data.vpids;
				अगर (vpids->product_id[j] == ste->product_id[j])
					matches++;
				अन्यथा
					अवरोध;
			पूर्ण अन्यथा
				matches++;
		पूर्ण

		अगर (matches == IPR_PROD_ID_LEN)
			वापस ste;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ipr_get_max_scsi_speed - Determine max SCSI speed क्रम a given bus
 * @ioa_cfg:	ioa config काष्ठा
 * @bus:		SCSI bus
 * @bus_width:	bus width
 *
 * Return value:
 *	SCSI bus speed in units of 100KHz, 1600 is 160 MHz
 *	For a 2-byte wide SCSI bus, the maximum transfer speed is
 *	twice the maximum transfer rate (e.g. क्रम a wide enabled bus,
 *	max 160MHz = max 320MB/sec).
 **/
अटल u32 ipr_get_max_scsi_speed(काष्ठा ipr_ioa_cfg *ioa_cfg, u8 bus, u8 bus_width)
अणु
	काष्ठा ipr_resource_entry *res;
	स्थिर काष्ठा ipr_ses_table_entry *ste;
	u32 max_xfer_rate = IPR_MAX_SCSI_RATE(bus_width);

	/* Loop through each config table entry in the config table buffer */
	list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
		अगर (!(IPR_IS_SES_DEVICE(res->std_inq_data)))
			जारी;

		अगर (bus != res->bus)
			जारी;

		अगर (!(ste = ipr_find_ses_entry(res)))
			जारी;

		max_xfer_rate = (ste->max_bus_speed_limit * 10) / (bus_width / 8);
	पूर्ण

	वापस max_xfer_rate;
पूर्ण

/**
 * ipr_रुको_iodbg_ack - Wait क्रम an IODEBUG ACK from the IOA
 * @ioa_cfg:		ioa config काष्ठा
 * @max_delay:		max delay in micro-seconds to रुको
 *
 * Waits क्रम an IODEBUG ACK from the IOA, करोing busy looping.
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक ipr_रुको_iodbg_ack(काष्ठा ipr_ioa_cfg *ioa_cfg, पूर्णांक max_delay)
अणु
	अस्थिर u32 pcii_reg;
	पूर्णांक delay = 1;

	/* Read पूर्णांकerrupt reg until IOA संकेतs IO Debug Acknowledge */
	जबतक (delay < max_delay) अणु
		pcii_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg);

		अगर (pcii_reg & IPR_PCII_IO_DEBUG_ACKNOWLEDGE)
			वापस 0;

		/* udelay cannot be used अगर delay is more than a few milliseconds */
		अगर ((delay / 1000) > MAX_UDELAY_MS)
			mdelay(delay / 1000);
		अन्यथा
			udelay(delay);

		delay += delay;
	पूर्ण
	वापस -EIO;
पूर्ण

/**
 * ipr_get_sis64_dump_data_section - Dump IOA memory
 * @ioa_cfg:			ioa config काष्ठा
 * @start_addr:			adapter address to dump
 * @dest:			destination kernel buffer
 * @length_in_words:		length to dump in 4 byte words
 *
 * Return value:
 * 	0 on success
 **/
अटल पूर्णांक ipr_get_sis64_dump_data_section(काष्ठा ipr_ioa_cfg *ioa_cfg,
					   u32 start_addr,
					   __be32 *dest, u32 length_in_words)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length_in_words; i++) अणु
		ग_लिखोl(start_addr+(i*4), ioa_cfg->regs.dump_addr_reg);
		*dest = cpu_to_be32(पढ़ोl(ioa_cfg->regs.dump_data_reg));
		dest++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ipr_get_ldump_data_section - Dump IOA memory
 * @ioa_cfg:			ioa config काष्ठा
 * @start_addr:			adapter address to dump
 * @dest:				destination kernel buffer
 * @length_in_words:	length to dump in 4 byte words
 *
 * Return value:
 * 	0 on success / -EIO on failure
 **/
अटल पूर्णांक ipr_get_ldump_data_section(काष्ठा ipr_ioa_cfg *ioa_cfg,
				      u32 start_addr,
				      __be32 *dest, u32 length_in_words)
अणु
	अस्थिर u32 temp_pcii_reg;
	पूर्णांक i, delay = 0;

	अगर (ioa_cfg->sis64)
		वापस ipr_get_sis64_dump_data_section(ioa_cfg, start_addr,
						       dest, length_in_words);

	/* Write IOA पूर्णांकerrupt reg starting LDUMP state  */
	ग_लिखोl((IPR_UPROCI_RESET_ALERT | IPR_UPROCI_IO_DEBUG_ALERT),
	       ioa_cfg->regs.set_uproc_पूर्णांकerrupt_reg32);

	/* Wait क्रम IO debug acknowledge */
	अगर (ipr_रुको_iodbg_ack(ioa_cfg,
			       IPR_LDUMP_MAX_LONG_ACK_DELAY_IN_USEC)) अणु
		dev_err(&ioa_cfg->pdev->dev,
			"IOA dump long data transfer timeout\n");
		वापस -EIO;
	पूर्ण

	/* Signal LDUMP पूर्णांकerlocked - clear IO debug ack */
	ग_लिखोl(IPR_PCII_IO_DEBUG_ACKNOWLEDGE,
	       ioa_cfg->regs.clr_पूर्णांकerrupt_reg);

	/* Write Mailbox with starting address */
	ग_लिखोl(start_addr, ioa_cfg->ioa_mailbox);

	/* Signal address valid - clear IOA Reset alert */
	ग_लिखोl(IPR_UPROCI_RESET_ALERT,
	       ioa_cfg->regs.clr_uproc_पूर्णांकerrupt_reg32);

	क्रम (i = 0; i < length_in_words; i++) अणु
		/* Wait क्रम IO debug acknowledge */
		अगर (ipr_रुको_iodbg_ack(ioa_cfg,
				       IPR_LDUMP_MAX_SHORT_ACK_DELAY_IN_USEC)) अणु
			dev_err(&ioa_cfg->pdev->dev,
				"IOA dump short data transfer timeout\n");
			वापस -EIO;
		पूर्ण

		/* Read data from mailbox and increment destination poपूर्णांकer */
		*dest = cpu_to_be32(पढ़ोl(ioa_cfg->ioa_mailbox));
		dest++;

		/* For all but the last word of data, संकेत data received */
		अगर (i < (length_in_words - 1)) अणु
			/* Signal dump data received - Clear IO debug Ack */
			ग_लिखोl(IPR_PCII_IO_DEBUG_ACKNOWLEDGE,
			       ioa_cfg->regs.clr_पूर्णांकerrupt_reg);
		पूर्ण
	पूर्ण

	/* Signal end of block transfer. Set reset alert then clear IO debug ack */
	ग_लिखोl(IPR_UPROCI_RESET_ALERT,
	       ioa_cfg->regs.set_uproc_पूर्णांकerrupt_reg32);

	ग_लिखोl(IPR_UPROCI_IO_DEBUG_ALERT,
	       ioa_cfg->regs.clr_uproc_पूर्णांकerrupt_reg32);

	/* Signal dump data received - Clear IO debug Ack */
	ग_लिखोl(IPR_PCII_IO_DEBUG_ACKNOWLEDGE,
	       ioa_cfg->regs.clr_पूर्णांकerrupt_reg);

	/* Wait क्रम IOA to संकेत LDUMP निकास - IOA reset alert will be cleared */
	जबतक (delay < IPR_LDUMP_MAX_SHORT_ACK_DELAY_IN_USEC) अणु
		temp_pcii_reg =
		    पढ़ोl(ioa_cfg->regs.sense_uproc_पूर्णांकerrupt_reg32);

		अगर (!(temp_pcii_reg & IPR_UPROCI_RESET_ALERT))
			वापस 0;

		udelay(10);
		delay += 10;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SCSI_IPR_DUMP
/**
 * ipr_sdt_copy - Copy Smart Dump Table to kernel buffer
 * @ioa_cfg:		ioa config काष्ठा
 * @pci_address:	adapter address
 * @length:			length of data to copy
 *
 * Copy data from PCI adapter to kernel buffer.
 * Note: length MUST be a 4 byte multiple
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक ipr_sdt_copy(काष्ठा ipr_ioa_cfg *ioa_cfg,
			अचिन्हित दीर्घ pci_address, u32 length)
अणु
	पूर्णांक bytes_copied = 0;
	पूर्णांक cur_len, rc, rem_len, rem_page_len, max_dump_size;
	__be32 *page;
	अचिन्हित दीर्घ lock_flags = 0;
	काष्ठा ipr_ioa_dump *ioa_dump = &ioa_cfg->dump->ioa_dump;

	अगर (ioa_cfg->sis64)
		max_dump_size = IPR_FMT3_MAX_IOA_DUMP_SIZE;
	अन्यथा
		max_dump_size = IPR_FMT2_MAX_IOA_DUMP_SIZE;

	जबतक (bytes_copied < length &&
	       (ioa_dump->hdr.len + bytes_copied) < max_dump_size) अणु
		अगर (ioa_dump->page_offset >= PAGE_SIZE ||
		    ioa_dump->page_offset == 0) अणु
			page = (__be32 *)__get_मुक्त_page(GFP_ATOMIC);

			अगर (!page) अणु
				ipr_trace;
				वापस bytes_copied;
			पूर्ण

			ioa_dump->page_offset = 0;
			ioa_dump->ioa_data[ioa_dump->next_page_index] = page;
			ioa_dump->next_page_index++;
		पूर्ण अन्यथा
			page = ioa_dump->ioa_data[ioa_dump->next_page_index - 1];

		rem_len = length - bytes_copied;
		rem_page_len = PAGE_SIZE - ioa_dump->page_offset;
		cur_len = min(rem_len, rem_page_len);

		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
		अगर (ioa_cfg->sdt_state == ABORT_DUMP) अणु
			rc = -EIO;
		पूर्ण अन्यथा अणु
			rc = ipr_get_ldump_data_section(ioa_cfg,
							pci_address + bytes_copied,
							&page[ioa_dump->page_offset / 4],
							(cur_len / माप(u32)));
		पूर्ण
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

		अगर (!rc) अणु
			ioa_dump->page_offset += cur_len;
			bytes_copied += cur_len;
		पूर्ण अन्यथा अणु
			ipr_trace;
			अवरोध;
		पूर्ण
		schedule();
	पूर्ण

	वापस bytes_copied;
पूर्ण

/**
 * ipr_init_dump_entry_hdr - Initialize a dump entry header.
 * @hdr:	dump entry header काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_init_dump_entry_hdr(काष्ठा ipr_dump_entry_header *hdr)
अणु
	hdr->eye_catcher = IPR_DUMP_EYE_CATCHER;
	hdr->num_elems = 1;
	hdr->offset = माप(*hdr);
	hdr->status = IPR_DUMP_STATUS_SUCCESS;
पूर्ण

/**
 * ipr_dump_ioa_type_data - Fill in the adapter type in the dump.
 * @ioa_cfg:	ioa config काष्ठा
 * @driver_dump:	driver dump काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_dump_ioa_type_data(काष्ठा ipr_ioa_cfg *ioa_cfg,
				   काष्ठा ipr_driver_dump *driver_dump)
अणु
	काष्ठा ipr_inquiry_page3 *ucode_vpd = &ioa_cfg->vpd_cbs->page3_data;

	ipr_init_dump_entry_hdr(&driver_dump->ioa_type_entry.hdr);
	driver_dump->ioa_type_entry.hdr.len =
		माप(काष्ठा ipr_dump_ioa_type_entry) -
		माप(काष्ठा ipr_dump_entry_header);
	driver_dump->ioa_type_entry.hdr.data_type = IPR_DUMP_DATA_TYPE_BINARY;
	driver_dump->ioa_type_entry.hdr.id = IPR_DUMP_DRIVER_TYPE_ID;
	driver_dump->ioa_type_entry.type = ioa_cfg->type;
	driver_dump->ioa_type_entry.fw_version = (ucode_vpd->major_release << 24) |
		(ucode_vpd->card_type << 16) | (ucode_vpd->minor_release[0] << 8) |
		ucode_vpd->minor_release[1];
	driver_dump->hdr.num_entries++;
पूर्ण

/**
 * ipr_dump_version_data - Fill in the driver version in the dump.
 * @ioa_cfg:	ioa config काष्ठा
 * @driver_dump:	driver dump काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_dump_version_data(काष्ठा ipr_ioa_cfg *ioa_cfg,
				  काष्ठा ipr_driver_dump *driver_dump)
अणु
	ipr_init_dump_entry_hdr(&driver_dump->version_entry.hdr);
	driver_dump->version_entry.hdr.len =
		माप(काष्ठा ipr_dump_version_entry) -
		माप(काष्ठा ipr_dump_entry_header);
	driver_dump->version_entry.hdr.data_type = IPR_DUMP_DATA_TYPE_ASCII;
	driver_dump->version_entry.hdr.id = IPR_DUMP_DRIVER_VERSION_ID;
	म_नकल(driver_dump->version_entry.version, IPR_DRIVER_VERSION);
	driver_dump->hdr.num_entries++;
पूर्ण

/**
 * ipr_dump_trace_data - Fill in the IOA trace in the dump.
 * @ioa_cfg:	ioa config काष्ठा
 * @driver_dump:	driver dump काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_dump_trace_data(काष्ठा ipr_ioa_cfg *ioa_cfg,
				   काष्ठा ipr_driver_dump *driver_dump)
अणु
	ipr_init_dump_entry_hdr(&driver_dump->trace_entry.hdr);
	driver_dump->trace_entry.hdr.len =
		माप(काष्ठा ipr_dump_trace_entry) -
		माप(काष्ठा ipr_dump_entry_header);
	driver_dump->trace_entry.hdr.data_type = IPR_DUMP_DATA_TYPE_BINARY;
	driver_dump->trace_entry.hdr.id = IPR_DUMP_TRACE_ID;
	स_नकल(driver_dump->trace_entry.trace, ioa_cfg->trace, IPR_TRACE_SIZE);
	driver_dump->hdr.num_entries++;
पूर्ण

/**
 * ipr_dump_location_data - Fill in the IOA location in the dump.
 * @ioa_cfg:	ioa config काष्ठा
 * @driver_dump:	driver dump काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_dump_location_data(काष्ठा ipr_ioa_cfg *ioa_cfg,
				   काष्ठा ipr_driver_dump *driver_dump)
अणु
	ipr_init_dump_entry_hdr(&driver_dump->location_entry.hdr);
	driver_dump->location_entry.hdr.len =
		माप(काष्ठा ipr_dump_location_entry) -
		माप(काष्ठा ipr_dump_entry_header);
	driver_dump->location_entry.hdr.data_type = IPR_DUMP_DATA_TYPE_ASCII;
	driver_dump->location_entry.hdr.id = IPR_DUMP_LOCATION_ID;
	म_नकल(driver_dump->location_entry.location, dev_name(&ioa_cfg->pdev->dev));
	driver_dump->hdr.num_entries++;
पूर्ण

/**
 * ipr_get_ioa_dump - Perक्रमm a dump of the driver and adapter.
 * @ioa_cfg:	ioa config काष्ठा
 * @dump:		dump काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_get_ioa_dump(काष्ठा ipr_ioa_cfg *ioa_cfg, काष्ठा ipr_dump *dump)
अणु
	अचिन्हित दीर्घ start_addr, sdt_word;
	अचिन्हित दीर्घ lock_flags = 0;
	काष्ठा ipr_driver_dump *driver_dump = &dump->driver_dump;
	काष्ठा ipr_ioa_dump *ioa_dump = &dump->ioa_dump;
	u32 num_entries, max_num_entries, start_off, end_off;
	u32 max_dump_size, bytes_to_copy, bytes_copied, rc;
	काष्ठा ipr_sdt *sdt;
	पूर्णांक valid = 1;
	पूर्णांक i;

	ENTER;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	अगर (ioa_cfg->sdt_state != READ_DUMP) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस;
	पूर्ण

	अगर (ioa_cfg->sis64) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		ssleep(IPR_DUMP_DELAY_SECONDS);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	पूर्ण

	start_addr = पढ़ोl(ioa_cfg->ioa_mailbox);

	अगर (!ioa_cfg->sis64 && !ipr_sdt_is_fmt2(start_addr)) अणु
		dev_err(&ioa_cfg->pdev->dev,
			"Invalid dump table format: %lx\n", start_addr);
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस;
	पूर्ण

	dev_err(&ioa_cfg->pdev->dev, "Dump of IOA initiated\n");

	driver_dump->hdr.eye_catcher = IPR_DUMP_EYE_CATCHER;

	/* Initialize the overall dump header */
	driver_dump->hdr.len = माप(काष्ठा ipr_driver_dump);
	driver_dump->hdr.num_entries = 1;
	driver_dump->hdr.first_entry_offset = माप(काष्ठा ipr_dump_header);
	driver_dump->hdr.status = IPR_DUMP_STATUS_SUCCESS;
	driver_dump->hdr.os = IPR_DUMP_OS_LINUX;
	driver_dump->hdr.driver_name = IPR_DUMP_DRIVER_NAME;

	ipr_dump_version_data(ioa_cfg, driver_dump);
	ipr_dump_location_data(ioa_cfg, driver_dump);
	ipr_dump_ioa_type_data(ioa_cfg, driver_dump);
	ipr_dump_trace_data(ioa_cfg, driver_dump);

	/* Update dump_header */
	driver_dump->hdr.len += माप(काष्ठा ipr_dump_entry_header);

	/* IOA Dump entry */
	ipr_init_dump_entry_hdr(&ioa_dump->hdr);
	ioa_dump->hdr.len = 0;
	ioa_dump->hdr.data_type = IPR_DUMP_DATA_TYPE_BINARY;
	ioa_dump->hdr.id = IPR_DUMP_IOA_DUMP_ID;

	/* First entries in sdt are actually a list of dump addresses and
	 lengths to gather the real dump data.  sdt represents the poपूर्णांकer
	 to the ioa generated dump table.  Dump data will be extracted based
	 on entries in this table */
	sdt = &ioa_dump->sdt;

	अगर (ioa_cfg->sis64) अणु
		max_num_entries = IPR_FMT3_NUM_SDT_ENTRIES;
		max_dump_size = IPR_FMT3_MAX_IOA_DUMP_SIZE;
	पूर्ण अन्यथा अणु
		max_num_entries = IPR_FMT2_NUM_SDT_ENTRIES;
		max_dump_size = IPR_FMT2_MAX_IOA_DUMP_SIZE;
	पूर्ण

	bytes_to_copy = दुरत्व(काष्ठा ipr_sdt, entry) +
			(max_num_entries * माप(काष्ठा ipr_sdt_entry));
	rc = ipr_get_ldump_data_section(ioa_cfg, start_addr, (__be32 *)sdt,
					bytes_to_copy / माप(__be32));

	/* Smart Dump table is पढ़ोy to use and the first entry is valid */
	अगर (rc || ((be32_to_cpu(sdt->hdr.state) != IPR_FMT3_SDT_READY_TO_USE) &&
	    (be32_to_cpu(sdt->hdr.state) != IPR_FMT2_SDT_READY_TO_USE))) अणु
		dev_err(&ioa_cfg->pdev->dev,
			"Dump of IOA failed. Dump table not valid: %d, %X.\n",
			rc, be32_to_cpu(sdt->hdr.state));
		driver_dump->hdr.status = IPR_DUMP_STATUS_FAILED;
		ioa_cfg->sdt_state = DUMP_OBTAINED;
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस;
	पूर्ण

	num_entries = be32_to_cpu(sdt->hdr.num_entries_used);

	अगर (num_entries > max_num_entries)
		num_entries = max_num_entries;

	/* Update dump length to the actual data to be copied */
	dump->driver_dump.hdr.len += माप(काष्ठा ipr_sdt_header);
	अगर (ioa_cfg->sis64)
		dump->driver_dump.hdr.len += num_entries * माप(काष्ठा ipr_sdt_entry);
	अन्यथा
		dump->driver_dump.hdr.len += max_num_entries * माप(काष्ठा ipr_sdt_entry);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	क्रम (i = 0; i < num_entries; i++) अणु
		अगर (ioa_dump->hdr.len > max_dump_size) अणु
			driver_dump->hdr.status = IPR_DUMP_STATUS_QUAL_SUCCESS;
			अवरोध;
		पूर्ण

		अगर (sdt->entry[i].flags & IPR_SDT_VALID_ENTRY) अणु
			sdt_word = be32_to_cpu(sdt->entry[i].start_token);
			अगर (ioa_cfg->sis64)
				bytes_to_copy = be32_to_cpu(sdt->entry[i].end_token);
			अन्यथा अणु
				start_off = sdt_word & IPR_FMT2_MBX_ADDR_MASK;
				end_off = be32_to_cpu(sdt->entry[i].end_token);

				अगर (ipr_sdt_is_fmt2(sdt_word) && sdt_word)
					bytes_to_copy = end_off - start_off;
				अन्यथा
					valid = 0;
			पूर्ण
			अगर (valid) अणु
				अगर (bytes_to_copy > max_dump_size) अणु
					sdt->entry[i].flags &= ~IPR_SDT_VALID_ENTRY;
					जारी;
				पूर्ण

				/* Copy data from adapter to driver buffers */
				bytes_copied = ipr_sdt_copy(ioa_cfg, sdt_word,
							    bytes_to_copy);

				ioa_dump->hdr.len += bytes_copied;

				अगर (bytes_copied != bytes_to_copy) अणु
					driver_dump->hdr.status = IPR_DUMP_STATUS_QUAL_SUCCESS;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	dev_err(&ioa_cfg->pdev->dev, "Dump of IOA completed.\n");

	/* Update dump_header */
	driver_dump->hdr.len += ioa_dump->hdr.len;
	wmb();
	ioa_cfg->sdt_state = DUMP_OBTAINED;
	LEAVE;
पूर्ण

#अन्यथा
#घोषणा ipr_get_ioa_dump(ioa_cfg, dump) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * ipr_release_dump - Free adapter dump memory
 * @kref:	kref काष्ठा
 *
 * Return value:
 *	nothing
 **/
अटल व्योम ipr_release_dump(काष्ठा kref *kref)
अणु
	काष्ठा ipr_dump *dump = container_of(kref, काष्ठा ipr_dump, kref);
	काष्ठा ipr_ioa_cfg *ioa_cfg = dump->ioa_cfg;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक i;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ioa_cfg->dump = शून्य;
	ioa_cfg->sdt_state = INACTIVE;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	क्रम (i = 0; i < dump->ioa_dump.next_page_index; i++)
		मुक्त_page((अचिन्हित दीर्घ) dump->ioa_dump.ioa_data[i]);

	vमुक्त(dump->ioa_dump.ioa_data);
	kमुक्त(dump);
	LEAVE;
पूर्ण

अटल व्योम ipr_add_हटाओ_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा ipr_resource_entry *res;
	काष्ठा scsi_device *sdev;
	काष्ठा ipr_ioa_cfg *ioa_cfg =
		container_of(work, काष्ठा ipr_ioa_cfg, scsi_add_work_q);
	u8 bus, target, lun;
	पूर्णांक did_work;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

restart:
	करो अणु
		did_work = 0;
		अगर (!ioa_cfg->hrrq[IPR_INIT_HRRQ].allow_cmds) अणु
			spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
			वापस;
		पूर्ण

		list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
			अगर (res->del_from_ml && res->sdev) अणु
				did_work = 1;
				sdev = res->sdev;
				अगर (!scsi_device_get(sdev)) अणु
					अगर (!res->add_to_ml)
						list_move_tail(&res->queue, &ioa_cfg->मुक्त_res_q);
					अन्यथा
						res->del_from_ml = 0;
					spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
					scsi_हटाओ_device(sdev);
					scsi_device_put(sdev);
					spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (did_work);

	list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
		अगर (res->add_to_ml) अणु
			bus = res->bus;
			target = res->target;
			lun = res->lun;
			res->add_to_ml = 0;
			spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
			scsi_add_device(ioa_cfg->host, bus, target, lun);
			spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
			जाओ restart;
		पूर्ण
	पूर्ण

	ioa_cfg->scan_करोne = 1;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	kobject_uevent(&ioa_cfg->host->shost_dev.kobj, KOBJ_CHANGE);
	LEAVE;
पूर्ण

/**
 * ipr_worker_thपढ़ो - Worker thपढ़ो
 * @work:		ioa config काष्ठा
 *
 * Called at task level from a work thपढ़ो. This function takes care
 * of adding and removing device from the mid-layer as configuration
 * changes are detected by the adapter.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_worker_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा ipr_dump *dump;
	काष्ठा ipr_ioa_cfg *ioa_cfg =
		container_of(work, काष्ठा ipr_ioa_cfg, work_q);

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	अगर (ioa_cfg->sdt_state == READ_DUMP) अणु
		dump = ioa_cfg->dump;
		अगर (!dump) अणु
			spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
			वापस;
		पूर्ण
		kref_get(&dump->kref);
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		ipr_get_ioa_dump(ioa_cfg, dump);
		kref_put(&dump->kref, ipr_release_dump);

		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
		अगर (ioa_cfg->sdt_state == DUMP_OBTAINED && !ioa_cfg->dump_समयout)
			ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस;
	पूर्ण

	अगर (ioa_cfg->scsi_unblock) अणु
		ioa_cfg->scsi_unblock = 0;
		ioa_cfg->scsi_blocked = 0;
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		scsi_unblock_requests(ioa_cfg->host);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
		अगर (ioa_cfg->scsi_blocked)
			scsi_block_requests(ioa_cfg->host);
	पूर्ण

	अगर (!ioa_cfg->scan_enabled) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस;
	पूर्ण

	schedule_work(&ioa_cfg->scsi_add_work_q);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
पूर्ण

#अगर_घोषित CONFIG_SCSI_IPR_TRACE
/**
 * ipr_पढ़ो_trace - Dump the adapter trace
 * @filp:		खोलो sysfs file
 * @kobj:		kobject काष्ठा
 * @bin_attr:		bin_attribute काष्ठा
 * @buf:		buffer
 * @off:		offset
 * @count:		buffer size
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_पढ़ो_trace(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr,
			      अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags = 0;
	sमाप_प्रकार ret;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ret = memory_पढ़ो_from_buffer(buf, count, &off, ioa_cfg->trace,
				IPR_TRACE_SIZE);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	वापस ret;
पूर्ण

अटल काष्ठा bin_attribute ipr_trace_attr = अणु
	.attr =	अणु
		.name = "trace",
		.mode = S_IRUGO,
	पूर्ण,
	.size = 0,
	.पढ़ो = ipr_पढ़ो_trace,
पूर्ण;
#पूर्ण_अगर

/**
 * ipr_show_fw_version - Show the firmware version
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_fw_version(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	काष्ठा ipr_inquiry_page3 *ucode_vpd = &ioa_cfg->vpd_cbs->page3_data;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	len = snम_लिखो(buf, PAGE_SIZE, "%02X%02X%02X%02X\n",
		       ucode_vpd->major_release, ucode_vpd->card_type,
		       ucode_vpd->minor_release[0],
		       ucode_vpd->minor_release[1]);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ipr_fw_version_attr = अणु
	.attr = अणु
		.name =		"fw_version",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = ipr_show_fw_version,
पूर्ण;

/**
 * ipr_show_log_level - Show the adapter's error logging level
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_log_level(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	len = snम_लिखो(buf, PAGE_SIZE, "%d\n", ioa_cfg->log_level);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

/**
 * ipr_store_log_level - Change the adapter's error logging level
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 * @count:	buffer size
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_store_log_level(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags = 0;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ioa_cfg->log_level = simple_म_से_अदीर्घ(buf, शून्य, 10);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस म_माप(buf);
पूर्ण

अटल काष्ठा device_attribute ipr_log_level_attr = अणु
	.attr = अणु
		.name =		"log_level",
		.mode =		S_IRUGO | S_IWUSR,
	पूर्ण,
	.show = ipr_show_log_level,
	.store = ipr_store_log_level
पूर्ण;

/**
 * ipr_store_diagnostics - IOA Diagnostics पूर्णांकerface
 * @dev:	device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 * @count:	buffer size
 *
 * This function will reset the adapter and रुको a reasonable
 * amount of समय क्रम any errors that the adapter might log.
 *
 * Return value:
 * 	count on success / other on failure
 **/
अटल sमाप_प्रकार ipr_store_diagnostics(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक rc = count;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	जबतक (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	पूर्ण

	ioa_cfg->errors_logged = 0;
	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NORMAL);

	अगर (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);

		/* Wait क्रम a second क्रम any errors to be logged */
		msleep(1000);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस -EIO;
	पूर्ण

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	अगर (ioa_cfg->in_reset_reload || ioa_cfg->errors_logged)
		rc = -EIO;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	वापस rc;
पूर्ण

अटल काष्ठा device_attribute ipr_diagnostics_attr = अणु
	.attr = अणु
		.name =		"run_diagnostics",
		.mode =		S_IWUSR,
	पूर्ण,
	.store = ipr_store_diagnostics
पूर्ण;

/**
 * ipr_show_adapter_state - Show the adapter's state
 * @dev:	device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_adapter_state(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead)
		len = snम_लिखो(buf, PAGE_SIZE, "offline\n");
	अन्यथा
		len = snम_लिखो(buf, PAGE_SIZE, "online\n");
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

/**
 * ipr_store_adapter_state - Change adapter state
 * @dev:	device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 * @count:	buffer size
 *
 * This function will change the adapter's state.
 *
 * Return value:
 * 	count on success / other on failure
 **/
अटल sमाप_प्रकार ipr_store_adapter_state(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक result = count, i;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead &&
	    !म_भेदन(buf, "online", 6)) अणु
		क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
			spin_lock(&ioa_cfg->hrrq[i]._lock);
			ioa_cfg->hrrq[i].ioa_is_dead = 0;
			spin_unlock(&ioa_cfg->hrrq[i]._lock);
		पूर्ण
		wmb();
		ioa_cfg->reset_retries = 0;
		ioa_cfg->in_ioa_bringकरोwn = 0;
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	पूर्ण
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);

	वापस result;
पूर्ण

अटल काष्ठा device_attribute ipr_ioa_state_attr = अणु
	.attr = अणु
		.name =		"online_state",
		.mode =		S_IRUGO | S_IWUSR,
	पूर्ण,
	.show = ipr_show_adapter_state,
	.store = ipr_store_adapter_state
पूर्ण;

/**
 * ipr_store_reset_adapter - Reset the adapter
 * @dev:	device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 * @count:	buffer size
 *
 * This function will reset the adapter.
 *
 * Return value:
 * 	count on success / other on failure
 **/
अटल sमाप_प्रकार ipr_store_reset_adapter(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक result = count;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	अगर (!ioa_cfg->in_reset_reload)
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NORMAL);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);

	वापस result;
पूर्ण

अटल काष्ठा device_attribute ipr_ioa_reset_attr = अणु
	.attr = अणु
		.name =		"reset_host",
		.mode =		S_IWUSR,
	पूर्ण,
	.store = ipr_store_reset_adapter
पूर्ण;

अटल पूर्णांक ipr_iopoll(काष्ठा irq_poll *iop, पूर्णांक budget);
 /**
 * ipr_show_iopoll_weight - Show ipr polling mode
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_iopoll_weight(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक len;

	spin_lock_irqsave(shost->host_lock, lock_flags);
	len = snम_लिखो(buf, PAGE_SIZE, "%d\n", ioa_cfg->iopoll_weight);
	spin_unlock_irqrestore(shost->host_lock, lock_flags);

	वापस len;
पूर्ण

/**
 * ipr_store_iopoll_weight - Change the adapter's polling mode
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 * @count:	buffer size
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_store_iopoll_weight(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ user_iopoll_weight;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक i;

	अगर (!ioa_cfg->sis64) अणु
		dev_info(&ioa_cfg->pdev->dev, "irq_poll not supported on this adapter\n");
		वापस -EINVAL;
	पूर्ण
	अगर (kम_से_अदीर्घ(buf, 10, &user_iopoll_weight))
		वापस -EINVAL;

	अगर (user_iopoll_weight > 256) अणु
		dev_info(&ioa_cfg->pdev->dev, "Invalid irq_poll weight. It must be less than 256\n");
		वापस -EINVAL;
	पूर्ण

	अगर (user_iopoll_weight == ioa_cfg->iopoll_weight) अणु
		dev_info(&ioa_cfg->pdev->dev, "Current irq_poll weight has the same weight\n");
		वापस म_माप(buf);
	पूर्ण

	अगर (ioa_cfg->iopoll_weight && ioa_cfg->sis64 && ioa_cfg->nvectors > 1) अणु
		क्रम (i = 1; i < ioa_cfg->hrrq_num; i++)
			irq_poll_disable(&ioa_cfg->hrrq[i].iopoll);
	पूर्ण

	spin_lock_irqsave(shost->host_lock, lock_flags);
	ioa_cfg->iopoll_weight = user_iopoll_weight;
	अगर (ioa_cfg->iopoll_weight && ioa_cfg->sis64 && ioa_cfg->nvectors > 1) अणु
		क्रम (i = 1; i < ioa_cfg->hrrq_num; i++) अणु
			irq_poll_init(&ioa_cfg->hrrq[i].iopoll,
					ioa_cfg->iopoll_weight, ipr_iopoll);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, lock_flags);

	वापस म_माप(buf);
पूर्ण

अटल काष्ठा device_attribute ipr_iopoll_weight_attr = अणु
	.attr = अणु
		.name =		"iopoll_weight",
		.mode =		S_IRUGO | S_IWUSR,
	पूर्ण,
	.show = ipr_show_iopoll_weight,
	.store = ipr_store_iopoll_weight
पूर्ण;

/**
 * ipr_alloc_ucode_buffer - Allocates a microcode करोwnload buffer
 * @buf_len:		buffer length
 *
 * Allocates a DMA'able buffer in chunks and assembles a scatter/gather
 * list to use क्रम microcode करोwnload
 *
 * Return value:
 * 	poपूर्णांकer to sglist / शून्य on failure
 **/
अटल काष्ठा ipr_sglist *ipr_alloc_ucode_buffer(पूर्णांक buf_len)
अणु
	पूर्णांक sg_size, order;
	काष्ठा ipr_sglist *sglist;

	/* Get the minimum size per scatter/gather element */
	sg_size = buf_len / (IPR_MAX_SGLIST - 1);

	/* Get the actual size per element */
	order = get_order(sg_size);

	/* Allocate a scatter/gather list क्रम the DMA */
	sglist = kzalloc(माप(काष्ठा ipr_sglist), GFP_KERNEL);
	अगर (sglist == शून्य) अणु
		ipr_trace;
		वापस शून्य;
	पूर्ण
	sglist->order = order;
	sglist->scatterlist = sgl_alloc_order(buf_len, order, false, GFP_KERNEL,
					      &sglist->num_sg);
	अगर (!sglist->scatterlist) अणु
		kमुक्त(sglist);
		वापस शून्य;
	पूर्ण

	वापस sglist;
पूर्ण

/**
 * ipr_मुक्त_ucode_buffer - Frees a microcode करोwnload buffer
 * @sglist:		scatter/gather list poपूर्णांकer
 *
 * Free a DMA'able ucode करोwnload buffer previously allocated with
 * ipr_alloc_ucode_buffer
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_मुक्त_ucode_buffer(काष्ठा ipr_sglist *sglist)
अणु
	sgl_मुक्त_order(sglist->scatterlist, sglist->order);
	kमुक्त(sglist);
पूर्ण

/**
 * ipr_copy_ucode_buffer - Copy user buffer to kernel buffer
 * @sglist:		scatter/gather list poपूर्णांकer
 * @buffer:		buffer poपूर्णांकer
 * @len:		buffer length
 *
 * Copy a microcode image from a user buffer पूर्णांकo a buffer allocated by
 * ipr_alloc_ucode_buffer
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक ipr_copy_ucode_buffer(काष्ठा ipr_sglist *sglist,
				 u8 *buffer, u32 len)
अणु
	पूर्णांक bsize_elem, i, result = 0;
	काष्ठा scatterlist *sg;
	व्योम *kaddr;

	/* Determine the actual number of bytes per element */
	bsize_elem = PAGE_SIZE * (1 << sglist->order);

	sg = sglist->scatterlist;

	क्रम (i = 0; i < (len / bsize_elem); i++, sg = sg_next(sg),
			buffer += bsize_elem) अणु
		काष्ठा page *page = sg_page(sg);

		kaddr = kmap(page);
		स_नकल(kaddr, buffer, bsize_elem);
		kunmap(page);

		sg->length = bsize_elem;

		अगर (result != 0) अणु
			ipr_trace;
			वापस result;
		पूर्ण
	पूर्ण

	अगर (len % bsize_elem) अणु
		काष्ठा page *page = sg_page(sg);

		kaddr = kmap(page);
		स_नकल(kaddr, buffer, len % bsize_elem);
		kunmap(page);

		sg->length = len % bsize_elem;
	पूर्ण

	sglist->buffer_len = len;
	वापस result;
पूर्ण

/**
 * ipr_build_ucode_ioadl64 - Build a microcode करोwnload IOADL
 * @ipr_cmd:		ipr command काष्ठा
 * @sglist:		scatter/gather list
 *
 * Builds a microcode करोwnload IOA data list (IOADL).
 *
 **/
अटल व्योम ipr_build_ucode_ioadl64(काष्ठा ipr_cmnd *ipr_cmd,
				    काष्ठा ipr_sglist *sglist)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioadl64_desc *ioadl64 = ipr_cmd->i.ioadl64;
	काष्ठा scatterlist *scatterlist = sglist->scatterlist;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	ipr_cmd->dma_use_sg = sglist->num_dma_sg;
	ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
	ioarcb->data_transfer_length = cpu_to_be32(sglist->buffer_len);

	ioarcb->ioadl_len =
		cpu_to_be32(माप(काष्ठा ipr_ioadl64_desc) * ipr_cmd->dma_use_sg);
	क्रम_each_sg(scatterlist, sg, ipr_cmd->dma_use_sg, i) अणु
		ioadl64[i].flags = cpu_to_be32(IPR_IOADL_FLAGS_WRITE);
		ioadl64[i].data_len = cpu_to_be32(sg_dma_len(sg));
		ioadl64[i].address = cpu_to_be64(sg_dma_address(sg));
	पूर्ण

	ioadl64[i-1].flags |= cpu_to_be32(IPR_IOADL_FLAGS_LAST);
पूर्ण

/**
 * ipr_build_ucode_ioadl - Build a microcode करोwnload IOADL
 * @ipr_cmd:	ipr command काष्ठा
 * @sglist:		scatter/gather list
 *
 * Builds a microcode करोwnload IOA data list (IOADL).
 *
 **/
अटल व्योम ipr_build_ucode_ioadl(काष्ठा ipr_cmnd *ipr_cmd,
				  काष्ठा ipr_sglist *sglist)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioadl_desc *ioadl = ipr_cmd->i.ioadl;
	काष्ठा scatterlist *scatterlist = sglist->scatterlist;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	ipr_cmd->dma_use_sg = sglist->num_dma_sg;
	ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
	ioarcb->data_transfer_length = cpu_to_be32(sglist->buffer_len);

	ioarcb->ioadl_len =
		cpu_to_be32(माप(काष्ठा ipr_ioadl_desc) * ipr_cmd->dma_use_sg);

	क्रम_each_sg(scatterlist, sg, ipr_cmd->dma_use_sg, i) अणु
		ioadl[i].flags_and_data_len =
			cpu_to_be32(IPR_IOADL_FLAGS_WRITE | sg_dma_len(sg));
		ioadl[i].address =
			cpu_to_be32(sg_dma_address(sg));
	पूर्ण

	ioadl[i-1].flags_and_data_len |=
		cpu_to_be32(IPR_IOADL_FLAGS_LAST);
पूर्ण

/**
 * ipr_update_ioa_ucode - Update IOA's microcode
 * @ioa_cfg:	ioa config काष्ठा
 * @sglist:		scatter/gather list
 *
 * Initiate an adapter reset to update the IOA's microcode
 *
 * Return value:
 * 	0 on success / -EIO on failure
 **/
अटल पूर्णांक ipr_update_ioa_ucode(काष्ठा ipr_ioa_cfg *ioa_cfg,
				काष्ठा ipr_sglist *sglist)
अणु
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	जबतक (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	पूर्ण

	अगर (ioa_cfg->ucode_sglist) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		dev_err(&ioa_cfg->pdev->dev,
			"Microcode download already in progress\n");
		वापस -EIO;
	पूर्ण

	sglist->num_dma_sg = dma_map_sg(&ioa_cfg->pdev->dev,
					sglist->scatterlist, sglist->num_sg,
					DMA_TO_DEVICE);

	अगर (!sglist->num_dma_sg) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		dev_err(&ioa_cfg->pdev->dev,
			"Failed to map microcode download buffer!\n");
		वापस -EIO;
	पूर्ण

	ioa_cfg->ucode_sglist = sglist;
	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NORMAL);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ioa_cfg->ucode_sglist = शून्य;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस 0;
पूर्ण

/**
 * ipr_store_update_fw - Update the firmware on the adapter
 * @dev:	device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 * @count:	buffer size
 *
 * This function will update the firmware on the adapter.
 *
 * Return value:
 * 	count on success / other on failure
 **/
अटल sमाप_प्रकार ipr_store_update_fw(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	काष्ठा ipr_ucode_image_header *image_hdr;
	स्थिर काष्ठा firmware *fw_entry;
	काष्ठा ipr_sglist *sglist;
	अक्षर fname[100];
	अक्षर *src;
	अक्षर *endline;
	पूर्णांक result, dnld_size;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	snम_लिखो(fname, माप(fname), "%s", buf);

	endline = म_अक्षर(fname, '\n');
	अगर (endline)
		*endline = '\0';

	अगर (request_firmware(&fw_entry, fname, &ioa_cfg->pdev->dev)) अणु
		dev_err(&ioa_cfg->pdev->dev, "Firmware file %s not found\n", fname);
		वापस -EIO;
	पूर्ण

	image_hdr = (काष्ठा ipr_ucode_image_header *)fw_entry->data;

	src = (u8 *)image_hdr + be32_to_cpu(image_hdr->header_length);
	dnld_size = fw_entry->size - be32_to_cpu(image_hdr->header_length);
	sglist = ipr_alloc_ucode_buffer(dnld_size);

	अगर (!sglist) अणु
		dev_err(&ioa_cfg->pdev->dev, "Microcode buffer allocation failed\n");
		release_firmware(fw_entry);
		वापस -ENOMEM;
	पूर्ण

	result = ipr_copy_ucode_buffer(sglist, src, dnld_size);

	अगर (result) अणु
		dev_err(&ioa_cfg->pdev->dev,
			"Microcode buffer copy to DMA buffer failed\n");
		जाओ out;
	पूर्ण

	ipr_info("Updating microcode, please be patient.  This may take up to 30 minutes.\n");

	result = ipr_update_ioa_ucode(ioa_cfg, sglist);

	अगर (!result)
		result = count;
out:
	ipr_मुक्त_ucode_buffer(sglist);
	release_firmware(fw_entry);
	वापस result;
पूर्ण

अटल काष्ठा device_attribute ipr_update_fw_attr = अणु
	.attr = अणु
		.name =		"update_fw",
		.mode =		S_IWUSR,
	पूर्ण,
	.store = ipr_store_update_fw
पूर्ण;

/**
 * ipr_show_fw_type - Show the adapter's firmware type.
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_fw_type(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	len = snम_लिखो(buf, PAGE_SIZE, "%d\n", ioa_cfg->sis64);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ipr_ioa_fw_type_attr = अणु
	.attr = अणु
		.name =		"fw_type",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = ipr_show_fw_type
पूर्ण;

अटल sमाप_प्रकार ipr_पढ़ो_async_err_log(काष्ठा file *filep, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	काष्ठा ipr_hostrcb *hostrcb;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक ret;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	hostrcb = list_first_entry_or_null(&ioa_cfg->hostrcb_report_q,
					काष्ठा ipr_hostrcb, queue);
	अगर (!hostrcb) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस 0;
	पूर्ण
	ret = memory_पढ़ो_from_buffer(buf, count, &off, &hostrcb->hcam,
				माप(hostrcb->hcam));
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ipr_next_async_err_log(काष्ठा file *filep, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	काष्ठा ipr_hostrcb *hostrcb;
	अचिन्हित दीर्घ lock_flags = 0;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	hostrcb = list_first_entry_or_null(&ioa_cfg->hostrcb_report_q,
					काष्ठा ipr_hostrcb, queue);
	अगर (!hostrcb) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस count;
	पूर्ण

	/* Reclaim hostrcb beक्रमe निकास */
	list_move_tail(&hostrcb->queue, &ioa_cfg->hostrcb_मुक्त_q);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस count;
पूर्ण

अटल काष्ठा bin_attribute ipr_ioa_async_err_log = अणु
	.attr = अणु
		.name =		"async_err_log",
		.mode =		S_IRUGO | S_IWUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = ipr_पढ़ो_async_err_log,
	.ग_लिखो = ipr_next_async_err_log
पूर्ण;

अटल काष्ठा device_attribute *ipr_ioa_attrs[] = अणु
	&ipr_fw_version_attr,
	&ipr_log_level_attr,
	&ipr_diagnostics_attr,
	&ipr_ioa_state_attr,
	&ipr_ioa_reset_attr,
	&ipr_update_fw_attr,
	&ipr_ioa_fw_type_attr,
	&ipr_iopoll_weight_attr,
	शून्य,
पूर्ण;

#अगर_घोषित CONFIG_SCSI_IPR_DUMP
/**
 * ipr_पढ़ो_dump - Dump the adapter
 * @filp:		खोलो sysfs file
 * @kobj:		kobject काष्ठा
 * @bin_attr:		bin_attribute काष्ठा
 * @buf:		buffer
 * @off:		offset
 * @count:		buffer size
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_पढ़ो_dump(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr,
			     अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	काष्ठा ipr_dump *dump;
	अचिन्हित दीर्घ lock_flags = 0;
	अक्षर *src;
	पूर्णांक len, sdt_end;
	माप_प्रकार rc = count;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	dump = ioa_cfg->dump;

	अगर (ioa_cfg->sdt_state != DUMP_OBTAINED || !dump) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस 0;
	पूर्ण
	kref_get(&dump->kref);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	अगर (off > dump->driver_dump.hdr.len) अणु
		kref_put(&dump->kref, ipr_release_dump);
		वापस 0;
	पूर्ण

	अगर (off + count > dump->driver_dump.hdr.len) अणु
		count = dump->driver_dump.hdr.len - off;
		rc = count;
	पूर्ण

	अगर (count && off < माप(dump->driver_dump)) अणु
		अगर (off + count > माप(dump->driver_dump))
			len = माप(dump->driver_dump) - off;
		अन्यथा
			len = count;
		src = (u8 *)&dump->driver_dump + off;
		स_नकल(buf, src, len);
		buf += len;
		off += len;
		count -= len;
	पूर्ण

	off -= माप(dump->driver_dump);

	अगर (ioa_cfg->sis64)
		sdt_end = दुरत्व(काष्ठा ipr_ioa_dump, sdt.entry) +
			  (be32_to_cpu(dump->ioa_dump.sdt.hdr.num_entries_used) *
			   माप(काष्ठा ipr_sdt_entry));
	अन्यथा
		sdt_end = दुरत्व(काष्ठा ipr_ioa_dump, sdt.entry) +
			  (IPR_FMT2_NUM_SDT_ENTRIES * माप(काष्ठा ipr_sdt_entry));

	अगर (count && off < sdt_end) अणु
		अगर (off + count > sdt_end)
			len = sdt_end - off;
		अन्यथा
			len = count;
		src = (u8 *)&dump->ioa_dump + off;
		स_नकल(buf, src, len);
		buf += len;
		off += len;
		count -= len;
	पूर्ण

	off -= sdt_end;

	जबतक (count) अणु
		अगर ((off & PAGE_MASK) != ((off + count) & PAGE_MASK))
			len = PAGE_ALIGN(off) - off;
		अन्यथा
			len = count;
		src = (u8 *)dump->ioa_dump.ioa_data[(off & PAGE_MASK) >> PAGE_SHIFT];
		src += off & ~PAGE_MASK;
		स_नकल(buf, src, len);
		buf += len;
		off += len;
		count -= len;
	पूर्ण

	kref_put(&dump->kref, ipr_release_dump);
	वापस rc;
पूर्ण

/**
 * ipr_alloc_dump - Prepare क्रम adapter dump
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ipr_alloc_dump(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा ipr_dump *dump;
	__be32 **ioa_data;
	अचिन्हित दीर्घ lock_flags = 0;

	dump = kzalloc(माप(काष्ठा ipr_dump), GFP_KERNEL);

	अगर (!dump) अणु
		ipr_err("Dump memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (ioa_cfg->sis64)
		ioa_data = vदो_स्मृति(array_size(IPR_FMT3_MAX_NUM_DUMP_PAGES,
					      माप(__be32 *)));
	अन्यथा
		ioa_data = vदो_स्मृति(array_size(IPR_FMT2_MAX_NUM_DUMP_PAGES,
					      माप(__be32 *)));

	अगर (!ioa_data) अणु
		ipr_err("Dump memory allocation failed\n");
		kमुक्त(dump);
		वापस -ENOMEM;
	पूर्ण

	dump->ioa_dump.ioa_data = ioa_data;

	kref_init(&dump->kref);
	dump->ioa_cfg = ioa_cfg;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	अगर (INACTIVE != ioa_cfg->sdt_state) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		vमुक्त(dump->ioa_dump.ioa_data);
		kमुक्त(dump);
		वापस 0;
	पूर्ण

	ioa_cfg->dump = dump;
	ioa_cfg->sdt_state = WAIT_FOR_DUMP;
	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead && !ioa_cfg->dump_taken) अणु
		ioa_cfg->dump_taken = 1;
		schedule_work(&ioa_cfg->work_q);
	पूर्ण
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	वापस 0;
पूर्ण

/**
 * ipr_मुक्त_dump - Free adapter dump memory
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ipr_मुक्त_dump(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा ipr_dump *dump;
	अचिन्हित दीर्घ lock_flags = 0;

	ENTER;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	dump = ioa_cfg->dump;
	अगर (!dump) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस 0;
	पूर्ण

	ioa_cfg->dump = शून्य;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	kref_put(&dump->kref, ipr_release_dump);

	LEAVE;
	वापस 0;
पूर्ण

/**
 * ipr_ग_लिखो_dump - Setup dump state of adapter
 * @filp:		खोलो sysfs file
 * @kobj:		kobject काष्ठा
 * @bin_attr:		bin_attribute काष्ठा
 * @buf:		buffer
 * @off:		offset
 * @count:		buffer size
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_ग_लिखो_dump(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr,
			      अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (buf[0] == '1')
		rc = ipr_alloc_dump(ioa_cfg);
	अन्यथा अगर (buf[0] == '0')
		rc = ipr_मुक्त_dump(ioa_cfg);
	अन्यथा
		वापस -EINVAL;

	अगर (rc)
		वापस rc;
	अन्यथा
		वापस count;
पूर्ण

अटल काष्ठा bin_attribute ipr_dump_attr = अणु
	.attr =	अणु
		.name = "dump",
		.mode = S_IRUSR | S_IWUSR,
	पूर्ण,
	.size = 0,
	.पढ़ो = ipr_पढ़ो_dump,
	.ग_लिखो = ipr_ग_लिखो_dump
पूर्ण;
#अन्यथा
अटल पूर्णांक ipr_मुक्त_dump(काष्ठा ipr_ioa_cfg *ioa_cfg) अणु वापस 0; पूर्ण;
#पूर्ण_अगर

/**
 * ipr_change_queue_depth - Change the device's queue depth
 * @sdev:	scsi device काष्ठा
 * @qdepth:	depth to set
 *
 * Return value:
 * 	actual depth set
 **/
अटल पूर्णांक ipr_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;

	अगर (res && ipr_is_gata(res) && qdepth > IPR_MAX_CMD_PER_ATA_LUN)
		qdepth = IPR_MAX_CMD_PER_ATA_LUN;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	scsi_change_queue_depth(sdev, qdepth);
	वापस sdev->queue_depth;
पूर्ण

/**
 * ipr_show_adapter_handle - Show the adapter's resource handle क्रम this device
 * @dev:	device काष्ठा
 * @attr:	device attribute काष्ठाure
 * @buf:	buffer
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_adapter_handle(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;
	sमाप_प्रकार len = -ENXIO;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;
	अगर (res)
		len = snम_लिखो(buf, PAGE_SIZE, "%08X\n", res->res_handle);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ipr_adapter_handle_attr = अणु
	.attr = अणु
		.name = 	"adapter_handle",
		.mode =		S_IRUSR,
	पूर्ण,
	.show = ipr_show_adapter_handle
पूर्ण;

/**
 * ipr_show_resource_path - Show the resource path or the resource address क्रम
 *			    this device.
 * @dev:	device काष्ठा
 * @attr:	device attribute काष्ठाure
 * @buf:	buffer
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_resource_path(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;
	sमाप_प्रकार len = -ENXIO;
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;
	अगर (res && ioa_cfg->sis64)
		len = snम_लिखो(buf, PAGE_SIZE, "%s\n",
			       __ipr_क्रमmat_res_path(res->res_path, buffer,
						     माप(buffer)));
	अन्यथा अगर (res)
		len = snम_लिखो(buf, PAGE_SIZE, "%d:%d:%d:%d\n", ioa_cfg->host->host_no,
			       res->bus, res->target, res->lun);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ipr_resource_path_attr = अणु
	.attr = अणु
		.name = 	"resource_path",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = ipr_show_resource_path
पूर्ण;

/**
 * ipr_show_device_id - Show the device_id क्रम this device.
 * @dev:	device काष्ठा
 * @attr:	device attribute काष्ठाure
 * @buf:	buffer
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_device_id(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;
	sमाप_प्रकार len = -ENXIO;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;
	अगर (res && ioa_cfg->sis64)
		len = snम_लिखो(buf, PAGE_SIZE, "0x%llx\n", be64_to_cpu(res->dev_id));
	अन्यथा अगर (res)
		len = snम_लिखो(buf, PAGE_SIZE, "0x%llx\n", res->lun_wwn);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ipr_device_id_attr = अणु
	.attr = अणु
		.name =		"device_id",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = ipr_show_device_id
पूर्ण;

/**
 * ipr_show_resource_type - Show the resource type क्रम this device.
 * @dev:	device काष्ठा
 * @attr:	device attribute काष्ठाure
 * @buf:	buffer
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_resource_type(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;
	sमाप_प्रकार len = -ENXIO;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;

	अगर (res)
		len = snम_लिखो(buf, PAGE_SIZE, "%x\n", res->type);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ipr_resource_type_attr = अणु
	.attr = अणु
		.name =		"resource_type",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = ipr_show_resource_type
पूर्ण;

/**
 * ipr_show_raw_mode - Show the adapter's raw mode
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_show_raw_mode(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;
	sमाप_प्रकार len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;
	अगर (res)
		len = snम_लिखो(buf, PAGE_SIZE, "%d\n", res->raw_mode);
	अन्यथा
		len = -ENXIO;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

/**
 * ipr_store_raw_mode - Change the adapter's raw mode
 * @dev:	class device काष्ठा
 * @attr:	device attribute (unused)
 * @buf:	buffer
 * @count:		buffer size
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ipr_store_raw_mode(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;
	sमाप_प्रकार len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;
	अगर (res) अणु
		अगर (ipr_is_af_dasd_device(res)) अणु
			res->raw_mode = simple_म_से_अदीर्घ(buf, शून्य, 10);
			len = म_माप(buf);
			अगर (res->sdev)
				sdev_prपूर्णांकk(KERN_INFO, res->sdev, "raw mode is %s\n",
					res->raw_mode ? "enabled" : "disabled");
		पूर्ण अन्यथा
			len = -EINVAL;
	पूर्ण अन्यथा
		len = -ENXIO;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ipr_raw_mode_attr = अणु
	.attr = अणु
		.name =		"raw_mode",
		.mode =		S_IRUGO | S_IWUSR,
	पूर्ण,
	.show = ipr_show_raw_mode,
	.store = ipr_store_raw_mode
पूर्ण;

अटल काष्ठा device_attribute *ipr_dev_attrs[] = अणु
	&ipr_adapter_handle_attr,
	&ipr_resource_path_attr,
	&ipr_device_id_attr,
	&ipr_resource_type_attr,
	&ipr_raw_mode_attr,
	शून्य,
पूर्ण;

/**
 * ipr_biosparam - Return the HSC mapping
 * @sdev:			scsi device काष्ठा
 * @block_device:	block device poपूर्णांकer
 * @capacity:		capacity of the device
 * @parm:			Array containing वापसed HSC values.
 *
 * This function generates the HSC parms that fdisk uses.
 * We want to make sure we वापस something that places partitions
 * on 4k boundaries क्रम best perक्रमmance with the IOA.
 *
 * Return value:
 * 	0 on success
 **/
अटल पूर्णांक ipr_biosparam(काष्ठा scsi_device *sdev,
			 काष्ठा block_device *block_device,
			 sector_t capacity, पूर्णांक *parm)
अणु
	पूर्णांक heads, sectors;
	sector_t cylinders;

	heads = 128;
	sectors = 32;

	cylinders = capacity;
	sector_भाग(cylinders, (128 * 32));

	/* वापस result */
	parm[0] = heads;
	parm[1] = sectors;
	parm[2] = cylinders;

	वापस 0;
पूर्ण

/**
 * ipr_find_starget - Find target based on bus/target.
 * @starget:	scsi target काष्ठा
 *
 * Return value:
 * 	resource entry poपूर्णांकer अगर found / शून्य अगर not found
 **/
अटल काष्ठा ipr_resource_entry *ipr_find_starget(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *) shost->hostdata;
	काष्ठा ipr_resource_entry *res;

	list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
		अगर ((res->bus == starget->channel) &&
		    (res->target == starget->id)) अणु
			वापस res;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा ata_port_info sata_port_info;

/**
 * ipr_target_alloc - Prepare क्रम commands to a SCSI target
 * @starget:	scsi target काष्ठा
 *
 * If the device is a SATA device, this function allocates an
 * ATA port with libata, अन्यथा it करोes nothing.
 *
 * Return value:
 * 	0 on success / non-0 on failure
 **/
अटल पूर्णांक ipr_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *) shost->hostdata;
	काष्ठा ipr_sata_port *sata_port;
	काष्ठा ata_port *ap;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = ipr_find_starget(starget);
	starget->hostdata = शून्य;

	अगर (res && ipr_is_gata(res)) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		sata_port = kzalloc(माप(*sata_port), GFP_KERNEL);
		अगर (!sata_port)
			वापस -ENOMEM;

		ap = ata_sas_port_alloc(&ioa_cfg->ata_host, &sata_port_info, shost);
		अगर (ap) अणु
			spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
			sata_port->ioa_cfg = ioa_cfg;
			sata_port->ap = ap;
			sata_port->res = res;

			res->sata_port = sata_port;
			ap->निजी_data = sata_port;
			starget->hostdata = sata_port;
		पूर्ण अन्यथा अणु
			kमुक्त(sata_port);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	वापस 0;
पूर्ण

/**
 * ipr_target_destroy - Destroy a SCSI target
 * @starget:	scsi target काष्ठा
 *
 * If the device was a SATA device, this function मुक्तs the libata
 * ATA port, अन्यथा it करोes nothing.
 *
 **/
अटल व्योम ipr_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा ipr_sata_port *sata_port = starget->hostdata;
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *) shost->hostdata;

	अगर (ioa_cfg->sis64) अणु
		अगर (!ipr_find_starget(starget)) अणु
			अगर (starget->channel == IPR_ARRAY_VIRTUAL_BUS)
				clear_bit(starget->id, ioa_cfg->array_ids);
			अन्यथा अगर (starget->channel == IPR_VSET_VIRTUAL_BUS)
				clear_bit(starget->id, ioa_cfg->vset_ids);
			अन्यथा अगर (starget->channel == 0)
				clear_bit(starget->id, ioa_cfg->target_ids);
		पूर्ण
	पूर्ण

	अगर (sata_port) अणु
		starget->hostdata = शून्य;
		ata_sas_port_destroy(sata_port->ap);
		kमुक्त(sata_port);
	पूर्ण
पूर्ण

/**
 * ipr_find_sdev - Find device based on bus/target/lun.
 * @sdev:	scsi device काष्ठा
 *
 * Return value:
 * 	resource entry poपूर्णांकer अगर found / शून्य अगर not found
 **/
अटल काष्ठा ipr_resource_entry *ipr_find_sdev(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *) sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;

	list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
		अगर ((res->bus == sdev->channel) &&
		    (res->target == sdev->id) &&
		    (res->lun == sdev->lun))
			वापस res;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ipr_slave_destroy - Unconfigure a SCSI device
 * @sdev:	scsi device काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ipr_resource_entry *res;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	अचिन्हित दीर्घ lock_flags = 0;

	ioa_cfg = (काष्ठा ipr_ioa_cfg *) sdev->host->hostdata;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (काष्ठा ipr_resource_entry *) sdev->hostdata;
	अगर (res) अणु
		अगर (res->sata_port)
			res->sata_port->ap->link.device[0].class = ATA_DEV_NONE;
		sdev->hostdata = शून्य;
		res->sdev = शून्य;
		res->sata_port = शून्य;
	पूर्ण
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
पूर्ण

/**
 * ipr_slave_configure - Configure a SCSI device
 * @sdev:	scsi device काष्ठा
 *
 * This function configures the specअगरied scsi device.
 *
 * Return value:
 * 	0 on success
 **/
अटल पूर्णांक ipr_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *) sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	काष्ठा ata_port *ap = शून्य;
	अचिन्हित दीर्घ lock_flags = 0;
	अक्षर buffer[IPR_MAX_RES_PATH_LENGTH];

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = sdev->hostdata;
	अगर (res) अणु
		अगर (ipr_is_af_dasd_device(res))
			sdev->type = TYPE_RAID;
		अगर (ipr_is_af_dasd_device(res) || ipr_is_ioa_resource(res)) अणु
			sdev->scsi_level = 4;
			sdev->no_uld_attach = 1;
		पूर्ण
		अगर (ipr_is_vset_device(res)) अणु
			sdev->scsi_level = SCSI_SPC_3;
			sdev->no_report_opcodes = 1;
			blk_queue_rq_समयout(sdev->request_queue,
					     IPR_VSET_RW_TIMEOUT);
			blk_queue_max_hw_sectors(sdev->request_queue, IPR_VSET_MAX_SECTORS);
		पूर्ण
		अगर (ipr_is_gata(res) && res->sata_port)
			ap = res->sata_port->ap;
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

		अगर (ap) अणु
			scsi_change_queue_depth(sdev, IPR_MAX_CMD_PER_ATA_LUN);
			ata_sas_slave_configure(sdev, ap);
		पूर्ण

		अगर (ioa_cfg->sis64)
			sdev_prपूर्णांकk(KERN_INFO, sdev, "Resource path: %s\n",
				    ipr_क्रमmat_res_path(ioa_cfg,
				res->res_path, buffer, माप(buffer)));
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस 0;
पूर्ण

/**
 * ipr_ata_slave_alloc - Prepare क्रम commands to a SATA device
 * @sdev:	scsi device काष्ठा
 *
 * This function initializes an ATA port so that future commands
 * sent through queuecommand will work.
 *
 * Return value:
 * 	0 on success
 **/
अटल पूर्णांक ipr_ata_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ipr_sata_port *sata_port = शून्य;
	पूर्णांक rc = -ENXIO;

	ENTER;
	अगर (sdev->sdev_target)
		sata_port = sdev->sdev_target->hostdata;
	अगर (sata_port) अणु
		rc = ata_sas_port_init(sata_port->ap);
		अगर (rc == 0)
			rc = ata_sas_sync_probe(sata_port->ap);
	पूर्ण

	अगर (rc)
		ipr_slave_destroy(sdev);

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_slave_alloc - Prepare क्रम commands to a device.
 * @sdev:	scsi device काष्ठा
 *
 * This function saves a poपूर्णांकer to the resource entry
 * in the scsi device काष्ठा अगर the device exists. We
 * can then use this poपूर्णांकer in ipr_queuecommand when
 * handling new commands.
 *
 * Return value:
 * 	0 on success / -ENXIO अगर device करोes not exist
 **/
अटल पूर्णांक ipr_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *) sdev->host->hostdata;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक rc = -ENXIO;

	sdev->hostdata = शून्य;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	res = ipr_find_sdev(sdev);
	अगर (res) अणु
		res->sdev = sdev;
		res->add_to_ml = 0;
		res->in_erp = 0;
		sdev->hostdata = res;
		अगर (!ipr_is_naca_model(res))
			res->needs_sync_complete = 1;
		rc = 0;
		अगर (ipr_is_gata(res)) अणु
			spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
			वापस ipr_ata_slave_alloc(sdev);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	वापस rc;
पूर्ण

/**
 * ipr_match_lun - Match function क्रम specअगरied LUN
 * @ipr_cmd:	ipr command काष्ठा
 * @device:		device to match (sdev)
 *
 * Returns:
 *	1 अगर command matches sdev / 0 अगर command करोes not match sdev
 **/
अटल पूर्णांक ipr_match_lun(काष्ठा ipr_cmnd *ipr_cmd, व्योम *device)
अणु
	अगर (ipr_cmd->scsi_cmd && ipr_cmd->scsi_cmd->device == device)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ipr_cmnd_is_मुक्त - Check अगर a command is मुक्त or not
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Returns:
 *	true / false
 **/
अटल bool ipr_cmnd_is_मुक्त(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_cmnd *loop_cmd;

	list_क्रम_each_entry(loop_cmd, &ipr_cmd->hrrq->hrrq_मुक्त_q, queue) अणु
		अगर (loop_cmd == ipr_cmd)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ipr_match_res - Match function क्रम specअगरied resource entry
 * @ipr_cmd:	ipr command काष्ठा
 * @resource:	resource entry to match
 *
 * Returns:
 *	1 अगर command matches sdev / 0 अगर command करोes not match sdev
 **/
अटल पूर्णांक ipr_match_res(काष्ठा ipr_cmnd *ipr_cmd, व्योम *resource)
अणु
	काष्ठा ipr_resource_entry *res = resource;

	अगर (res && ipr_cmd->ioarcb.res_handle == res->res_handle)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ipr_रुको_क्रम_ops - Wait क्रम matching commands to complete
 * @ioa_cfg:	ioa config काष्ठा
 * @device:		device to match (sdev)
 * @match:		match function to use
 *
 * Returns:
 *	SUCCESS / FAILED
 **/
अटल पूर्णांक ipr_रुको_क्रम_ops(काष्ठा ipr_ioa_cfg *ioa_cfg, व्योम *device,
			    पूर्णांक (*match)(काष्ठा ipr_cmnd *, व्योम *))
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	पूर्णांक रुको, i;
	अचिन्हित दीर्घ flags;
	काष्ठा ipr_hrr_queue *hrrq;
	चिन्हित दीर्घ समयout = IPR_ABORT_TASK_TIMEOUT;
	DECLARE_COMPLETION_ONSTACK(comp);

	ENTER;
	करो अणु
		रुको = 0;

		क्रम_each_hrrq(hrrq, ioa_cfg) अणु
			spin_lock_irqsave(hrrq->lock, flags);
			क्रम (i = hrrq->min_cmd_id; i <= hrrq->max_cmd_id; i++) अणु
				ipr_cmd = ioa_cfg->ipr_cmnd_list[i];
				अगर (!ipr_cmnd_is_मुक्त(ipr_cmd)) अणु
					अगर (match(ipr_cmd, device)) अणु
						ipr_cmd->eh_comp = &comp;
						रुको++;
					पूर्ण
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(hrrq->lock, flags);
		पूर्ण

		अगर (रुको) अणु
			समयout = रुको_क्रम_completion_समयout(&comp, समयout);

			अगर (!समयout) अणु
				रुको = 0;

				क्रम_each_hrrq(hrrq, ioa_cfg) अणु
					spin_lock_irqsave(hrrq->lock, flags);
					क्रम (i = hrrq->min_cmd_id; i <= hrrq->max_cmd_id; i++) अणु
						ipr_cmd = ioa_cfg->ipr_cmnd_list[i];
						अगर (!ipr_cmnd_is_मुक्त(ipr_cmd)) अणु
							अगर (match(ipr_cmd, device)) अणु
								ipr_cmd->eh_comp = शून्य;
								रुको++;
							पूर्ण
						पूर्ण
					पूर्ण
					spin_unlock_irqrestore(hrrq->lock, flags);
				पूर्ण

				अगर (रुको)
					dev_err(&ioa_cfg->pdev->dev, "Timed out waiting for aborted commands\n");
				LEAVE;
				वापस रुको ? FAILED : SUCCESS;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (रुको);

	LEAVE;
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक ipr_eh_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक rc = SUCCESS;

	ENTER;
	ioa_cfg = (काष्ठा ipr_ioa_cfg *) cmd->device->host->hostdata;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	अगर (!ioa_cfg->in_reset_reload && !ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead) अणु
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_ABBREV);
		dev_err(&ioa_cfg->pdev->dev,
			"Adapter being reset as a result of error recovery.\n");

		अगर (WAIT_FOR_DUMP == ioa_cfg->sdt_state)
			ioa_cfg->sdt_state = GET_DUMP;
	पूर्ण

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	/* If we got hit with a host reset जबतक we were alपढ़ोy resetting
	 the adapter क्रम some reason, and the reset failed. */
	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead) अणु
		ipr_trace;
		rc = FAILED;
	पूर्ण

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_device_reset - Reset the device
 * @ioa_cfg:	ioa config काष्ठा
 * @res:		resource entry काष्ठा
 *
 * This function issues a device reset to the affected device.
 * If the device is a SCSI device, a LUN reset will be sent
 * to the device first. If that करोes not work, a target reset
 * will be sent. If the device is a SATA device, a PHY reset will
 * be sent.
 *
 * Return value:
 *	0 on success / non-zero on failure
 **/
अटल पूर्णांक ipr_device_reset(काष्ठा ipr_ioa_cfg *ioa_cfg,
			    काष्ठा ipr_resource_entry *res)
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioarcb *ioarcb;
	काष्ठा ipr_cmd_pkt *cmd_pkt;
	काष्ठा ipr_ioarcb_ata_regs *regs;
	u32 ioasc;

	ENTER;
	ipr_cmd = ipr_get_मुक्त_ipr_cmnd(ioa_cfg);
	ioarcb = &ipr_cmd->ioarcb;
	cmd_pkt = &ioarcb->cmd_pkt;

	अगर (ipr_cmd->ioa_cfg->sis64) अणु
		regs = &ipr_cmd->i.ata_ioadl.regs;
		ioarcb->add_cmd_parms_offset = cpu_to_be16(माप(*ioarcb));
	पूर्ण अन्यथा
		regs = &ioarcb->u.add_data.u.regs;

	ioarcb->res_handle = res->res_handle;
	cmd_pkt->request_type = IPR_RQTYPE_IOACMD;
	cmd_pkt->cdb[0] = IPR_RESET_DEVICE;
	अगर (ipr_is_gata(res)) अणु
		cmd_pkt->cdb[2] = IPR_ATA_PHY_RESET;
		ioarcb->add_cmd_parms_len = cpu_to_be16(माप(regs->flags));
		regs->flags |= IPR_ATA_FLAG_STATUS_ON_GOOD_COMPLETION;
	पूर्ण

	ipr_send_blocking_cmd(ipr_cmd, ipr_समयout, IPR_DEVICE_RESET_TIMEOUT);
	ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
	अगर (ipr_is_gata(res) && res->sata_port && ioasc != IPR_IOASC_IOA_WAS_RESET) अणु
		अगर (ipr_cmd->ioa_cfg->sis64)
			स_नकल(&res->sata_port->ioasa, &ipr_cmd->s.ioasa64.u.gata,
			       माप(काष्ठा ipr_ioasa_gata));
		अन्यथा
			स_नकल(&res->sata_port->ioasa, &ipr_cmd->s.ioasa.u.gata,
			       माप(काष्ठा ipr_ioasa_gata));
	पूर्ण

	LEAVE;
	वापस IPR_IOASC_SENSE_KEY(ioasc) ? -EIO : 0;
पूर्ण

/**
 * ipr_sata_reset - Reset the SATA port
 * @link:	SATA link to reset
 * @classes:	class of the attached device
 * @deadline:	unused
 *
 * This function issues a SATA phy reset to the affected ATA link.
 *
 * Return value:
 *	0 on success / non-zero on failure
 **/
अटल पूर्णांक ipr_sata_reset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes,
				अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ipr_sata_port *sata_port = link->ap->निजी_data;
	काष्ठा ipr_ioa_cfg *ioa_cfg = sata_port->ioa_cfg;
	काष्ठा ipr_resource_entry *res;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक rc = -ENXIO, ret;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	जबतक (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	पूर्ण

	res = sata_port->res;
	अगर (res) अणु
		rc = ipr_device_reset(ioa_cfg, res);
		*classes = res->ata_class;
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

		ret = ipr_रुको_क्रम_ops(ioa_cfg, res, ipr_match_res);
		अगर (ret != SUCCESS) अणु
			spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
			ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_ABBREV);
			spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

			रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		पूर्ण
	पूर्ण अन्यथा
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	LEAVE;
	वापस rc;
पूर्ण

/**
 * __ipr_eh_dev_reset - Reset the device
 * @scsi_cmd:	scsi command काष्ठा
 *
 * This function issues a device reset to the affected device.
 * A LUN reset will be sent to the device first. If that करोes
 * not work, a target reset will be sent.
 *
 * Return value:
 *	SUCCESS / FAILED
 **/
अटल पूर्णांक __ipr_eh_dev_reset(काष्ठा scsi_cmnd *scsi_cmd)
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा ipr_resource_entry *res;
	काष्ठा ata_port *ap;
	पूर्णांक rc = 0, i;
	काष्ठा ipr_hrr_queue *hrrq;

	ENTER;
	ioa_cfg = (काष्ठा ipr_ioa_cfg *) scsi_cmd->device->host->hostdata;
	res = scsi_cmd->device->hostdata;

	/*
	 * If we are currently going through reset/reload, वापस failed. This will क्रमce the
	 * mid-layer to call ipr_eh_host_reset, which will then go to sleep and रुको क्रम the
	 * reset to complete
	 */
	अगर (ioa_cfg->in_reset_reload)
		वापस FAILED;
	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead)
		वापस FAILED;

	क्रम_each_hrrq(hrrq, ioa_cfg) अणु
		spin_lock(&hrrq->_lock);
		क्रम (i = hrrq->min_cmd_id; i <= hrrq->max_cmd_id; i++) अणु
			ipr_cmd = ioa_cfg->ipr_cmnd_list[i];

			अगर (ipr_cmd->ioarcb.res_handle == res->res_handle) अणु
				अगर (!ipr_cmd->qc)
					जारी;
				अगर (ipr_cmnd_is_मुक्त(ipr_cmd))
					जारी;

				ipr_cmd->करोne = ipr_sata_eh_करोne;
				अगर (!(ipr_cmd->qc->flags & ATA_QCFLAG_FAILED)) अणु
					ipr_cmd->qc->err_mask |= AC_ERR_TIMEOUT;
					ipr_cmd->qc->flags |= ATA_QCFLAG_FAILED;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock(&hrrq->_lock);
	पूर्ण
	res->resetting_device = 1;
	scmd_prपूर्णांकk(KERN_ERR, scsi_cmd, "Resetting device\n");

	अगर (ipr_is_gata(res) && res->sata_port) अणु
		ap = res->sata_port->ap;
		spin_unlock_irq(scsi_cmd->device->host->host_lock);
		ata_std_error_handler(ap);
		spin_lock_irq(scsi_cmd->device->host->host_lock);
	पूर्ण अन्यथा
		rc = ipr_device_reset(ioa_cfg, res);
	res->resetting_device = 0;
	res->reset_occurred = 1;

	LEAVE;
	वापस rc ? FAILED : SUCCESS;
पूर्ण

अटल पूर्णांक ipr_eh_dev_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक rc;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा ipr_resource_entry *res;

	ioa_cfg = (काष्ठा ipr_ioa_cfg *) cmd->device->host->hostdata;
	res = cmd->device->hostdata;

	अगर (!res)
		वापस FAILED;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = __ipr_eh_dev_reset(cmd);
	spin_unlock_irq(cmd->device->host->host_lock);

	अगर (rc == SUCCESS) अणु
		अगर (ipr_is_gata(res) && res->sata_port)
			rc = ipr_रुको_क्रम_ops(ioa_cfg, res, ipr_match_res);
		अन्यथा
			rc = ipr_रुको_क्रम_ops(ioa_cfg, cmd->device, ipr_match_lun);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ipr_bus_reset_करोne - Op करोne function क्रम bus reset.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is the op करोne function क्रम a bus reset
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_bus_reset_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_resource_entry *res;

	ENTER;
	अगर (!ioa_cfg->sis64)
		list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
			अगर (res->res_handle == ipr_cmd->ioarcb.res_handle) अणु
				scsi_report_bus_reset(ioa_cfg->host, res->bus);
				अवरोध;
			पूर्ण
		पूर्ण

	/*
	 * If पात has not completed, indicate the reset has, अन्यथा call the
	 * पात's करोne function to wake the sleeping eh thपढ़ो
	 */
	अगर (ipr_cmd->sibling->sibling)
		ipr_cmd->sibling->sibling = शून्य;
	अन्यथा
		ipr_cmd->sibling->करोne(ipr_cmd->sibling);

	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
	LEAVE;
पूर्ण

/**
 * ipr_पात_समयout - An पात task has समयd out
 * @t: Timer context used to fetch ipr command काष्ठा
 *
 * This function handles when an पात task बार out. If this
 * happens we issue a bus reset since we have resources tied
 * up that must be मुक्तd beक्रमe वापसing to the midlayer.
 *
 * Return value:
 *	none
 **/
अटल व्योम ipr_पात_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ipr_cmnd *ipr_cmd = from_समयr(ipr_cmd, t, समयr);
	काष्ठा ipr_cmnd *reset_cmd;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_cmd_pkt *cmd_pkt;
	अचिन्हित दीर्घ lock_flags = 0;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	अगर (ipr_cmd->completion.करोne || ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस;
	पूर्ण

	sdev_prपूर्णांकk(KERN_ERR, ipr_cmd->u.sdev, "Abort timed out. Resetting bus.\n");
	reset_cmd = ipr_get_मुक्त_ipr_cmnd(ioa_cfg);
	ipr_cmd->sibling = reset_cmd;
	reset_cmd->sibling = ipr_cmd;
	reset_cmd->ioarcb.res_handle = ipr_cmd->ioarcb.res_handle;
	cmd_pkt = &reset_cmd->ioarcb.cmd_pkt;
	cmd_pkt->request_type = IPR_RQTYPE_IOACMD;
	cmd_pkt->cdb[0] = IPR_RESET_DEVICE;
	cmd_pkt->cdb[2] = IPR_RESET_TYPE_SELECT | IPR_BUS_RESET;

	ipr_करो_req(reset_cmd, ipr_bus_reset_करोne, ipr_समयout, IPR_DEVICE_RESET_TIMEOUT);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
पूर्ण

/**
 * ipr_cancel_op - Cancel specअगरied op
 * @scsi_cmd:	scsi command काष्ठा
 *
 * This function cancels specअगरied op.
 *
 * Return value:
 *	SUCCESS / FAILED
 **/
अटल पूर्णांक ipr_cancel_op(काष्ठा scsi_cmnd *scsi_cmd)
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा ipr_resource_entry *res;
	काष्ठा ipr_cmd_pkt *cmd_pkt;
	u32 ioasc;
	पूर्णांक i, op_found = 0;
	काष्ठा ipr_hrr_queue *hrrq;

	ENTER;
	ioa_cfg = (काष्ठा ipr_ioa_cfg *)scsi_cmd->device->host->hostdata;
	res = scsi_cmd->device->hostdata;

	/* If we are currently going through reset/reload, वापस failed.
	 * This will क्रमce the mid-layer to call ipr_eh_host_reset,
	 * which will then go to sleep and रुको क्रम the reset to complete
	 */
	अगर (ioa_cfg->in_reset_reload ||
	    ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead)
		वापस FAILED;
	अगर (!res)
		वापस FAILED;

	/*
	 * If we are पातing a समयd out op, chances are that the समयout was caused
	 * by a still not detected EEH error. In such हालs, पढ़ोing a रेजिस्टर will
	 * trigger the EEH recovery infraकाष्ठाure.
	 */
	पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg);

	अगर (!ipr_is_gscsi(res))
		वापस FAILED;

	क्रम_each_hrrq(hrrq, ioa_cfg) अणु
		spin_lock(&hrrq->_lock);
		क्रम (i = hrrq->min_cmd_id; i <= hrrq->max_cmd_id; i++) अणु
			अगर (ioa_cfg->ipr_cmnd_list[i]->scsi_cmd == scsi_cmd) अणु
				अगर (!ipr_cmnd_is_मुक्त(ioa_cfg->ipr_cmnd_list[i])) अणु
					op_found = 1;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock(&hrrq->_lock);
	पूर्ण

	अगर (!op_found)
		वापस SUCCESS;

	ipr_cmd = ipr_get_मुक्त_ipr_cmnd(ioa_cfg);
	ipr_cmd->ioarcb.res_handle = res->res_handle;
	cmd_pkt = &ipr_cmd->ioarcb.cmd_pkt;
	cmd_pkt->request_type = IPR_RQTYPE_IOACMD;
	cmd_pkt->cdb[0] = IPR_CANCEL_ALL_REQUESTS;
	ipr_cmd->u.sdev = scsi_cmd->device;

	scmd_prपूर्णांकk(KERN_ERR, scsi_cmd, "Aborting command: %02X\n",
		    scsi_cmd->cmnd[0]);
	ipr_send_blocking_cmd(ipr_cmd, ipr_पात_समयout, IPR_CANCEL_ALL_TIMEOUT);
	ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	/*
	 * If the पात task समयd out and we sent a bus reset, we will get
	 * one the following responses to the पात
	 */
	अगर (ioasc == IPR_IOASC_BUS_WAS_RESET || ioasc == IPR_IOASC_SYNC_REQUIRED) अणु
		ioasc = 0;
		ipr_trace;
	पूर्ण

	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
	अगर (!ipr_is_naca_model(res))
		res->needs_sync_complete = 1;

	LEAVE;
	वापस IPR_IOASC_SENSE_KEY(ioasc) ? FAILED : SUCCESS;
पूर्ण

/**
 * ipr_scan_finished - Report whether scan is करोne
 * @shost:           scsi host काष्ठा
 * @elapsed_समय:    elapsed समय
 *
 * Return value:
 *	0 अगर scan in progress / 1 अगर scan is complete
 **/
अटल पूर्णांक ipr_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ elapsed_समय)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *) shost->hostdata;
	पूर्णांक rc = 0;

	spin_lock_irqsave(shost->host_lock, lock_flags);
	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead || ioa_cfg->scan_करोne)
		rc = 1;
	अगर ((elapsed_समय/HZ) > (ioa_cfg->transop_समयout * 2))
		rc = 1;
	spin_unlock_irqrestore(shost->host_lock, lock_flags);
	वापस rc;
पूर्ण

/**
 * ipr_eh_पात - Reset the host adapter
 * @scsi_cmd:	scsi command काष्ठा
 *
 * Return value:
 * 	SUCCESS / FAILED
 **/
अटल पूर्णांक ipr_eh_पात(काष्ठा scsi_cmnd *scsi_cmd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	काष्ठा ipr_ioa_cfg *ioa_cfg;

	ENTER;

	ioa_cfg = (काष्ठा ipr_ioa_cfg *) scsi_cmd->device->host->hostdata;

	spin_lock_irqsave(scsi_cmd->device->host->host_lock, flags);
	rc = ipr_cancel_op(scsi_cmd);
	spin_unlock_irqrestore(scsi_cmd->device->host->host_lock, flags);

	अगर (rc == SUCCESS)
		rc = ipr_रुको_क्रम_ops(ioa_cfg, scsi_cmd->device, ipr_match_lun);
	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_handle_other_पूर्णांकerrupt - Handle "other" पूर्णांकerrupts
 * @ioa_cfg:	ioa config काष्ठा
 * @पूर्णांक_reg:	पूर्णांकerrupt रेजिस्टर
 *
 * Return value:
 * 	IRQ_NONE / IRQ_HANDLED
 **/
अटल irqवापस_t ipr_handle_other_पूर्णांकerrupt(काष्ठा ipr_ioa_cfg *ioa_cfg,
					      u32 पूर्णांक_reg)
अणु
	irqवापस_t rc = IRQ_HANDLED;
	u32 पूर्णांक_mask_reg;

	पूर्णांक_mask_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg32);
	पूर्णांक_reg &= ~पूर्णांक_mask_reg;

	/* If an पूर्णांकerrupt on the adapter did not occur, ignore it.
	 * Or in the हाल of SIS 64, check क्रम a stage change पूर्णांकerrupt.
	 */
	अगर ((पूर्णांक_reg & IPR_PCII_OPER_INTERRUPTS) == 0) अणु
		अगर (ioa_cfg->sis64) अणु
			पूर्णांक_mask_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg);
			पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg) & ~पूर्णांक_mask_reg;
			अगर (पूर्णांक_reg & IPR_PCII_IPL_STAGE_CHANGE) अणु

				/* clear stage change */
				ग_लिखोl(IPR_PCII_IPL_STAGE_CHANGE, ioa_cfg->regs.clr_पूर्णांकerrupt_reg);
				पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg) & ~पूर्णांक_mask_reg;
				list_del(&ioa_cfg->reset_cmd->queue);
				del_समयr(&ioa_cfg->reset_cmd->समयr);
				ipr_reset_ioa_job(ioa_cfg->reset_cmd);
				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण

		वापस IRQ_NONE;
	पूर्ण

	अगर (पूर्णांक_reg & IPR_PCII_IOA_TRANS_TO_OPER) अणु
		/* Mask the पूर्णांकerrupt */
		ग_लिखोl(IPR_PCII_IOA_TRANS_TO_OPER, ioa_cfg->regs.set_पूर्णांकerrupt_mask_reg);
		पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg);

		list_del(&ioa_cfg->reset_cmd->queue);
		del_समयr(&ioa_cfg->reset_cmd->समयr);
		ipr_reset_ioa_job(ioa_cfg->reset_cmd);
	पूर्ण अन्यथा अगर ((पूर्णांक_reg & IPR_PCII_HRRQ_UPDATED) == पूर्णांक_reg) अणु
		अगर (ioa_cfg->clear_isr) अणु
			अगर (ipr_debug && prपूर्णांकk_ratelimit())
				dev_err(&ioa_cfg->pdev->dev,
					"Spurious interrupt detected. 0x%08X\n", पूर्णांक_reg);
			ग_लिखोl(IPR_PCII_HRRQ_UPDATED, ioa_cfg->regs.clr_पूर्णांकerrupt_reg32);
			पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg32);
			वापस IRQ_NONE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (पूर्णांक_reg & IPR_PCII_IOA_UNIT_CHECKED)
			ioa_cfg->ioa_unit_checked = 1;
		अन्यथा अगर (पूर्णांक_reg & IPR_PCII_NO_HOST_RRQ)
			dev_err(&ioa_cfg->pdev->dev,
				"No Host RRQ. 0x%08X\n", पूर्णांक_reg);
		अन्यथा
			dev_err(&ioa_cfg->pdev->dev,
				"Permanent IOA failure. 0x%08X\n", पूर्णांक_reg);

		अगर (WAIT_FOR_DUMP == ioa_cfg->sdt_state)
			ioa_cfg->sdt_state = GET_DUMP;

		ipr_mask_and_clear_पूर्णांकerrupts(ioa_cfg, ~0);
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ipr_isr_eh - Interrupt service routine error handler
 * @ioa_cfg:	ioa config काष्ठा
 * @msg:	message to log
 * @number:	various meanings depending on the caller/message
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_isr_eh(काष्ठा ipr_ioa_cfg *ioa_cfg, अक्षर *msg, u16 number)
अणु
	ioa_cfg->errors_logged++;
	dev_err(&ioa_cfg->pdev->dev, "%s %d\n", msg, number);

	अगर (WAIT_FOR_DUMP == ioa_cfg->sdt_state)
		ioa_cfg->sdt_state = GET_DUMP;

	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
पूर्ण

अटल पूर्णांक ipr_process_hrrq(काष्ठा ipr_hrr_queue *hrr_queue, पूर्णांक budget,
						काष्ठा list_head *करोneq)
अणु
	u32 ioasc;
	u16 cmd_index;
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioa_cfg *ioa_cfg = hrr_queue->ioa_cfg;
	पूर्णांक num_hrrq = 0;

	/* If पूर्णांकerrupts are disabled, ignore the पूर्णांकerrupt */
	अगर (!hrr_queue->allow_पूर्णांकerrupts)
		वापस 0;

	जबतक ((be32_to_cpu(*hrr_queue->hrrq_curr) & IPR_HRRQ_TOGGLE_BIT) ==
	       hrr_queue->toggle_bit) अणु

		cmd_index = (be32_to_cpu(*hrr_queue->hrrq_curr) &
			     IPR_HRRQ_REQ_RESP_HANDLE_MASK) >>
			     IPR_HRRQ_REQ_RESP_HANDLE_SHIFT;

		अगर (unlikely(cmd_index > hrr_queue->max_cmd_id ||
			     cmd_index < hrr_queue->min_cmd_id)) अणु
			ipr_isr_eh(ioa_cfg,
				"Invalid response handle from IOA: ",
				cmd_index);
			अवरोध;
		पूर्ण

		ipr_cmd = ioa_cfg->ipr_cmnd_list[cmd_index];
		ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

		ipr_trc_hook(ipr_cmd, IPR_TRACE_FINISH, ioasc);

		list_move_tail(&ipr_cmd->queue, करोneq);

		अगर (hrr_queue->hrrq_curr < hrr_queue->hrrq_end) अणु
			hrr_queue->hrrq_curr++;
		पूर्ण अन्यथा अणु
			hrr_queue->hrrq_curr = hrr_queue->hrrq_start;
			hrr_queue->toggle_bit ^= 1u;
		पूर्ण
		num_hrrq++;
		अगर (budget > 0 && num_hrrq >= budget)
			अवरोध;
	पूर्ण

	वापस num_hrrq;
पूर्ण

अटल पूर्णांक ipr_iopoll(काष्ठा irq_poll *iop, पूर्णांक budget)
अणु
	काष्ठा ipr_hrr_queue *hrrq;
	काष्ठा ipr_cmnd *ipr_cmd, *temp;
	अचिन्हित दीर्घ hrrq_flags;
	पूर्णांक completed_ops;
	LIST_HEAD(करोneq);

	hrrq = container_of(iop, काष्ठा ipr_hrr_queue, iopoll);

	spin_lock_irqsave(hrrq->lock, hrrq_flags);
	completed_ops = ipr_process_hrrq(hrrq, budget, &करोneq);

	अगर (completed_ops < budget)
		irq_poll_complete(iop);
	spin_unlock_irqrestore(hrrq->lock, hrrq_flags);

	list_क्रम_each_entry_safe(ipr_cmd, temp, &करोneq, queue) अणु
		list_del(&ipr_cmd->queue);
		del_समयr(&ipr_cmd->समयr);
		ipr_cmd->fast_करोne(ipr_cmd);
	पूर्ण

	वापस completed_ops;
पूर्ण

/**
 * ipr_isr - Interrupt service routine
 * @irq:	irq number
 * @devp:	poपूर्णांकer to ioa config काष्ठा
 *
 * Return value:
 * 	IRQ_NONE / IRQ_HANDLED
 **/
अटल irqवापस_t ipr_isr(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा ipr_hrr_queue *hrrq = (काष्ठा ipr_hrr_queue *)devp;
	काष्ठा ipr_ioa_cfg *ioa_cfg = hrrq->ioa_cfg;
	अचिन्हित दीर्घ hrrq_flags = 0;
	u32 पूर्णांक_reg = 0;
	पूर्णांक num_hrrq = 0;
	पूर्णांक irq_none = 0;
	काष्ठा ipr_cmnd *ipr_cmd, *temp;
	irqवापस_t rc = IRQ_NONE;
	LIST_HEAD(करोneq);

	spin_lock_irqsave(hrrq->lock, hrrq_flags);
	/* If पूर्णांकerrupts are disabled, ignore the पूर्णांकerrupt */
	अगर (!hrrq->allow_पूर्णांकerrupts) अणु
		spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
		वापस IRQ_NONE;
	पूर्ण

	जबतक (1) अणु
		अगर (ipr_process_hrrq(hrrq, -1, &करोneq)) अणु
			rc =  IRQ_HANDLED;

			अगर (!ioa_cfg->clear_isr)
				अवरोध;

			/* Clear the PCI पूर्णांकerrupt */
			num_hrrq = 0;
			करो अणु
				ग_लिखोl(IPR_PCII_HRRQ_UPDATED,
				     ioa_cfg->regs.clr_पूर्णांकerrupt_reg32);
				पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg32);
			पूर्ण जबतक (पूर्णांक_reg & IPR_PCII_HRRQ_UPDATED &&
				num_hrrq++ < IPR_MAX_HRRQ_RETRIES);

		पूर्ण अन्यथा अगर (rc == IRQ_NONE && irq_none == 0) अणु
			पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg32);
			irq_none++;
		पूर्ण अन्यथा अगर (num_hrrq == IPR_MAX_HRRQ_RETRIES &&
			   पूर्णांक_reg & IPR_PCII_HRRQ_UPDATED) अणु
			ipr_isr_eh(ioa_cfg,
				"Error clearing HRRQ: ", num_hrrq);
			rc = IRQ_HANDLED;
			अवरोध;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	अगर (unlikely(rc == IRQ_NONE))
		rc = ipr_handle_other_पूर्णांकerrupt(ioa_cfg, पूर्णांक_reg);

	spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
	list_क्रम_each_entry_safe(ipr_cmd, temp, &करोneq, queue) अणु
		list_del(&ipr_cmd->queue);
		del_समयr(&ipr_cmd->समयr);
		ipr_cmd->fast_करोne(ipr_cmd);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ipr_isr_mhrrq - Interrupt service routine
 * @irq:	irq number
 * @devp:	poपूर्णांकer to ioa config काष्ठा
 *
 * Return value:
 *	IRQ_NONE / IRQ_HANDLED
 **/
अटल irqवापस_t ipr_isr_mhrrq(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा ipr_hrr_queue *hrrq = (काष्ठा ipr_hrr_queue *)devp;
	काष्ठा ipr_ioa_cfg *ioa_cfg = hrrq->ioa_cfg;
	अचिन्हित दीर्घ hrrq_flags = 0;
	काष्ठा ipr_cmnd *ipr_cmd, *temp;
	irqवापस_t rc = IRQ_NONE;
	LIST_HEAD(करोneq);

	spin_lock_irqsave(hrrq->lock, hrrq_flags);

	/* If पूर्णांकerrupts are disabled, ignore the पूर्णांकerrupt */
	अगर (!hrrq->allow_पूर्णांकerrupts) अणु
		spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर (ioa_cfg->iopoll_weight && ioa_cfg->sis64 && ioa_cfg->nvectors > 1) अणु
		अगर ((be32_to_cpu(*hrrq->hrrq_curr) & IPR_HRRQ_TOGGLE_BIT) ==
		       hrrq->toggle_bit) अणु
			irq_poll_sched(&hrrq->iopoll);
			spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((be32_to_cpu(*hrrq->hrrq_curr) & IPR_HRRQ_TOGGLE_BIT) ==
			hrrq->toggle_bit)

			अगर (ipr_process_hrrq(hrrq, -1, &करोneq))
				rc =  IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(hrrq->lock, hrrq_flags);

	list_क्रम_each_entry_safe(ipr_cmd, temp, &करोneq, queue) अणु
		list_del(&ipr_cmd->queue);
		del_समयr(&ipr_cmd->समयr);
		ipr_cmd->fast_करोne(ipr_cmd);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ipr_build_ioadl64 - Build a scatter/gather list and map the buffer
 * @ioa_cfg:	ioa config काष्ठा
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 * 	0 on success / -1 on failure
 **/
अटल पूर्णांक ipr_build_ioadl64(काष्ठा ipr_ioa_cfg *ioa_cfg,
			     काष्ठा ipr_cmnd *ipr_cmd)
अणु
	पूर्णांक i, nseg;
	काष्ठा scatterlist *sg;
	u32 length;
	u32 ioadl_flags = 0;
	काष्ठा scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioadl64_desc *ioadl64 = ipr_cmd->i.ioadl64;

	length = scsi_bufflen(scsi_cmd);
	अगर (!length)
		वापस 0;

	nseg = scsi_dma_map(scsi_cmd);
	अगर (nseg < 0) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_err(&ioa_cfg->pdev->dev, "scsi_dma_map failed!\n");
		वापस -1;
	पूर्ण

	ipr_cmd->dma_use_sg = nseg;

	ioarcb->data_transfer_length = cpu_to_be32(length);
	ioarcb->ioadl_len =
		cpu_to_be32(माप(काष्ठा ipr_ioadl64_desc) * ipr_cmd->dma_use_sg);

	अगर (scsi_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		ioadl_flags = IPR_IOADL_FLAGS_WRITE;
		ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
	पूर्ण अन्यथा अगर (scsi_cmd->sc_data_direction == DMA_FROM_DEVICE)
		ioadl_flags = IPR_IOADL_FLAGS_READ;

	scsi_क्रम_each_sg(scsi_cmd, sg, ipr_cmd->dma_use_sg, i) अणु
		ioadl64[i].flags = cpu_to_be32(ioadl_flags);
		ioadl64[i].data_len = cpu_to_be32(sg_dma_len(sg));
		ioadl64[i].address = cpu_to_be64(sg_dma_address(sg));
	पूर्ण

	ioadl64[i-1].flags |= cpu_to_be32(IPR_IOADL_FLAGS_LAST);
	वापस 0;
पूर्ण

/**
 * ipr_build_ioadl - Build a scatter/gather list and map the buffer
 * @ioa_cfg:	ioa config काष्ठा
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 * 	0 on success / -1 on failure
 **/
अटल पूर्णांक ipr_build_ioadl(काष्ठा ipr_ioa_cfg *ioa_cfg,
			   काष्ठा ipr_cmnd *ipr_cmd)
अणु
	पूर्णांक i, nseg;
	काष्ठा scatterlist *sg;
	u32 length;
	u32 ioadl_flags = 0;
	काष्ठा scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioadl_desc *ioadl = ipr_cmd->i.ioadl;

	length = scsi_bufflen(scsi_cmd);
	अगर (!length)
		वापस 0;

	nseg = scsi_dma_map(scsi_cmd);
	अगर (nseg < 0) अणु
		dev_err(&ioa_cfg->pdev->dev, "scsi_dma_map failed!\n");
		वापस -1;
	पूर्ण

	ipr_cmd->dma_use_sg = nseg;

	अगर (scsi_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		ioadl_flags = IPR_IOADL_FLAGS_WRITE;
		ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
		ioarcb->data_transfer_length = cpu_to_be32(length);
		ioarcb->ioadl_len =
			cpu_to_be32(माप(काष्ठा ipr_ioadl_desc) * ipr_cmd->dma_use_sg);
	पूर्ण अन्यथा अगर (scsi_cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		ioadl_flags = IPR_IOADL_FLAGS_READ;
		ioarcb->पढ़ो_data_transfer_length = cpu_to_be32(length);
		ioarcb->पढ़ो_ioadl_len =
			cpu_to_be32(माप(काष्ठा ipr_ioadl_desc) * ipr_cmd->dma_use_sg);
	पूर्ण

	अगर (ipr_cmd->dma_use_sg <= ARRAY_SIZE(ioarcb->u.add_data.u.ioadl)) अणु
		ioadl = ioarcb->u.add_data.u.ioadl;
		ioarcb->ग_लिखो_ioadl_addr = cpu_to_be32((ipr_cmd->dma_addr) +
				    दुरत्व(काष्ठा ipr_ioarcb, u.add_data));
		ioarcb->पढ़ो_ioadl_addr = ioarcb->ग_लिखो_ioadl_addr;
	पूर्ण

	scsi_क्रम_each_sg(scsi_cmd, sg, ipr_cmd->dma_use_sg, i) अणु
		ioadl[i].flags_and_data_len =
			cpu_to_be32(ioadl_flags | sg_dma_len(sg));
		ioadl[i].address = cpu_to_be32(sg_dma_address(sg));
	पूर्ण

	ioadl[i-1].flags_and_data_len |= cpu_to_be32(IPR_IOADL_FLAGS_LAST);
	वापस 0;
पूर्ण

/**
 * __ipr_erp_करोne - Process completion of ERP क्रम a device
 * @ipr_cmd:		ipr command काष्ठा
 *
 * This function copies the sense buffer पूर्णांकo the scsi_cmd
 * काष्ठा and pushes the scsi_करोne function.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम __ipr_erp_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	काष्ठा ipr_resource_entry *res = scsi_cmd->device->hostdata;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	अगर (IPR_IOASC_SENSE_KEY(ioasc) > 0) अणु
		scsi_cmd->result |= (DID_ERROR << 16);
		scmd_prपूर्णांकk(KERN_ERR, scsi_cmd,
			    "Request Sense failed with IOASC: 0x%08X\n", ioasc);
	पूर्ण अन्यथा अणु
		स_नकल(scsi_cmd->sense_buffer, ipr_cmd->sense_buffer,
		       SCSI_SENSE_BUFFERSIZE);
	पूर्ण

	अगर (res) अणु
		अगर (!ipr_is_naca_model(res))
			res->needs_sync_complete = 1;
		res->in_erp = 0;
	पूर्ण
	scsi_dma_unmap(ipr_cmd->scsi_cmd);
	scsi_cmd->scsi_करोne(scsi_cmd);
	अगर (ipr_cmd->eh_comp)
		complete(ipr_cmd->eh_comp);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
पूर्ण

/**
 * ipr_erp_करोne - Process completion of ERP क्रम a device
 * @ipr_cmd:		ipr command काष्ठा
 *
 * This function copies the sense buffer पूर्णांकo the scsi_cmd
 * काष्ठा and pushes the scsi_करोne function.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_erp_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_hrr_queue *hrrq = ipr_cmd->hrrq;
	अचिन्हित दीर्घ hrrq_flags;

	spin_lock_irqsave(&hrrq->_lock, hrrq_flags);
	__ipr_erp_करोne(ipr_cmd);
	spin_unlock_irqrestore(&hrrq->_lock, hrrq_flags);
पूर्ण

/**
 * ipr_reinit_ipr_cmnd_क्रम_erp - Re-initialize a cmnd block to be used क्रम ERP
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_reinit_ipr_cmnd_क्रम_erp(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	dma_addr_t dma_addr = ipr_cmd->dma_addr;

	स_रखो(&ioarcb->cmd_pkt, 0, माप(काष्ठा ipr_cmd_pkt));
	ioarcb->data_transfer_length = 0;
	ioarcb->पढ़ो_data_transfer_length = 0;
	ioarcb->ioadl_len = 0;
	ioarcb->पढ़ो_ioadl_len = 0;
	ioasa->hdr.ioasc = 0;
	ioasa->hdr.residual_data_len = 0;

	अगर (ipr_cmd->ioa_cfg->sis64)
		ioarcb->u.sis64_addr_data.data_ioadl_addr =
			cpu_to_be64(dma_addr + दुरत्व(काष्ठा ipr_cmnd, i.ioadl64));
	अन्यथा अणु
		ioarcb->ग_लिखो_ioadl_addr =
			cpu_to_be32(dma_addr + दुरत्व(काष्ठा ipr_cmnd, i.ioadl));
		ioarcb->पढ़ो_ioadl_addr = ioarcb->ग_लिखो_ioadl_addr;
	पूर्ण
पूर्ण

/**
 * __ipr_erp_request_sense - Send request sense to a device
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a request sense to a device as a result
 * of a check condition.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम __ipr_erp_request_sense(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_cmd_pkt *cmd_pkt = &ipr_cmd->ioarcb.cmd_pkt;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	अगर (IPR_IOASC_SENSE_KEY(ioasc) > 0) अणु
		__ipr_erp_करोne(ipr_cmd);
		वापस;
	पूर्ण

	ipr_reinit_ipr_cmnd_क्रम_erp(ipr_cmd);

	cmd_pkt->request_type = IPR_RQTYPE_SCSICDB;
	cmd_pkt->cdb[0] = REQUEST_SENSE;
	cmd_pkt->cdb[4] = SCSI_SENSE_BUFFERSIZE;
	cmd_pkt->flags_hi |= IPR_FLAGS_HI_SYNC_OVERRIDE;
	cmd_pkt->flags_hi |= IPR_FLAGS_HI_NO_ULEN_CHK;
	cmd_pkt->समयout = cpu_to_be16(IPR_REQUEST_SENSE_TIMEOUT / HZ);

	ipr_init_ioadl(ipr_cmd, ipr_cmd->sense_buffer_dma,
		       SCSI_SENSE_BUFFERSIZE, IPR_IOADL_FLAGS_READ_LAST);

	ipr_करो_req(ipr_cmd, ipr_erp_करोne, ipr_समयout,
		   IPR_REQUEST_SENSE_TIMEOUT * 2);
पूर्ण

/**
 * ipr_erp_request_sense - Send request sense to a device
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a request sense to a device as a result
 * of a check condition.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_erp_request_sense(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_hrr_queue *hrrq = ipr_cmd->hrrq;
	अचिन्हित दीर्घ hrrq_flags;

	spin_lock_irqsave(&hrrq->_lock, hrrq_flags);
	__ipr_erp_request_sense(ipr_cmd);
	spin_unlock_irqrestore(&hrrq->_lock, hrrq_flags);
पूर्ण

/**
 * ipr_erp_cancel_all - Send cancel all to a device
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a cancel all to a device to clear the
 * queue. If we are running TCQ on the device, QERR is set to 1,
 * which means all outstanding ops have been dropped on the न्यूनमान.
 * Cancel all will वापस them to us.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_erp_cancel_all(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	काष्ठा ipr_resource_entry *res = scsi_cmd->device->hostdata;
	काष्ठा ipr_cmd_pkt *cmd_pkt;

	res->in_erp = 1;

	ipr_reinit_ipr_cmnd_क्रम_erp(ipr_cmd);

	अगर (!scsi_cmd->device->simple_tags) अणु
		__ipr_erp_request_sense(ipr_cmd);
		वापस;
	पूर्ण

	cmd_pkt = &ipr_cmd->ioarcb.cmd_pkt;
	cmd_pkt->request_type = IPR_RQTYPE_IOACMD;
	cmd_pkt->cdb[0] = IPR_CANCEL_ALL_REQUESTS;

	ipr_करो_req(ipr_cmd, ipr_erp_request_sense, ipr_समयout,
		   IPR_CANCEL_ALL_TIMEOUT);
पूर्ण

/**
 * ipr_dump_ioasa - Dump contents of IOASA
 * @ioa_cfg:	ioa config काष्ठा
 * @ipr_cmd:	ipr command काष्ठा
 * @res:		resource entry काष्ठा
 *
 * This function is invoked by the पूर्णांकerrupt handler when ops
 * fail. It will log the IOASA अगर appropriate. Only called
 * क्रम GPDD ops.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_dump_ioasa(काष्ठा ipr_ioa_cfg *ioa_cfg,
			   काष्ठा ipr_cmnd *ipr_cmd, काष्ठा ipr_resource_entry *res)
अणु
	पूर्णांक i;
	u16 data_len;
	u32 ioasc, fd_ioasc;
	काष्ठा ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	__be32 *ioasa_data = (__be32 *)ioasa;
	पूर्णांक error_index;

	ioasc = be32_to_cpu(ioasa->hdr.ioasc) & IPR_IOASC_IOASC_MASK;
	fd_ioasc = be32_to_cpu(ioasa->hdr.fd_ioasc) & IPR_IOASC_IOASC_MASK;

	अगर (0 == ioasc)
		वापस;

	अगर (ioa_cfg->log_level < IPR_DEFAULT_LOG_LEVEL)
		वापस;

	अगर (ioasc == IPR_IOASC_BUS_WAS_RESET && fd_ioasc)
		error_index = ipr_get_error(fd_ioasc);
	अन्यथा
		error_index = ipr_get_error(ioasc);

	अगर (ioa_cfg->log_level < IPR_MAX_LOG_LEVEL) अणु
		/* Don't log an error अगर the IOA alपढ़ोy logged one */
		अगर (ioasa->hdr.ilid != 0)
			वापस;

		अगर (!ipr_is_gscsi(res))
			वापस;

		अगर (ipr_error_table[error_index].log_ioasa == 0)
			वापस;
	पूर्ण

	ipr_res_err(ioa_cfg, res, "%s\n", ipr_error_table[error_index].error);

	data_len = be16_to_cpu(ioasa->hdr.ret_stat_len);
	अगर (ioa_cfg->sis64 && माप(काष्ठा ipr_ioasa64) < data_len)
		data_len = माप(काष्ठा ipr_ioasa64);
	अन्यथा अगर (!ioa_cfg->sis64 && माप(काष्ठा ipr_ioasa) < data_len)
		data_len = माप(काष्ठा ipr_ioasa);

	ipr_err("IOASA Dump:\n");

	क्रम (i = 0; i < data_len / 4; i += 4) अणु
		ipr_err("%08X: %08X %08X %08X %08X\n", i*4,
			be32_to_cpu(ioasa_data[i]),
			be32_to_cpu(ioasa_data[i+1]),
			be32_to_cpu(ioasa_data[i+2]),
			be32_to_cpu(ioasa_data[i+3]));
	पूर्ण
पूर्ण

/**
 * ipr_gen_sense - Generate SCSI sense data from an IOASA
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_gen_sense(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	u32 failing_lba;
	u8 *sense_buf = ipr_cmd->scsi_cmd->sense_buffer;
	काष्ठा ipr_resource_entry *res = ipr_cmd->scsi_cmd->device->hostdata;
	काष्ठा ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	u32 ioasc = be32_to_cpu(ioasa->hdr.ioasc);

	स_रखो(sense_buf, 0, SCSI_SENSE_BUFFERSIZE);

	अगर (ioasc >= IPR_FIRST_DRIVER_IOASC)
		वापस;

	ipr_cmd->scsi_cmd->result = SAM_STAT_CHECK_CONDITION;

	अगर (ipr_is_vset_device(res) &&
	    ioasc == IPR_IOASC_MED_DO_NOT_REALLOC &&
	    ioasa->u.vset.failing_lba_hi != 0) अणु
		sense_buf[0] = 0x72;
		sense_buf[1] = IPR_IOASC_SENSE_KEY(ioasc);
		sense_buf[2] = IPR_IOASC_SENSE_CODE(ioasc);
		sense_buf[3] = IPR_IOASC_SENSE_QUAL(ioasc);

		sense_buf[7] = 12;
		sense_buf[8] = 0;
		sense_buf[9] = 0x0A;
		sense_buf[10] = 0x80;

		failing_lba = be32_to_cpu(ioasa->u.vset.failing_lba_hi);

		sense_buf[12] = (failing_lba & 0xff000000) >> 24;
		sense_buf[13] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[14] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[15] = failing_lba & 0x000000ff;

		failing_lba = be32_to_cpu(ioasa->u.vset.failing_lba_lo);

		sense_buf[16] = (failing_lba & 0xff000000) >> 24;
		sense_buf[17] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[18] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[19] = failing_lba & 0x000000ff;
	पूर्ण अन्यथा अणु
		sense_buf[0] = 0x70;
		sense_buf[2] = IPR_IOASC_SENSE_KEY(ioasc);
		sense_buf[12] = IPR_IOASC_SENSE_CODE(ioasc);
		sense_buf[13] = IPR_IOASC_SENSE_QUAL(ioasc);

		/* Illegal request */
		अगर ((IPR_IOASC_SENSE_KEY(ioasc) == 0x05) &&
		    (be32_to_cpu(ioasa->hdr.ioasc_specअगरic) & IPR_FIELD_POINTER_VALID)) अणु
			sense_buf[7] = 10;	/* additional length */

			/* IOARCB was in error */
			अगर (IPR_IOASC_SENSE_CODE(ioasc) == 0x24)
				sense_buf[15] = 0xC0;
			अन्यथा	/* Parameter data was invalid */
				sense_buf[15] = 0x80;

			sense_buf[16] =
			    ((IPR_FIELD_POINTER_MASK &
			      be32_to_cpu(ioasa->hdr.ioasc_specअगरic)) >> 8) & 0xff;
			sense_buf[17] =
			    (IPR_FIELD_POINTER_MASK &
			     be32_to_cpu(ioasa->hdr.ioasc_specअगरic)) & 0xff;
		पूर्ण अन्यथा अणु
			अगर (ioasc == IPR_IOASC_MED_DO_NOT_REALLOC) अणु
				अगर (ipr_is_vset_device(res))
					failing_lba = be32_to_cpu(ioasa->u.vset.failing_lba_lo);
				अन्यथा
					failing_lba = be32_to_cpu(ioasa->u.dasd.failing_lba);

				sense_buf[0] |= 0x80;	/* Or in the Valid bit */
				sense_buf[3] = (failing_lba & 0xff000000) >> 24;
				sense_buf[4] = (failing_lba & 0x00ff0000) >> 16;
				sense_buf[5] = (failing_lba & 0x0000ff00) >> 8;
				sense_buf[6] = failing_lba & 0x000000ff;
			पूर्ण

			sense_buf[7] = 6;	/* additional length */
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ipr_get_स्वतःsense - Copy स्वतःsense data to sense buffer
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function copies the स्वतःsense buffer to the buffer
 * in the scsi_cmd, अगर there is स्वतःsense available.
 *
 * Return value:
 *	1 अगर स्वतःsense was available / 0 अगर not
 **/
अटल पूर्णांक ipr_get_स्वतःsense(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	काष्ठा ipr_ioasa64 *ioasa64 = &ipr_cmd->s.ioasa64;

	अगर ((be32_to_cpu(ioasa->hdr.ioasc_specअगरic) & IPR_AUTOSENSE_VALID) == 0)
		वापस 0;

	अगर (ipr_cmd->ioa_cfg->sis64)
		स_नकल(ipr_cmd->scsi_cmd->sense_buffer, ioasa64->स्वतः_sense.data,
		       min_t(u16, be16_to_cpu(ioasa64->स्वतः_sense.स्वतः_sense_len),
			   SCSI_SENSE_BUFFERSIZE));
	अन्यथा
		स_नकल(ipr_cmd->scsi_cmd->sense_buffer, ioasa->स्वतः_sense.data,
		       min_t(u16, be16_to_cpu(ioasa->स्वतः_sense.स्वतः_sense_len),
			   SCSI_SENSE_BUFFERSIZE));
	वापस 1;
पूर्ण

/**
 * ipr_erp_start - Process an error response क्रम a SCSI op
 * @ioa_cfg:	ioa config काष्ठा
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function determines whether or not to initiate ERP
 * on the affected device.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_erp_start(काष्ठा ipr_ioa_cfg *ioa_cfg,
			      काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	काष्ठा ipr_resource_entry *res = scsi_cmd->device->hostdata;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);
	u32 masked_ioasc = ioasc & IPR_IOASC_IOASC_MASK;

	अगर (!res) अणु
		__ipr_scsi_eh_करोne(ipr_cmd);
		वापस;
	पूर्ण

	अगर (!ipr_is_gscsi(res) && masked_ioasc != IPR_IOASC_HW_DEV_BUS_STATUS)
		ipr_gen_sense(ipr_cmd);

	ipr_dump_ioasa(ioa_cfg, ipr_cmd, res);

	चयन (masked_ioasc) अणु
	हाल IPR_IOASC_ABORTED_CMD_TERM_BY_HOST:
		अगर (ipr_is_naca_model(res))
			scsi_cmd->result |= (DID_ABORT << 16);
		अन्यथा
			scsi_cmd->result |= (DID_IMM_RETRY << 16);
		अवरोध;
	हाल IPR_IOASC_IR_RESOURCE_HANDLE:
	हाल IPR_IOASC_IR_NO_CMDS_TO_2ND_IOA:
		scsi_cmd->result |= (DID_NO_CONNECT << 16);
		अवरोध;
	हाल IPR_IOASC_HW_SEL_TIMEOUT:
		scsi_cmd->result |= (DID_NO_CONNECT << 16);
		अगर (!ipr_is_naca_model(res))
			res->needs_sync_complete = 1;
		अवरोध;
	हाल IPR_IOASC_SYNC_REQUIRED:
		अगर (!res->in_erp)
			res->needs_sync_complete = 1;
		scsi_cmd->result |= (DID_IMM_RETRY << 16);
		अवरोध;
	हाल IPR_IOASC_MED_DO_NOT_REALLOC: /* prevent retries */
	हाल IPR_IOASA_IR_DUAL_IOA_DISABLED:
		/*
		 * exception: करो not set DID_PASSTHROUGH on CHECK CONDITION
		 * so SCSI mid-layer and upper layers handle it accordingly.
		 */
		अगर (scsi_cmd->result != SAM_STAT_CHECK_CONDITION)
			scsi_cmd->result |= (DID_PASSTHROUGH << 16);
		अवरोध;
	हाल IPR_IOASC_BUS_WAS_RESET:
	हाल IPR_IOASC_BUS_WAS_RESET_BY_OTHER:
		/*
		 * Report the bus reset and ask क्रम a retry. The device
		 * will give CC/UA the next command.
		 */
		अगर (!res->resetting_device)
			scsi_report_bus_reset(ioa_cfg->host, scsi_cmd->device->channel);
		scsi_cmd->result |= (DID_ERROR << 16);
		अगर (!ipr_is_naca_model(res))
			res->needs_sync_complete = 1;
		अवरोध;
	हाल IPR_IOASC_HW_DEV_BUS_STATUS:
		scsi_cmd->result |= IPR_IOASC_SENSE_STATUS(ioasc);
		अगर (IPR_IOASC_SENSE_STATUS(ioasc) == SAM_STAT_CHECK_CONDITION) अणु
			अगर (!ipr_get_स्वतःsense(ipr_cmd)) अणु
				अगर (!ipr_is_naca_model(res)) अणु
					ipr_erp_cancel_all(ipr_cmd);
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!ipr_is_naca_model(res))
			res->needs_sync_complete = 1;
		अवरोध;
	हाल IPR_IOASC_NR_INIT_CMD_REQUIRED:
		अवरोध;
	हाल IPR_IOASC_IR_NON_OPTIMIZED:
		अगर (res->raw_mode) अणु
			res->raw_mode = 0;
			scsi_cmd->result |= (DID_IMM_RETRY << 16);
		पूर्ण अन्यथा
			scsi_cmd->result |= (DID_ERROR << 16);
		अवरोध;
	शेष:
		अगर (IPR_IOASC_SENSE_KEY(ioasc) > RECOVERED_ERROR)
			scsi_cmd->result |= (DID_ERROR << 16);
		अगर (!ipr_is_vset_device(res) && !ipr_is_naca_model(res))
			res->needs_sync_complete = 1;
		अवरोध;
	पूर्ण

	scsi_dma_unmap(ipr_cmd->scsi_cmd);
	scsi_cmd->scsi_करोne(scsi_cmd);
	अगर (ipr_cmd->eh_comp)
		complete(ipr_cmd->eh_comp);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
पूर्ण

/**
 * ipr_scsi_करोne - mid-layer करोne function
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is invoked by the पूर्णांकerrupt handler क्रम
 * ops generated by the SCSI mid-layer
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_scsi_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);
	अचिन्हित दीर्घ lock_flags;

	scsi_set_resid(scsi_cmd, be32_to_cpu(ipr_cmd->s.ioasa.hdr.residual_data_len));

	अगर (likely(IPR_IOASC_SENSE_KEY(ioasc) == 0)) अणु
		scsi_dma_unmap(scsi_cmd);

		spin_lock_irqsave(ipr_cmd->hrrq->lock, lock_flags);
		scsi_cmd->scsi_करोne(scsi_cmd);
		अगर (ipr_cmd->eh_comp)
			complete(ipr_cmd->eh_comp);
		list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
		spin_unlock_irqrestore(ipr_cmd->hrrq->lock, lock_flags);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
		spin_lock(&ipr_cmd->hrrq->_lock);
		ipr_erp_start(ioa_cfg, ipr_cmd);
		spin_unlock(&ipr_cmd->hrrq->_lock);
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	पूर्ण
पूर्ण

/**
 * ipr_queuecommand - Queue a mid-layer request
 * @shost:		scsi host काष्ठा
 * @scsi_cmd:	scsi command काष्ठा
 *
 * This function queues a request generated by the mid-layer.
 *
 * Return value:
 *	0 on success
 *	SCSI_MLQUEUE_DEVICE_BUSY अगर device is busy
 *	SCSI_MLQUEUE_HOST_BUSY अगर host is busy
 **/
अटल पूर्णांक ipr_queuecommand(काष्ठा Scsi_Host *shost,
			    काष्ठा scsi_cmnd *scsi_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा ipr_resource_entry *res;
	काष्ठा ipr_ioarcb *ioarcb;
	काष्ठा ipr_cmnd *ipr_cmd;
	अचिन्हित दीर्घ hrrq_flags, lock_flags;
	पूर्णांक rc;
	काष्ठा ipr_hrr_queue *hrrq;
	पूर्णांक hrrq_id;

	ioa_cfg = (काष्ठा ipr_ioa_cfg *)shost->hostdata;

	scsi_cmd->result = (DID_OK << 16);
	res = scsi_cmd->device->hostdata;

	अगर (ipr_is_gata(res) && res->sata_port) अणु
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
		rc = ata_sas_queuecmd(scsi_cmd, res->sata_port->ap);
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		वापस rc;
	पूर्ण

	hrrq_id = ipr_get_hrrq_index(ioa_cfg);
	hrrq = &ioa_cfg->hrrq[hrrq_id];

	spin_lock_irqsave(hrrq->lock, hrrq_flags);
	/*
	 * We are currently blocking all devices due to a host reset
	 * We have told the host to stop giving us new requests, but
	 * ERP ops करोn't count. FIXME
	 */
	अगर (unlikely(!hrrq->allow_cmds && !hrrq->ioa_is_dead && !hrrq->removing_ioa)) अणु
		spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	/*
	 * FIXME - Create scsi_set_host_offline पूर्णांकerface
	 *  and the ioa_is_dead check can be हटाओd
	 */
	अगर (unlikely(hrrq->ioa_is_dead || hrrq->removing_ioa || !res)) अणु
		spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
		जाओ err_nodev;
	पूर्ण

	ipr_cmd = __ipr_get_मुक्त_ipr_cmnd(hrrq);
	अगर (ipr_cmd == शून्य) अणु
		spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	spin_unlock_irqrestore(hrrq->lock, hrrq_flags);

	ipr_init_ipr_cmnd(ipr_cmd, ipr_scsi_करोne);
	ioarcb = &ipr_cmd->ioarcb;

	स_नकल(ioarcb->cmd_pkt.cdb, scsi_cmd->cmnd, scsi_cmd->cmd_len);
	ipr_cmd->scsi_cmd = scsi_cmd;
	ipr_cmd->करोne = ipr_scsi_eh_करोne;

	अगर (ipr_is_gscsi(res)) अणु
		अगर (scsi_cmd->underflow == 0)
			ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_NO_ULEN_CHK;

		अगर (res->reset_occurred) अणु
			res->reset_occurred = 0;
			ioarcb->cmd_pkt.flags_lo |= IPR_FLAGS_LO_DELAY_AFTER_RST;
		पूर्ण
	पूर्ण

	अगर (ipr_is_gscsi(res) || ipr_is_vset_device(res)) अणु
		ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_NO_LINK_DESC;

		ioarcb->cmd_pkt.flags_lo |= IPR_FLAGS_LO_ALIGNED_BFR;
		अगर (scsi_cmd->flags & SCMD_TAGGED)
			ioarcb->cmd_pkt.flags_lo |= IPR_FLAGS_LO_SIMPLE_TASK;
		अन्यथा
			ioarcb->cmd_pkt.flags_lo |= IPR_FLAGS_LO_UNTAGGED_TASK;
	पूर्ण

	अगर (scsi_cmd->cmnd[0] >= 0xC0 &&
	    (!ipr_is_gscsi(res) || scsi_cmd->cmnd[0] == IPR_QUERY_RSRC_STATE)) अणु
		ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
	पूर्ण
	अगर (res->raw_mode && ipr_is_af_dasd_device(res)) अणु
		ioarcb->cmd_pkt.request_type = IPR_RQTYPE_PIPE;

		अगर (scsi_cmd->underflow == 0)
			ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_NO_ULEN_CHK;
	पूर्ण

	अगर (ioa_cfg->sis64)
		rc = ipr_build_ioadl64(ioa_cfg, ipr_cmd);
	अन्यथा
		rc = ipr_build_ioadl(ioa_cfg, ipr_cmd);

	spin_lock_irqsave(hrrq->lock, hrrq_flags);
	अगर (unlikely(rc || (!hrrq->allow_cmds && !hrrq->ioa_is_dead))) अणु
		list_add_tail(&ipr_cmd->queue, &hrrq->hrrq_मुक्त_q);
		spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
		अगर (!rc)
			scsi_dma_unmap(scsi_cmd);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	अगर (unlikely(hrrq->ioa_is_dead)) अणु
		list_add_tail(&ipr_cmd->queue, &hrrq->hrrq_मुक्त_q);
		spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
		scsi_dma_unmap(scsi_cmd);
		जाओ err_nodev;
	पूर्ण

	ioarcb->res_handle = res->res_handle;
	अगर (res->needs_sync_complete) अणु
		ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_SYNC_COMPLETE;
		res->needs_sync_complete = 0;
	पूर्ण
	list_add_tail(&ipr_cmd->queue, &hrrq->hrrq_pending_q);
	ipr_trc_hook(ipr_cmd, IPR_TRACE_START, IPR_GET_RES_PHYS_LOC(res));
	ipr_send_command(ipr_cmd);
	spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
	वापस 0;

err_nodev:
	spin_lock_irqsave(hrrq->lock, hrrq_flags);
	स_रखो(scsi_cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
	scsi_cmd->result = (DID_NO_CONNECT << 16);
	scsi_cmd->scsi_करोne(scsi_cmd);
	spin_unlock_irqrestore(hrrq->lock, hrrq_flags);
	वापस 0;
पूर्ण

/**
 * ipr_ioctl - IOCTL handler
 * @sdev:	scsi device काष्ठा
 * @cmd:	IOCTL cmd
 * @arg:	IOCTL arg
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक ipr_ioctl(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd,
		     व्योम __user *arg)
अणु
	काष्ठा ipr_resource_entry *res;

	res = (काष्ठा ipr_resource_entry *)sdev->hostdata;
	अगर (res && ipr_is_gata(res)) अणु
		अगर (cmd == HDIO_GET_IDENTITY)
			वापस -ENOTTY;
		वापस ata_sas_scsi_ioctl(res->sata_port->ap, sdev, cmd, arg);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * ipr_ioa_info - Get inक्रमmation about the card/driver
 * @host:	scsi host काष्ठा
 *
 * Return value:
 * 	poपूर्णांकer to buffer with description string
 **/
अटल स्थिर अक्षर *ipr_ioa_info(काष्ठा Scsi_Host *host)
अणु
	अटल अक्षर buffer[512];
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	अचिन्हित दीर्घ lock_flags = 0;

	ioa_cfg = (काष्ठा ipr_ioa_cfg *) host->hostdata;

	spin_lock_irqsave(host->host_lock, lock_flags);
	प्र_लिखो(buffer, "IBM %X Storage Adapter", ioa_cfg->type);
	spin_unlock_irqrestore(host->host_lock, lock_flags);

	वापस buffer;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = "IPR",
	.info = ipr_ioa_info,
	.ioctl = ipr_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = ipr_ioctl,
#पूर्ण_अगर
	.queuecommand = ipr_queuecommand,
	.dma_need_drain = ata_scsi_dma_need_drain,
	.eh_पात_handler = ipr_eh_पात,
	.eh_device_reset_handler = ipr_eh_dev_reset,
	.eh_host_reset_handler = ipr_eh_host_reset,
	.slave_alloc = ipr_slave_alloc,
	.slave_configure = ipr_slave_configure,
	.slave_destroy = ipr_slave_destroy,
	.scan_finished = ipr_scan_finished,
	.target_alloc = ipr_target_alloc,
	.target_destroy = ipr_target_destroy,
	.change_queue_depth = ipr_change_queue_depth,
	.bios_param = ipr_biosparam,
	.can_queue = IPR_MAX_COMMANDS,
	.this_id = -1,
	.sg_tablesize = IPR_MAX_SGLIST,
	.max_sectors = IPR_IOA_MAX_SECTORS,
	.cmd_per_lun = IPR_MAX_CMD_PER_LUN,
	.shost_attrs = ipr_ioa_attrs,
	.sdev_attrs = ipr_dev_attrs,
	.proc_name = IPR_NAME,
पूर्ण;

/**
 * ipr_ata_phy_reset - libata phy_reset handler
 * @ap:		ata port to reset
 *
 **/
अटल व्योम ipr_ata_phy_reset(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ipr_sata_port *sata_port = ap->निजी_data;
	काष्ठा ipr_resource_entry *res = sata_port->res;
	काष्ठा ipr_ioa_cfg *ioa_cfg = sata_port->ioa_cfg;
	पूर्णांक rc;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	जबतक (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	पूर्ण

	अगर (!ioa_cfg->hrrq[IPR_INIT_HRRQ].allow_cmds)
		जाओ out_unlock;

	rc = ipr_device_reset(ioa_cfg, res);

	अगर (rc) अणु
		ap->link.device[0].class = ATA_DEV_NONE;
		जाओ out_unlock;
	पूर्ण

	ap->link.device[0].class = res->ata_class;
	अगर (ap->link.device[0].class == ATA_DEV_UNKNOWN)
		ap->link.device[0].class = ATA_DEV_NONE;

out_unlock:
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
	LEAVE;
पूर्ण

/**
 * ipr_ata_post_पूर्णांकernal - Cleanup after an पूर्णांकernal command
 * @qc:	ATA queued command
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_ata_post_पूर्णांकernal(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ipr_sata_port *sata_port = qc->ap->निजी_data;
	काष्ठा ipr_ioa_cfg *ioa_cfg = sata_port->ioa_cfg;
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_hrr_queue *hrrq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	जबतक (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	पूर्ण

	क्रम_each_hrrq(hrrq, ioa_cfg) अणु
		spin_lock(&hrrq->_lock);
		list_क्रम_each_entry(ipr_cmd, &hrrq->hrrq_pending_q, queue) अणु
			अगर (ipr_cmd->qc == qc) अणु
				ipr_device_reset(ioa_cfg, sata_port->res);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&hrrq->_lock);
	पूर्ण
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
पूर्ण

/**
 * ipr_copy_sata_tf - Copy a SATA taskfile to an IOA data काष्ठाure
 * @regs:	destination
 * @tf:	source ATA taskfile
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_copy_sata_tf(काष्ठा ipr_ioarcb_ata_regs *regs,
			     काष्ठा ata_taskfile *tf)
अणु
	regs->feature = tf->feature;
	regs->nsect = tf->nsect;
	regs->lbal = tf->lbal;
	regs->lbam = tf->lbam;
	regs->lbah = tf->lbah;
	regs->device = tf->device;
	regs->command = tf->command;
	regs->hob_feature = tf->hob_feature;
	regs->hob_nsect = tf->hob_nsect;
	regs->hob_lbal = tf->hob_lbal;
	regs->hob_lbam = tf->hob_lbam;
	regs->hob_lbah = tf->hob_lbah;
	regs->ctl = tf->ctl;
पूर्ण

/**
 * ipr_sata_करोne - करोne function क्रम SATA commands
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is invoked by the पूर्णांकerrupt handler क्रम
 * ops generated by the SCSI mid-layer to SATA devices
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_sata_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ata_queued_cmd *qc = ipr_cmd->qc;
	काष्ठा ipr_sata_port *sata_port = qc->ap->निजी_data;
	काष्ठा ipr_resource_entry *res = sata_port->res;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	spin_lock(&ipr_cmd->hrrq->_lock);
	अगर (ipr_cmd->ioa_cfg->sis64)
		स_नकल(&sata_port->ioasa, &ipr_cmd->s.ioasa64.u.gata,
		       माप(काष्ठा ipr_ioasa_gata));
	अन्यथा
		स_नकल(&sata_port->ioasa, &ipr_cmd->s.ioasa.u.gata,
		       माप(काष्ठा ipr_ioasa_gata));
	ipr_dump_ioasa(ioa_cfg, ipr_cmd, res);

	अगर (be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc_specअगरic) & IPR_ATA_DEVICE_WAS_RESET)
		scsi_report_device_reset(ioa_cfg->host, res->bus, res->target);

	अगर (IPR_IOASC_SENSE_KEY(ioasc) > RECOVERED_ERROR)
		qc->err_mask |= __ac_err_mask(sata_port->ioasa.status);
	अन्यथा
		qc->err_mask |= ac_err_mask(sata_port->ioasa.status);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
	spin_unlock(&ipr_cmd->hrrq->_lock);
	ata_qc_complete(qc);
पूर्ण

/**
 * ipr_build_ata_ioadl64 - Build an ATA scatter/gather list
 * @ipr_cmd:	ipr command काष्ठा
 * @qc:		ATA queued command
 *
 **/
अटल व्योम ipr_build_ata_ioadl64(काष्ठा ipr_cmnd *ipr_cmd,
				  काष्ठा ata_queued_cmd *qc)
अणु
	u32 ioadl_flags = 0;
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioadl64_desc *ioadl64 = ipr_cmd->i.ata_ioadl.ioadl64;
	काष्ठा ipr_ioadl64_desc *last_ioadl64 = शून्य;
	पूर्णांक len = qc->nbytes;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक si;
	dma_addr_t dma_addr = ipr_cmd->dma_addr;

	अगर (len == 0)
		वापस;

	अगर (qc->dma_dir == DMA_TO_DEVICE) अणु
		ioadl_flags = IPR_IOADL_FLAGS_WRITE;
		ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
	पूर्ण अन्यथा अगर (qc->dma_dir == DMA_FROM_DEVICE)
		ioadl_flags = IPR_IOADL_FLAGS_READ;

	ioarcb->data_transfer_length = cpu_to_be32(len);
	ioarcb->ioadl_len =
		cpu_to_be32(माप(काष्ठा ipr_ioadl64_desc) * ipr_cmd->dma_use_sg);
	ioarcb->u.sis64_addr_data.data_ioadl_addr =
		cpu_to_be64(dma_addr + दुरत्व(काष्ठा ipr_cmnd, i.ata_ioadl.ioadl64));

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		ioadl64->flags = cpu_to_be32(ioadl_flags);
		ioadl64->data_len = cpu_to_be32(sg_dma_len(sg));
		ioadl64->address = cpu_to_be64(sg_dma_address(sg));

		last_ioadl64 = ioadl64;
		ioadl64++;
	पूर्ण

	अगर (likely(last_ioadl64))
		last_ioadl64->flags |= cpu_to_be32(IPR_IOADL_FLAGS_LAST);
पूर्ण

/**
 * ipr_build_ata_ioadl - Build an ATA scatter/gather list
 * @ipr_cmd:	ipr command काष्ठा
 * @qc:		ATA queued command
 *
 **/
अटल व्योम ipr_build_ata_ioadl(काष्ठा ipr_cmnd *ipr_cmd,
				काष्ठा ata_queued_cmd *qc)
अणु
	u32 ioadl_flags = 0;
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioadl_desc *ioadl = ipr_cmd->i.ioadl;
	काष्ठा ipr_ioadl_desc *last_ioadl = शून्य;
	पूर्णांक len = qc->nbytes;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक si;

	अगर (len == 0)
		वापस;

	अगर (qc->dma_dir == DMA_TO_DEVICE) अणु
		ioadl_flags = IPR_IOADL_FLAGS_WRITE;
		ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
		ioarcb->data_transfer_length = cpu_to_be32(len);
		ioarcb->ioadl_len =
			cpu_to_be32(माप(काष्ठा ipr_ioadl_desc) * ipr_cmd->dma_use_sg);
	पूर्ण अन्यथा अगर (qc->dma_dir == DMA_FROM_DEVICE) अणु
		ioadl_flags = IPR_IOADL_FLAGS_READ;
		ioarcb->पढ़ो_data_transfer_length = cpu_to_be32(len);
		ioarcb->पढ़ो_ioadl_len =
			cpu_to_be32(माप(काष्ठा ipr_ioadl_desc) * ipr_cmd->dma_use_sg);
	पूर्ण

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		ioadl->flags_and_data_len = cpu_to_be32(ioadl_flags | sg_dma_len(sg));
		ioadl->address = cpu_to_be32(sg_dma_address(sg));

		last_ioadl = ioadl;
		ioadl++;
	पूर्ण

	अगर (likely(last_ioadl))
		last_ioadl->flags_and_data_len |= cpu_to_be32(IPR_IOADL_FLAGS_LAST);
पूर्ण

/**
 * ipr_qc_defer - Get a मुक्त ipr_cmd
 * @qc:	queued command
 *
 * Return value:
 *	0 अगर success
 **/
अटल पूर्णांक ipr_qc_defer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ipr_sata_port *sata_port = ap->निजी_data;
	काष्ठा ipr_ioa_cfg *ioa_cfg = sata_port->ioa_cfg;
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_hrr_queue *hrrq;
	पूर्णांक hrrq_id;

	hrrq_id = ipr_get_hrrq_index(ioa_cfg);
	hrrq = &ioa_cfg->hrrq[hrrq_id];

	qc->lldd_task = शून्य;
	spin_lock(&hrrq->_lock);
	अगर (unlikely(hrrq->ioa_is_dead)) अणु
		spin_unlock(&hrrq->_lock);
		वापस 0;
	पूर्ण

	अगर (unlikely(!hrrq->allow_cmds)) अणु
		spin_unlock(&hrrq->_lock);
		वापस ATA_DEFER_LINK;
	पूर्ण

	ipr_cmd = __ipr_get_मुक्त_ipr_cmnd(hrrq);
	अगर (ipr_cmd == शून्य) अणु
		spin_unlock(&hrrq->_lock);
		वापस ATA_DEFER_LINK;
	पूर्ण

	qc->lldd_task = ipr_cmd;
	spin_unlock(&hrrq->_lock);
	वापस 0;
पूर्ण

/**
 * ipr_qc_issue - Issue a SATA qc to a device
 * @qc:	queued command
 *
 * Return value:
 * 	0 अगर success
 **/
अटल अचिन्हित पूर्णांक ipr_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ipr_sata_port *sata_port = ap->निजी_data;
	काष्ठा ipr_resource_entry *res = sata_port->res;
	काष्ठा ipr_ioa_cfg *ioa_cfg = sata_port->ioa_cfg;
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioarcb *ioarcb;
	काष्ठा ipr_ioarcb_ata_regs *regs;

	अगर (qc->lldd_task == शून्य)
		ipr_qc_defer(qc);

	ipr_cmd = qc->lldd_task;
	अगर (ipr_cmd == शून्य)
		वापस AC_ERR_SYSTEM;

	qc->lldd_task = शून्य;
	spin_lock(&ipr_cmd->hrrq->_lock);
	अगर (unlikely(!ipr_cmd->hrrq->allow_cmds ||
			ipr_cmd->hrrq->ioa_is_dead)) अणु
		list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
		spin_unlock(&ipr_cmd->hrrq->_lock);
		वापस AC_ERR_SYSTEM;
	पूर्ण

	ipr_init_ipr_cmnd(ipr_cmd, ipr_lock_and_करोne);
	ioarcb = &ipr_cmd->ioarcb;

	अगर (ioa_cfg->sis64) अणु
		regs = &ipr_cmd->i.ata_ioadl.regs;
		ioarcb->add_cmd_parms_offset = cpu_to_be16(माप(*ioarcb));
	पूर्ण अन्यथा
		regs = &ioarcb->u.add_data.u.regs;

	स_रखो(regs, 0, माप(*regs));
	ioarcb->add_cmd_parms_len = cpu_to_be16(माप(*regs));

	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);
	ipr_cmd->qc = qc;
	ipr_cmd->करोne = ipr_sata_करोne;
	ipr_cmd->ioarcb.res_handle = res->res_handle;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_ATA_PASSTHRU;
	ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_NO_LINK_DESC;
	ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_NO_ULEN_CHK;
	ipr_cmd->dma_use_sg = qc->n_elem;

	अगर (ioa_cfg->sis64)
		ipr_build_ata_ioadl64(ipr_cmd, qc);
	अन्यथा
		ipr_build_ata_ioadl(ipr_cmd, qc);

	regs->flags |= IPR_ATA_FLAG_STATUS_ON_GOOD_COMPLETION;
	ipr_copy_sata_tf(regs, &qc->tf);
	स_नकल(ioarcb->cmd_pkt.cdb, qc->cdb, IPR_MAX_CDB_LEN);
	ipr_trc_hook(ipr_cmd, IPR_TRACE_START, IPR_GET_RES_PHYS_LOC(res));

	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_NODATA:
	हाल ATA_PROT_PIO:
		अवरोध;

	हाल ATA_PROT_DMA:
		regs->flags |= IPR_ATA_FLAG_XFER_TYPE_DMA;
		अवरोध;

	हाल ATAPI_PROT_PIO:
	हाल ATAPI_PROT_NODATA:
		regs->flags |= IPR_ATA_FLAG_PACKET_CMD;
		अवरोध;

	हाल ATAPI_PROT_DMA:
		regs->flags |= IPR_ATA_FLAG_PACKET_CMD;
		regs->flags |= IPR_ATA_FLAG_XFER_TYPE_DMA;
		अवरोध;

	शेष:
		WARN_ON(1);
		spin_unlock(&ipr_cmd->hrrq->_lock);
		वापस AC_ERR_INVALID;
	पूर्ण

	ipr_send_command(ipr_cmd);
	spin_unlock(&ipr_cmd->hrrq->_lock);

	वापस 0;
पूर्ण

/**
 * ipr_qc_fill_rtf - Read result TF
 * @qc: ATA queued command
 *
 * Return value:
 * 	true
 **/
अटल bool ipr_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ipr_sata_port *sata_port = qc->ap->निजी_data;
	काष्ठा ipr_ioasa_gata *g = &sata_port->ioasa;
	काष्ठा ata_taskfile *tf = &qc->result_tf;

	tf->feature = g->error;
	tf->nsect = g->nsect;
	tf->lbal = g->lbal;
	tf->lbam = g->lbam;
	tf->lbah = g->lbah;
	tf->device = g->device;
	tf->command = g->status;
	tf->hob_nsect = g->hob_nsect;
	tf->hob_lbal = g->hob_lbal;
	tf->hob_lbam = g->hob_lbam;
	tf->hob_lbah = g->hob_lbah;

	वापस true;
पूर्ण

अटल काष्ठा ata_port_operations ipr_sata_ops = अणु
	.phy_reset = ipr_ata_phy_reset,
	.hardreset = ipr_sata_reset,
	.post_पूर्णांकernal_cmd = ipr_ata_post_पूर्णांकernal,
	.qc_prep = ata_noop_qc_prep,
	.qc_defer = ipr_qc_defer,
	.qc_issue = ipr_qc_issue,
	.qc_fill_rtf = ipr_qc_fill_rtf,
	.port_start = ata_sas_port_start,
	.port_stop = ata_sas_port_stop
पूर्ण;

अटल काष्ठा ata_port_info sata_port_info = अणु
	.flags		= ATA_FLAG_SATA | ATA_FLAG_PIO_DMA |
			  ATA_FLAG_SAS_HOST,
	.pio_mask	= ATA_PIO4_ONLY,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ipr_sata_ops
पूर्ण;

#अगर_घोषित CONFIG_PPC_PSERIES
अटल स्थिर u16 ipr_blocked_processors[] = अणु
	PVR_NORTHSTAR,
	PVR_PULSAR,
	PVR_POWER4,
	PVR_ICESTAR,
	PVR_SSTAR,
	PVR_POWER4p,
	PVR_630,
	PVR_630p
पूर्ण;

/**
 * ipr_invalid_adapter - Determine अगर this adapter is supported on this hardware
 * @ioa_cfg:	ioa cfg काष्ठा
 *
 * Adapters that use Gemstone revision < 3.1 करो not work reliably on
 * certain pSeries hardware. This function determines अगर the given
 * adapter is in one of these confgurations or not.
 *
 * Return value:
 * 	1 अगर adapter is not supported / 0 अगर adapter is supported
 **/
अटल पूर्णांक ipr_invalid_adapter(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक i;

	अगर ((ioa_cfg->type == 0x5702) && (ioa_cfg->pdev->revision < 4)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ipr_blocked_processors); i++) अणु
			अगर (pvr_version_is(ipr_blocked_processors[i]))
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ipr_invalid_adapter(ioa_cfg) 0
#पूर्ण_अगर

/**
 * ipr_ioa_bringकरोwn_करोne - IOA bring करोwn completion.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function processes the completion of an adapter bring करोwn.
 * It wakes any reset sleepers.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioa_bringकरोwn_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	पूर्णांक i;

	ENTER;
	अगर (!ioa_cfg->hrrq[IPR_INIT_HRRQ].removing_ioa) अणु
		ipr_trace;
		ioa_cfg->scsi_unblock = 1;
		schedule_work(&ioa_cfg->work_q);
	पूर्ण

	ioa_cfg->in_reset_reload = 0;
	ioa_cfg->reset_retries = 0;
	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].ioa_is_dead = 1;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	पूर्ण
	wmb();

	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
	wake_up_all(&ioa_cfg->reset_रुको_q);
	LEAVE;

	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_ioa_reset_करोne - IOA reset completion.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function processes the completion of an adapter reset.
 * It schedules any necessary mid-layer add/हटाओs and
 * wakes any reset sleepers.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioa_reset_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_resource_entry *res;
	पूर्णांक j;

	ENTER;
	ioa_cfg->in_reset_reload = 0;
	क्रम (j = 0; j < ioa_cfg->hrrq_num; j++) अणु
		spin_lock(&ioa_cfg->hrrq[j]._lock);
		ioa_cfg->hrrq[j].allow_cmds = 1;
		spin_unlock(&ioa_cfg->hrrq[j]._lock);
	पूर्ण
	wmb();
	ioa_cfg->reset_cmd = शून्य;
	ioa_cfg->करोorbell |= IPR_RUNTIME_RESET;

	list_क्रम_each_entry(res, &ioa_cfg->used_res_q, queue) अणु
		अगर (res->add_to_ml || res->del_from_ml) अणु
			ipr_trace;
			अवरोध;
		पूर्ण
	पूर्ण
	schedule_work(&ioa_cfg->work_q);

	क्रम (j = 0; j < IPR_NUM_HCAMS; j++) अणु
		list_del_init(&ioa_cfg->hostrcb[j]->queue);
		अगर (j < IPR_NUM_LOG_HCAMS)
			ipr_send_hcam(ioa_cfg,
				IPR_HCAM_CDB_OP_CODE_LOG_DATA,
				ioa_cfg->hostrcb[j]);
		अन्यथा
			ipr_send_hcam(ioa_cfg,
				IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE,
				ioa_cfg->hostrcb[j]);
	पूर्ण

	scsi_report_bus_reset(ioa_cfg->host, IPR_VSET_BUS);
	dev_info(&ioa_cfg->pdev->dev, "IOA initialized.\n");

	ioa_cfg->reset_retries = 0;
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
	wake_up_all(&ioa_cfg->reset_रुको_q);

	ioa_cfg->scsi_unblock = 1;
	schedule_work(&ioa_cfg->work_q);
	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_set_sup_dev_dflt - Initialize a Set Supported Device buffer
 * @supported_dev:	supported device काष्ठा
 * @vpids:			venकरोr product id काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_set_sup_dev_dflt(काष्ठा ipr_supported_device *supported_dev,
				 काष्ठा ipr_std_inq_vpids *vpids)
अणु
	स_रखो(supported_dev, 0, माप(काष्ठा ipr_supported_device));
	स_नकल(&supported_dev->vpids, vpids, माप(काष्ठा ipr_std_inq_vpids));
	supported_dev->num_records = 1;
	supported_dev->data_length =
		cpu_to_be16(माप(काष्ठा ipr_supported_device));
	supported_dev->reserved = 0;
पूर्ण

/**
 * ipr_set_supported_devs - Send Set Supported Devices क्रम a device
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a Set Supported Devices to the adapter
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_set_supported_devs(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_supported_device *supp_dev = &ioa_cfg->vpd_cbs->supp_dev;
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_resource_entry *res = ipr_cmd->u.res;

	ipr_cmd->job_step = ipr_ioa_reset_करोne;

	list_क्रम_each_entry_जारी(res, &ioa_cfg->used_res_q, queue) अणु
		अगर (!ipr_is_scsi_disk(res))
			जारी;

		ipr_cmd->u.res = res;
		ipr_set_sup_dev_dflt(supp_dev, &res->std_inq_data.vpids);

		ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
		ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
		ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;

		ioarcb->cmd_pkt.cdb[0] = IPR_SET_SUPPORTED_DEVICES;
		ioarcb->cmd_pkt.cdb[1] = IPR_SET_ALL_SUPPORTED_DEVICES;
		ioarcb->cmd_pkt.cdb[7] = (माप(काष्ठा ipr_supported_device) >> 8) & 0xff;
		ioarcb->cmd_pkt.cdb[8] = माप(काष्ठा ipr_supported_device) & 0xff;

		ipr_init_ioadl(ipr_cmd,
			       ioa_cfg->vpd_cbs_dma +
				 दुरत्व(काष्ठा ipr_misc_cbs, supp_dev),
			       माप(काष्ठा ipr_supported_device),
			       IPR_IOADL_FLAGS_WRITE_LAST);

		ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout,
			   IPR_SET_SUP_DEVICE_TIMEOUT);

		अगर (!ioa_cfg->sis64)
			ipr_cmd->job_step = ipr_set_supported_devs;
		LEAVE;
		वापस IPR_RC_JOB_RETURN;
	पूर्ण

	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_get_mode_page - Locate specअगरied mode page
 * @mode_pages:	mode page buffer
 * @page_code:	page code to find
 * @len:		minimum required length क्रम mode page
 *
 * Return value:
 * 	poपूर्णांकer to mode page / शून्य on failure
 **/
अटल व्योम *ipr_get_mode_page(काष्ठा ipr_mode_pages *mode_pages,
			       u32 page_code, u32 len)
अणु
	काष्ठा ipr_mode_page_hdr *mode_hdr;
	u32 page_length;
	u32 length;

	अगर (!mode_pages || (mode_pages->hdr.length == 0))
		वापस शून्य;

	length = (mode_pages->hdr.length + 1) - 4 - mode_pages->hdr.block_desc_len;
	mode_hdr = (काष्ठा ipr_mode_page_hdr *)
		(mode_pages->data + mode_pages->hdr.block_desc_len);

	जबतक (length) अणु
		अगर (IPR_GET_MODE_PAGE_CODE(mode_hdr) == page_code) अणु
			अगर (mode_hdr->page_length >= (len - माप(काष्ठा ipr_mode_page_hdr)))
				वापस mode_hdr;
			अवरोध;
		पूर्ण अन्यथा अणु
			page_length = (माप(काष्ठा ipr_mode_page_hdr) +
				       mode_hdr->page_length);
			length -= page_length;
			mode_hdr = (काष्ठा ipr_mode_page_hdr *)
				((अचिन्हित दीर्घ)mode_hdr + page_length);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * ipr_check_term_घातer - Check क्रम term घातer errors
 * @ioa_cfg:	ioa config काष्ठा
 * @mode_pages:	IOAFP mode pages buffer
 *
 * Check the IOAFP's mode page 28 क्रम term घातer errors
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_check_term_घातer(काष्ठा ipr_ioa_cfg *ioa_cfg,
				 काष्ठा ipr_mode_pages *mode_pages)
अणु
	पूर्णांक i;
	पूर्णांक entry_length;
	काष्ठा ipr_dev_bus_entry *bus;
	काष्ठा ipr_mode_page28 *mode_page;

	mode_page = ipr_get_mode_page(mode_pages, 0x28,
				      माप(काष्ठा ipr_mode_page28));

	entry_length = mode_page->entry_length;

	bus = mode_page->bus;

	क्रम (i = 0; i < mode_page->num_entries; i++) अणु
		अगर (bus->flags & IPR_SCSI_ATTR_NO_TERM_PWR) अणु
			dev_err(&ioa_cfg->pdev->dev,
				"Term power is absent on scsi bus %d\n",
				bus->res_addr.bus);
		पूर्ण

		bus = (काष्ठा ipr_dev_bus_entry *)((अक्षर *)bus + entry_length);
	पूर्ण
पूर्ण

/**
 * ipr_scsi_bus_speed_limit - Limit the SCSI speed based on SES table
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Looks through the config table checking क्रम SES devices. If
 * the SES device is in the SES table indicating a maximum SCSI
 * bus speed, the speed is limited क्रम the bus.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_scsi_bus_speed_limit(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	u32 max_xfer_rate;
	पूर्णांक i;

	क्रम (i = 0; i < IPR_MAX_NUM_BUSES; i++) अणु
		max_xfer_rate = ipr_get_max_scsi_speed(ioa_cfg, i,
						       ioa_cfg->bus_attr[i].bus_width);

		अगर (max_xfer_rate < ioa_cfg->bus_attr[i].max_xfer_rate)
			ioa_cfg->bus_attr[i].max_xfer_rate = max_xfer_rate;
	पूर्ण
पूर्ण

/**
 * ipr_modअगरy_ioafp_mode_page_28 - Modअगरy IOAFP Mode Page 28
 * @ioa_cfg:	ioa config काष्ठा
 * @mode_pages:	mode page 28 buffer
 *
 * Updates mode page 28 based on driver configuration
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_modअगरy_ioafp_mode_page_28(काष्ठा ipr_ioa_cfg *ioa_cfg,
					  काष्ठा ipr_mode_pages *mode_pages)
अणु
	पूर्णांक i, entry_length;
	काष्ठा ipr_dev_bus_entry *bus;
	काष्ठा ipr_bus_attributes *bus_attr;
	काष्ठा ipr_mode_page28 *mode_page;

	mode_page = ipr_get_mode_page(mode_pages, 0x28,
				      माप(काष्ठा ipr_mode_page28));

	entry_length = mode_page->entry_length;

	/* Loop क्रम each device bus entry */
	क्रम (i = 0, bus = mode_page->bus;
	     i < mode_page->num_entries;
	     i++, bus = (काष्ठा ipr_dev_bus_entry *)((u8 *)bus + entry_length)) अणु
		अगर (bus->res_addr.bus > IPR_MAX_NUM_BUSES) अणु
			dev_err(&ioa_cfg->pdev->dev,
				"Invalid resource address reported: 0x%08X\n",
				IPR_GET_PHYS_LOC(bus->res_addr));
			जारी;
		पूर्ण

		bus_attr = &ioa_cfg->bus_attr[i];
		bus->extended_reset_delay = IPR_EXTENDED_RESET_DELAY;
		bus->bus_width = bus_attr->bus_width;
		bus->max_xfer_rate = cpu_to_be32(bus_attr->max_xfer_rate);
		bus->flags &= ~IPR_SCSI_ATTR_QAS_MASK;
		अगर (bus_attr->qas_enabled)
			bus->flags |= IPR_SCSI_ATTR_ENABLE_QAS;
		अन्यथा
			bus->flags |= IPR_SCSI_ATTR_DISABLE_QAS;
	पूर्ण
पूर्ण

/**
 * ipr_build_mode_select - Build a mode select command
 * @ipr_cmd:	ipr command काष्ठा
 * @res_handle:	resource handle to send command to
 * @parm:		Byte 2 of Mode Sense command
 * @dma_addr:	DMA buffer address
 * @xfer_len:	data transfer length
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_build_mode_select(काष्ठा ipr_cmnd *ipr_cmd,
				  __be32 res_handle, u8 parm,
				  dma_addr_t dma_addr, u8 xfer_len)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;

	ioarcb->res_handle = res_handle;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_SCSICDB;
	ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
	ioarcb->cmd_pkt.cdb[0] = MODE_SELECT;
	ioarcb->cmd_pkt.cdb[1] = parm;
	ioarcb->cmd_pkt.cdb[4] = xfer_len;

	ipr_init_ioadl(ipr_cmd, dma_addr, xfer_len, IPR_IOADL_FLAGS_WRITE_LAST);
पूर्ण

/**
 * ipr_ioafp_mode_select_page28 - Issue Mode Select Page 28 to IOA
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sets up the SCSI bus attributes and sends
 * a Mode Select क्रम Page 28 to activate them.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_mode_select_page28(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_mode_pages *mode_pages = &ioa_cfg->vpd_cbs->mode_pages;
	पूर्णांक length;

	ENTER;
	ipr_scsi_bus_speed_limit(ioa_cfg);
	ipr_check_term_घातer(ioa_cfg, mode_pages);
	ipr_modअगरy_ioafp_mode_page_28(ioa_cfg, mode_pages);
	length = mode_pages->hdr.length + 1;
	mode_pages->hdr.length = 0;

	ipr_build_mode_select(ipr_cmd, cpu_to_be32(IPR_IOA_RES_HANDLE), 0x11,
			      ioa_cfg->vpd_cbs_dma + दुरत्व(काष्ठा ipr_misc_cbs, mode_pages),
			      length);

	ipr_cmd->job_step = ipr_set_supported_devs;
	ipr_cmd->u.res = list_entry(ioa_cfg->used_res_q.next,
				    काष्ठा ipr_resource_entry, queue);
	ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout, IPR_INTERNAL_TIMEOUT);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_build_mode_sense - Builds a mode sense command
 * @ipr_cmd:	ipr command काष्ठा
 * @res_handle:		resource entry काष्ठा
 * @parm:		Byte 2 of mode sense command
 * @dma_addr:	DMA address of mode sense buffer
 * @xfer_len:	Size of DMA buffer
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_build_mode_sense(काष्ठा ipr_cmnd *ipr_cmd,
				 __be32 res_handle,
				 u8 parm, dma_addr_t dma_addr, u8 xfer_len)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;

	ioarcb->res_handle = res_handle;
	ioarcb->cmd_pkt.cdb[0] = MODE_SENSE;
	ioarcb->cmd_pkt.cdb[2] = parm;
	ioarcb->cmd_pkt.cdb[4] = xfer_len;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_SCSICDB;

	ipr_init_ioadl(ipr_cmd, dma_addr, xfer_len, IPR_IOADL_FLAGS_READ_LAST);
पूर्ण

/**
 * ipr_reset_cmd_failed - Handle failure of IOA reset command
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function handles the failure of an IOA bringup command.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_cmd_failed(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	dev_err(&ioa_cfg->pdev->dev,
		"0x%02X failed with IOASC: 0x%08X\n",
		ipr_cmd->ioarcb.cmd_pkt.cdb[0], ioasc);

	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_mode_sense_failed - Handle failure of IOAFP mode sense
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function handles the failure of a Mode Sense to the IOAFP.
 * Some adapters करो not handle all mode pages.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_mode_sense_failed(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	अगर (ioasc == IPR_IOASC_IR_INVALID_REQ_TYPE_OR_PKT) अणु
		ipr_cmd->job_step = ipr_set_supported_devs;
		ipr_cmd->u.res = list_entry(ioa_cfg->used_res_q.next,
					    काष्ठा ipr_resource_entry, queue);
		वापस IPR_RC_JOB_CONTINUE;
	पूर्ण

	वापस ipr_reset_cmd_failed(ipr_cmd);
पूर्ण

/**
 * ipr_ioafp_mode_sense_page28 - Issue Mode Sense Page 28 to IOA
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function send a Page 28 mode sense to the IOA to
 * retrieve SCSI bus attributes.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_mode_sense_page28(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ipr_build_mode_sense(ipr_cmd, cpu_to_be32(IPR_IOA_RES_HANDLE),
			     0x28, ioa_cfg->vpd_cbs_dma +
			     दुरत्व(काष्ठा ipr_misc_cbs, mode_pages),
			     माप(काष्ठा ipr_mode_pages));

	ipr_cmd->job_step = ipr_ioafp_mode_select_page28;
	ipr_cmd->job_step_failed = ipr_reset_mode_sense_failed;

	ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout, IPR_INTERNAL_TIMEOUT);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_ioafp_mode_select_page24 - Issue Mode Select to IOA
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function enables dual IOA RAID support अगर possible.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_mode_select_page24(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_mode_pages *mode_pages = &ioa_cfg->vpd_cbs->mode_pages;
	काष्ठा ipr_mode_page24 *mode_page;
	पूर्णांक length;

	ENTER;
	mode_page = ipr_get_mode_page(mode_pages, 0x24,
				      माप(काष्ठा ipr_mode_page24));

	अगर (mode_page)
		mode_page->flags |= IPR_ENABLE_DUAL_IOA_AF;

	length = mode_pages->hdr.length + 1;
	mode_pages->hdr.length = 0;

	ipr_build_mode_select(ipr_cmd, cpu_to_be32(IPR_IOA_RES_HANDLE), 0x11,
			      ioa_cfg->vpd_cbs_dma + दुरत्व(काष्ठा ipr_misc_cbs, mode_pages),
			      length);

	ipr_cmd->job_step = ipr_ioafp_mode_sense_page28;
	ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout, IPR_INTERNAL_TIMEOUT);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_mode_sense_page24_failed - Handle failure of IOAFP mode sense
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function handles the failure of a Mode Sense to the IOAFP.
 * Some adapters करो not handle all mode pages.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_mode_sense_page24_failed(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	अगर (ioasc == IPR_IOASC_IR_INVALID_REQ_TYPE_OR_PKT) अणु
		ipr_cmd->job_step = ipr_ioafp_mode_sense_page28;
		वापस IPR_RC_JOB_CONTINUE;
	पूर्ण

	वापस ipr_reset_cmd_failed(ipr_cmd);
पूर्ण

/**
 * ipr_ioafp_mode_sense_page24 - Issue Page 24 Mode Sense to IOA
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function send a mode sense to the IOA to retrieve
 * the IOA Advanced Function Control mode page.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_mode_sense_page24(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ipr_build_mode_sense(ipr_cmd, cpu_to_be32(IPR_IOA_RES_HANDLE),
			     0x24, ioa_cfg->vpd_cbs_dma +
			     दुरत्व(काष्ठा ipr_misc_cbs, mode_pages),
			     माप(काष्ठा ipr_mode_pages));

	ipr_cmd->job_step = ipr_ioafp_mode_select_page24;
	ipr_cmd->job_step_failed = ipr_reset_mode_sense_page24_failed;

	ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout, IPR_INTERNAL_TIMEOUT);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_init_res_table - Initialize the resource table
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function looks through the existing resource table, comparing
 * it with the config table. This function will take care of old/new
 * devices and schedule adding/removing them from the mid-layer
 * as appropriate.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE
 **/
अटल पूर्णांक ipr_init_res_table(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_resource_entry *res, *temp;
	काष्ठा ipr_config_table_entry_wrapper cfgtew;
	पूर्णांक entries, found, flag, i;
	LIST_HEAD(old_res);

	ENTER;
	अगर (ioa_cfg->sis64)
		flag = ioa_cfg->u.cfg_table64->hdr64.flags;
	अन्यथा
		flag = ioa_cfg->u.cfg_table->hdr.flags;

	अगर (flag & IPR_UCODE_DOWNLOAD_REQ)
		dev_err(&ioa_cfg->pdev->dev, "Microcode download required\n");

	list_क्रम_each_entry_safe(res, temp, &ioa_cfg->used_res_q, queue)
		list_move_tail(&res->queue, &old_res);

	अगर (ioa_cfg->sis64)
		entries = be16_to_cpu(ioa_cfg->u.cfg_table64->hdr64.num_entries);
	अन्यथा
		entries = ioa_cfg->u.cfg_table->hdr.num_entries;

	क्रम (i = 0; i < entries; i++) अणु
		अगर (ioa_cfg->sis64)
			cfgtew.u.cfgte64 = &ioa_cfg->u.cfg_table64->dev[i];
		अन्यथा
			cfgtew.u.cfgte = &ioa_cfg->u.cfg_table->dev[i];
		found = 0;

		list_क्रम_each_entry_safe(res, temp, &old_res, queue) अणु
			अगर (ipr_is_same_device(res, &cfgtew)) अणु
				list_move_tail(&res->queue, &ioa_cfg->used_res_q);
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			अगर (list_empty(&ioa_cfg->मुक्त_res_q)) अणु
				dev_err(&ioa_cfg->pdev->dev, "Too many devices attached\n");
				अवरोध;
			पूर्ण

			found = 1;
			res = list_entry(ioa_cfg->मुक्त_res_q.next,
					 काष्ठा ipr_resource_entry, queue);
			list_move_tail(&res->queue, &ioa_cfg->used_res_q);
			ipr_init_res_entry(res, &cfgtew);
			res->add_to_ml = 1;
		पूर्ण अन्यथा अगर (res->sdev && (ipr_is_vset_device(res) || ipr_is_scsi_disk(res)))
			res->sdev->allow_restart = 1;

		अगर (found)
			ipr_update_res_entry(res, &cfgtew);
	पूर्ण

	list_क्रम_each_entry_safe(res, temp, &old_res, queue) अणु
		अगर (res->sdev) अणु
			res->del_from_ml = 1;
			res->res_handle = IPR_INVALID_RES_HANDLE;
			list_move_tail(&res->queue, &ioa_cfg->used_res_q);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(res, temp, &old_res, queue) अणु
		ipr_clear_res_target(res);
		list_move_tail(&res->queue, &ioa_cfg->मुक्त_res_q);
	पूर्ण

	अगर (ioa_cfg->dual_raid && ipr_dual_ioa_raid)
		ipr_cmd->job_step = ipr_ioafp_mode_sense_page24;
	अन्यथा
		ipr_cmd->job_step = ipr_ioafp_mode_sense_page28;

	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_ioafp_query_ioa_cfg - Send a Query IOA Config to the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a Query IOA Configuration command
 * to the adapter to retrieve the IOA configuration table.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_query_ioa_cfg(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_inquiry_page3 *ucode_vpd = &ioa_cfg->vpd_cbs->page3_data;
	काष्ठा ipr_inquiry_cap *cap = &ioa_cfg->vpd_cbs->cap;

	ENTER;
	अगर (cap->cap & IPR_CAP_DUAL_IOA_RAID)
		ioa_cfg->dual_raid = 1;
	dev_info(&ioa_cfg->pdev->dev, "Adapter firmware version: %02X%02X%02X%02X\n",
		 ucode_vpd->major_release, ucode_vpd->card_type,
		 ucode_vpd->minor_release[0], ucode_vpd->minor_release[1]);
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
	ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);

	ioarcb->cmd_pkt.cdb[0] = IPR_QUERY_IOA_CONFIG;
	ioarcb->cmd_pkt.cdb[6] = (ioa_cfg->cfg_table_size >> 16) & 0xff;
	ioarcb->cmd_pkt.cdb[7] = (ioa_cfg->cfg_table_size >> 8) & 0xff;
	ioarcb->cmd_pkt.cdb[8] = ioa_cfg->cfg_table_size & 0xff;

	ipr_init_ioadl(ipr_cmd, ioa_cfg->cfg_table_dma, ioa_cfg->cfg_table_size,
		       IPR_IOADL_FLAGS_READ_LAST);

	ipr_cmd->job_step = ipr_init_res_table;

	ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout, IPR_INTERNAL_TIMEOUT);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

अटल पूर्णांक ipr_ioa_service_action_failed(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	अगर (ioasc == IPR_IOASC_IR_INVALID_REQ_TYPE_OR_PKT)
		वापस IPR_RC_JOB_CONTINUE;

	वापस ipr_reset_cmd_failed(ipr_cmd);
पूर्ण

अटल व्योम ipr_build_ioa_service_action(काष्ठा ipr_cmnd *ipr_cmd,
					 __be32 res_handle, u8 sa_code)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;

	ioarcb->res_handle = res_handle;
	ioarcb->cmd_pkt.cdb[0] = IPR_IOA_SERVICE_ACTION;
	ioarcb->cmd_pkt.cdb[1] = sa_code;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
पूर्ण

/**
 * ipr_ioafp_set_caching_parameters - Issue Set Cache parameters service
 * action
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 *	none
 **/
अटल पूर्णांक ipr_ioafp_set_caching_parameters(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_inquiry_pageC4 *pageC4 = &ioa_cfg->vpd_cbs->pageC4_data;

	ENTER;

	ipr_cmd->job_step = ipr_ioafp_query_ioa_cfg;

	अगर (pageC4->cache_cap[0] & IPR_CAP_SYNC_CACHE) अणु
		ipr_build_ioa_service_action(ipr_cmd,
					     cpu_to_be32(IPR_IOA_RES_HANDLE),
					     IPR_IOA_SA_CHANGE_CACHE_PARAMS);

		ioarcb->cmd_pkt.cdb[2] = 0x40;

		ipr_cmd->job_step_failed = ipr_ioa_service_action_failed;
		ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout,
			   IPR_SET_SUP_DEVICE_TIMEOUT);

		LEAVE;
		वापस IPR_RC_JOB_RETURN;
	पूर्ण

	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_ioafp_inquiry - Send an Inquiry to the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 * @flags:	flags to send
 * @page:	page to inquire
 * @dma_addr:	DMA address
 * @xfer_len:	transfer data length
 *
 * This utility function sends an inquiry to the adapter.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_ioafp_inquiry(काष्ठा ipr_cmnd *ipr_cmd, u8 flags, u8 page,
			      dma_addr_t dma_addr, u8 xfer_len)
अणु
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;

	ENTER;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_SCSICDB;
	ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);

	ioarcb->cmd_pkt.cdb[0] = INQUIRY;
	ioarcb->cmd_pkt.cdb[1] = flags;
	ioarcb->cmd_pkt.cdb[2] = page;
	ioarcb->cmd_pkt.cdb[4] = xfer_len;

	ipr_init_ioadl(ipr_cmd, dma_addr, xfer_len, IPR_IOADL_FLAGS_READ_LAST);

	ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout, IPR_INTERNAL_TIMEOUT);
	LEAVE;
पूर्ण

/**
 * ipr_inquiry_page_supported - Is the given inquiry page supported
 * @page0:		inquiry page 0 buffer
 * @page:		page code.
 *
 * This function determines अगर the specअगरied inquiry page is supported.
 *
 * Return value:
 *	1 अगर page is supported / 0 अगर not
 **/
अटल पूर्णांक ipr_inquiry_page_supported(काष्ठा ipr_inquiry_page0 *page0, u8 page)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < min_t(u8, page0->len, IPR_INQUIRY_PAGE0_ENTRIES); i++)
		अगर (page0->page[i] == page)
			वापस 1;

	वापस 0;
पूर्ण

/**
 * ipr_ioafp_pageC4_inquiry - Send a Page 0xC4 Inquiry to the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a Page 0xC4 inquiry to the adapter
 * to retrieve software VPD inक्रमmation.
 *
 * Return value:
 *	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_pageC4_inquiry(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_inquiry_page0 *page0 = &ioa_cfg->vpd_cbs->page0_data;
	काष्ठा ipr_inquiry_pageC4 *pageC4 = &ioa_cfg->vpd_cbs->pageC4_data;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_set_caching_parameters;
	स_रखो(pageC4, 0, माप(*pageC4));

	अगर (ipr_inquiry_page_supported(page0, 0xC4)) अणु
		ipr_ioafp_inquiry(ipr_cmd, 1, 0xC4,
				  (ioa_cfg->vpd_cbs_dma
				   + दुरत्व(काष्ठा ipr_misc_cbs,
					      pageC4_data)),
				  माप(काष्ठा ipr_inquiry_pageC4));
		वापस IPR_RC_JOB_RETURN;
	पूर्ण

	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_ioafp_cap_inquiry - Send a Page 0xD0 Inquiry to the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a Page 0xD0 inquiry to the adapter
 * to retrieve adapter capabilities.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_cap_inquiry(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_inquiry_page0 *page0 = &ioa_cfg->vpd_cbs->page0_data;
	काष्ठा ipr_inquiry_cap *cap = &ioa_cfg->vpd_cbs->cap;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_pageC4_inquiry;
	स_रखो(cap, 0, माप(*cap));

	अगर (ipr_inquiry_page_supported(page0, 0xD0)) अणु
		ipr_ioafp_inquiry(ipr_cmd, 1, 0xD0,
				  ioa_cfg->vpd_cbs_dma + दुरत्व(काष्ठा ipr_misc_cbs, cap),
				  माप(काष्ठा ipr_inquiry_cap));
		वापस IPR_RC_JOB_RETURN;
	पूर्ण

	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_ioafp_page3_inquiry - Send a Page 3 Inquiry to the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a Page 3 inquiry to the adapter
 * to retrieve software VPD inक्रमmation.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_page3_inquiry(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;

	ipr_cmd->job_step = ipr_ioafp_cap_inquiry;

	ipr_ioafp_inquiry(ipr_cmd, 1, 3,
			  ioa_cfg->vpd_cbs_dma + दुरत्व(काष्ठा ipr_misc_cbs, page3_data),
			  माप(काष्ठा ipr_inquiry_page3));

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_ioafp_page0_inquiry - Send a Page 0 Inquiry to the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a Page 0 inquiry to the adapter
 * to retrieve supported inquiry pages.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_page0_inquiry(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	अक्षर type[5];

	ENTER;

	/* Grab the type out of the VPD and store it away */
	स_नकल(type, ioa_cfg->vpd_cbs->ioa_vpd.std_inq_data.vpids.product_id, 4);
	type[4] = '\0';
	ioa_cfg->type = simple_म_से_अदीर्घ((अक्षर *)type, शून्य, 16);

	अगर (ipr_invalid_adapter(ioa_cfg)) अणु
		dev_err(&ioa_cfg->pdev->dev,
			"Adapter not supported in this hardware configuration.\n");

		अगर (!ipr_tesपंचांगode) अणु
			ioa_cfg->reset_retries += IPR_NUM_RESET_RELOAD_RETRIES;
			ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
			list_add_tail(&ipr_cmd->queue,
					&ioa_cfg->hrrq->hrrq_मुक्त_q);
			वापस IPR_RC_JOB_RETURN;
		पूर्ण
	पूर्ण

	ipr_cmd->job_step = ipr_ioafp_page3_inquiry;

	ipr_ioafp_inquiry(ipr_cmd, 1, 0,
			  ioa_cfg->vpd_cbs_dma + दुरत्व(काष्ठा ipr_misc_cbs, page0_data),
			  माप(काष्ठा ipr_inquiry_page0));

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_ioafp_std_inquiry - Send a Standard Inquiry to the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function sends a standard inquiry to the adapter.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_std_inquiry(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_page0_inquiry;

	ipr_ioafp_inquiry(ipr_cmd, 0, 0,
			  ioa_cfg->vpd_cbs_dma + दुरत्व(काष्ठा ipr_misc_cbs, ioa_vpd),
			  माप(काष्ठा ipr_ioa_vpd));

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_ioafp_identअगरy_hrrq - Send Identअगरy Host RRQ.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function send an Identअगरy Host Request Response Queue
 * command to establish the HRRQ with the adapter.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_ioafp_identअगरy_hrrq(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	काष्ठा ipr_hrr_queue *hrrq;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_std_inquiry;
	अगर (ioa_cfg->identअगरy_hrrq_index == 0)
		dev_info(&ioa_cfg->pdev->dev, "Starting IOA initialization sequence.\n");

	अगर (ioa_cfg->identअगरy_hrrq_index < ioa_cfg->hrrq_num) अणु
		hrrq = &ioa_cfg->hrrq[ioa_cfg->identअगरy_hrrq_index];

		ioarcb->cmd_pkt.cdb[0] = IPR_ID_HOST_RR_Q;
		ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);

		ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
		अगर (ioa_cfg->sis64)
			ioarcb->cmd_pkt.cdb[1] = 0x1;

		अगर (ioa_cfg->nvectors == 1)
			ioarcb->cmd_pkt.cdb[1] &= ~IPR_ID_HRRQ_SELE_ENABLE;
		अन्यथा
			ioarcb->cmd_pkt.cdb[1] |= IPR_ID_HRRQ_SELE_ENABLE;

		ioarcb->cmd_pkt.cdb[2] =
			((u64) hrrq->host_rrq_dma >> 24) & 0xff;
		ioarcb->cmd_pkt.cdb[3] =
			((u64) hrrq->host_rrq_dma >> 16) & 0xff;
		ioarcb->cmd_pkt.cdb[4] =
			((u64) hrrq->host_rrq_dma >> 8) & 0xff;
		ioarcb->cmd_pkt.cdb[5] =
			((u64) hrrq->host_rrq_dma) & 0xff;
		ioarcb->cmd_pkt.cdb[7] =
			((माप(u32) * hrrq->size) >> 8) & 0xff;
		ioarcb->cmd_pkt.cdb[8] =
			(माप(u32) * hrrq->size) & 0xff;

		अगर (ioarcb->cmd_pkt.cdb[1] & IPR_ID_HRRQ_SELE_ENABLE)
			ioarcb->cmd_pkt.cdb[9] =
					ioa_cfg->identअगरy_hrrq_index;

		अगर (ioa_cfg->sis64) अणु
			ioarcb->cmd_pkt.cdb[10] =
				((u64) hrrq->host_rrq_dma >> 56) & 0xff;
			ioarcb->cmd_pkt.cdb[11] =
				((u64) hrrq->host_rrq_dma >> 48) & 0xff;
			ioarcb->cmd_pkt.cdb[12] =
				((u64) hrrq->host_rrq_dma >> 40) & 0xff;
			ioarcb->cmd_pkt.cdb[13] =
				((u64) hrrq->host_rrq_dma >> 32) & 0xff;
		पूर्ण

		अगर (ioarcb->cmd_pkt.cdb[1] & IPR_ID_HRRQ_SELE_ENABLE)
			ioarcb->cmd_pkt.cdb[14] =
					ioa_cfg->identअगरy_hrrq_index;

		ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout,
			   IPR_INTERNAL_TIMEOUT);

		अगर (++ioa_cfg->identअगरy_hrrq_index < ioa_cfg->hrrq_num)
			ipr_cmd->job_step = ipr_ioafp_identअगरy_hrrq;

		LEAVE;
		वापस IPR_RC_JOB_RETURN;
	पूर्ण

	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_reset_समयr_करोne - Adapter reset समयr function
 * @t: Timer context used to fetch ipr command काष्ठा
 *
 * Description: This function is used in adapter reset processing
 * क्रम timing events. If the reset_cmd poपूर्णांकer in the IOA
 * config काष्ठा is not this adapter's we are करोing nested
 * resets and fail_all_ops will take care of मुक्तing the
 * command block.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_reset_समयr_करोne(काष्ठा समयr_list *t)
अणु
	काष्ठा ipr_cmnd *ipr_cmd = from_समयr(ipr_cmd, t, समयr);
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	अचिन्हित दीर्घ lock_flags = 0;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	अगर (ioa_cfg->reset_cmd == ipr_cmd) अणु
		list_del(&ipr_cmd->queue);
		ipr_cmd->करोne(ipr_cmd);
	पूर्ण

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
पूर्ण

/**
 * ipr_reset_start_समयr - Start a समयr क्रम adapter reset job
 * @ipr_cmd:	ipr command काष्ठा
 * @समयout:	समयout value
 *
 * Description: This function is used in adapter reset processing
 * क्रम timing events. If the reset_cmd poपूर्णांकer in the IOA
 * config काष्ठा is not this adapter's we are करोing nested
 * resets and fail_all_ops will take care of मुक्तing the
 * command block.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_reset_start_समयr(काष्ठा ipr_cmnd *ipr_cmd,
				  अचिन्हित दीर्घ समयout)
अणु

	ENTER;
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);
	ipr_cmd->करोne = ipr_reset_ioa_job;

	ipr_cmd->समयr.expires = jअगरfies + समयout;
	ipr_cmd->समयr.function = ipr_reset_समयr_करोne;
	add_समयr(&ipr_cmd->समयr);
पूर्ण

/**
 * ipr_init_ioa_mem - Initialize ioa_cfg control block
 * @ioa_cfg:	ioa cfg काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_init_ioa_mem(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा ipr_hrr_queue *hrrq;

	क्रम_each_hrrq(hrrq, ioa_cfg) अणु
		spin_lock(&hrrq->_lock);
		स_रखो(hrrq->host_rrq, 0, माप(u32) * hrrq->size);

		/* Initialize Host RRQ poपूर्णांकers */
		hrrq->hrrq_start = hrrq->host_rrq;
		hrrq->hrrq_end = &hrrq->host_rrq[hrrq->size - 1];
		hrrq->hrrq_curr = hrrq->hrrq_start;
		hrrq->toggle_bit = 1;
		spin_unlock(&hrrq->_lock);
	पूर्ण
	wmb();

	ioa_cfg->identअगरy_hrrq_index = 0;
	अगर (ioa_cfg->hrrq_num == 1)
		atomic_set(&ioa_cfg->hrrq_index, 0);
	अन्यथा
		atomic_set(&ioa_cfg->hrrq_index, 1);

	/* Zero out config table */
	स_रखो(ioa_cfg->u.cfg_table, 0, ioa_cfg->cfg_table_size);
पूर्ण

/**
 * ipr_reset_next_stage - Process IPL stage change based on feedback रेजिस्टर.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_next_stage(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	अचिन्हित दीर्घ stage, stage_समय;
	u32 feedback;
	अस्थिर u32 पूर्णांक_reg;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	u64 maskval = 0;

	feedback = पढ़ोl(ioa_cfg->regs.init_feedback_reg);
	stage = feedback & IPR_IPL_INIT_STAGE_MASK;
	stage_समय = feedback & IPR_IPL_INIT_STAGE_TIME_MASK;

	ipr_dbg("IPL stage = 0x%lx, IPL stage time = %ld\n", stage, stage_समय);

	/* sanity check the stage_समय value */
	अगर (stage_समय == 0)
		stage_समय = IPR_IPL_INIT_DEFAULT_STAGE_TIME;
	अन्यथा अगर (stage_समय < IPR_IPL_INIT_MIN_STAGE_TIME)
		stage_समय = IPR_IPL_INIT_MIN_STAGE_TIME;
	अन्यथा अगर (stage_समय > IPR_LONG_OPERATIONAL_TIMEOUT)
		stage_समय = IPR_LONG_OPERATIONAL_TIMEOUT;

	अगर (stage == IPR_IPL_INIT_STAGE_UNKNOWN) अणु
		ग_लिखोl(IPR_PCII_IPL_STAGE_CHANGE, ioa_cfg->regs.set_पूर्णांकerrupt_mask_reg);
		पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg);
		stage_समय = ioa_cfg->transop_समयout;
		ipr_cmd->job_step = ipr_ioafp_identअगरy_hrrq;
	पूर्ण अन्यथा अगर (stage == IPR_IPL_INIT_STAGE_TRANSOP) अणु
		पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg32);
		अगर (पूर्णांक_reg & IPR_PCII_IOA_TRANS_TO_OPER) अणु
			ipr_cmd->job_step = ipr_ioafp_identअगरy_hrrq;
			maskval = IPR_PCII_IPL_STAGE_CHANGE;
			maskval = (maskval << 32) | IPR_PCII_IOA_TRANS_TO_OPER;
			ग_लिखोq(maskval, ioa_cfg->regs.set_पूर्णांकerrupt_mask_reg);
			पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg);
			वापस IPR_RC_JOB_CONTINUE;
		पूर्ण
	पूर्ण

	ipr_cmd->समयr.expires = jअगरfies + stage_समय * HZ;
	ipr_cmd->समयr.function = ipr_oper_समयout;
	ipr_cmd->करोne = ipr_reset_ioa_job;
	add_समयr(&ipr_cmd->समयr);

	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);

	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_enable_ioa - Enable the IOA following a reset.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function reinitializes some control blocks and
 * enables deकाष्ठाive diagnostics on the adapter.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_enable_ioa(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	अस्थिर u32 पूर्णांक_reg;
	अस्थिर u64 maskval;
	पूर्णांक i;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_identअगरy_hrrq;
	ipr_init_ioa_mem(ioa_cfg);

	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_पूर्णांकerrupts = 1;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	पूर्ण
	अगर (ioa_cfg->sis64) अणु
		/* Set the adapter to the correct endian mode. */
		ग_लिखोl(IPR_ENDIAN_SWAP_KEY, ioa_cfg->regs.endian_swap_reg);
		पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.endian_swap_reg);
	पूर्ण

	पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg32);

	अगर (पूर्णांक_reg & IPR_PCII_IOA_TRANS_TO_OPER) अणु
		ग_लिखोl((IPR_PCII_ERROR_INTERRUPTS | IPR_PCII_HRRQ_UPDATED),
		       ioa_cfg->regs.clr_पूर्णांकerrupt_mask_reg32);
		पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg);
		वापस IPR_RC_JOB_CONTINUE;
	पूर्ण

	/* Enable deकाष्ठाive diagnostics on IOA */
	ग_लिखोl(ioa_cfg->करोorbell, ioa_cfg->regs.set_uproc_पूर्णांकerrupt_reg32);

	अगर (ioa_cfg->sis64) अणु
		maskval = IPR_PCII_IPL_STAGE_CHANGE;
		maskval = (maskval << 32) | IPR_PCII_OPER_INTERRUPTS;
		ग_लिखोq(maskval, ioa_cfg->regs.clr_पूर्णांकerrupt_mask_reg);
	पूर्ण अन्यथा
		ग_लिखोl(IPR_PCII_OPER_INTERRUPTS, ioa_cfg->regs.clr_पूर्णांकerrupt_mask_reg32);

	पूर्णांक_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg);

	dev_info(&ioa_cfg->pdev->dev, "Initializing IOA.\n");

	अगर (ioa_cfg->sis64) अणु
		ipr_cmd->job_step = ipr_reset_next_stage;
		वापस IPR_RC_JOB_CONTINUE;
	पूर्ण

	ipr_cmd->समयr.expires = jअगरfies + (ioa_cfg->transop_समयout * HZ);
	ipr_cmd->समयr.function = ipr_oper_समयout;
	ipr_cmd->करोne = ipr_reset_ioa_job;
	add_समयr(&ipr_cmd->समयr);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_रुको_क्रम_dump - Wait क्रम a dump to समयout.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * This function is invoked when an adapter dump has run out
 * of processing समय.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE
 **/
अटल पूर्णांक ipr_reset_रुको_क्रम_dump(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	अगर (ioa_cfg->sdt_state == GET_DUMP)
		ioa_cfg->sdt_state = WAIT_FOR_DUMP;
	अन्यथा अगर (ioa_cfg->sdt_state == READ_DUMP)
		ioa_cfg->sdt_state = ABORT_DUMP;

	ioa_cfg->dump_समयout = 1;
	ipr_cmd->job_step = ipr_reset_alert;

	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_unit_check_no_data - Log a unit check/no data error log
 * @ioa_cfg:		ioa config काष्ठा
 *
 * Logs an error indicating the adapter unit checked, but क्रम some
 * reason, we were unable to fetch the unit check buffer.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_unit_check_no_data(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	ioa_cfg->errors_logged++;
	dev_err(&ioa_cfg->pdev->dev, "IOA unit check with no data\n");
पूर्ण

/**
 * ipr_get_unit_check_buffer - Get the unit check buffer from the IOA
 * @ioa_cfg:		ioa config काष्ठा
 *
 * Fetches the unit check buffer from the adapter by घड़ीing the data
 * through the mailbox रेजिस्टर.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_get_unit_check_buffer(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	अचिन्हित दीर्घ mailbox;
	काष्ठा ipr_hostrcb *hostrcb;
	काष्ठा ipr_uc_sdt sdt;
	पूर्णांक rc, length;
	u32 ioasc;

	mailbox = पढ़ोl(ioa_cfg->ioa_mailbox);

	अगर (!ioa_cfg->sis64 && !ipr_sdt_is_fmt2(mailbox)) अणु
		ipr_unit_check_no_data(ioa_cfg);
		वापस;
	पूर्ण

	स_रखो(&sdt, 0, माप(काष्ठा ipr_uc_sdt));
	rc = ipr_get_ldump_data_section(ioa_cfg, mailbox, (__be32 *) &sdt,
					(माप(काष्ठा ipr_uc_sdt)) / माप(__be32));

	अगर (rc || !(sdt.entry[0].flags & IPR_SDT_VALID_ENTRY) ||
	    ((be32_to_cpu(sdt.hdr.state) != IPR_FMT3_SDT_READY_TO_USE) &&
	    (be32_to_cpu(sdt.hdr.state) != IPR_FMT2_SDT_READY_TO_USE))) अणु
		ipr_unit_check_no_data(ioa_cfg);
		वापस;
	पूर्ण

	/* Find length of the first sdt entry (UC buffer) */
	अगर (be32_to_cpu(sdt.hdr.state) == IPR_FMT3_SDT_READY_TO_USE)
		length = be32_to_cpu(sdt.entry[0].end_token);
	अन्यथा
		length = (be32_to_cpu(sdt.entry[0].end_token) -
			  be32_to_cpu(sdt.entry[0].start_token)) &
			  IPR_FMT2_MBX_ADDR_MASK;

	hostrcb = list_entry(ioa_cfg->hostrcb_मुक्त_q.next,
			     काष्ठा ipr_hostrcb, queue);
	list_del_init(&hostrcb->queue);
	स_रखो(&hostrcb->hcam, 0, माप(hostrcb->hcam));

	rc = ipr_get_ldump_data_section(ioa_cfg,
					be32_to_cpu(sdt.entry[0].start_token),
					(__be32 *)&hostrcb->hcam,
					min(length, (पूर्णांक)माप(hostrcb->hcam)) / माप(__be32));

	अगर (!rc) अणु
		ipr_handle_log_data(ioa_cfg, hostrcb);
		ioasc = be32_to_cpu(hostrcb->hcam.u.error.fd_ioasc);
		अगर (ioasc == IPR_IOASC_NR_IOA_RESET_REQUIRED &&
		    ioa_cfg->sdt_state == GET_DUMP)
			ioa_cfg->sdt_state = WAIT_FOR_DUMP;
	पूर्ण अन्यथा
		ipr_unit_check_no_data(ioa_cfg);

	list_add_tail(&hostrcb->queue, &ioa_cfg->hostrcb_मुक्त_q);
पूर्ण

/**
 * ipr_reset_get_unit_check_job - Call to get the unit check buffer.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function will call to get the unit check buffer.
 *
 * Return value:
 *	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_get_unit_check_job(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ioa_cfg->ioa_unit_checked = 0;
	ipr_get_unit_check_buffer(ioa_cfg);
	ipr_cmd->job_step = ipr_reset_alert;
	ipr_reset_start_समयr(ipr_cmd, 0);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

अटल पूर्णांक ipr_dump_mailbox_रुको(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;

	अगर (ioa_cfg->sdt_state != GET_DUMP)
		वापस IPR_RC_JOB_RETURN;

	अगर (!ioa_cfg->sis64 || !ipr_cmd->u.समय_left ||
	    (पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg) &
	     IPR_PCII_MAILBOX_STABLE)) अणु

		अगर (!ipr_cmd->u.समय_left)
			dev_err(&ioa_cfg->pdev->dev,
				"Timed out waiting for Mailbox register.\n");

		ioa_cfg->sdt_state = READ_DUMP;
		ioa_cfg->dump_समयout = 0;
		अगर (ioa_cfg->sis64)
			ipr_reset_start_समयr(ipr_cmd, IPR_SIS64_DUMP_TIMEOUT);
		अन्यथा
			ipr_reset_start_समयr(ipr_cmd, IPR_SIS32_DUMP_TIMEOUT);
		ipr_cmd->job_step = ipr_reset_रुको_क्रम_dump;
		schedule_work(&ioa_cfg->work_q);

	पूर्ण अन्यथा अणु
		ipr_cmd->u.समय_left -= IPR_CHECK_FOR_RESET_TIMEOUT;
		ipr_reset_start_समयr(ipr_cmd,
				      IPR_CHECK_FOR_RESET_TIMEOUT);
	पूर्ण

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_restore_cfg_space - Restore PCI config space.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function restores the saved PCI config space of
 * the adapter, fails all outstanding ops back to the callers, and
 * fetches the dump/unit check अगर applicable to this reset.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_restore_cfg_space(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ioa_cfg->pdev->state_saved = true;
	pci_restore_state(ioa_cfg->pdev);

	अगर (ipr_set_pcix_cmd_reg(ioa_cfg)) अणु
		ipr_cmd->s.ioasa.hdr.ioasc = cpu_to_be32(IPR_IOASC_PCI_ACCESS_ERROR);
		वापस IPR_RC_JOB_CONTINUE;
	पूर्ण

	ipr_fail_all_ops(ioa_cfg);

	अगर (ioa_cfg->sis64) अणु
		/* Set the adapter to the correct endian mode. */
		ग_लिखोl(IPR_ENDIAN_SWAP_KEY, ioa_cfg->regs.endian_swap_reg);
		पढ़ोl(ioa_cfg->regs.endian_swap_reg);
	पूर्ण

	अगर (ioa_cfg->ioa_unit_checked) अणु
		अगर (ioa_cfg->sis64) अणु
			ipr_cmd->job_step = ipr_reset_get_unit_check_job;
			ipr_reset_start_समयr(ipr_cmd, IPR_DUMP_DELAY_TIMEOUT);
			वापस IPR_RC_JOB_RETURN;
		पूर्ण अन्यथा अणु
			ioa_cfg->ioa_unit_checked = 0;
			ipr_get_unit_check_buffer(ioa_cfg);
			ipr_cmd->job_step = ipr_reset_alert;
			ipr_reset_start_समयr(ipr_cmd, 0);
			वापस IPR_RC_JOB_RETURN;
		पूर्ण
	पूर्ण

	अगर (ioa_cfg->in_ioa_bringकरोwn) अणु
		ipr_cmd->job_step = ipr_ioa_bringकरोwn_करोne;
	पूर्ण अन्यथा अगर (ioa_cfg->sdt_state == GET_DUMP) अणु
		ipr_cmd->job_step = ipr_dump_mailbox_रुको;
		ipr_cmd->u.समय_left = IPR_WAIT_FOR_MAILBOX;
	पूर्ण अन्यथा अणु
		ipr_cmd->job_step = ipr_reset_enable_ioa;
	पूर्ण

	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_reset_bist_करोne - BIST has completed on the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: Unblock config space and resume the reset process.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE
 **/
अटल पूर्णांक ipr_reset_bist_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	अगर (ioa_cfg->cfg_locked)
		pci_cfg_access_unlock(ioa_cfg->pdev);
	ioa_cfg->cfg_locked = 0;
	ipr_cmd->job_step = ipr_reset_restore_cfg_space;
	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_reset_start_bist - Run BIST on the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function runs BIST on the adapter, then delays 2 seconds.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_start_bist(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	पूर्णांक rc = PCIBIOS_SUCCESSFUL;

	ENTER;
	अगर (ioa_cfg->ipr_chip->bist_method == IPR_MMIO)
		ग_लिखोl(IPR_UPROCI_SIS64_START_BIST,
		       ioa_cfg->regs.set_uproc_पूर्णांकerrupt_reg32);
	अन्यथा
		rc = pci_ग_लिखो_config_byte(ioa_cfg->pdev, PCI_BIST, PCI_BIST_START);

	अगर (rc == PCIBIOS_SUCCESSFUL) अणु
		ipr_cmd->job_step = ipr_reset_bist_करोne;
		ipr_reset_start_समयr(ipr_cmd, IPR_WAIT_FOR_BIST_TIMEOUT);
		rc = IPR_RC_JOB_RETURN;
	पूर्ण अन्यथा अणु
		अगर (ioa_cfg->cfg_locked)
			pci_cfg_access_unlock(ipr_cmd->ioa_cfg->pdev);
		ioa_cfg->cfg_locked = 0;
		ipr_cmd->s.ioasa.hdr.ioasc = cpu_to_be32(IPR_IOASC_PCI_ACCESS_ERROR);
		rc = IPR_RC_JOB_CONTINUE;
	पूर्ण

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_reset_slot_reset_करोne - Clear PCI reset to the adapter
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This clears PCI reset to the adapter and delays two seconds.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_slot_reset_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	ENTER;
	ipr_cmd->job_step = ipr_reset_bist_करोne;
	ipr_reset_start_समयr(ipr_cmd, IPR_WAIT_FOR_BIST_TIMEOUT);
	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_reset_work - Pulse a PCIe fundamental reset
 * @work:	work काष्ठा
 *
 * Description: This pulses warm reset to a slot.
 *
 **/
अटल व्योम ipr_reset_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipr_cmnd *ipr_cmd = container_of(work, काष्ठा ipr_cmnd, work);
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा pci_dev *pdev = ioa_cfg->pdev;
	अचिन्हित दीर्घ lock_flags = 0;

	ENTER;
	pci_set_pcie_reset_state(pdev, pcie_warm_reset);
	msleep(jअगरfies_to_msecs(IPR_PCI_RESET_TIMEOUT));
	pci_set_pcie_reset_state(pdev, pcie_deनिश्चित_reset);

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	अगर (ioa_cfg->reset_cmd == ipr_cmd)
		ipr_reset_ioa_job(ipr_cmd);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	LEAVE;
पूर्ण

/**
 * ipr_reset_slot_reset - Reset the PCI slot of the adapter.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This निश्चितs PCI reset to the adapter.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_slot_reset(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	INIT_WORK(&ipr_cmd->work, ipr_reset_reset_work);
	queue_work(ioa_cfg->reset_work_q, &ipr_cmd->work);
	ipr_cmd->job_step = ipr_reset_slot_reset_करोne;
	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_block_config_access_रुको - Wait क्रम permission to block config access
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This attempts to block config access to the IOA.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_block_config_access_रुको(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	पूर्णांक rc = IPR_RC_JOB_CONTINUE;

	अगर (pci_cfg_access_trylock(ioa_cfg->pdev)) अणु
		ioa_cfg->cfg_locked = 1;
		ipr_cmd->job_step = ioa_cfg->reset;
	पूर्ण अन्यथा अणु
		अगर (ipr_cmd->u.समय_left) अणु
			rc = IPR_RC_JOB_RETURN;
			ipr_cmd->u.समय_left -= IPR_CHECK_FOR_RESET_TIMEOUT;
			ipr_reset_start_समयr(ipr_cmd,
					      IPR_CHECK_FOR_RESET_TIMEOUT);
		पूर्ण अन्यथा अणु
			ipr_cmd->job_step = ioa_cfg->reset;
			dev_err(&ioa_cfg->pdev->dev,
				"Timed out waiting to lock config access. Resetting anyway.\n");
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ipr_reset_block_config_access - Block config access to the IOA
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This attempts to block config access to the IOA
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE
 **/
अटल पूर्णांक ipr_reset_block_config_access(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	ipr_cmd->ioa_cfg->cfg_locked = 0;
	ipr_cmd->job_step = ipr_reset_block_config_access_रुको;
	ipr_cmd->u.समय_left = IPR_WAIT_FOR_RESET_TIMEOUT;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_reset_allowed - Query whether or not IOA can be reset
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	0 अगर reset not allowed / non-zero अगर reset is allowed
 **/
अटल पूर्णांक ipr_reset_allowed(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	अस्थिर u32 temp_reg;

	temp_reg = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg);
	वापस ((temp_reg & IPR_PCII_CRITICAL_OPERATION) == 0);
पूर्ण

/**
 * ipr_reset_रुको_to_start_bist - Wait क्रम permission to reset IOA.
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function रुकोs क्रम adapter permission to run BIST,
 * then runs BIST. If the adapter करोes not give permission after a
 * reasonable समय, we will reset the adapter anyway. The impact of
 * resetting the adapter without warning the adapter is the risk of
 * losing the persistent error log on the adapter. If the adapter is
 * reset जबतक it is writing to the flash on the adapter, the flash
 * segment will have bad ECC and be zeroed.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_रुको_to_start_bist(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	पूर्णांक rc = IPR_RC_JOB_RETURN;

	अगर (!ipr_reset_allowed(ioa_cfg) && ipr_cmd->u.समय_left) अणु
		ipr_cmd->u.समय_left -= IPR_CHECK_FOR_RESET_TIMEOUT;
		ipr_reset_start_समयr(ipr_cmd, IPR_CHECK_FOR_RESET_TIMEOUT);
	पूर्ण अन्यथा अणु
		ipr_cmd->job_step = ipr_reset_block_config_access;
		rc = IPR_RC_JOB_CONTINUE;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ipr_reset_alert - Alert the adapter of a pending reset
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function alerts the adapter that it will be reset.
 * If memory space is not currently enabled, proceed directly
 * to running BIST on the adapter. The समयr must always be started
 * so we guarantee we करो not run BIST from ipr_isr.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_alert(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	u16 cmd_reg;
	पूर्णांक rc;

	ENTER;
	rc = pci_पढ़ो_config_word(ioa_cfg->pdev, PCI_COMMAND, &cmd_reg);

	अगर ((rc == PCIBIOS_SUCCESSFUL) && (cmd_reg & PCI_COMMAND_MEMORY)) अणु
		ipr_mask_and_clear_पूर्णांकerrupts(ioa_cfg, ~0);
		ग_लिखोl(IPR_UPROCI_RESET_ALERT, ioa_cfg->regs.set_uproc_पूर्णांकerrupt_reg32);
		ipr_cmd->job_step = ipr_reset_रुको_to_start_bist;
	पूर्ण अन्यथा अणु
		ipr_cmd->job_step = ipr_reset_block_config_access;
	पूर्ण

	ipr_cmd->u.समय_left = IPR_WAIT_FOR_RESET_TIMEOUT;
	ipr_reset_start_समयr(ipr_cmd, IPR_CHECK_FOR_RESET_TIMEOUT);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_quiesce_करोne - Complete IOA disconnect
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: Freeze the adapter to complete quiesce processing
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE
 **/
अटल पूर्णांक ipr_reset_quiesce_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ipr_cmd->job_step = ipr_ioa_bringकरोwn_करोne;
	ipr_mask_and_clear_पूर्णांकerrupts(ioa_cfg, ~IPR_PCII_IOA_TRANS_TO_OPER);
	LEAVE;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_reset_cancel_hcam_करोne - Check क्रम outstanding commands
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: Ensure nothing is outstanding to the IOA and
 *			proceed with IOA disconnect. Otherwise reset the IOA.
 *
 * Return value:
 * 	IPR_RC_JOB_RETURN / IPR_RC_JOB_CONTINUE
 **/
अटल पूर्णांक ipr_reset_cancel_hcam_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_cmnd *loop_cmd;
	काष्ठा ipr_hrr_queue *hrrq;
	पूर्णांक rc = IPR_RC_JOB_CONTINUE;
	पूर्णांक count = 0;

	ENTER;
	ipr_cmd->job_step = ipr_reset_quiesce_करोne;

	क्रम_each_hrrq(hrrq, ioa_cfg) अणु
		spin_lock(&hrrq->_lock);
		list_क्रम_each_entry(loop_cmd, &hrrq->hrrq_pending_q, queue) अणु
			count++;
			ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
			list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
			rc = IPR_RC_JOB_RETURN;
			अवरोध;
		पूर्ण
		spin_unlock(&hrrq->_lock);

		अगर (count)
			अवरोध;
	पूर्ण

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_reset_cancel_hcam - Cancel outstanding HCAMs
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: Cancel any oustanding HCAMs to the IOA.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_cancel_hcam(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	पूर्णांक rc = IPR_RC_JOB_CONTINUE;
	काष्ठा ipr_cmd_pkt *cmd_pkt;
	काष्ठा ipr_cmnd *hcam_cmd;
	काष्ठा ipr_hrr_queue *hrrq = &ioa_cfg->hrrq[IPR_INIT_HRRQ];

	ENTER;
	ipr_cmd->job_step = ipr_reset_cancel_hcam_करोne;

	अगर (!hrrq->ioa_is_dead) अणु
		अगर (!list_empty(&ioa_cfg->hostrcb_pending_q)) अणु
			list_क्रम_each_entry(hcam_cmd, &hrrq->hrrq_pending_q, queue) अणु
				अगर (hcam_cmd->ioarcb.cmd_pkt.cdb[0] != IPR_HOST_CONTROLLED_ASYNC)
					जारी;

				ipr_cmd->ioarcb.res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
				ipr_cmd->ioarcb.cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
				cmd_pkt = &ipr_cmd->ioarcb.cmd_pkt;
				cmd_pkt->request_type = IPR_RQTYPE_IOACMD;
				cmd_pkt->cdb[0] = IPR_CANCEL_REQUEST;
				cmd_pkt->cdb[1] = IPR_CANCEL_64BIT_IOARCB;
				cmd_pkt->cdb[10] = ((u64) hcam_cmd->dma_addr >> 56) & 0xff;
				cmd_pkt->cdb[11] = ((u64) hcam_cmd->dma_addr >> 48) & 0xff;
				cmd_pkt->cdb[12] = ((u64) hcam_cmd->dma_addr >> 40) & 0xff;
				cmd_pkt->cdb[13] = ((u64) hcam_cmd->dma_addr >> 32) & 0xff;
				cmd_pkt->cdb[2] = ((u64) hcam_cmd->dma_addr >> 24) & 0xff;
				cmd_pkt->cdb[3] = ((u64) hcam_cmd->dma_addr >> 16) & 0xff;
				cmd_pkt->cdb[4] = ((u64) hcam_cmd->dma_addr >> 8) & 0xff;
				cmd_pkt->cdb[5] = ((u64) hcam_cmd->dma_addr) & 0xff;

				ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout,
					   IPR_CANCEL_TIMEOUT);

				rc = IPR_RC_JOB_RETURN;
				ipr_cmd->job_step = ipr_reset_cancel_hcam;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		ipr_cmd->job_step = ipr_reset_alert;

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_reset_ucode_करोwnload_करोne - Microcode करोwnload completion
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function unmaps the microcode करोwnload buffer.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE
 **/
अटल पूर्णांक ipr_reset_ucode_करोwnload_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_sglist *sglist = ioa_cfg->ucode_sglist;

	dma_unmap_sg(&ioa_cfg->pdev->dev, sglist->scatterlist,
		     sglist->num_sg, DMA_TO_DEVICE);

	ipr_cmd->job_step = ipr_reset_alert;
	वापस IPR_RC_JOB_CONTINUE;
पूर्ण

/**
 * ipr_reset_ucode_करोwnload - Download microcode to the adapter
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function checks to see अगर it there is microcode
 * to करोwnload to the adapter. If there is, a करोwnload is perक्रमmed.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_ucode_करोwnload(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	काष्ठा ipr_sglist *sglist = ioa_cfg->ucode_sglist;

	ENTER;
	ipr_cmd->job_step = ipr_reset_alert;

	अगर (!sglist)
		वापस IPR_RC_JOB_CONTINUE;

	ipr_cmd->ioarcb.res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
	ipr_cmd->ioarcb.cmd_pkt.request_type = IPR_RQTYPE_SCSICDB;
	ipr_cmd->ioarcb.cmd_pkt.cdb[0] = WRITE_BUFFER;
	ipr_cmd->ioarcb.cmd_pkt.cdb[1] = IPR_WR_BUF_DOWNLOAD_AND_SAVE;
	ipr_cmd->ioarcb.cmd_pkt.cdb[6] = (sglist->buffer_len & 0xff0000) >> 16;
	ipr_cmd->ioarcb.cmd_pkt.cdb[7] = (sglist->buffer_len & 0x00ff00) >> 8;
	ipr_cmd->ioarcb.cmd_pkt.cdb[8] = sglist->buffer_len & 0x0000ff;

	अगर (ioa_cfg->sis64)
		ipr_build_ucode_ioadl64(ipr_cmd, sglist);
	अन्यथा
		ipr_build_ucode_ioadl(ipr_cmd, sglist);
	ipr_cmd->job_step = ipr_reset_ucode_करोwnload_करोne;

	ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout,
		   IPR_WRITE_BUFFER_TIMEOUT);

	LEAVE;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_reset_shutकरोwn_ioa - Shutकरोwn the adapter
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function issues an adapter shutकरोwn of the
 * specअगरied type to the specअगरied adapter as part of the
 * adapter reset job.
 *
 * Return value:
 * 	IPR_RC_JOB_CONTINUE / IPR_RC_JOB_RETURN
 **/
अटल पूर्णांक ipr_reset_shutकरोwn_ioa(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	क्रमागत ipr_shutकरोwn_type shutकरोwn_type = ipr_cmd->u.shutकरोwn_type;
	अचिन्हित दीर्घ समयout;
	पूर्णांक rc = IPR_RC_JOB_CONTINUE;

	ENTER;
	अगर (shutकरोwn_type == IPR_SHUTDOWN_QUIESCE)
		ipr_cmd->job_step = ipr_reset_cancel_hcam;
	अन्यथा अगर (shutकरोwn_type != IPR_SHUTDOWN_NONE &&
			!ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead) अणु
		ipr_cmd->ioarcb.res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
		ipr_cmd->ioarcb.cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
		ipr_cmd->ioarcb.cmd_pkt.cdb[0] = IPR_IOA_SHUTDOWN;
		ipr_cmd->ioarcb.cmd_pkt.cdb[1] = shutकरोwn_type;

		अगर (shutकरोwn_type == IPR_SHUTDOWN_NORMAL)
			समयout = IPR_SHUTDOWN_TIMEOUT;
		अन्यथा अगर (shutकरोwn_type == IPR_SHUTDOWN_PREPARE_FOR_NORMAL)
			समयout = IPR_INTERNAL_TIMEOUT;
		अन्यथा अगर (ioa_cfg->dual_raid && ipr_dual_ioa_raid)
			समयout = IPR_DUAL_IOA_ABBR_SHUTDOWN_TO;
		अन्यथा
			समयout = IPR_ABBREV_SHUTDOWN_TIMEOUT;

		ipr_करो_req(ipr_cmd, ipr_reset_ioa_job, ipr_समयout, समयout);

		rc = IPR_RC_JOB_RETURN;
		ipr_cmd->job_step = ipr_reset_ucode_करोwnload;
	पूर्ण अन्यथा
		ipr_cmd->job_step = ipr_reset_alert;

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_reset_ioa_job - Adapter reset job
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: This function is the job router क्रम the adapter reset job.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_reset_ioa_job(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	u32 rc, ioasc;
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	करो अणु
		ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

		अगर (ioa_cfg->reset_cmd != ipr_cmd) अणु
			/*
			 * We are करोing nested adapter resets and this is
			 * not the current reset job.
			 */
			list_add_tail(&ipr_cmd->queue,
					&ipr_cmd->hrrq->hrrq_मुक्त_q);
			वापस;
		पूर्ण

		अगर (IPR_IOASC_SENSE_KEY(ioasc)) अणु
			rc = ipr_cmd->job_step_failed(ipr_cmd);
			अगर (rc == IPR_RC_JOB_RETURN)
				वापस;
		पूर्ण

		ipr_reinit_ipr_cmnd(ipr_cmd);
		ipr_cmd->job_step_failed = ipr_reset_cmd_failed;
		rc = ipr_cmd->job_step(ipr_cmd);
	पूर्ण जबतक (rc == IPR_RC_JOB_CONTINUE);
पूर्ण

/**
 * _ipr_initiate_ioa_reset - Initiate an adapter reset
 * @ioa_cfg:		ioa config काष्ठा
 * @job_step:		first job step of reset job
 * @shutकरोwn_type:	shutकरोwn type
 *
 * Description: This function will initiate the reset of the given adapter
 * starting at the selected job step.
 * If the caller needs to रुको on the completion of the reset,
 * the caller must sleep on the reset_रुको_q.
 *
 * Return value:
 * 	none
 **/
अटल व्योम _ipr_initiate_ioa_reset(काष्ठा ipr_ioa_cfg *ioa_cfg,
				    पूर्णांक (*job_step) (काष्ठा ipr_cmnd *),
				    क्रमागत ipr_shutकरोwn_type shutकरोwn_type)
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	पूर्णांक i;

	ioa_cfg->in_reset_reload = 1;
	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_cmds = 0;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	पूर्ण
	wmb();
	अगर (!ioa_cfg->hrrq[IPR_INIT_HRRQ].removing_ioa) अणु
		ioa_cfg->scsi_unblock = 0;
		ioa_cfg->scsi_blocked = 1;
		scsi_block_requests(ioa_cfg->host);
	पूर्ण

	ipr_cmd = ipr_get_मुक्त_ipr_cmnd(ioa_cfg);
	ioa_cfg->reset_cmd = ipr_cmd;
	ipr_cmd->job_step = job_step;
	ipr_cmd->u.shutकरोwn_type = shutकरोwn_type;

	ipr_reset_ioa_job(ipr_cmd);
पूर्ण

/**
 * ipr_initiate_ioa_reset - Initiate an adapter reset
 * @ioa_cfg:		ioa config काष्ठा
 * @shutकरोwn_type:	shutकरोwn type
 *
 * Description: This function will initiate the reset of the given adapter.
 * If the caller needs to रुको on the completion of the reset,
 * the caller must sleep on the reset_रुको_q.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_initiate_ioa_reset(काष्ठा ipr_ioa_cfg *ioa_cfg,
				   क्रमागत ipr_shutकरोwn_type shutकरोwn_type)
अणु
	पूर्णांक i;

	अगर (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead)
		वापस;

	अगर (ioa_cfg->in_reset_reload) अणु
		अगर (ioa_cfg->sdt_state == GET_DUMP)
			ioa_cfg->sdt_state = WAIT_FOR_DUMP;
		अन्यथा अगर (ioa_cfg->sdt_state == READ_DUMP)
			ioa_cfg->sdt_state = ABORT_DUMP;
	पूर्ण

	अगर (ioa_cfg->reset_retries++ >= IPR_NUM_RESET_RELOAD_RETRIES) अणु
		dev_err(&ioa_cfg->pdev->dev,
			"IOA taken offline - error recovery failed\n");

		ioa_cfg->reset_retries = 0;
		क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
			spin_lock(&ioa_cfg->hrrq[i]._lock);
			ioa_cfg->hrrq[i].ioa_is_dead = 1;
			spin_unlock(&ioa_cfg->hrrq[i]._lock);
		पूर्ण
		wmb();

		अगर (ioa_cfg->in_ioa_bringकरोwn) अणु
			ioa_cfg->reset_cmd = शून्य;
			ioa_cfg->in_reset_reload = 0;
			ipr_fail_all_ops(ioa_cfg);
			wake_up_all(&ioa_cfg->reset_रुको_q);

			अगर (!ioa_cfg->hrrq[IPR_INIT_HRRQ].removing_ioa) अणु
				ioa_cfg->scsi_unblock = 1;
				schedule_work(&ioa_cfg->work_q);
			पूर्ण
			वापस;
		पूर्ण अन्यथा अणु
			ioa_cfg->in_ioa_bringकरोwn = 1;
			shutकरोwn_type = IPR_SHUTDOWN_NONE;
		पूर्ण
	पूर्ण

	_ipr_initiate_ioa_reset(ioa_cfg, ipr_reset_shutकरोwn_ioa,
				shutकरोwn_type);
पूर्ण

/**
 * ipr_reset_मुक्तze - Hold off all I/O activity
 * @ipr_cmd:	ipr command काष्ठा
 *
 * Description: If the PCI slot is frozen, hold off all I/O
 * activity; then, as soon as the slot is available again,
 * initiate an adapter reset.
 */
अटल पूर्णांक ipr_reset_मुक्तze(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	पूर्णांक i;

	/* Disallow new पूर्णांकerrupts, aव्योम loop */
	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_पूर्णांकerrupts = 0;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	पूर्ण
	wmb();
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);
	ipr_cmd->करोne = ipr_reset_ioa_job;
	वापस IPR_RC_JOB_RETURN;
पूर्ण

/**
 * ipr_pci_mmio_enabled - Called when MMIO has been re-enabled
 * @pdev:	PCI device काष्ठा
 *
 * Description: This routine is called to tell us that the MMIO
 * access to the IOA has been restored
 */
अटल pci_ers_result_t ipr_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);

	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	अगर (!ioa_cfg->probe_करोne)
		pci_save_state(pdev);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * ipr_pci_frozen - Called when slot has experienced a PCI bus error.
 * @pdev:	PCI device काष्ठा
 *
 * Description: This routine is called to tell us that the PCI bus
 * is करोwn. Can't करो anything here, except put the device driver
 * पूर्णांकo a holding pattern, रुकोing क्रम the PCI bus to come back.
 */
अटल व्योम ipr_pci_frozen(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);

	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	अगर (ioa_cfg->probe_करोne)
		_ipr_initiate_ioa_reset(ioa_cfg, ipr_reset_मुक्तze, IPR_SHUTDOWN_NONE);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
पूर्ण

/**
 * ipr_pci_slot_reset - Called when PCI slot has been reset.
 * @pdev:	PCI device काष्ठा
 *
 * Description: This routine is called by the pci error recovery
 * code after the PCI slot has been reset, just beक्रमe we
 * should resume normal operations.
 */
अटल pci_ers_result_t ipr_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);

	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	अगर (ioa_cfg->probe_करोne) अणु
		अगर (ioa_cfg->needs_warm_reset)
			ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
		अन्यथा
			_ipr_initiate_ioa_reset(ioa_cfg, ipr_reset_restore_cfg_space,
						IPR_SHUTDOWN_NONE);
	पूर्ण अन्यथा
		wake_up_all(&ioa_cfg->eeh_रुको_q);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * ipr_pci_perm_failure - Called when PCI slot is dead क्रम good.
 * @pdev:	PCI device काष्ठा
 *
 * Description: This routine is called when the PCI bus has
 * permanently failed.
 */
अटल व्योम ipr_pci_perm_failure(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);
	पूर्णांक i;

	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	अगर (ioa_cfg->probe_करोne) अणु
		अगर (ioa_cfg->sdt_state == WAIT_FOR_DUMP)
			ioa_cfg->sdt_state = ABORT_DUMP;
		ioa_cfg->reset_retries = IPR_NUM_RESET_RELOAD_RETRIES - 1;
		ioa_cfg->in_ioa_bringकरोwn = 1;
		क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
			spin_lock(&ioa_cfg->hrrq[i]._lock);
			ioa_cfg->hrrq[i].allow_cmds = 0;
			spin_unlock(&ioa_cfg->hrrq[i]._lock);
		पूर्ण
		wmb();
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	पूर्ण अन्यथा
		wake_up_all(&ioa_cfg->eeh_रुको_q);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
पूर्ण

/**
 * ipr_pci_error_detected - Called when a PCI error is detected.
 * @pdev:	PCI device काष्ठा
 * @state:	PCI channel state
 *
 * Description: Called when a PCI error is detected.
 *
 * Return value:
 * 	PCI_ERS_RESULT_NEED_RESET or PCI_ERS_RESULT_DISCONNECT
 */
अटल pci_ers_result_t ipr_pci_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	चयन (state) अणु
	हाल pci_channel_io_frozen:
		ipr_pci_frozen(pdev);
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	हाल pci_channel_io_perm_failure:
		ipr_pci_perm_failure(pdev);
		वापस PCI_ERS_RESULT_DISCONNECT;
	शेष:
		अवरोध;
	पूर्ण
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * ipr_probe_ioa_part2 - Initializes IOAs found in ipr_probe_ioa(..)
 * @ioa_cfg:	ioa cfg काष्ठा
 *
 * Description: This is the second phase of adapter initialization
 * This function takes care of initilizing the adapter to the poपूर्णांक
 * where it can accept new commands.
 * Return value:
 * 	0 on success / -EIO on failure
 **/
अटल पूर्णांक ipr_probe_ioa_part2(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ host_lock_flags = 0;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, host_lock_flags);
	dev_dbg(&ioa_cfg->pdev->dev, "ioa_cfg adx: 0x%p\n", ioa_cfg);
	ioa_cfg->probe_करोne = 1;
	अगर (ioa_cfg->needs_hard_reset) अणु
		ioa_cfg->needs_hard_reset = 0;
		ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
	पूर्ण अन्यथा
		_ipr_initiate_ioa_reset(ioa_cfg, ipr_reset_enable_ioa,
					IPR_SHUTDOWN_NONE);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, host_lock_flags);

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ipr_मुक्त_cmd_blks - Frees command blocks allocated क्रम an adapter
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_मुक्त_cmd_blks(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक i;

	अगर (ioa_cfg->ipr_cmnd_list) अणु
		क्रम (i = 0; i < IPR_NUM_CMD_BLKS; i++) अणु
			अगर (ioa_cfg->ipr_cmnd_list[i])
				dma_pool_मुक्त(ioa_cfg->ipr_cmd_pool,
					      ioa_cfg->ipr_cmnd_list[i],
					      ioa_cfg->ipr_cmnd_list_dma[i]);

			ioa_cfg->ipr_cmnd_list[i] = शून्य;
		पूर्ण
	पूर्ण

	dma_pool_destroy(ioa_cfg->ipr_cmd_pool);

	kमुक्त(ioa_cfg->ipr_cmnd_list);
	kमुक्त(ioa_cfg->ipr_cmnd_list_dma);
	ioa_cfg->ipr_cmnd_list = शून्य;
	ioa_cfg->ipr_cmnd_list_dma = शून्य;
	ioa_cfg->ipr_cmd_pool = शून्य;
पूर्ण

/**
 * ipr_मुक्त_mem - Frees memory allocated क्रम an adapter
 * @ioa_cfg:	ioa cfg काष्ठा
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम ipr_मुक्त_mem(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक i;

	kमुक्त(ioa_cfg->res_entries);
	dma_मुक्त_coherent(&ioa_cfg->pdev->dev, माप(काष्ठा ipr_misc_cbs),
			  ioa_cfg->vpd_cbs, ioa_cfg->vpd_cbs_dma);
	ipr_मुक्त_cmd_blks(ioa_cfg);

	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++)
		dma_मुक्त_coherent(&ioa_cfg->pdev->dev,
				  माप(u32) * ioa_cfg->hrrq[i].size,
				  ioa_cfg->hrrq[i].host_rrq,
				  ioa_cfg->hrrq[i].host_rrq_dma);

	dma_मुक्त_coherent(&ioa_cfg->pdev->dev, ioa_cfg->cfg_table_size,
			  ioa_cfg->u.cfg_table, ioa_cfg->cfg_table_dma);

	क्रम (i = 0; i < IPR_MAX_HCAMS; i++) अणु
		dma_मुक्त_coherent(&ioa_cfg->pdev->dev,
				  माप(काष्ठा ipr_hostrcb),
				  ioa_cfg->hostrcb[i],
				  ioa_cfg->hostrcb_dma[i]);
	पूर्ण

	ipr_मुक्त_dump(ioa_cfg);
	kमुक्त(ioa_cfg->trace);
पूर्ण

/**
 * ipr_मुक्त_irqs - Free all allocated IRQs क्रम the adapter.
 * @ioa_cfg:	ipr cfg काष्ठा
 *
 * This function मुक्तs all allocated IRQs क्रम the
 * specअगरied adapter.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_मुक्त_irqs(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा pci_dev *pdev = ioa_cfg->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < ioa_cfg->nvectors; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), &ioa_cfg->hrrq[i]);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

/**
 * ipr_मुक्त_all_resources - Free all allocated resources क्रम an adapter.
 * @ioa_cfg:	ioa config काष्ठा
 *
 * This function मुक्तs all allocated resources क्रम the
 * specअगरied adapter.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_मुक्त_all_resources(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा pci_dev *pdev = ioa_cfg->pdev;

	ENTER;
	ipr_मुक्त_irqs(ioa_cfg);
	अगर (ioa_cfg->reset_work_q)
		destroy_workqueue(ioa_cfg->reset_work_q);
	iounmap(ioa_cfg->hdw_dma_regs);
	pci_release_regions(pdev);
	ipr_मुक्त_mem(ioa_cfg);
	scsi_host_put(ioa_cfg->host);
	pci_disable_device(pdev);
	LEAVE;
पूर्ण

/**
 * ipr_alloc_cmd_blks - Allocate command blocks क्रम an adapter
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	0 on success / -ENOMEM on allocation failure
 **/
अटल पूर्णांक ipr_alloc_cmd_blks(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioarcb *ioarcb;
	dma_addr_t dma_addr;
	पूर्णांक i, entries_each_hrrq, hrrq_id = 0;

	ioa_cfg->ipr_cmd_pool = dma_pool_create(IPR_NAME, &ioa_cfg->pdev->dev,
						माप(काष्ठा ipr_cmnd), 512, 0);

	अगर (!ioa_cfg->ipr_cmd_pool)
		वापस -ENOMEM;

	ioa_cfg->ipr_cmnd_list = kसुस्मृति(IPR_NUM_CMD_BLKS, माप(काष्ठा ipr_cmnd *), GFP_KERNEL);
	ioa_cfg->ipr_cmnd_list_dma = kसुस्मृति(IPR_NUM_CMD_BLKS, माप(dma_addr_t), GFP_KERNEL);

	अगर (!ioa_cfg->ipr_cmnd_list || !ioa_cfg->ipr_cmnd_list_dma) अणु
		ipr_मुक्त_cmd_blks(ioa_cfg);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		अगर (ioa_cfg->hrrq_num > 1) अणु
			अगर (i == 0) अणु
				entries_each_hrrq = IPR_NUM_INTERNAL_CMD_BLKS;
				ioa_cfg->hrrq[i].min_cmd_id = 0;
				ioa_cfg->hrrq[i].max_cmd_id =
					(entries_each_hrrq - 1);
			पूर्ण अन्यथा अणु
				entries_each_hrrq =
					IPR_NUM_BASE_CMD_BLKS/
					(ioa_cfg->hrrq_num - 1);
				ioa_cfg->hrrq[i].min_cmd_id =
					IPR_NUM_INTERNAL_CMD_BLKS +
					(i - 1) * entries_each_hrrq;
				ioa_cfg->hrrq[i].max_cmd_id =
					(IPR_NUM_INTERNAL_CMD_BLKS +
					i * entries_each_hrrq - 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			entries_each_hrrq = IPR_NUM_CMD_BLKS;
			ioa_cfg->hrrq[i].min_cmd_id = 0;
			ioa_cfg->hrrq[i].max_cmd_id = (entries_each_hrrq - 1);
		पूर्ण
		ioa_cfg->hrrq[i].size = entries_each_hrrq;
	पूर्ण

	BUG_ON(ioa_cfg->hrrq_num == 0);

	i = IPR_NUM_CMD_BLKS -
		ioa_cfg->hrrq[ioa_cfg->hrrq_num - 1].max_cmd_id - 1;
	अगर (i > 0) अणु
		ioa_cfg->hrrq[ioa_cfg->hrrq_num - 1].size += i;
		ioa_cfg->hrrq[ioa_cfg->hrrq_num - 1].max_cmd_id += i;
	पूर्ण

	क्रम (i = 0; i < IPR_NUM_CMD_BLKS; i++) अणु
		ipr_cmd = dma_pool_zalloc(ioa_cfg->ipr_cmd_pool,
				GFP_KERNEL, &dma_addr);

		अगर (!ipr_cmd) अणु
			ipr_मुक्त_cmd_blks(ioa_cfg);
			वापस -ENOMEM;
		पूर्ण

		ioa_cfg->ipr_cmnd_list[i] = ipr_cmd;
		ioa_cfg->ipr_cmnd_list_dma[i] = dma_addr;

		ioarcb = &ipr_cmd->ioarcb;
		ipr_cmd->dma_addr = dma_addr;
		अगर (ioa_cfg->sis64)
			ioarcb->a.ioarcb_host_pci_addr64 = cpu_to_be64(dma_addr);
		अन्यथा
			ioarcb->a.ioarcb_host_pci_addr = cpu_to_be32(dma_addr);

		ioarcb->host_response_handle = cpu_to_be32(i << 2);
		अगर (ioa_cfg->sis64) अणु
			ioarcb->u.sis64_addr_data.data_ioadl_addr =
				cpu_to_be64(dma_addr + दुरत्व(काष्ठा ipr_cmnd, i.ioadl64));
			ioarcb->u.sis64_addr_data.ioasa_host_pci_addr =
				cpu_to_be64(dma_addr + दुरत्व(काष्ठा ipr_cmnd, s.ioasa64));
		पूर्ण अन्यथा अणु
			ioarcb->ग_लिखो_ioadl_addr =
				cpu_to_be32(dma_addr + दुरत्व(काष्ठा ipr_cmnd, i.ioadl));
			ioarcb->पढ़ो_ioadl_addr = ioarcb->ग_लिखो_ioadl_addr;
			ioarcb->ioasa_host_pci_addr =
				cpu_to_be32(dma_addr + दुरत्व(काष्ठा ipr_cmnd, s.ioasa));
		पूर्ण
		ioarcb->ioasa_len = cpu_to_be16(माप(काष्ठा ipr_ioasa));
		ipr_cmd->cmd_index = i;
		ipr_cmd->ioa_cfg = ioa_cfg;
		ipr_cmd->sense_buffer_dma = dma_addr +
			दुरत्व(काष्ठा ipr_cmnd, sense_buffer);

		ipr_cmd->ioarcb.cmd_pkt.hrrq_id = hrrq_id;
		ipr_cmd->hrrq = &ioa_cfg->hrrq[hrrq_id];
		list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
		अगर (i >= ioa_cfg->hrrq[hrrq_id].max_cmd_id)
			hrrq_id++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ipr_alloc_mem - Allocate memory क्रम an adapter
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	0 on success / non-zero क्रम error
 **/
अटल पूर्णांक ipr_alloc_mem(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा pci_dev *pdev = ioa_cfg->pdev;
	पूर्णांक i, rc = -ENOMEM;

	ENTER;
	ioa_cfg->res_entries = kसुस्मृति(ioa_cfg->max_devs_supported,
				       माप(काष्ठा ipr_resource_entry),
				       GFP_KERNEL);

	अगर (!ioa_cfg->res_entries)
		जाओ out;

	क्रम (i = 0; i < ioa_cfg->max_devs_supported; i++) अणु
		list_add_tail(&ioa_cfg->res_entries[i].queue, &ioa_cfg->मुक्त_res_q);
		ioa_cfg->res_entries[i].ioa_cfg = ioa_cfg;
	पूर्ण

	ioa_cfg->vpd_cbs = dma_alloc_coherent(&pdev->dev,
					      माप(काष्ठा ipr_misc_cbs),
					      &ioa_cfg->vpd_cbs_dma,
					      GFP_KERNEL);

	अगर (!ioa_cfg->vpd_cbs)
		जाओ out_मुक्त_res_entries;

	अगर (ipr_alloc_cmd_blks(ioa_cfg))
		जाओ out_मुक्त_vpd_cbs;

	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		ioa_cfg->hrrq[i].host_rrq = dma_alloc_coherent(&pdev->dev,
					माप(u32) * ioa_cfg->hrrq[i].size,
					&ioa_cfg->hrrq[i].host_rrq_dma,
					GFP_KERNEL);

		अगर (!ioa_cfg->hrrq[i].host_rrq)  अणु
			जबतक (--i > 0)
				dma_मुक्त_coherent(&pdev->dev,
					माप(u32) * ioa_cfg->hrrq[i].size,
					ioa_cfg->hrrq[i].host_rrq,
					ioa_cfg->hrrq[i].host_rrq_dma);
			जाओ out_ipr_मुक्त_cmd_blocks;
		पूर्ण
		ioa_cfg->hrrq[i].ioa_cfg = ioa_cfg;
	पूर्ण

	ioa_cfg->u.cfg_table = dma_alloc_coherent(&pdev->dev,
						  ioa_cfg->cfg_table_size,
						  &ioa_cfg->cfg_table_dma,
						  GFP_KERNEL);

	अगर (!ioa_cfg->u.cfg_table)
		जाओ out_मुक्त_host_rrq;

	क्रम (i = 0; i < IPR_MAX_HCAMS; i++) अणु
		ioa_cfg->hostrcb[i] = dma_alloc_coherent(&pdev->dev,
							 माप(काष्ठा ipr_hostrcb),
							 &ioa_cfg->hostrcb_dma[i],
							 GFP_KERNEL);

		अगर (!ioa_cfg->hostrcb[i])
			जाओ out_मुक्त_hostrcb_dma;

		ioa_cfg->hostrcb[i]->hostrcb_dma =
			ioa_cfg->hostrcb_dma[i] + दुरत्व(काष्ठा ipr_hostrcb, hcam);
		ioa_cfg->hostrcb[i]->ioa_cfg = ioa_cfg;
		list_add_tail(&ioa_cfg->hostrcb[i]->queue, &ioa_cfg->hostrcb_मुक्त_q);
	पूर्ण

	ioa_cfg->trace = kसुस्मृति(IPR_NUM_TRACE_ENTRIES,
				 माप(काष्ठा ipr_trace_entry),
				 GFP_KERNEL);

	अगर (!ioa_cfg->trace)
		जाओ out_मुक्त_hostrcb_dma;

	rc = 0;
out:
	LEAVE;
	वापस rc;

out_मुक्त_hostrcb_dma:
	जबतक (i-- > 0) अणु
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा ipr_hostrcb),
				  ioa_cfg->hostrcb[i],
				  ioa_cfg->hostrcb_dma[i]);
	पूर्ण
	dma_मुक्त_coherent(&pdev->dev, ioa_cfg->cfg_table_size,
			  ioa_cfg->u.cfg_table, ioa_cfg->cfg_table_dma);
out_मुक्त_host_rrq:
	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		dma_मुक्त_coherent(&pdev->dev,
				  माप(u32) * ioa_cfg->hrrq[i].size,
				  ioa_cfg->hrrq[i].host_rrq,
				  ioa_cfg->hrrq[i].host_rrq_dma);
	पूर्ण
out_ipr_मुक्त_cmd_blocks:
	ipr_मुक्त_cmd_blks(ioa_cfg);
out_मुक्त_vpd_cbs:
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा ipr_misc_cbs),
			  ioa_cfg->vpd_cbs, ioa_cfg->vpd_cbs_dma);
out_मुक्त_res_entries:
	kमुक्त(ioa_cfg->res_entries);
	जाओ out;
पूर्ण

/**
 * ipr_initialize_bus_attr - Initialize SCSI bus attributes to शेष values
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_initialize_bus_attr(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IPR_MAX_NUM_BUSES; i++) अणु
		ioa_cfg->bus_attr[i].bus = i;
		ioa_cfg->bus_attr[i].qas_enabled = 0;
		ioa_cfg->bus_attr[i].bus_width = IPR_DEFAULT_BUS_WIDTH;
		अगर (ipr_max_speed < ARRAY_SIZE(ipr_max_bus_speeds))
			ioa_cfg->bus_attr[i].max_xfer_rate = ipr_max_bus_speeds[ipr_max_speed];
		अन्यथा
			ioa_cfg->bus_attr[i].max_xfer_rate = IPR_U160_SCSI_RATE;
	पूर्ण
पूर्ण

/**
 * ipr_init_regs - Initialize IOA रेजिस्टरs
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 *	none
 **/
अटल व्योम ipr_init_regs(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	स्थिर काष्ठा ipr_पूर्णांकerrupt_offsets *p;
	काष्ठा ipr_पूर्णांकerrupts *t;
	व्योम __iomem *base;

	p = &ioa_cfg->chip_cfg->regs;
	t = &ioa_cfg->regs;
	base = ioa_cfg->hdw_dma_regs;

	t->set_पूर्णांकerrupt_mask_reg = base + p->set_पूर्णांकerrupt_mask_reg;
	t->clr_पूर्णांकerrupt_mask_reg = base + p->clr_पूर्णांकerrupt_mask_reg;
	t->clr_पूर्णांकerrupt_mask_reg32 = base + p->clr_पूर्णांकerrupt_mask_reg32;
	t->sense_पूर्णांकerrupt_mask_reg = base + p->sense_पूर्णांकerrupt_mask_reg;
	t->sense_पूर्णांकerrupt_mask_reg32 = base + p->sense_पूर्णांकerrupt_mask_reg32;
	t->clr_पूर्णांकerrupt_reg = base + p->clr_पूर्णांकerrupt_reg;
	t->clr_पूर्णांकerrupt_reg32 = base + p->clr_पूर्णांकerrupt_reg32;
	t->sense_पूर्णांकerrupt_reg = base + p->sense_पूर्णांकerrupt_reg;
	t->sense_पूर्णांकerrupt_reg32 = base + p->sense_पूर्णांकerrupt_reg32;
	t->ioarrin_reg = base + p->ioarrin_reg;
	t->sense_uproc_पूर्णांकerrupt_reg = base + p->sense_uproc_पूर्णांकerrupt_reg;
	t->sense_uproc_पूर्णांकerrupt_reg32 = base + p->sense_uproc_पूर्णांकerrupt_reg32;
	t->set_uproc_पूर्णांकerrupt_reg = base + p->set_uproc_पूर्णांकerrupt_reg;
	t->set_uproc_पूर्णांकerrupt_reg32 = base + p->set_uproc_पूर्णांकerrupt_reg32;
	t->clr_uproc_पूर्णांकerrupt_reg = base + p->clr_uproc_पूर्णांकerrupt_reg;
	t->clr_uproc_पूर्णांकerrupt_reg32 = base + p->clr_uproc_पूर्णांकerrupt_reg32;

	अगर (ioa_cfg->sis64) अणु
		t->init_feedback_reg = base + p->init_feedback_reg;
		t->dump_addr_reg = base + p->dump_addr_reg;
		t->dump_data_reg = base + p->dump_data_reg;
		t->endian_swap_reg = base + p->endian_swap_reg;
	पूर्ण
पूर्ण

/**
 * ipr_init_ioa_cfg - Initialize IOA config काष्ठा
 * @ioa_cfg:	ioa config काष्ठा
 * @host:		scsi host काष्ठा
 * @pdev:		PCI dev काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_init_ioa_cfg(काष्ठा ipr_ioa_cfg *ioa_cfg,
			     काष्ठा Scsi_Host *host, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;

	ioa_cfg->host = host;
	ioa_cfg->pdev = pdev;
	ioa_cfg->log_level = ipr_log_level;
	ioa_cfg->करोorbell = IPR_DOORBELL;
	प्र_लिखो(ioa_cfg->eye_catcher, IPR_EYECATCHER);
	प्र_लिखो(ioa_cfg->trace_start, IPR_TRACE_START_LABEL);
	प्र_लिखो(ioa_cfg->cfg_table_start, IPR_CFG_TBL_START);
	प्र_लिखो(ioa_cfg->resource_table_label, IPR_RES_TABLE_LABEL);
	प्र_लिखो(ioa_cfg->ipr_hcam_label, IPR_HCAM_LABEL);
	प्र_लिखो(ioa_cfg->ipr_cmd_label, IPR_CMD_LABEL);

	INIT_LIST_HEAD(&ioa_cfg->hostrcb_मुक्त_q);
	INIT_LIST_HEAD(&ioa_cfg->hostrcb_pending_q);
	INIT_LIST_HEAD(&ioa_cfg->hostrcb_report_q);
	INIT_LIST_HEAD(&ioa_cfg->मुक्त_res_q);
	INIT_LIST_HEAD(&ioa_cfg->used_res_q);
	INIT_WORK(&ioa_cfg->work_q, ipr_worker_thपढ़ो);
	INIT_WORK(&ioa_cfg->scsi_add_work_q, ipr_add_हटाओ_thपढ़ो);
	init_रुकोqueue_head(&ioa_cfg->reset_रुको_q);
	init_रुकोqueue_head(&ioa_cfg->msi_रुको_q);
	init_रुकोqueue_head(&ioa_cfg->eeh_रुको_q);
	ioa_cfg->sdt_state = INACTIVE;

	ipr_initialize_bus_attr(ioa_cfg);
	ioa_cfg->max_devs_supported = ipr_max_devs;

	अगर (ioa_cfg->sis64) अणु
		host->max_channel = IPR_MAX_SIS64_BUSES;
		host->max_id = IPR_MAX_SIS64_TARGETS_PER_BUS;
		host->max_lun = IPR_MAX_SIS64_LUNS_PER_TARGET;
		अगर (ipr_max_devs > IPR_MAX_SIS64_DEVS)
			ioa_cfg->max_devs_supported = IPR_MAX_SIS64_DEVS;
		ioa_cfg->cfg_table_size = (माप(काष्ठा ipr_config_table_hdr64)
					   + ((माप(काष्ठा ipr_config_table_entry64)
					       * ioa_cfg->max_devs_supported)));
	पूर्ण अन्यथा अणु
		host->max_channel = IPR_VSET_BUS;
		host->max_id = IPR_MAX_NUM_TARGETS_PER_BUS;
		host->max_lun = IPR_MAX_NUM_LUNS_PER_TARGET;
		अगर (ipr_max_devs > IPR_MAX_PHYSICAL_DEVS)
			ioa_cfg->max_devs_supported = IPR_MAX_PHYSICAL_DEVS;
		ioa_cfg->cfg_table_size = (माप(काष्ठा ipr_config_table_hdr)
					   + ((माप(काष्ठा ipr_config_table_entry)
					       * ioa_cfg->max_devs_supported)));
	पूर्ण

	host->unique_id = host->host_no;
	host->max_cmd_len = IPR_MAX_CDB_LEN;
	host->can_queue = ioa_cfg->max_cmds;
	pci_set_drvdata(pdev, ioa_cfg);

	क्रम (i = 0; i < ARRAY_SIZE(ioa_cfg->hrrq); i++) अणु
		INIT_LIST_HEAD(&ioa_cfg->hrrq[i].hrrq_मुक्त_q);
		INIT_LIST_HEAD(&ioa_cfg->hrrq[i].hrrq_pending_q);
		spin_lock_init(&ioa_cfg->hrrq[i]._lock);
		अगर (i == 0)
			ioa_cfg->hrrq[i].lock = ioa_cfg->host->host_lock;
		अन्यथा
			ioa_cfg->hrrq[i].lock = &ioa_cfg->hrrq[i]._lock;
	पूर्ण
पूर्ण

/**
 * ipr_get_chip_info - Find adapter chip inक्रमmation
 * @dev_id:		PCI device id काष्ठा
 *
 * Return value:
 * 	ptr to chip inक्रमmation on success / शून्य on failure
 **/
अटल स्थिर काष्ठा ipr_chip_t *
ipr_get_chip_info(स्थिर काष्ठा pci_device_id *dev_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ipr_chip); i++)
		अगर (ipr_chip[i].venकरोr == dev_id->venकरोr &&
		    ipr_chip[i].device == dev_id->device)
			वापस &ipr_chip[i];
	वापस शून्य;
पूर्ण

/**
 * ipr_रुको_क्रम_pci_err_recovery - Wait क्रम any PCI error recovery to complete
 *						during probe समय
 * @ioa_cfg:	ioa config काष्ठा
 *
 * Return value:
 * 	None
 **/
अटल व्योम ipr_रुको_क्रम_pci_err_recovery(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	काष्ठा pci_dev *pdev = ioa_cfg->pdev;

	अगर (pci_channel_offline(pdev)) अणु
		रुको_event_समयout(ioa_cfg->eeh_रुको_q,
				   !pci_channel_offline(pdev),
				   IPR_PCI_ERROR_RECOVERY_TIMEOUT);
		pci_restore_state(pdev);
	पूर्ण
पूर्ण

अटल व्योम name_msi_vectors(काष्ठा ipr_ioa_cfg *ioa_cfg)
अणु
	पूर्णांक vec_idx, n = माप(ioa_cfg->vectors_info[0].desc) - 1;

	क्रम (vec_idx = 0; vec_idx < ioa_cfg->nvectors; vec_idx++) अणु
		snम_लिखो(ioa_cfg->vectors_info[vec_idx].desc, n,
			 "host%d-%d", ioa_cfg->host->host_no, vec_idx);
		ioa_cfg->vectors_info[vec_idx].
			desc[म_माप(ioa_cfg->vectors_info[vec_idx].desc)] = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ipr_request_other_msi_irqs(काष्ठा ipr_ioa_cfg *ioa_cfg,
		काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i, rc;

	क्रम (i = 1; i < ioa_cfg->nvectors; i++) अणु
		rc = request_irq(pci_irq_vector(pdev, i),
			ipr_isr_mhrrq,
			0,
			ioa_cfg->vectors_info[i].desc,
			&ioa_cfg->hrrq[i]);
		अगर (rc) अणु
			जबतक (--i >= 0)
				मुक्त_irq(pci_irq_vector(pdev, i),
					&ioa_cfg->hrrq[i]);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ipr_test_पूर्णांकr - Handle the पूर्णांकerrupt generated in ipr_test_msi().
 * @devp:		PCI device काष्ठा
 * @irq:		IRQ number
 *
 * Description: Simply set the msi_received flag to 1 indicating that
 * Message Signaled Interrupts are supported.
 *
 * Return value:
 * 	0 on success / non-zero on failure
 **/
अटल irqवापस_t ipr_test_पूर्णांकr(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = (काष्ठा ipr_ioa_cfg *)devp;
	अचिन्हित दीर्घ lock_flags = 0;
	irqवापस_t rc = IRQ_HANDLED;

	dev_info(&ioa_cfg->pdev->dev, "Received IRQ : %d\n", irq);
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	ioa_cfg->msi_received = 1;
	wake_up(&ioa_cfg->msi_रुको_q);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	वापस rc;
पूर्ण

/**
 * ipr_test_msi - Test क्रम Message Signaled Interrupt (MSI) support.
 * @ioa_cfg:		ioa config काष्ठा
 * @pdev:		PCI device काष्ठा
 *
 * Description: This routine sets up and initiates a test पूर्णांकerrupt to determine
 * अगर the पूर्णांकerrupt is received via the ipr_test_पूर्णांकr() service routine.
 * If the tests fails, the driver will fall back to LSI.
 *
 * Return value:
 * 	0 on success / non-zero on failure
 **/
अटल पूर्णांक ipr_test_msi(काष्ठा ipr_ioa_cfg *ioa_cfg, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ lock_flags = 0;
	पूर्णांक irq = pci_irq_vector(pdev, 0);

	ENTER;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	init_रुकोqueue_head(&ioa_cfg->msi_रुको_q);
	ioa_cfg->msi_received = 0;
	ipr_mask_and_clear_पूर्णांकerrupts(ioa_cfg, ~IPR_PCII_IOA_TRANS_TO_OPER);
	ग_लिखोl(IPR_PCII_IO_DEBUG_ACKNOWLEDGE, ioa_cfg->regs.clr_पूर्णांकerrupt_mask_reg32);
	पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	rc = request_irq(irq, ipr_test_पूर्णांकr, 0, IPR_NAME, ioa_cfg);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Can not assign irq %d\n", irq);
		वापस rc;
	पूर्ण अन्यथा अगर (ipr_debug)
		dev_info(&pdev->dev, "IRQ assigned: %d\n", irq);

	ग_लिखोl(IPR_PCII_IO_DEBUG_ACKNOWLEDGE, ioa_cfg->regs.sense_पूर्णांकerrupt_reg32);
	पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg);
	रुको_event_समयout(ioa_cfg->msi_रुको_q, ioa_cfg->msi_received, HZ);
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ipr_mask_and_clear_पूर्णांकerrupts(ioa_cfg, ~IPR_PCII_IOA_TRANS_TO_OPER);

	अगर (!ioa_cfg->msi_received) अणु
		/* MSI test failed */
		dev_info(&pdev->dev, "MSI test failed.  Falling back to LSI.\n");
		rc = -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (ipr_debug)
		dev_info(&pdev->dev, "MSI test succeeded.\n");

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	मुक्त_irq(irq, ioa_cfg);

	LEAVE;

	वापस rc;
पूर्ण

 /* ipr_probe_ioa - Allocates memory and करोes first stage of initialization
 * @pdev:		PCI device काष्ठा
 * @dev_id:		PCI device id काष्ठा
 *
 * Return value:
 * 	0 on success / non-zero on failure
 **/
अटल पूर्णांक ipr_probe_ioa(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	काष्ठा Scsi_Host *host;
	अचिन्हित दीर्घ ipr_regs_pci;
	व्योम __iomem *ipr_regs;
	पूर्णांक rc = PCIBIOS_SUCCESSFUL;
	अस्थिर u32 mask, uproc, पूर्णांकerrupts;
	अचिन्हित दीर्घ lock_flags, driver_lock_flags;
	अचिन्हित पूर्णांक irq_flag;

	ENTER;

	dev_info(&pdev->dev, "Found IOA with IRQ: %d\n", pdev->irq);
	host = scsi_host_alloc(&driver_ढाँचा, माप(*ioa_cfg));

	अगर (!host) अणु
		dev_err(&pdev->dev, "call to scsi_host_alloc failed!\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	ioa_cfg = (काष्ठा ipr_ioa_cfg *)host->hostdata;
	स_रखो(ioa_cfg, 0, माप(काष्ठा ipr_ioa_cfg));
	ata_host_init(&ioa_cfg->ata_host, &pdev->dev, &ipr_sata_ops);

	ioa_cfg->ipr_chip = ipr_get_chip_info(dev_id);

	अगर (!ioa_cfg->ipr_chip) अणु
		dev_err(&pdev->dev, "Unknown adapter chipset 0x%04X 0x%04X\n",
			dev_id->venकरोr, dev_id->device);
		जाओ out_scsi_host_put;
	पूर्ण

	/* set SIS 32 or SIS 64 */
	ioa_cfg->sis64 = ioa_cfg->ipr_chip->sis_type == IPR_SIS64 ? 1 : 0;
	ioa_cfg->chip_cfg = ioa_cfg->ipr_chip->cfg;
	ioa_cfg->clear_isr = ioa_cfg->chip_cfg->clear_isr;
	ioa_cfg->max_cmds = ioa_cfg->chip_cfg->max_cmds;

	अगर (ipr_transop_समयout)
		ioa_cfg->transop_समयout = ipr_transop_समयout;
	अन्यथा अगर (dev_id->driver_data & IPR_USE_LONG_TRANSOP_TIMEOUT)
		ioa_cfg->transop_समयout = IPR_LONG_OPERATIONAL_TIMEOUT;
	अन्यथा
		ioa_cfg->transop_समयout = IPR_OPERATIONAL_TIMEOUT;

	ioa_cfg->revid = pdev->revision;

	ipr_init_ioa_cfg(ioa_cfg, host, pdev);

	ipr_regs_pci = pci_resource_start(pdev, 0);

	rc = pci_request_regions(pdev, IPR_NAME);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev,
			"Couldn't register memory range of registers\n");
		जाओ out_scsi_host_put;
	पूर्ण

	rc = pci_enable_device(pdev);

	अगर (rc || pci_channel_offline(pdev)) अणु
		अगर (pci_channel_offline(pdev)) अणु
			ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);
			rc = pci_enable_device(pdev);
		पूर्ण

		अगर (rc) अणु
			dev_err(&pdev->dev, "Cannot enable adapter\n");
			ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);
			जाओ out_release_regions;
		पूर्ण
	पूर्ण

	ipr_regs = pci_ioremap_bar(pdev, 0);

	अगर (!ipr_regs) अणु
		dev_err(&pdev->dev,
			"Couldn't map memory range of registers\n");
		rc = -ENOMEM;
		जाओ out_disable;
	पूर्ण

	ioa_cfg->hdw_dma_regs = ipr_regs;
	ioa_cfg->hdw_dma_regs_pci = ipr_regs_pci;
	ioa_cfg->ioa_mailbox = ioa_cfg->chip_cfg->mailbox + ipr_regs;

	ipr_init_regs(ioa_cfg);

	अगर (ioa_cfg->sis64) अणु
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
		अगर (rc < 0) अणु
			dev_dbg(&pdev->dev, "Failed to set 64 bit DMA mask\n");
			rc = dma_set_mask_and_coherent(&pdev->dev,
						       DMA_BIT_MASK(32));
		पूर्ण
	पूर्ण अन्यथा
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));

	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Failed to set DMA mask\n");
		जाओ cleanup_nomem;
	पूर्ण

	rc = pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE,
				   ioa_cfg->chip_cfg->cache_line_size);

	अगर (rc != PCIBIOS_SUCCESSFUL) अणु
		dev_err(&pdev->dev, "Write of cache line size failed\n");
		ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);
		rc = -EIO;
		जाओ cleanup_nomem;
	पूर्ण

	/* Issue MMIO पढ़ो to ensure card is not in EEH */
	पूर्णांकerrupts = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg);
	ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);

	अगर (ipr_number_of_msix > IPR_MAX_MSIX_VECTORS) अणु
		dev_err(&pdev->dev, "The max number of MSIX is %d\n",
			IPR_MAX_MSIX_VECTORS);
		ipr_number_of_msix = IPR_MAX_MSIX_VECTORS;
	पूर्ण

	irq_flag = PCI_IRQ_LEGACY;
	अगर (ioa_cfg->ipr_chip->has_msi)
		irq_flag |= PCI_IRQ_MSI | PCI_IRQ_MSIX;
	rc = pci_alloc_irq_vectors(pdev, 1, ipr_number_of_msix, irq_flag);
	अगर (rc < 0) अणु
		ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);
		जाओ cleanup_nomem;
	पूर्ण
	ioa_cfg->nvectors = rc;

	अगर (!pdev->msi_enabled && !pdev->msix_enabled)
		ioa_cfg->clear_isr = 1;

	pci_set_master(pdev);

	अगर (pci_channel_offline(pdev)) अणु
		ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);
		pci_set_master(pdev);
		अगर (pci_channel_offline(pdev)) अणु
			rc = -EIO;
			जाओ out_msi_disable;
		पूर्ण
	पूर्ण

	अगर (pdev->msi_enabled || pdev->msix_enabled) अणु
		rc = ipr_test_msi(ioa_cfg, pdev);
		चयन (rc) अणु
		हाल 0:
			dev_info(&pdev->dev,
				"Request for %d MSI%ss succeeded.", ioa_cfg->nvectors,
				pdev->msix_enabled ? "-X" : "");
			अवरोध;
		हाल -EOPNOTSUPP:
			ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);
			pci_मुक्त_irq_vectors(pdev);

			ioa_cfg->nvectors = 1;
			ioa_cfg->clear_isr = 1;
			अवरोध;
		शेष:
			जाओ out_msi_disable;
		पूर्ण
	पूर्ण

	ioa_cfg->hrrq_num = min3(ioa_cfg->nvectors,
				(अचिन्हित पूर्णांक)num_online_cpus(),
				(अचिन्हित पूर्णांक)IPR_MAX_HRRQ_NUM);

	अगर ((rc = ipr_save_pcix_cmd_reg(ioa_cfg)))
		जाओ out_msi_disable;

	अगर ((rc = ipr_set_pcix_cmd_reg(ioa_cfg)))
		जाओ out_msi_disable;

	rc = ipr_alloc_mem(ioa_cfg);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev,
			"Couldn't allocate enough memory for device driver!\n");
		जाओ out_msi_disable;
	पूर्ण

	/* Save away PCI config space क्रम use following IOA reset */
	rc = pci_save_state(pdev);

	अगर (rc != PCIBIOS_SUCCESSFUL) अणु
		dev_err(&pdev->dev, "Failed to save PCI config space\n");
		rc = -EIO;
		जाओ cleanup_nolog;
	पूर्ण

	/*
	 * If HRRQ updated पूर्णांकerrupt is not masked, or reset alert is set,
	 * the card is in an unknown state and needs a hard reset
	 */
	mask = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_mask_reg32);
	पूर्णांकerrupts = पढ़ोl(ioa_cfg->regs.sense_पूर्णांकerrupt_reg32);
	uproc = पढ़ोl(ioa_cfg->regs.sense_uproc_पूर्णांकerrupt_reg32);
	अगर ((mask & IPR_PCII_HRRQ_UPDATED) == 0 || (uproc & IPR_UPROCI_RESET_ALERT))
		ioa_cfg->needs_hard_reset = 1;
	अगर ((पूर्णांकerrupts & IPR_PCII_ERROR_INTERRUPTS) || reset_devices)
		ioa_cfg->needs_hard_reset = 1;
	अगर (पूर्णांकerrupts & IPR_PCII_IOA_UNIT_CHECKED)
		ioa_cfg->ioa_unit_checked = 1;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ipr_mask_and_clear_पूर्णांकerrupts(ioa_cfg, ~IPR_PCII_IOA_TRANS_TO_OPER);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	अगर (pdev->msi_enabled || pdev->msix_enabled) अणु
		name_msi_vectors(ioa_cfg);
		rc = request_irq(pci_irq_vector(pdev, 0), ipr_isr, 0,
			ioa_cfg->vectors_info[0].desc,
			&ioa_cfg->hrrq[0]);
		अगर (!rc)
			rc = ipr_request_other_msi_irqs(ioa_cfg, pdev);
	पूर्ण अन्यथा अणु
		rc = request_irq(pdev->irq, ipr_isr,
			 IRQF_SHARED,
			 IPR_NAME, &ioa_cfg->hrrq[0]);
	पूर्ण
	अगर (rc) अणु
		dev_err(&pdev->dev, "Couldn't register IRQ %d! rc=%d\n",
			pdev->irq, rc);
		जाओ cleanup_nolog;
	पूर्ण

	अगर ((dev_id->driver_data & IPR_USE_PCI_WARM_RESET) ||
	    (dev_id->device == PCI_DEVICE_ID_IBM_OBSIDIAN_E && !ioa_cfg->revid)) अणु
		ioa_cfg->needs_warm_reset = 1;
		ioa_cfg->reset = ipr_reset_slot_reset;

		ioa_cfg->reset_work_q = alloc_ordered_workqueue("ipr_reset_%d",
								WQ_MEM_RECLAIM, host->host_no);

		अगर (!ioa_cfg->reset_work_q) अणु
			dev_err(&pdev->dev, "Couldn't register reset workqueue\n");
			rc = -ENOMEM;
			जाओ out_मुक्त_irq;
		पूर्ण
	पूर्ण अन्यथा
		ioa_cfg->reset = ipr_reset_start_bist;

	spin_lock_irqsave(&ipr_driver_lock, driver_lock_flags);
	list_add_tail(&ioa_cfg->queue, &ipr_ioa_head);
	spin_unlock_irqrestore(&ipr_driver_lock, driver_lock_flags);

	LEAVE;
out:
	वापस rc;

out_मुक्त_irq:
	ipr_मुक्त_irqs(ioa_cfg);
cleanup_nolog:
	ipr_मुक्त_mem(ioa_cfg);
out_msi_disable:
	ipr_रुको_क्रम_pci_err_recovery(ioa_cfg);
	pci_मुक्त_irq_vectors(pdev);
cleanup_nomem:
	iounmap(ipr_regs);
out_disable:
	pci_disable_device(pdev);
out_release_regions:
	pci_release_regions(pdev);
out_scsi_host_put:
	scsi_host_put(host);
	जाओ out;
पूर्ण

/**
 * ipr_initiate_ioa_bringकरोwn - Bring करोwn an adapter
 * @ioa_cfg:		ioa config काष्ठा
 * @shutकरोwn_type:	shutकरोwn type
 *
 * Description: This function will initiate bringing करोwn the adapter.
 * This consists of issuing an IOA shutकरोwn to the adapter
 * to flush the cache, and running BIST.
 * If the caller needs to रुको on the completion of the reset,
 * the caller must sleep on the reset_रुको_q.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_initiate_ioa_bringकरोwn(काष्ठा ipr_ioa_cfg *ioa_cfg,
				       क्रमागत ipr_shutकरोwn_type shutकरोwn_type)
अणु
	ENTER;
	अगर (ioa_cfg->sdt_state == WAIT_FOR_DUMP)
		ioa_cfg->sdt_state = ABORT_DUMP;
	ioa_cfg->reset_retries = 0;
	ioa_cfg->in_ioa_bringकरोwn = 1;
	ipr_initiate_ioa_reset(ioa_cfg, shutकरोwn_type);
	LEAVE;
पूर्ण

/**
 * __ipr_हटाओ - Remove a single adapter
 * @pdev:	pci device काष्ठा
 *
 * Adapter hot plug हटाओ entry poपूर्णांक.
 *
 * Return value:
 * 	none
 **/
अटल व्योम __ipr_हटाओ(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ host_lock_flags = 0;
	काष्ठा ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);
	पूर्णांक i;
	अचिन्हित दीर्घ driver_lock_flags;
	ENTER;

	spin_lock_irqsave(ioa_cfg->host->host_lock, host_lock_flags);
	जबतक (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, host_lock_flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, host_lock_flags);
	पूर्ण

	क्रम (i = 0; i < ioa_cfg->hrrq_num; i++) अणु
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].removing_ioa = 1;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	पूर्ण
	wmb();
	ipr_initiate_ioa_bringकरोwn(ioa_cfg, IPR_SHUTDOWN_NORMAL);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, host_lock_flags);
	रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
	flush_work(&ioa_cfg->work_q);
	अगर (ioa_cfg->reset_work_q)
		flush_workqueue(ioa_cfg->reset_work_q);
	INIT_LIST_HEAD(&ioa_cfg->used_res_q);
	spin_lock_irqsave(ioa_cfg->host->host_lock, host_lock_flags);

	spin_lock_irqsave(&ipr_driver_lock, driver_lock_flags);
	list_del(&ioa_cfg->queue);
	spin_unlock_irqrestore(&ipr_driver_lock, driver_lock_flags);

	अगर (ioa_cfg->sdt_state == ABORT_DUMP)
		ioa_cfg->sdt_state = WAIT_FOR_DUMP;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, host_lock_flags);

	ipr_मुक्त_all_resources(ioa_cfg);

	LEAVE;
पूर्ण

/**
 * ipr_हटाओ - IOA hot plug हटाओ entry poपूर्णांक
 * @pdev:	pci device काष्ठा
 *
 * Adapter hot plug हटाओ entry poपूर्णांक.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);

	ENTER;

	ipr_हटाओ_trace_file(&ioa_cfg->host->shost_dev.kobj,
			      &ipr_trace_attr);
	ipr_हटाओ_dump_file(&ioa_cfg->host->shost_dev.kobj,
			     &ipr_dump_attr);
	sysfs_हटाओ_bin_file(&ioa_cfg->host->shost_dev.kobj,
			&ipr_ioa_async_err_log);
	scsi_हटाओ_host(ioa_cfg->host);

	__ipr_हटाओ(pdev);

	LEAVE;
पूर्ण

/**
 * ipr_probe - Adapter hot plug add entry poपूर्णांक
 * @pdev:	pci device काष्ठा
 * @dev_id:	pci device ID
 *
 * Return value:
 * 	0 on success / non-zero on failure
 **/
अटल पूर्णांक ipr_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc, i;

	rc = ipr_probe_ioa(pdev, dev_id);

	अगर (rc)
		वापस rc;

	ioa_cfg = pci_get_drvdata(pdev);
	rc = ipr_probe_ioa_part2(ioa_cfg);

	अगर (rc) अणु
		__ipr_हटाओ(pdev);
		वापस rc;
	पूर्ण

	rc = scsi_add_host(ioa_cfg->host, &pdev->dev);

	अगर (rc) अणु
		__ipr_हटाओ(pdev);
		वापस rc;
	पूर्ण

	rc = ipr_create_trace_file(&ioa_cfg->host->shost_dev.kobj,
				   &ipr_trace_attr);

	अगर (rc) अणु
		scsi_हटाओ_host(ioa_cfg->host);
		__ipr_हटाओ(pdev);
		वापस rc;
	पूर्ण

	rc = sysfs_create_bin_file(&ioa_cfg->host->shost_dev.kobj,
			&ipr_ioa_async_err_log);

	अगर (rc) अणु
		ipr_हटाओ_dump_file(&ioa_cfg->host->shost_dev.kobj,
				&ipr_dump_attr);
		ipr_हटाओ_trace_file(&ioa_cfg->host->shost_dev.kobj,
				&ipr_trace_attr);
		scsi_हटाओ_host(ioa_cfg->host);
		__ipr_हटाओ(pdev);
		वापस rc;
	पूर्ण

	rc = ipr_create_dump_file(&ioa_cfg->host->shost_dev.kobj,
				   &ipr_dump_attr);

	अगर (rc) अणु
		sysfs_हटाओ_bin_file(&ioa_cfg->host->shost_dev.kobj,
				      &ipr_ioa_async_err_log);
		ipr_हटाओ_trace_file(&ioa_cfg->host->shost_dev.kobj,
				      &ipr_trace_attr);
		scsi_हटाओ_host(ioa_cfg->host);
		__ipr_हटाओ(pdev);
		वापस rc;
	पूर्ण
	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	ioa_cfg->scan_enabled = 1;
	schedule_work(&ioa_cfg->work_q);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);

	ioa_cfg->iopoll_weight = ioa_cfg->chip_cfg->iopoll_weight;

	अगर (ioa_cfg->iopoll_weight && ioa_cfg->sis64 && ioa_cfg->nvectors > 1) अणु
		क्रम (i = 1; i < ioa_cfg->hrrq_num; i++) अणु
			irq_poll_init(&ioa_cfg->hrrq[i].iopoll,
					ioa_cfg->iopoll_weight, ipr_iopoll);
		पूर्ण
	पूर्ण

	scsi_scan_host(ioa_cfg->host);

	वापस 0;
पूर्ण

/**
 * ipr_shutकरोwn - Shutकरोwn handler.
 * @pdev:	pci device काष्ठा
 *
 * This function is invoked upon प्रणाली shutकरोwn/reboot. It will issue
 * an adapter shutकरोwn to the adapter to flush the ग_लिखो cache.
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ lock_flags = 0;
	क्रमागत ipr_shutकरोwn_type shutकरोwn_type = IPR_SHUTDOWN_NORMAL;
	पूर्णांक i;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	अगर (ioa_cfg->iopoll_weight && ioa_cfg->sis64 && ioa_cfg->nvectors > 1) अणु
		ioa_cfg->iopoll_weight = 0;
		क्रम (i = 1; i < ioa_cfg->hrrq_num; i++)
			irq_poll_disable(&ioa_cfg->hrrq[i].iopoll);
	पूर्ण

	जबतक (ioa_cfg->in_reset_reload) अणु
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	पूर्ण

	अगर (ipr_fast_reboot && प्रणाली_state == SYSTEM_RESTART && ioa_cfg->sis64)
		shutकरोwn_type = IPR_SHUTDOWN_QUIESCE;

	ipr_initiate_ioa_bringकरोwn(ioa_cfg, shutकरोwn_type);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	रुको_event(ioa_cfg->reset_रुको_q, !ioa_cfg->in_reset_reload);
	अगर (ipr_fast_reboot && प्रणाली_state == SYSTEM_RESTART && ioa_cfg->sis64) अणु
		ipr_मुक्त_irqs(ioa_cfg);
		pci_disable_device(ioa_cfg->pdev);
	पूर्ण
पूर्ण

अटल काष्ठा pci_device_id ipr_pci_table[] = अणु
	अणु PCI_VENDOR_ID_MYLEX, PCI_DEVICE_ID_IBM_GEMSTONE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_5702, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_MYLEX, PCI_DEVICE_ID_IBM_GEMSTONE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_5703, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_MYLEX, PCI_DEVICE_ID_IBM_GEMSTONE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_573D, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_MYLEX, PCI_DEVICE_ID_IBM_GEMSTONE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_573E, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CITRINE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_571B, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CITRINE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_572E, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CITRINE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_571A, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CITRINE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_575B, 0, 0,
		IPR_USE_LONG_TRANSOP_TIMEOUT पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_OBSIDIAN,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_572A, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_OBSIDIAN,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_572B, 0, 0,
	      IPR_USE_LONG_TRANSOP_TIMEOUT पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_OBSIDIAN,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_575C, 0, 0,
	      IPR_USE_LONG_TRANSOP_TIMEOUT पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_572A, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_572B, 0, 0,
	      IPR_USE_LONG_TRANSOP_TIMEOUTपूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_575C, 0, 0,
	      IPR_USE_LONG_TRANSOP_TIMEOUT पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN_E,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_574E, 0, 0,
	      IPR_USE_LONG_TRANSOP_TIMEOUT पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN_E,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57B3, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN_E,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57CC, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN_E,
	      PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57B7, 0, 0,
	      IPR_USE_LONG_TRANSOP_TIMEOUT | IPR_USE_PCI_WARM_RESET पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_SNIPE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_2780, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_SCAMP,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_571E, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_SCAMP,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_571F, 0, 0,
		IPR_USE_LONG_TRANSOP_TIMEOUT पूर्ण,
	अणु PCI_VENDOR_ID_ADAPTEC2, PCI_DEVICE_ID_ADAPTEC2_SCAMP,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_572F, 0, 0,
		IPR_USE_LONG_TRANSOP_TIMEOUT पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROC_FPGA_E2,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57B5, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROC_FPGA_E2,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_574D, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROC_FPGA_E2,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57B2, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROC_FPGA_E2,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57C0, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROC_FPGA_E2,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57C3, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROC_FPGA_E2,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57C4, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57B4, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57B1, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57C6, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57C8, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57CE, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57D5, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57D6, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57D7, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57D8, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57D9, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57DA, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57EB, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57EC, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57ED, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57EE, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57EF, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_57F0, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_2CCA, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_2CD2, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CROCODILE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_2CCD, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_RATTLESNAKE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_580A, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_RATTLESNAKE,
		PCI_VENDOR_ID_IBM, IPR_SUBS_DEV_ID_580B, 0, 0, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ipr_pci_table);

अटल स्थिर काष्ठा pci_error_handlers ipr_err_handler = अणु
	.error_detected = ipr_pci_error_detected,
	.mmio_enabled = ipr_pci_mmio_enabled,
	.slot_reset = ipr_pci_slot_reset,
पूर्ण;

अटल काष्ठा pci_driver ipr_driver = अणु
	.name = IPR_NAME,
	.id_table = ipr_pci_table,
	.probe = ipr_probe,
	.हटाओ = ipr_हटाओ,
	.shutकरोwn = ipr_shutकरोwn,
	.err_handler = &ipr_err_handler,
पूर्ण;

/**
 * ipr_halt_करोne - Shutकरोwn prepare completion
 * @ipr_cmd:   ipr command काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ipr_halt_करोne(काष्ठा ipr_cmnd *ipr_cmd)
अणु
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_मुक्त_q);
पूर्ण

/**
 * ipr_halt - Issue shutकरोwn prepare to all adapters
 * @nb: Notअगरier block
 * @event: Notअगरier event
 * @buf: Notअगरier data (unused)
 *
 * Return value:
 * 	NOTIFY_OK on success / NOTIFY_DONE on failure
 **/
अटल पूर्णांक ipr_halt(काष्ठा notअगरier_block *nb, uदीर्घ event, व्योम *buf)
अणु
	काष्ठा ipr_cmnd *ipr_cmd;
	काष्ठा ipr_ioa_cfg *ioa_cfg;
	अचिन्हित दीर्घ flags = 0, driver_lock_flags;

	अगर (event != SYS_RESTART && event != SYS_HALT && event != SYS_POWER_OFF)
		वापस NOTIFY_DONE;

	spin_lock_irqsave(&ipr_driver_lock, driver_lock_flags);

	list_क्रम_each_entry(ioa_cfg, &ipr_ioa_head, queue) अणु
		spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
		अगर (!ioa_cfg->hrrq[IPR_INIT_HRRQ].allow_cmds ||
		    (ipr_fast_reboot && event == SYS_RESTART && ioa_cfg->sis64)) अणु
			spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
			जारी;
		पूर्ण

		ipr_cmd = ipr_get_मुक्त_ipr_cmnd(ioa_cfg);
		ipr_cmd->ioarcb.res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
		ipr_cmd->ioarcb.cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
		ipr_cmd->ioarcb.cmd_pkt.cdb[0] = IPR_IOA_SHUTDOWN;
		ipr_cmd->ioarcb.cmd_pkt.cdb[1] = IPR_SHUTDOWN_PREPARE_FOR_NORMAL;

		ipr_करो_req(ipr_cmd, ipr_halt_करोne, ipr_समयout, IPR_DEVICE_RESET_TIMEOUT);
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ipr_driver_lock, driver_lock_flags);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block ipr_notअगरier = अणु
	ipr_halt, शून्य, 0
पूर्ण;

/**
 * ipr_init - Module entry poपूर्णांक
 *
 * Return value:
 * 	0 on success / negative value on failure
 **/
अटल पूर्णांक __init ipr_init(व्योम)
अणु
	ipr_info("IBM Power RAID SCSI Device Driver version: %s %s\n",
		 IPR_DRIVER_VERSION, IPR_DRIVER_DATE);

	रेजिस्टर_reboot_notअगरier(&ipr_notअगरier);
	वापस pci_रेजिस्टर_driver(&ipr_driver);
पूर्ण

/**
 * ipr_निकास - Module unload
 *
 * Module unload entry poपूर्णांक.
 *
 * Return value:
 * 	none
 **/
अटल व्योम __निकास ipr_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&ipr_notअगरier);
	pci_unरेजिस्टर_driver(&ipr_driver);
पूर्ण

module_init(ipr_init);
module_निकास(ipr_निकास);
