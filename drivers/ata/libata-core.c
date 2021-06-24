<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  libata-core.c - helper library क्रम ATA
 *
 *  Copyright 2003-2004 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2004 Jeff Garzik
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available from http://www.t13.org/ and
 *  http://www.sata-io.org/
 *
 *  Standards करोcuments from:
 *	http://www.t13.org (ATA standards, PCI DMA IDE spec)
 *	http://www.t10.org (SCSI MMC - क्रम ATAPI MMC)
 *	http://www.sata-io.org (SATA)
 *	http://www.compactflash.org (CF)
 *	http://www.qic.org (QIC157 - Tape and DSC)
 *	http://www.ce-ata.org (CE-ATA: not supported)
 *
 * libata is essentially a library of पूर्णांकernal helper functions क्रम
 * low-level ATA host controller drivers.  As such, the API/ABI is
 * likely to change as new drivers are added and updated.
 * Do not depend on ABI/API stability.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/suspend.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/glob.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/leds.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/setup.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/libata.h>

#समावेश "libata.h"
#समावेश "libata-transport.h"

स्थिर काष्ठा ata_port_operations ata_base_port_ops = अणु
	.prereset		= ata_std_prereset,
	.postreset		= ata_std_postreset,
	.error_handler		= ata_std_error_handler,
	.sched_eh		= ata_std_sched_eh,
	.end_eh			= ata_std_end_eh,
पूर्ण;

स्थिर काष्ठा ata_port_operations sata_port_ops = अणु
	.inherits		= &ata_base_port_ops,

	.qc_defer		= ata_std_qc_defer,
	.hardreset		= sata_std_hardreset,
पूर्ण;
EXPORT_SYMBOL_GPL(sata_port_ops);

अटल अचिन्हित पूर्णांक ata_dev_init_params(काष्ठा ata_device *dev,
					u16 heads, u16 sectors);
अटल अचिन्हित पूर्णांक ata_dev_set_xfermode(काष्ठा ata_device *dev);
अटल व्योम ata_dev_xfermask(काष्ठा ata_device *dev);
अटल अचिन्हित दीर्घ ata_dev_blacklisted(स्थिर काष्ठा ata_device *dev);

atomic_t ata_prपूर्णांक_id = ATOMIC_INIT(0);

#अगर_घोषित CONFIG_ATA_FORCE
काष्ठा ata_क्रमce_param अणु
	स्थिर अक्षर	*name;
	u8		cbl;
	u8		spd_limit;
	अचिन्हित दीर्घ	xfer_mask;
	अचिन्हित पूर्णांक	horkage_on;
	अचिन्हित पूर्णांक	horkage_off;
	u16		lflags;
पूर्ण;

काष्ठा ata_क्रमce_ent अणु
	पूर्णांक			port;
	पूर्णांक			device;
	काष्ठा ata_क्रमce_param	param;
पूर्ण;

अटल काष्ठा ata_क्रमce_ent *ata_क्रमce_tbl;
अटल पूर्णांक ata_क्रमce_tbl_size;

अटल अक्षर ata_क्रमce_param_buf[COMMAND_LINE_SIZE] __initdata;
/* param_buf is thrown away after initialization, disallow पढ़ो */
module_param_string(क्रमce, ata_क्रमce_param_buf, माप(ata_क्रमce_param_buf), 0);
MODULE_PARM_DESC(क्रमce, "Force ATA configurations including cable type, link speed and transfer mode (see Documentation/admin-guide/kernel-parameters.rst for details)");
#पूर्ण_अगर

अटल पूर्णांक atapi_enabled = 1;
module_param(atapi_enabled, पूर्णांक, 0444);
MODULE_PARM_DESC(atapi_enabled, "Enable discovery of ATAPI devices (0=off, 1=on [default])");

अटल पूर्णांक atapi_dmadir = 0;
module_param(atapi_dmadir, पूर्णांक, 0444);
MODULE_PARM_DESC(atapi_dmadir, "Enable ATAPI DMADIR bridge support (0=off [default], 1=on)");

पूर्णांक atapi_passthru16 = 1;
module_param(atapi_passthru16, पूर्णांक, 0444);
MODULE_PARM_DESC(atapi_passthru16, "Enable ATA_16 passthru for ATAPI devices (0=off, 1=on [default])");

पूर्णांक libata_fua = 0;
module_param_named(fua, libata_fua, पूर्णांक, 0444);
MODULE_PARM_DESC(fua, "FUA support (0=off [default], 1=on)");

अटल पूर्णांक ata_ignore_hpa;
module_param_named(ignore_hpa, ata_ignore_hpa, पूर्णांक, 0644);
MODULE_PARM_DESC(ignore_hpa, "Ignore HPA limit (0=keep BIOS limits, 1=ignore limits, using full disk)");

अटल पूर्णांक libata_dma_mask = ATA_DMA_MASK_ATA|ATA_DMA_MASK_ATAPI|ATA_DMA_MASK_CFA;
module_param_named(dma, libata_dma_mask, पूर्णांक, 0444);
MODULE_PARM_DESC(dma, "DMA enable/disable (0x1==ATA, 0x2==ATAPI, 0x4==CF)");

अटल पूर्णांक ata_probe_समयout;
module_param(ata_probe_समयout, पूर्णांक, 0444);
MODULE_PARM_DESC(ata_probe_समयout, "Set ATA probing timeout (seconds)");

पूर्णांक libata_noacpi = 0;
module_param_named(noacpi, libata_noacpi, पूर्णांक, 0444);
MODULE_PARM_DESC(noacpi, "Disable the use of ACPI in probe/suspend/resume (0=off [default], 1=on)");

पूर्णांक libata_allow_tpm = 0;
module_param_named(allow_tpm, libata_allow_tpm, पूर्णांक, 0444);
MODULE_PARM_DESC(allow_tpm, "Permit the use of TPM commands (0=off [default], 1=on)");

अटल पूर्णांक atapi_an;
module_param(atapi_an, पूर्णांक, 0444);
MODULE_PARM_DESC(atapi_an, "Enable ATAPI AN media presence notification (0=0ff [default], 1=on)");

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("Library module for ATA devices");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);


अटल bool ata_sstatus_online(u32 sstatus)
अणु
	वापस (sstatus & 0xf) == 0x3;
पूर्ण

/**
 *	ata_link_next - link iteration helper
 *	@link: the previous link, शून्य to start
 *	@ap: ATA port containing links to iterate
 *	@mode: iteration mode, one of ATA_LITER_*
 *
 *	LOCKING:
 *	Host lock or EH context.
 *
 *	RETURNS:
 *	Poपूर्णांकer to the next link.
 */
काष्ठा ata_link *ata_link_next(काष्ठा ata_link *link, काष्ठा ata_port *ap,
			       क्रमागत ata_link_iter_mode mode)
अणु
	BUG_ON(mode != ATA_LITER_EDGE &&
	       mode != ATA_LITER_PMP_FIRST && mode != ATA_LITER_HOST_FIRST);

	/* शून्य link indicates start of iteration */
	अगर (!link)
		चयन (mode) अणु
		हाल ATA_LITER_EDGE:
		हाल ATA_LITER_PMP_FIRST:
			अगर (sata_pmp_attached(ap))
				वापस ap->pmp_link;
			fallthrough;
		हाल ATA_LITER_HOST_FIRST:
			वापस &ap->link;
		पूर्ण

	/* we just iterated over the host link, what's next? */
	अगर (link == &ap->link)
		चयन (mode) अणु
		हाल ATA_LITER_HOST_FIRST:
			अगर (sata_pmp_attached(ap))
				वापस ap->pmp_link;
			fallthrough;
		हाल ATA_LITER_PMP_FIRST:
			अगर (unlikely(ap->slave_link))
				वापस ap->slave_link;
			fallthrough;
		हाल ATA_LITER_EDGE:
			वापस शून्य;
		पूर्ण

	/* slave_link excludes PMP */
	अगर (unlikely(link == ap->slave_link))
		वापस शून्य;

	/* we were over a PMP link */
	अगर (++link < ap->pmp_link + ap->nr_pmp_links)
		वापस link;

	अगर (mode == ATA_LITER_PMP_FIRST)
		वापस &ap->link;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ata_link_next);

/**
 *	ata_dev_next - device iteration helper
 *	@dev: the previous device, शून्य to start
 *	@link: ATA link containing devices to iterate
 *	@mode: iteration mode, one of ATA_DITER_*
 *
 *	LOCKING:
 *	Host lock or EH context.
 *
 *	RETURNS:
 *	Poपूर्णांकer to the next device.
 */
काष्ठा ata_device *ata_dev_next(काष्ठा ata_device *dev, काष्ठा ata_link *link,
				क्रमागत ata_dev_iter_mode mode)
अणु
	BUG_ON(mode != ATA_DITER_ENABLED && mode != ATA_DITER_ENABLED_REVERSE &&
	       mode != ATA_DITER_ALL && mode != ATA_DITER_ALL_REVERSE);

	/* शून्य dev indicates start of iteration */
	अगर (!dev)
		चयन (mode) अणु
		हाल ATA_DITER_ENABLED:
		हाल ATA_DITER_ALL:
			dev = link->device;
			जाओ check;
		हाल ATA_DITER_ENABLED_REVERSE:
		हाल ATA_DITER_ALL_REVERSE:
			dev = link->device + ata_link_max_devices(link) - 1;
			जाओ check;
		पूर्ण

 next:
	/* move to the next one */
	चयन (mode) अणु
	हाल ATA_DITER_ENABLED:
	हाल ATA_DITER_ALL:
		अगर (++dev < link->device + ata_link_max_devices(link))
			जाओ check;
		वापस शून्य;
	हाल ATA_DITER_ENABLED_REVERSE:
	हाल ATA_DITER_ALL_REVERSE:
		अगर (--dev >= link->device)
			जाओ check;
		वापस शून्य;
	पूर्ण

 check:
	अगर ((mode == ATA_DITER_ENABLED || mode == ATA_DITER_ENABLED_REVERSE) &&
	    !ata_dev_enabled(dev))
		जाओ next;
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(ata_dev_next);

/**
 *	ata_dev_phys_link - find physical link क्रम a device
 *	@dev: ATA device to look up physical link क्रम
 *
 *	Look up physical link which @dev is attached to.  Note that
 *	this is dअगरferent from @dev->link only when @dev is on slave
 *	link.  For all other हालs, it's the same as @dev->link.
 *
 *	LOCKING:
 *	Don't care.
 *
 *	RETURNS:
 *	Poपूर्णांकer to the found physical link.
 */
काष्ठा ata_link *ata_dev_phys_link(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;

	अगर (!ap->slave_link)
		वापस dev->link;
	अगर (!dev->devno)
		वापस &ap->link;
	वापस ap->slave_link;
पूर्ण

#अगर_घोषित CONFIG_ATA_FORCE
/**
 *	ata_क्रमce_cbl - क्रमce cable type according to libata.क्रमce
 *	@ap: ATA port of पूर्णांकerest
 *
 *	Force cable type according to libata.क्रमce and whine about it.
 *	The last entry which has matching port number is used, so it
 *	can be specअगरied as part of device क्रमce parameters.  For
 *	example, both "a:40c,1.00:udma4" and "1.00:40c,udma4" have the
 *	same effect.
 *
 *	LOCKING:
 *	EH context.
 */
व्योम ata_क्रमce_cbl(काष्ठा ata_port *ap)
अणु
	पूर्णांक i;

	क्रम (i = ata_क्रमce_tbl_size - 1; i >= 0; i--) अणु
		स्थिर काष्ठा ata_क्रमce_ent *fe = &ata_क्रमce_tbl[i];

		अगर (fe->port != -1 && fe->port != ap->prपूर्णांक_id)
			जारी;

		अगर (fe->param.cbl == ATA_CBL_NONE)
			जारी;

		ap->cbl = fe->param.cbl;
		ata_port_notice(ap, "FORCE: cable set to %s\n", fe->param.name);
		वापस;
	पूर्ण
पूर्ण

/**
 *	ata_क्रमce_link_limits - क्रमce link limits according to libata.क्रमce
 *	@link: ATA link of पूर्णांकerest
 *
 *	Force link flags and SATA spd limit according to libata.क्रमce
 *	and whine about it.  When only the port part is specअगरied
 *	(e.g. 1:), the limit applies to all links connected to both
 *	the host link and all fan-out ports connected via PMP.  If the
 *	device part is specअगरied as 0 (e.g. 1.00:), it specअगरies the
 *	first fan-out link not the host link.  Device number 15 always
 *	poपूर्णांकs to the host link whether PMP is attached or not.  If the
 *	controller has slave link, device number 16 poपूर्णांकs to it.
 *
 *	LOCKING:
 *	EH context.
 */
अटल व्योम ata_क्रमce_link_limits(काष्ठा ata_link *link)
अणु
	bool did_spd = false;
	पूर्णांक linkno = link->pmp;
	पूर्णांक i;

	अगर (ata_is_host_link(link))
		linkno += 15;

	क्रम (i = ata_क्रमce_tbl_size - 1; i >= 0; i--) अणु
		स्थिर काष्ठा ata_क्रमce_ent *fe = &ata_क्रमce_tbl[i];

		अगर (fe->port != -1 && fe->port != link->ap->prपूर्णांक_id)
			जारी;

		अगर (fe->device != -1 && fe->device != linkno)
			जारी;

		/* only honor the first spd limit */
		अगर (!did_spd && fe->param.spd_limit) अणु
			link->hw_sata_spd_limit = (1 << fe->param.spd_limit) - 1;
			ata_link_notice(link, "FORCE: PHY spd limit set to %s\n",
					fe->param.name);
			did_spd = true;
		पूर्ण

		/* let lflags stack */
		अगर (fe->param.lflags) अणु
			link->flags |= fe->param.lflags;
			ata_link_notice(link,
					"FORCE: link flag 0x%x forced -> 0x%x\n",
					fe->param.lflags, link->flags);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	ata_क्रमce_xfermask - क्रमce xfermask according to libata.क्रमce
 *	@dev: ATA device of पूर्णांकerest
 *
 *	Force xfer_mask according to libata.क्रमce and whine about it.
 *	For consistency with link selection, device number 15 selects
 *	the first device connected to the host link.
 *
 *	LOCKING:
 *	EH context.
 */
अटल व्योम ata_क्रमce_xfermask(काष्ठा ata_device *dev)
अणु
	पूर्णांक devno = dev->link->pmp + dev->devno;
	पूर्णांक alt_devno = devno;
	पूर्णांक i;

	/* allow n.15/16 क्रम devices attached to host port */
	अगर (ata_is_host_link(dev->link))
		alt_devno += 15;

	क्रम (i = ata_क्रमce_tbl_size - 1; i >= 0; i--) अणु
		स्थिर काष्ठा ata_क्रमce_ent *fe = &ata_क्रमce_tbl[i];
		अचिन्हित दीर्घ pio_mask, mwdma_mask, udma_mask;

		अगर (fe->port != -1 && fe->port != dev->link->ap->prपूर्णांक_id)
			जारी;

		अगर (fe->device != -1 && fe->device != devno &&
		    fe->device != alt_devno)
			जारी;

		अगर (!fe->param.xfer_mask)
			जारी;

		ata_unpack_xfermask(fe->param.xfer_mask,
				    &pio_mask, &mwdma_mask, &udma_mask);
		अगर (udma_mask)
			dev->udma_mask = udma_mask;
		अन्यथा अगर (mwdma_mask) अणु
			dev->udma_mask = 0;
			dev->mwdma_mask = mwdma_mask;
		पूर्ण अन्यथा अणु
			dev->udma_mask = 0;
			dev->mwdma_mask = 0;
			dev->pio_mask = pio_mask;
		पूर्ण

		ata_dev_notice(dev, "FORCE: xfer_mask set to %s\n",
			       fe->param.name);
		वापस;
	पूर्ण
पूर्ण

/**
 *	ata_क्रमce_horkage - क्रमce horkage according to libata.क्रमce
 *	@dev: ATA device of पूर्णांकerest
 *
 *	Force horkage according to libata.क्रमce and whine about it.
 *	For consistency with link selection, device number 15 selects
 *	the first device connected to the host link.
 *
 *	LOCKING:
 *	EH context.
 */
अटल व्योम ata_क्रमce_horkage(काष्ठा ata_device *dev)
अणु
	पूर्णांक devno = dev->link->pmp + dev->devno;
	पूर्णांक alt_devno = devno;
	पूर्णांक i;

	/* allow n.15/16 क्रम devices attached to host port */
	अगर (ata_is_host_link(dev->link))
		alt_devno += 15;

	क्रम (i = 0; i < ata_क्रमce_tbl_size; i++) अणु
		स्थिर काष्ठा ata_क्रमce_ent *fe = &ata_क्रमce_tbl[i];

		अगर (fe->port != -1 && fe->port != dev->link->ap->prपूर्णांक_id)
			जारी;

		अगर (fe->device != -1 && fe->device != devno &&
		    fe->device != alt_devno)
			जारी;

		अगर (!(~dev->horkage & fe->param.horkage_on) &&
		    !(dev->horkage & fe->param.horkage_off))
			जारी;

		dev->horkage |= fe->param.horkage_on;
		dev->horkage &= ~fe->param.horkage_off;

		ata_dev_notice(dev, "FORCE: horkage modified (%s)\n",
			       fe->param.name);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ata_क्रमce_link_limits(काष्ठा ata_link *link) अणु पूर्ण
अटल अंतरभूत व्योम ata_क्रमce_xfermask(काष्ठा ata_device *dev) अणु पूर्ण
अटल अंतरभूत व्योम ata_क्रमce_horkage(काष्ठा ata_device *dev) अणु पूर्ण
#पूर्ण_अगर

/**
 *	atapi_cmd_type - Determine ATAPI command type from SCSI opcode
 *	@opcode: SCSI opcode
 *
 *	Determine ATAPI command type from @opcode.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	ATAPI_अणुREAD|WRITE|READ_CD|PASS_THRU|MISCपूर्ण
 */
पूर्णांक atapi_cmd_type(u8 opcode)
अणु
	चयन (opcode) अणु
	हाल GPCMD_READ_10:
	हाल GPCMD_READ_12:
		वापस ATAPI_READ;

	हाल GPCMD_WRITE_10:
	हाल GPCMD_WRITE_12:
	हाल GPCMD_WRITE_AND_VERIFY_10:
		वापस ATAPI_WRITE;

	हाल GPCMD_READ_CD:
	हाल GPCMD_READ_CD_MSF:
		वापस ATAPI_READ_CD;

	हाल ATA_16:
	हाल ATA_12:
		अगर (atapi_passthru16)
			वापस ATAPI_PASS_THRU;
		fallthrough;
	शेष:
		वापस ATAPI_MISC;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(atapi_cmd_type);

अटल स्थिर u8 ata_rw_cmds[] = अणु
	/* pio multi */
	ATA_CMD_READ_MULTI,
	ATA_CMD_WRITE_MULTI,
	ATA_CMD_READ_MULTI_EXT,
	ATA_CMD_WRITE_MULTI_EXT,
	0,
	0,
	0,
	ATA_CMD_WRITE_MULTI_FUA_EXT,
	/* pio */
	ATA_CMD_PIO_READ,
	ATA_CMD_PIO_WRITE,
	ATA_CMD_PIO_READ_EXT,
	ATA_CMD_PIO_WRITE_EXT,
	0,
	0,
	0,
	0,
	/* dma */
	ATA_CMD_READ,
	ATA_CMD_WRITE,
	ATA_CMD_READ_EXT,
	ATA_CMD_WRITE_EXT,
	0,
	0,
	0,
	ATA_CMD_WRITE_FUA_EXT
पूर्ण;

/**
 *	ata_rwcmd_protocol - set taskfile r/w commands and protocol
 *	@tf: command to examine and configure
 *	@dev: device tf beदीर्घs to
 *
 *	Examine the device configuration and tf->flags to calculate
 *	the proper पढ़ो/ग_लिखो commands and protocol to use.
 *
 *	LOCKING:
 *	caller.
 */
अटल पूर्णांक ata_rwcmd_protocol(काष्ठा ata_taskfile *tf, काष्ठा ata_device *dev)
अणु
	u8 cmd;

	पूर्णांक index, fua, lba48, ग_लिखो;

	fua = (tf->flags & ATA_TFLAG_FUA) ? 4 : 0;
	lba48 = (tf->flags & ATA_TFLAG_LBA48) ? 2 : 0;
	ग_लिखो = (tf->flags & ATA_TFLAG_WRITE) ? 1 : 0;

	अगर (dev->flags & ATA_DFLAG_PIO) अणु
		tf->protocol = ATA_PROT_PIO;
		index = dev->multi_count ? 0 : 8;
	पूर्ण अन्यथा अगर (lba48 && (dev->link->ap->flags & ATA_FLAG_PIO_LBA48)) अणु
		/* Unable to use DMA due to host limitation */
		tf->protocol = ATA_PROT_PIO;
		index = dev->multi_count ? 0 : 8;
	पूर्ण अन्यथा अणु
		tf->protocol = ATA_PROT_DMA;
		index = 16;
	पूर्ण

	cmd = ata_rw_cmds[index + fua + lba48 + ग_लिखो];
	अगर (cmd) अणु
		tf->command = cmd;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

/**
 *	ata_tf_पढ़ो_block - Read block address from ATA taskfile
 *	@tf: ATA taskfile of पूर्णांकerest
 *	@dev: ATA device @tf beदीर्घs to
 *
 *	LOCKING:
 *	None.
 *
 *	Read block address from @tf.  This function can handle all
 *	three address क्रमmats - LBA, LBA48 and CHS.  tf->protocol and
 *	flags select the address क्रमmat to use.
 *
 *	RETURNS:
 *	Block address पढ़ो from @tf.
 */
u64 ata_tf_पढ़ो_block(स्थिर काष्ठा ata_taskfile *tf, काष्ठा ata_device *dev)
अणु
	u64 block = 0;

	अगर (tf->flags & ATA_TFLAG_LBA) अणु
		अगर (tf->flags & ATA_TFLAG_LBA48) अणु
			block |= (u64)tf->hob_lbah << 40;
			block |= (u64)tf->hob_lbam << 32;
			block |= (u64)tf->hob_lbal << 24;
		पूर्ण अन्यथा
			block |= (tf->device & 0xf) << 24;

		block |= tf->lbah << 16;
		block |= tf->lbam << 8;
		block |= tf->lbal;
	पूर्ण अन्यथा अणु
		u32 cyl, head, sect;

		cyl = tf->lbam | (tf->lbah << 8);
		head = tf->device & 0xf;
		sect = tf->lbal;

		अगर (!sect) अणु
			ata_dev_warn(dev,
				     "device reported invalid CHS sector 0\n");
			वापस U64_MAX;
		पूर्ण

		block = (cyl * dev->heads + head) * dev->sectors + sect - 1;
	पूर्ण

	वापस block;
पूर्ण

/**
 *	ata_build_rw_tf - Build ATA taskfile क्रम given पढ़ो/ग_लिखो request
 *	@tf: Target ATA taskfile
 *	@dev: ATA device @tf beदीर्घs to
 *	@block: Block address
 *	@n_block: Number of blocks
 *	@tf_flags: RW/FUA etc...
 *	@tag: tag
 *	@class: IO priority class
 *
 *	LOCKING:
 *	None.
 *
 *	Build ATA taskfile @tf क्रम पढ़ो/ग_लिखो request described by
 *	@block, @n_block, @tf_flags and @tag on @dev.
 *
 *	RETURNS:
 *
 *	0 on success, -दुस्फल अगर the request is too large क्रम @dev,
 *	-EINVAL अगर the request is invalid.
 */
पूर्णांक ata_build_rw_tf(काष्ठा ata_taskfile *tf, काष्ठा ata_device *dev,
		    u64 block, u32 n_block, अचिन्हित पूर्णांक tf_flags,
		    अचिन्हित पूर्णांक tag, पूर्णांक class)
अणु
	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf->flags |= tf_flags;

	अगर (ata_ncq_enabled(dev) && !ata_tag_पूर्णांकernal(tag)) अणु
		/* yay, NCQ */
		अगर (!lba_48_ok(block, n_block))
			वापस -दुस्फल;

		tf->protocol = ATA_PROT_NCQ;
		tf->flags |= ATA_TFLAG_LBA | ATA_TFLAG_LBA48;

		अगर (tf->flags & ATA_TFLAG_WRITE)
			tf->command = ATA_CMD_FPDMA_WRITE;
		अन्यथा
			tf->command = ATA_CMD_FPDMA_READ;

		tf->nsect = tag << 3;
		tf->hob_feature = (n_block >> 8) & 0xff;
		tf->feature = n_block & 0xff;

		tf->hob_lbah = (block >> 40) & 0xff;
		tf->hob_lbam = (block >> 32) & 0xff;
		tf->hob_lbal = (block >> 24) & 0xff;
		tf->lbah = (block >> 16) & 0xff;
		tf->lbam = (block >> 8) & 0xff;
		tf->lbal = block & 0xff;

		tf->device = ATA_LBA;
		अगर (tf->flags & ATA_TFLAG_FUA)
			tf->device |= 1 << 7;

		अगर (dev->flags & ATA_DFLAG_NCQ_PRIO) अणु
			अगर (class == IOPRIO_CLASS_RT)
				tf->hob_nsect |= ATA_PRIO_HIGH <<
						 ATA_SHIFT_PRIO;
		पूर्ण
	पूर्ण अन्यथा अगर (dev->flags & ATA_DFLAG_LBA) अणु
		tf->flags |= ATA_TFLAG_LBA;

		अगर (lba_28_ok(block, n_block)) अणु
			/* use LBA28 */
			tf->device |= (block >> 24) & 0xf;
		पूर्ण अन्यथा अगर (lba_48_ok(block, n_block)) अणु
			अगर (!(dev->flags & ATA_DFLAG_LBA48))
				वापस -दुस्फल;

			/* use LBA48 */
			tf->flags |= ATA_TFLAG_LBA48;

			tf->hob_nsect = (n_block >> 8) & 0xff;

			tf->hob_lbah = (block >> 40) & 0xff;
			tf->hob_lbam = (block >> 32) & 0xff;
			tf->hob_lbal = (block >> 24) & 0xff;
		पूर्ण अन्यथा
			/* request too large even क्रम LBA48 */
			वापस -दुस्फल;

		अगर (unlikely(ata_rwcmd_protocol(tf, dev) < 0))
			वापस -EINVAL;

		tf->nsect = n_block & 0xff;

		tf->lbah = (block >> 16) & 0xff;
		tf->lbam = (block >> 8) & 0xff;
		tf->lbal = block & 0xff;

		tf->device |= ATA_LBA;
	पूर्ण अन्यथा अणु
		/* CHS */
		u32 sect, head, cyl, track;

		/* The request -may- be too large क्रम CHS addressing. */
		अगर (!lba_28_ok(block, n_block))
			वापस -दुस्फल;

		अगर (unlikely(ata_rwcmd_protocol(tf, dev) < 0))
			वापस -EINVAL;

		/* Convert LBA to CHS */
		track = (u32)block / dev->sectors;
		cyl   = track / dev->heads;
		head  = track % dev->heads;
		sect  = (u32)block % dev->sectors + 1;

		DPRINTK("block %u track %u cyl %u head %u sect %u\n",
			(u32)block, track, cyl, head, sect);

		/* Check whether the converted CHS can fit.
		   Cylinder: 0-65535
		   Head: 0-15
		   Sector: 1-255*/
		अगर ((cyl >> 16) || (head >> 4) || (sect >> 8) || (!sect))
			वापस -दुस्फल;

		tf->nsect = n_block & 0xff; /* Sector count 0 means 256 sectors */
		tf->lbal = sect;
		tf->lbam = cyl;
		tf->lbah = cyl >> 8;
		tf->device |= head;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	ata_pack_xfermask - Pack pio, mwdma and udma masks पूर्णांकo xfer_mask
 *	@pio_mask: pio_mask
 *	@mwdma_mask: mwdma_mask
 *	@udma_mask: udma_mask
 *
 *	Pack @pio_mask, @mwdma_mask and @udma_mask पूर्णांकo a single
 *	अचिन्हित पूर्णांक xfer_mask.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Packed xfer_mask.
 */
अचिन्हित दीर्घ ata_pack_xfermask(अचिन्हित दीर्घ pio_mask,
				अचिन्हित दीर्घ mwdma_mask,
				अचिन्हित दीर्घ udma_mask)
अणु
	वापस ((pio_mask << ATA_SHIFT_PIO) & ATA_MASK_PIO) |
		((mwdma_mask << ATA_SHIFT_MWDMA) & ATA_MASK_MWDMA) |
		((udma_mask << ATA_SHIFT_UDMA) & ATA_MASK_UDMA);
पूर्ण
EXPORT_SYMBOL_GPL(ata_pack_xfermask);

/**
 *	ata_unpack_xfermask - Unpack xfer_mask पूर्णांकo pio, mwdma and udma masks
 *	@xfer_mask: xfer_mask to unpack
 *	@pio_mask: resulting pio_mask
 *	@mwdma_mask: resulting mwdma_mask
 *	@udma_mask: resulting udma_mask
 *
 *	Unpack @xfer_mask पूर्णांकo @pio_mask, @mwdma_mask and @udma_mask.
 *	Any शून्य destination masks will be ignored.
 */
व्योम ata_unpack_xfermask(अचिन्हित दीर्घ xfer_mask, अचिन्हित दीर्घ *pio_mask,
			 अचिन्हित दीर्घ *mwdma_mask, अचिन्हित दीर्घ *udma_mask)
अणु
	अगर (pio_mask)
		*pio_mask = (xfer_mask & ATA_MASK_PIO) >> ATA_SHIFT_PIO;
	अगर (mwdma_mask)
		*mwdma_mask = (xfer_mask & ATA_MASK_MWDMA) >> ATA_SHIFT_MWDMA;
	अगर (udma_mask)
		*udma_mask = (xfer_mask & ATA_MASK_UDMA) >> ATA_SHIFT_UDMA;
पूर्ण

अटल स्थिर काष्ठा ata_xfer_ent अणु
	पूर्णांक shअगरt, bits;
	u8 base;
पूर्ण ata_xfer_tbl[] = अणु
	अणु ATA_SHIFT_PIO, ATA_NR_PIO_MODES, XFER_PIO_0 पूर्ण,
	अणु ATA_SHIFT_MWDMA, ATA_NR_MWDMA_MODES, XFER_MW_DMA_0 पूर्ण,
	अणु ATA_SHIFT_UDMA, ATA_NR_UDMA_MODES, XFER_UDMA_0 पूर्ण,
	अणु -1, पूर्ण,
पूर्ण;

/**
 *	ata_xfer_mask2mode - Find matching XFER_* क्रम the given xfer_mask
 *	@xfer_mask: xfer_mask of पूर्णांकerest
 *
 *	Return matching XFER_* value क्रम @xfer_mask.  Only the highest
 *	bit of @xfer_mask is considered.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Matching XFER_* value, 0xff अगर no match found.
 */
u8 ata_xfer_mask2mode(अचिन्हित दीर्घ xfer_mask)
अणु
	पूर्णांक highbit = fls(xfer_mask) - 1;
	स्थिर काष्ठा ata_xfer_ent *ent;

	क्रम (ent = ata_xfer_tbl; ent->shअगरt >= 0; ent++)
		अगर (highbit >= ent->shअगरt && highbit < ent->shअगरt + ent->bits)
			वापस ent->base + highbit - ent->shअगरt;
	वापस 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(ata_xfer_mask2mode);

/**
 *	ata_xfer_mode2mask - Find matching xfer_mask क्रम XFER_*
 *	@xfer_mode: XFER_* of पूर्णांकerest
 *
 *	Return matching xfer_mask क्रम @xfer_mode.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Matching xfer_mask, 0 अगर no match found.
 */
अचिन्हित दीर्घ ata_xfer_mode2mask(u8 xfer_mode)
अणु
	स्थिर काष्ठा ata_xfer_ent *ent;

	क्रम (ent = ata_xfer_tbl; ent->shअगरt >= 0; ent++)
		अगर (xfer_mode >= ent->base && xfer_mode < ent->base + ent->bits)
			वापस ((2 << (ent->shअगरt + xfer_mode - ent->base)) - 1)
				& ~((1 << ent->shअगरt) - 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_xfer_mode2mask);

/**
 *	ata_xfer_mode2shअगरt - Find matching xfer_shअगरt क्रम XFER_*
 *	@xfer_mode: XFER_* of पूर्णांकerest
 *
 *	Return matching xfer_shअगरt क्रम @xfer_mode.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Matching xfer_shअगरt, -1 अगर no match found.
 */
पूर्णांक ata_xfer_mode2shअगरt(अचिन्हित दीर्घ xfer_mode)
अणु
	स्थिर काष्ठा ata_xfer_ent *ent;

	क्रम (ent = ata_xfer_tbl; ent->shअगरt >= 0; ent++)
		अगर (xfer_mode >= ent->base && xfer_mode < ent->base + ent->bits)
			वापस ent->shअगरt;
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(ata_xfer_mode2shअगरt);

/**
 *	ata_mode_string - convert xfer_mask to string
 *	@xfer_mask: mask of bits supported; only highest bit counts.
 *
 *	Determine string which represents the highest speed
 *	(highest bit in @modemask).
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Constant C string representing highest speed listed in
 *	@mode_mask, or the स्थिरant C string "<n/a>".
 */
स्थिर अक्षर *ata_mode_string(अचिन्हित दीर्घ xfer_mask)
अणु
	अटल स्थिर अक्षर * स्थिर xfer_mode_str[] = अणु
		"PIO0",
		"PIO1",
		"PIO2",
		"PIO3",
		"PIO4",
		"PIO5",
		"PIO6",
		"MWDMA0",
		"MWDMA1",
		"MWDMA2",
		"MWDMA3",
		"MWDMA4",
		"UDMA/16",
		"UDMA/25",
		"UDMA/33",
		"UDMA/44",
		"UDMA/66",
		"UDMA/100",
		"UDMA/133",
		"UDMA7",
	पूर्ण;
	पूर्णांक highbit;

	highbit = fls(xfer_mask) - 1;
	अगर (highbit >= 0 && highbit < ARRAY_SIZE(xfer_mode_str))
		वापस xfer_mode_str[highbit];
	वापस "<n/a>";
पूर्ण
EXPORT_SYMBOL_GPL(ata_mode_string);

स्थिर अक्षर *sata_spd_string(अचिन्हित पूर्णांक spd)
अणु
	अटल स्थिर अक्षर * स्थिर spd_str[] = अणु
		"1.5 Gbps",
		"3.0 Gbps",
		"6.0 Gbps",
	पूर्ण;

	अगर (spd == 0 || (spd - 1) >= ARRAY_SIZE(spd_str))
		वापस "<unknown>";
	वापस spd_str[spd - 1];
पूर्ण

/**
 *	ata_dev_classअगरy - determine device type based on ATA-spec signature
 *	@tf: ATA taskfile रेजिस्टर set क्रम device to be identअगरied
 *
 *	Determine from taskfile रेजिस्टर contents whether a device is
 *	ATA or ATAPI, as per "Signature and persistence" section
 *	of ATA/PI spec (volume 1, sect 5.14).
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Device type, %ATA_DEV_ATA, %ATA_DEV_ATAPI, %ATA_DEV_PMP,
 *	%ATA_DEV_ZAC, or %ATA_DEV_UNKNOWN the event of failure.
 */
अचिन्हित पूर्णांक ata_dev_classअगरy(स्थिर काष्ठा ata_taskfile *tf)
अणु
	/* Apple's खोलो source Darwin code hपूर्णांकs that some devices only
	 * put a proper signature पूर्णांकo the LBA mid/high रेजिस्टरs,
	 * So, we only check those.  It's sufficient क्रम uniqueness.
	 *
	 * ATA/ATAPI-7 (d1532v1r1: Feb. 19, 2003) specअगरied separate
	 * signatures क्रम ATA and ATAPI devices attached on SerialATA,
	 * 0x3c/0xc3 and 0x69/0x96 respectively.  However, SerialATA
	 * spec has never mentioned about using dअगरferent signatures
	 * क्रम ATA/ATAPI devices.  Then, Serial ATA II: Port
	 * Multiplier specअगरication began to use 0x69/0x96 to identअगरy
	 * port multpliers and 0x3c/0xc3 to identअगरy SEMB device.
	 * ATA/ATAPI-7 dropped descriptions about 0x3c/0xc3 and
	 * 0x69/0x96 लघुly and described them as reserved क्रम
	 * SerialATA.
	 *
	 * We follow the current spec and consider that 0x69/0x96
	 * identअगरies a port multiplier and 0x3c/0xc3 a SEMB device.
	 * Unक्रमtunately, WDC WD1600JS-62MHB5 (a hard drive) reports
	 * SEMB signature.  This is worked around in
	 * ata_dev_पढ़ो_id().
	 */
	अगर ((tf->lbam == 0) && (tf->lbah == 0)) अणु
		DPRINTK("found ATA device by sig\n");
		वापस ATA_DEV_ATA;
	पूर्ण

	अगर ((tf->lbam == 0x14) && (tf->lbah == 0xeb)) अणु
		DPRINTK("found ATAPI device by sig\n");
		वापस ATA_DEV_ATAPI;
	पूर्ण

	अगर ((tf->lbam == 0x69) && (tf->lbah == 0x96)) अणु
		DPRINTK("found PMP device by sig\n");
		वापस ATA_DEV_PMP;
	पूर्ण

	अगर ((tf->lbam == 0x3c) && (tf->lbah == 0xc3)) अणु
		DPRINTK("found SEMB device by sig (could be ATA device)\n");
		वापस ATA_DEV_SEMB;
	पूर्ण

	अगर ((tf->lbam == 0xcd) && (tf->lbah == 0xab)) अणु
		DPRINTK("found ZAC device by sig\n");
		वापस ATA_DEV_ZAC;
	पूर्ण

	DPRINTK("unknown device\n");
	वापस ATA_DEV_UNKNOWN;
पूर्ण
EXPORT_SYMBOL_GPL(ata_dev_classअगरy);

/**
 *	ata_id_string - Convert IDENTIFY DEVICE page पूर्णांकo string
 *	@id: IDENTIFY DEVICE results we will examine
 *	@s: string पूर्णांकo which data is output
 *	@ofs: offset पूर्णांकo identअगरy device page
 *	@len: length of string to वापस. must be an even number.
 *
 *	The strings in the IDENTIFY DEVICE page are broken up पूर्णांकo
 *	16-bit chunks.  Run through the string, and output each
 *	8-bit chunk linearly, regardless of platक्रमm.
 *
 *	LOCKING:
 *	caller.
 */

व्योम ata_id_string(स्थिर u16 *id, अचिन्हित अक्षर *s,
		   अचिन्हित पूर्णांक ofs, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक c;

	BUG_ON(len & 1);

	जबतक (len > 0) अणु
		c = id[ofs] >> 8;
		*s = c;
		s++;

		c = id[ofs] & 0xff;
		*s = c;
		s++;

		ofs++;
		len -= 2;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_id_string);

/**
 *	ata_id_c_string - Convert IDENTIFY DEVICE page पूर्णांकo C string
 *	@id: IDENTIFY DEVICE results we will examine
 *	@s: string पूर्णांकo which data is output
 *	@ofs: offset पूर्णांकo identअगरy device page
 *	@len: length of string to वापस. must be an odd number.
 *
 *	This function is identical to ata_id_string except that it
 *	trims trailing spaces and terminates the resulting string with
 *	null.  @len must be actual maximum length (even number) + 1.
 *
 *	LOCKING:
 *	caller.
 */
व्योम ata_id_c_string(स्थिर u16 *id, अचिन्हित अक्षर *s,
		     अचिन्हित पूर्णांक ofs, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *p;

	ata_id_string(id, s, ofs, len - 1);

	p = s + strnlen(s, len - 1);
	जबतक (p > s && p[-1] == ' ')
		p--;
	*p = '\0';
पूर्ण
EXPORT_SYMBOL_GPL(ata_id_c_string);

अटल u64 ata_id_n_sectors(स्थिर u16 *id)
अणु
	अगर (ata_id_has_lba(id)) अणु
		अगर (ata_id_has_lba48(id))
			वापस ata_id_u64(id, ATA_ID_LBA_CAPACITY_2);
		अन्यथा
			वापस ata_id_u32(id, ATA_ID_LBA_CAPACITY);
	पूर्ण अन्यथा अणु
		अगर (ata_id_current_chs_valid(id))
			वापस id[ATA_ID_CUR_CYLS] * id[ATA_ID_CUR_HEADS] *
			       id[ATA_ID_CUR_SECTORS];
		अन्यथा
			वापस id[ATA_ID_CYLS] * id[ATA_ID_HEADS] *
			       id[ATA_ID_SECTORS];
	पूर्ण
पूर्ण

u64 ata_tf_to_lba48(स्थिर काष्ठा ata_taskfile *tf)
अणु
	u64 sectors = 0;

	sectors |= ((u64)(tf->hob_lbah & 0xff)) << 40;
	sectors |= ((u64)(tf->hob_lbam & 0xff)) << 32;
	sectors |= ((u64)(tf->hob_lbal & 0xff)) << 24;
	sectors |= (tf->lbah & 0xff) << 16;
	sectors |= (tf->lbam & 0xff) << 8;
	sectors |= (tf->lbal & 0xff);

	वापस sectors;
पूर्ण

u64 ata_tf_to_lba(स्थिर काष्ठा ata_taskfile *tf)
अणु
	u64 sectors = 0;

	sectors |= (tf->device & 0x0f) << 24;
	sectors |= (tf->lbah & 0xff) << 16;
	sectors |= (tf->lbam & 0xff) << 8;
	sectors |= (tf->lbal & 0xff);

	वापस sectors;
पूर्ण

/**
 *	ata_पढ़ो_native_max_address - Read native max address
 *	@dev: target device
 *	@max_sectors: out parameter क्रम the result native max address
 *
 *	Perक्रमm an LBA48 or LBA28 native size query upon the device in
 *	question.
 *
 *	RETURNS:
 *	0 on success, -EACCES अगर command is पातed by the drive.
 *	-EIO on other errors.
 */
अटल पूर्णांक ata_पढ़ो_native_max_address(काष्ठा ata_device *dev, u64 *max_sectors)
अणु
	अचिन्हित पूर्णांक err_mask;
	काष्ठा ata_taskfile tf;
	पूर्णांक lba48 = ata_id_has_lba48(dev->id);

	ata_tf_init(dev, &tf);

	/* always clear all address रेजिस्टरs */
	tf.flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;

	अगर (lba48) अणु
		tf.command = ATA_CMD_READ_NATIVE_MAX_EXT;
		tf.flags |= ATA_TFLAG_LBA48;
	पूर्ण अन्यथा
		tf.command = ATA_CMD_READ_NATIVE_MAX;

	tf.protocol = ATA_PROT_NODATA;
	tf.device |= ATA_LBA;

	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, 0);
	अगर (err_mask) अणु
		ata_dev_warn(dev,
			     "failed to read native max address (err_mask=0x%x)\n",
			     err_mask);
		अगर (err_mask == AC_ERR_DEV && (tf.feature & ATA_ABORTED))
			वापस -EACCES;
		वापस -EIO;
	पूर्ण

	अगर (lba48)
		*max_sectors = ata_tf_to_lba48(&tf) + 1;
	अन्यथा
		*max_sectors = ata_tf_to_lba(&tf) + 1;
	अगर (dev->horkage & ATA_HORKAGE_HPA_SIZE)
		(*max_sectors)--;
	वापस 0;
पूर्ण

/**
 *	ata_set_max_sectors - Set max sectors
 *	@dev: target device
 *	@new_sectors: new max sectors value to set क्रम the device
 *
 *	Set max sectors of @dev to @new_sectors.
 *
 *	RETURNS:
 *	0 on success, -EACCES अगर command is पातed or denied (due to
 *	previous non-अस्थिर SET_MAX) by the drive.  -EIO on other
 *	errors.
 */
अटल पूर्णांक ata_set_max_sectors(काष्ठा ata_device *dev, u64 new_sectors)
अणु
	अचिन्हित पूर्णांक err_mask;
	काष्ठा ata_taskfile tf;
	पूर्णांक lba48 = ata_id_has_lba48(dev->id);

	new_sectors--;

	ata_tf_init(dev, &tf);

	tf.flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;

	अगर (lba48) अणु
		tf.command = ATA_CMD_SET_MAX_EXT;
		tf.flags |= ATA_TFLAG_LBA48;

		tf.hob_lbal = (new_sectors >> 24) & 0xff;
		tf.hob_lbam = (new_sectors >> 32) & 0xff;
		tf.hob_lbah = (new_sectors >> 40) & 0xff;
	पूर्ण अन्यथा अणु
		tf.command = ATA_CMD_SET_MAX;

		tf.device |= (new_sectors >> 24) & 0xf;
	पूर्ण

	tf.protocol = ATA_PROT_NODATA;
	tf.device |= ATA_LBA;

	tf.lbal = (new_sectors >> 0) & 0xff;
	tf.lbam = (new_sectors >> 8) & 0xff;
	tf.lbah = (new_sectors >> 16) & 0xff;

	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, 0);
	अगर (err_mask) अणु
		ata_dev_warn(dev,
			     "failed to set max address (err_mask=0x%x)\n",
			     err_mask);
		अगर (err_mask == AC_ERR_DEV &&
		    (tf.feature & (ATA_ABORTED | ATA_IDNF)))
			वापस -EACCES;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	ata_hpa_resize		-	Resize a device with an HPA set
 *	@dev: Device to resize
 *
 *	Read the size of an LBA28 or LBA48 disk with HPA features and resize
 *	it अगर required to the full size of the media. The caller must check
 *	the drive has the HPA feature set enabled.
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक ata_hpa_resize(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;
	पूर्णांक prपूर्णांक_info = ehc->i.flags & ATA_EHI_PRINTINFO;
	bool unlock_hpa = ata_ignore_hpa || dev->flags & ATA_DFLAG_UNLOCK_HPA;
	u64 sectors = ata_id_n_sectors(dev->id);
	u64 native_sectors;
	पूर्णांक rc;

	/* करो we need to करो it? */
	अगर ((dev->class != ATA_DEV_ATA && dev->class != ATA_DEV_ZAC) ||
	    !ata_id_has_lba(dev->id) || !ata_id_hpa_enabled(dev->id) ||
	    (dev->horkage & ATA_HORKAGE_BROKEN_HPA))
		वापस 0;

	/* पढ़ो native max address */
	rc = ata_पढ़ो_native_max_address(dev, &native_sectors);
	अगर (rc) अणु
		/* If device पातed the command or HPA isn't going to
		 * be unlocked, skip HPA resizing.
		 */
		अगर (rc == -EACCES || !unlock_hpa) अणु
			ata_dev_warn(dev,
				     "HPA support seems broken, skipping HPA handling\n");
			dev->horkage |= ATA_HORKAGE_BROKEN_HPA;

			/* we can जारी अगर device पातed the command */
			अगर (rc == -EACCES)
				rc = 0;
		पूर्ण

		वापस rc;
	पूर्ण
	dev->n_native_sectors = native_sectors;

	/* nothing to करो? */
	अगर (native_sectors <= sectors || !unlock_hpa) अणु
		अगर (!prपूर्णांक_info || native_sectors == sectors)
			वापस 0;

		अगर (native_sectors > sectors)
			ata_dev_info(dev,
				"HPA detected: current %llu, native %llu\n",
				(अचिन्हित दीर्घ दीर्घ)sectors,
				(अचिन्हित दीर्घ दीर्घ)native_sectors);
		अन्यथा अगर (native_sectors < sectors)
			ata_dev_warn(dev,
				"native sectors (%llu) is smaller than sectors (%llu)\n",
				(अचिन्हित दीर्घ दीर्घ)native_sectors,
				(अचिन्हित दीर्घ दीर्घ)sectors);
		वापस 0;
	पूर्ण

	/* let's unlock HPA */
	rc = ata_set_max_sectors(dev, native_sectors);
	अगर (rc == -EACCES) अणु
		/* अगर device पातed the command, skip HPA resizing */
		ata_dev_warn(dev,
			     "device aborted resize (%llu -> %llu), skipping HPA handling\n",
			     (अचिन्हित दीर्घ दीर्घ)sectors,
			     (अचिन्हित दीर्घ दीर्घ)native_sectors);
		dev->horkage |= ATA_HORKAGE_BROKEN_HPA;
		वापस 0;
	पूर्ण अन्यथा अगर (rc)
		वापस rc;

	/* re-पढ़ो IDENTIFY data */
	rc = ata_dev_reपढ़ो_id(dev, 0);
	अगर (rc) अणु
		ata_dev_err(dev,
			    "failed to re-read IDENTIFY data after HPA resizing\n");
		वापस rc;
	पूर्ण

	अगर (prपूर्णांक_info) अणु
		u64 new_sectors = ata_id_n_sectors(dev->id);
		ata_dev_info(dev,
			"HPA unlocked: %llu -> %llu, native %llu\n",
			(अचिन्हित दीर्घ दीर्घ)sectors,
			(अचिन्हित दीर्घ दीर्घ)new_sectors,
			(अचिन्हित दीर्घ दीर्घ)native_sectors);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	ata_dump_id - IDENTIFY DEVICE info debugging output
 *	@id: IDENTIFY DEVICE page to dump
 *
 *	Dump selected 16-bit words from the given IDENTIFY DEVICE
 *	page.
 *
 *	LOCKING:
 *	caller.
 */

अटल अंतरभूत व्योम ata_dump_id(स्थिर u16 *id)
अणु
	DPRINTK("49==0x%04x  "
		"53==0x%04x  "
		"63==0x%04x  "
		"64==0x%04x  "
		"75==0x%04x  \n",
		id[49],
		id[53],
		id[63],
		id[64],
		id[75]);
	DPRINTK("80==0x%04x  "
		"81==0x%04x  "
		"82==0x%04x  "
		"83==0x%04x  "
		"84==0x%04x  \n",
		id[80],
		id[81],
		id[82],
		id[83],
		id[84]);
	DPRINTK("88==0x%04x  "
		"93==0x%04x\n",
		id[88],
		id[93]);
पूर्ण

/**
 *	ata_id_xfermask - Compute xfermask from the given IDENTIFY data
 *	@id: IDENTIFY data to compute xfer mask from
 *
 *	Compute the xfermask क्रम this device. This is not as trivial
 *	as it seems अगर we must consider early devices correctly.
 *
 *	FIXME: pre IDE drive timing (करो we care ?).
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Computed xfermask
 */
अचिन्हित दीर्घ ata_id_xfermask(स्थिर u16 *id)
अणु
	अचिन्हित दीर्घ pio_mask, mwdma_mask, udma_mask;

	/* Usual हाल. Word 53 indicates word 64 is valid */
	अगर (id[ATA_ID_FIELD_VALID] & (1 << 1)) अणु
		pio_mask = id[ATA_ID_PIO_MODES] & 0x03;
		pio_mask <<= 3;
		pio_mask |= 0x7;
	पूर्ण अन्यथा अणु
		/* If word 64 isn't valid then Word 51 high byte holds
		 * the PIO timing number क्रम the maximum. Turn it पूर्णांकo
		 * a mask.
		 */
		u8 mode = (id[ATA_ID_OLD_PIO_MODES] >> 8) & 0xFF;
		अगर (mode < 5)	/* Valid PIO range */
			pio_mask = (2 << mode) - 1;
		अन्यथा
			pio_mask = 1;

		/* But रुको.. there's more. Design your standards by
		 * committee and you too can get a मुक्त iordy field to
		 * process. However its the speeds not the modes that
		 * are supported... Note drivers using the timing API
		 * will get this right anyway
		 */
	पूर्ण

	mwdma_mask = id[ATA_ID_MWDMA_MODES] & 0x07;

	अगर (ata_id_is_cfa(id)) अणु
		/*
		 *	Process compact flash extended modes
		 */
		पूर्णांक pio = (id[ATA_ID_CFA_MODES] >> 0) & 0x7;
		पूर्णांक dma = (id[ATA_ID_CFA_MODES] >> 3) & 0x7;

		अगर (pio)
			pio_mask |= (1 << 5);
		अगर (pio > 1)
			pio_mask |= (1 << 6);
		अगर (dma)
			mwdma_mask |= (1 << 3);
		अगर (dma > 1)
			mwdma_mask |= (1 << 4);
	पूर्ण

	udma_mask = 0;
	अगर (id[ATA_ID_FIELD_VALID] & (1 << 2))
		udma_mask = id[ATA_ID_UDMA_MODES] & 0xff;

	वापस ata_pack_xfermask(pio_mask, mwdma_mask, udma_mask);
पूर्ण
EXPORT_SYMBOL_GPL(ata_id_xfermask);

अटल व्योम ata_qc_complete_पूर्णांकernal(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा completion *रुकोing = qc->निजी_data;

	complete(रुकोing);
पूर्ण

/**
 *	ata_exec_पूर्णांकernal_sg - execute libata पूर्णांकernal command
 *	@dev: Device to which the command is sent
 *	@tf: Taskfile रेजिस्टरs क्रम the command and the result
 *	@cdb: CDB क्रम packet command
 *	@dma_dir: Data transfer direction of the command
 *	@sgl: sg list क्रम the data buffer of the command
 *	@n_elem: Number of sg entries
 *	@समयout: Timeout in msecs (0 क्रम शेष)
 *
 *	Executes libata पूर्णांकernal command with समयout.  @tf contains
 *	command on entry and result on वापस.  Timeout and error
 *	conditions are reported via वापस value.  No recovery action
 *	is taken after a command बार out.  It's caller's duty to
 *	clean up after समयout.
 *
 *	LOCKING:
 *	None.  Should be called with kernel context, might sleep.
 *
 *	RETURNS:
 *	Zero on success, AC_ERR_* mask on failure
 */
अचिन्हित ata_exec_पूर्णांकernal_sg(काष्ठा ata_device *dev,
			      काष्ठा ata_taskfile *tf, स्थिर u8 *cdb,
			      पूर्णांक dma_dir, काष्ठा scatterlist *sgl,
			      अचिन्हित पूर्णांक n_elem, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	u8 command = tf->command;
	पूर्णांक स्वतः_समयout = 0;
	काष्ठा ata_queued_cmd *qc;
	अचिन्हित पूर्णांक preempted_tag;
	u32 preempted_sactive;
	u64 preempted_qc_active;
	पूर्णांक preempted_nr_active_links;
	DECLARE_COMPLETION_ONSTACK(रुको);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक err_mask;
	पूर्णांक rc;

	spin_lock_irqsave(ap->lock, flags);

	/* no पूर्णांकernal command जबतक frozen */
	अगर (ap->pflags & ATA_PFLAG_FROZEN) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		वापस AC_ERR_SYSTEM;
	पूर्ण

	/* initialize पूर्णांकernal qc */
	qc = __ata_qc_from_tag(ap, ATA_TAG_INTERNAL);

	qc->tag = ATA_TAG_INTERNAL;
	qc->hw_tag = 0;
	qc->scsicmd = शून्य;
	qc->ap = ap;
	qc->dev = dev;
	ata_qc_reinit(qc);

	preempted_tag = link->active_tag;
	preempted_sactive = link->sactive;
	preempted_qc_active = ap->qc_active;
	preempted_nr_active_links = ap->nr_active_links;
	link->active_tag = ATA_TAG_POISON;
	link->sactive = 0;
	ap->qc_active = 0;
	ap->nr_active_links = 0;

	/* prepare & issue qc */
	qc->tf = *tf;
	अगर (cdb)
		स_नकल(qc->cdb, cdb, ATAPI_CDB_LEN);

	/* some SATA bridges need us to indicate data xfer direction */
	अगर (tf->protocol == ATAPI_PROT_DMA && (dev->flags & ATA_DFLAG_DMAसूची) &&
	    dma_dir == DMA_FROM_DEVICE)
		qc->tf.feature |= ATAPI_DMAसूची;

	qc->flags |= ATA_QCFLAG_RESULT_TF;
	qc->dma_dir = dma_dir;
	अगर (dma_dir != DMA_NONE) अणु
		अचिन्हित पूर्णांक i, buflen = 0;
		काष्ठा scatterlist *sg;

		क्रम_each_sg(sgl, sg, n_elem, i)
			buflen += sg->length;

		ata_sg_init(qc, sgl, n_elem);
		qc->nbytes = buflen;
	पूर्ण

	qc->निजी_data = &रुको;
	qc->complete_fn = ata_qc_complete_पूर्णांकernal;

	ata_qc_issue(qc);

	spin_unlock_irqrestore(ap->lock, flags);

	अगर (!समयout) अणु
		अगर (ata_probe_समयout)
			समयout = ata_probe_समयout * 1000;
		अन्यथा अणु
			समयout = ata_पूर्णांकernal_cmd_समयout(dev, command);
			स्वतः_समयout = 1;
		पूर्ण
	पूर्ण

	अगर (ap->ops->error_handler)
		ata_eh_release(ap);

	rc = रुको_क्रम_completion_समयout(&रुको, msecs_to_jअगरfies(समयout));

	अगर (ap->ops->error_handler)
		ata_eh_acquire(ap);

	ata_sff_flush_pio_task(ap);

	अगर (!rc) अणु
		spin_lock_irqsave(ap->lock, flags);

		/* We're racing with irq here.  If we lose, the
		 * following test prevents us from completing the qc
		 * twice.  If we win, the port is frozen and will be
		 * cleaned up by ->post_पूर्णांकernal_cmd().
		 */
		अगर (qc->flags & ATA_QCFLAG_ACTIVE) अणु
			qc->err_mask |= AC_ERR_TIMEOUT;

			अगर (ap->ops->error_handler)
				ata_port_मुक्तze(ap);
			अन्यथा
				ata_qc_complete(qc);

			अगर (ata_msg_warn(ap))
				ata_dev_warn(dev, "qc timeout (cmd 0x%x)\n",
					     command);
		पूर्ण

		spin_unlock_irqrestore(ap->lock, flags);
	पूर्ण

	/* करो post_पूर्णांकernal_cmd */
	अगर (ap->ops->post_पूर्णांकernal_cmd)
		ap->ops->post_पूर्णांकernal_cmd(qc);

	/* perक्रमm minimal error analysis */
	अगर (qc->flags & ATA_QCFLAG_FAILED) अणु
		अगर (qc->result_tf.command & (ATA_ERR | ATA_DF))
			qc->err_mask |= AC_ERR_DEV;

		अगर (!qc->err_mask)
			qc->err_mask |= AC_ERR_OTHER;

		अगर (qc->err_mask & ~AC_ERR_OTHER)
			qc->err_mask &= ~AC_ERR_OTHER;
	पूर्ण अन्यथा अगर (qc->tf.command == ATA_CMD_REQ_SENSE_DATA) अणु
		qc->result_tf.command |= ATA_SENSE;
	पूर्ण

	/* finish up */
	spin_lock_irqsave(ap->lock, flags);

	*tf = qc->result_tf;
	err_mask = qc->err_mask;

	ata_qc_मुक्त(qc);
	link->active_tag = preempted_tag;
	link->sactive = preempted_sactive;
	ap->qc_active = preempted_qc_active;
	ap->nr_active_links = preempted_nr_active_links;

	spin_unlock_irqrestore(ap->lock, flags);

	अगर ((err_mask & AC_ERR_TIMEOUT) && स्वतः_समयout)
		ata_पूर्णांकernal_cmd_समयd_out(dev, command);

	वापस err_mask;
पूर्ण

/**
 *	ata_exec_पूर्णांकernal - execute libata पूर्णांकernal command
 *	@dev: Device to which the command is sent
 *	@tf: Taskfile रेजिस्टरs क्रम the command and the result
 *	@cdb: CDB क्रम packet command
 *	@dma_dir: Data transfer direction of the command
 *	@buf: Data buffer of the command
 *	@buflen: Length of data buffer
 *	@समयout: Timeout in msecs (0 क्रम शेष)
 *
 *	Wrapper around ata_exec_पूर्णांकernal_sg() which takes simple
 *	buffer instead of sg list.
 *
 *	LOCKING:
 *	None.  Should be called with kernel context, might sleep.
 *
 *	RETURNS:
 *	Zero on success, AC_ERR_* mask on failure
 */
अचिन्हित ata_exec_पूर्णांकernal(काष्ठा ata_device *dev,
			   काष्ठा ata_taskfile *tf, स्थिर u8 *cdb,
			   पूर्णांक dma_dir, व्योम *buf, अचिन्हित पूर्णांक buflen,
			   अचिन्हित दीर्घ समयout)
अणु
	काष्ठा scatterlist *psg = शून्य, sg;
	अचिन्हित पूर्णांक n_elem = 0;

	अगर (dma_dir != DMA_NONE) अणु
		WARN_ON(!buf);
		sg_init_one(&sg, buf, buflen);
		psg = &sg;
		n_elem++;
	पूर्ण

	वापस ata_exec_पूर्णांकernal_sg(dev, tf, cdb, dma_dir, psg, n_elem,
				    समयout);
पूर्ण

/**
 *	ata_pio_need_iordy	-	check अगर iordy needed
 *	@adev: ATA device
 *
 *	Check अगर the current speed of the device requires IORDY. Used
 *	by various controllers क्रम chip configuration.
 */
अचिन्हित पूर्णांक ata_pio_need_iordy(स्थिर काष्ठा ata_device *adev)
अणु
	/* Don't set IORDY if we're preparing क्रम reset.  IORDY may
	 * lead to controller lock up on certain controllers अगर the
	 * port is not occupied.  See bko#11703 क्रम details.
	 */
	अगर (adev->link->ap->pflags & ATA_PFLAG_RESETTING)
		वापस 0;
	/* Controller करोesn't support IORDY.  Probably a poपूर्णांकless
	 * check as the caller should know this.
	 */
	अगर (adev->link->ap->flags & ATA_FLAG_NO_IORDY)
		वापस 0;
	/* CF spec. r4.1 Table 22 says no iordy on PIO5 and PIO6.  */
	अगर (ata_id_is_cfa(adev->id)
	    && (adev->pio_mode == XFER_PIO_5 || adev->pio_mode == XFER_PIO_6))
		वापस 0;
	/* PIO3 and higher it is mandatory */
	अगर (adev->pio_mode > XFER_PIO_2)
		वापस 1;
	/* We turn it on when possible */
	अगर (ata_id_has_iordy(adev->id))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pio_need_iordy);

/**
 *	ata_pio_mask_no_iordy	-	Return the non IORDY mask
 *	@adev: ATA device
 *
 *	Compute the highest mode possible अगर we are not using iordy. Return
 *	-1 अगर no iordy mode is available.
 */
अटल u32 ata_pio_mask_no_iordy(स्थिर काष्ठा ata_device *adev)
अणु
	/* If we have no drive specअगरic rule, then PIO 2 is non IORDY */
	अगर (adev->id[ATA_ID_FIELD_VALID] & 2) अणु	/* EIDE */
		u16 pio = adev->id[ATA_ID_EIDE_PIO];
		/* Is the speed faster than the drive allows non IORDY ? */
		अगर (pio) अणु
			/* This is cycle बार not frequency - watch the logic! */
			अगर (pio > 240)	/* PIO2 is 240nS per cycle */
				वापस 3 << ATA_SHIFT_PIO;
			वापस 7 << ATA_SHIFT_PIO;
		पूर्ण
	पूर्ण
	वापस 3 << ATA_SHIFT_PIO;
पूर्ण

/**
 *	ata_करो_dev_पढ़ो_id		-	शेष ID पढ़ो method
 *	@dev: device
 *	@tf: proposed taskfile
 *	@id: data buffer
 *
 *	Issue the identअगरy taskfile and hand back the buffer containing
 *	identअगरy data. For some RAID controllers and क्रम pre ATA devices
 *	this function is wrapped or replaced by the driver
 */
अचिन्हित पूर्णांक ata_करो_dev_पढ़ो_id(काष्ठा ata_device *dev,
					काष्ठा ata_taskfile *tf, u16 *id)
अणु
	वापस ata_exec_पूर्णांकernal(dev, tf, शून्य, DMA_FROM_DEVICE,
				     id, माप(id[0]) * ATA_ID_WORDS, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ata_करो_dev_पढ़ो_id);

/**
 *	ata_dev_पढ़ो_id - Read ID data from the specअगरied device
 *	@dev: target device
 *	@p_class: poपूर्णांकer to class of the target device (may be changed)
 *	@flags: ATA_READID_* flags
 *	@id: buffer to पढ़ो IDENTIFY data पूर्णांकo
 *
 *	Read ID data from the specअगरied device.  ATA_CMD_ID_ATA is
 *	perक्रमmed on ATA devices and ATA_CMD_ID_ATAPI on ATAPI
 *	devices.  This function also issues ATA_CMD_INIT_DEV_PARAMS
 *	क्रम pre-ATA4 drives.
 *
 *	FIXME: ATA_CMD_ID_ATA is optional क्रम early drives and right
 *	now we पात अगर we hit that हाल.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_dev_पढ़ो_id(काष्ठा ata_device *dev, अचिन्हित पूर्णांक *p_class,
		    अचिन्हित पूर्णांक flags, u16 *id)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	अचिन्हित पूर्णांक class = *p_class;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask = 0;
	स्थिर अक्षर *reason;
	bool is_semb = class == ATA_DEV_SEMB;
	पूर्णांक may_fallback = 1, tried_spinup = 0;
	पूर्णांक rc;

	अगर (ata_msg_ctl(ap))
		ata_dev_dbg(dev, "%s: ENTER\n", __func__);

retry:
	ata_tf_init(dev, &tf);

	चयन (class) अणु
	हाल ATA_DEV_SEMB:
		class = ATA_DEV_ATA;	/* some hard drives report SEMB sig */
		fallthrough;
	हाल ATA_DEV_ATA:
	हाल ATA_DEV_ZAC:
		tf.command = ATA_CMD_ID_ATA;
		अवरोध;
	हाल ATA_DEV_ATAPI:
		tf.command = ATA_CMD_ID_ATAPI;
		अवरोध;
	शेष:
		rc = -ENODEV;
		reason = "unsupported class";
		जाओ err_out;
	पूर्ण

	tf.protocol = ATA_PROT_PIO;

	/* Some devices choke अगर TF रेजिस्टरs contain garbage.  Make
	 * sure those are properly initialized.
	 */
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;

	/* Device presence detection is unreliable on some
	 * controllers.  Always poll IDENTIFY अगर available.
	 */
	tf.flags |= ATA_TFLAG_POLLING;

	अगर (ap->ops->पढ़ो_id)
		err_mask = ap->ops->पढ़ो_id(dev, &tf, id);
	अन्यथा
		err_mask = ata_करो_dev_पढ़ो_id(dev, &tf, id);

	अगर (err_mask) अणु
		अगर (err_mask & AC_ERR_NODEV_HINT) अणु
			ata_dev_dbg(dev, "NODEV after polling detection\n");
			वापस -ENOENT;
		पूर्ण

		अगर (is_semb) अणु
			ata_dev_info(dev,
		     "IDENTIFY failed on device w/ SEMB sig, disabled\n");
			/* SEMB is not supported yet */
			*p_class = ATA_DEV_SEMB_UNSUP;
			वापस 0;
		पूर्ण

		अगर ((err_mask == AC_ERR_DEV) && (tf.feature & ATA_ABORTED)) अणु
			/* Device or controller might have reported
			 * the wrong device class.  Give a shot at the
			 * other IDENTIFY अगर the current one is
			 * पातed by the device.
			 */
			अगर (may_fallback) अणु
				may_fallback = 0;

				अगर (class == ATA_DEV_ATA)
					class = ATA_DEV_ATAPI;
				अन्यथा
					class = ATA_DEV_ATA;
				जाओ retry;
			पूर्ण

			/* Control reaches here अगरf the device पातed
			 * both flavors of IDENTIFYs which happens
			 * someबार with phantom devices.
			 */
			ata_dev_dbg(dev,
				    "both IDENTIFYs aborted, assuming NODEV\n");
			वापस -ENOENT;
		पूर्ण

		rc = -EIO;
		reason = "I/O error";
		जाओ err_out;
	पूर्ण

	अगर (dev->horkage & ATA_HORKAGE_DUMP_ID) अणु
		ata_dev_dbg(dev, "dumping IDENTIFY data, "
			    "class=%d may_fallback=%d tried_spinup=%d\n",
			    class, may_fallback, tried_spinup);
		prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET,
			       16, 2, id, ATA_ID_WORDS * माप(*id), true);
	पूर्ण

	/* Falling back करोesn't make sense अगर ID data was पढ़ो
	 * successfully at least once.
	 */
	may_fallback = 0;

	swap_buf_le16(id, ATA_ID_WORDS);

	/* sanity check */
	rc = -EINVAL;
	reason = "device reports invalid type";

	अगर (class == ATA_DEV_ATA || class == ATA_DEV_ZAC) अणु
		अगर (!ata_id_is_ata(id) && !ata_id_is_cfa(id))
			जाओ err_out;
		अगर (ap->host->flags & ATA_HOST_IGNORE_ATA &&
							ata_id_is_ata(id)) अणु
			ata_dev_dbg(dev,
				"host indicates ignore ATA devices, ignored\n");
			वापस -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ata_id_is_ata(id))
			जाओ err_out;
	पूर्ण

	अगर (!tried_spinup && (id[2] == 0x37c8 || id[2] == 0x738c)) अणु
		tried_spinup = 1;
		/*
		 * Drive घातered-up in standby mode, and requires a specअगरic
		 * SET_FEATURES spin-up subcommand beक्रमe it will accept
		 * anything other than the original IDENTIFY command.
		 */
		err_mask = ata_dev_set_feature(dev, SETFEATURES_SPINUP, 0);
		अगर (err_mask && id[2] != 0x738c) अणु
			rc = -EIO;
			reason = "SPINUP failed";
			जाओ err_out;
		पूर्ण
		/*
		 * If the drive initially वापसed incomplete IDENTIFY info,
		 * we now must reissue the IDENTIFY command.
		 */
		अगर (id[2] == 0x37c8)
			जाओ retry;
	पूर्ण

	अगर ((flags & ATA_READID_POSTRESET) &&
	    (class == ATA_DEV_ATA || class == ATA_DEV_ZAC)) अणु
		/*
		 * The exact sequence expected by certain pre-ATA4 drives is:
		 * SRST RESET
		 * IDENTIFY (optional in early ATA)
		 * INITIALIZE DEVICE PARAMETERS (later IDE and ATA)
		 * anything अन्यथा..
		 * Some drives were very specअगरic about that exact sequence.
		 *
		 * Note that ATA4 says lba is mandatory so the second check
		 * should never trigger.
		 */
		अगर (ata_id_major_version(id) < 4 || !ata_id_has_lba(id)) अणु
			err_mask = ata_dev_init_params(dev, id[3], id[6]);
			अगर (err_mask) अणु
				rc = -EIO;
				reason = "INIT_DEV_PARAMS failed";
				जाओ err_out;
			पूर्ण

			/* current CHS translation info (id[53-58]) might be
			 * changed. reपढ़ो the identअगरy device info.
			 */
			flags &= ~ATA_READID_POSTRESET;
			जाओ retry;
		पूर्ण
	पूर्ण

	*p_class = class;

	वापस 0;

 err_out:
	अगर (ata_msg_warn(ap))
		ata_dev_warn(dev, "failed to IDENTIFY (%s, err_mask=0x%x)\n",
			     reason, err_mask);
	वापस rc;
पूर्ण

/**
 *	ata_पढ़ो_log_page - पढ़ो a specअगरic log page
 *	@dev: target device
 *	@log: log to पढ़ो
 *	@page: page to पढ़ो
 *	@buf: buffer to store पढ़ो page
 *	@sectors: number of sectors to पढ़ो
 *
 *	Read log page using READ_LOG_EXT command.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask otherwise.
 */
अचिन्हित पूर्णांक ata_पढ़ो_log_page(काष्ठा ata_device *dev, u8 log,
			       u8 page, व्योम *buf, अचिन्हित पूर्णांक sectors)
अणु
	अचिन्हित दीर्घ ap_flags = dev->link->ap->flags;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;
	bool dma = false;

	DPRINTK("read log page - log 0x%x, page 0x%x\n", log, page);

	/*
	 * Return error without actually issuing the command on controllers
	 * which e.g. lockup on a पढ़ो log page.
	 */
	अगर (ap_flags & ATA_FLAG_NO_LOG_PAGE)
		वापस AC_ERR_DEV;

retry:
	ata_tf_init(dev, &tf);
	अगर (dev->dma_mode && ata_id_has_पढ़ो_log_dma_ext(dev->id) &&
	    !(dev->horkage & ATA_HORKAGE_NO_DMA_LOG)) अणु
		tf.command = ATA_CMD_READ_LOG_DMA_EXT;
		tf.protocol = ATA_PROT_DMA;
		dma = true;
	पूर्ण अन्यथा अणु
		tf.command = ATA_CMD_READ_LOG_EXT;
		tf.protocol = ATA_PROT_PIO;
		dma = false;
	पूर्ण
	tf.lbal = log;
	tf.lbam = page;
	tf.nsect = sectors;
	tf.hob_nsect = sectors >> 8;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_LBA48 | ATA_TFLAG_DEVICE;

	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_FROM_DEVICE,
				     buf, sectors * ATA_SECT_SIZE, 0);

	अगर (err_mask && dma) अणु
		dev->horkage |= ATA_HORKAGE_NO_DMA_LOG;
		ata_dev_warn(dev, "READ LOG DMA EXT failed, trying PIO\n");
		जाओ retry;
	पूर्ण

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	वापस err_mask;
पूर्ण

अटल bool ata_log_supported(काष्ठा ata_device *dev, u8 log)
अणु
	काष्ठा ata_port *ap = dev->link->ap;

	अगर (ata_पढ़ो_log_page(dev, ATA_LOG_सूचीECTORY, 0, ap->sector_buf, 1))
		वापस false;
	वापस get_unaligned_le16(&ap->sector_buf[log * 2]) ? true : false;
पूर्ण

अटल bool ata_identअगरy_page_supported(काष्ठा ata_device *dev, u8 page)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	अचिन्हित पूर्णांक err, i;

	अगर (!ata_log_supported(dev, ATA_LOG_IDENTIFY_DEVICE)) अणु
		ata_dev_warn(dev, "ATA Identify Device Log not supported\n");
		वापस false;
	पूर्ण

	/*
	 * Read IDENTIFY DEVICE data log, page 0, to figure out अगर the page is
	 * supported.
	 */
	err = ata_पढ़ो_log_page(dev, ATA_LOG_IDENTIFY_DEVICE, 0, ap->sector_buf,
				1);
	अगर (err) अणु
		ata_dev_info(dev,
			     "failed to get Device Identify Log Emask 0x%x\n",
			     err);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < ap->sector_buf[8]; i++) अणु
		अगर (ap->sector_buf[9 + i] == page)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ata_करो_link_spd_horkage(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_link *plink = ata_dev_phys_link(dev);
	u32 target, target_limit;

	अगर (!sata_scr_valid(plink))
		वापस 0;

	अगर (dev->horkage & ATA_HORKAGE_1_5_GBPS)
		target = 1;
	अन्यथा
		वापस 0;

	target_limit = (1 << target) - 1;

	/* अगर alपढ़ोy on stricter limit, no need to push further */
	अगर (plink->sata_spd_limit <= target_limit)
		वापस 0;

	plink->sata_spd_limit = target_limit;

	/* Request another EH round by वापसing -EAGAIN अगर link is
	 * going faster than the target speed.  Forward progress is
	 * guaranteed by setting sata_spd_limit to target_limit above.
	 */
	अगर (plink->sata_spd > target) अणु
		ata_dev_info(dev, "applying link speed limit horkage to %s\n",
			     sata_spd_string(target));
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u8 ata_dev_knobble(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;

	अगर (ata_dev_blacklisted(dev) & ATA_HORKAGE_BRIDGE_OK)
		वापस 0;

	वापस ((ap->cbl == ATA_CBL_SATA) && (!ata_id_is_sata(dev->id)));
पूर्ण

अटल व्योम ata_dev_config_ncq_send_recv(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	अचिन्हित पूर्णांक err_mask;

	अगर (!ata_log_supported(dev, ATA_LOG_NCQ_SEND_RECV)) अणु
		ata_dev_warn(dev, "NCQ Send/Recv Log not supported\n");
		वापस;
	पूर्ण
	err_mask = ata_पढ़ो_log_page(dev, ATA_LOG_NCQ_SEND_RECV,
				     0, ap->sector_buf, 1);
	अगर (err_mask) अणु
		ata_dev_dbg(dev,
			    "failed to get NCQ Send/Recv Log Emask 0x%x\n",
			    err_mask);
	पूर्ण अन्यथा अणु
		u8 *cmds = dev->ncq_send_recv_cmds;

		dev->flags |= ATA_DFLAG_NCQ_SEND_RECV;
		स_नकल(cmds, ap->sector_buf, ATA_LOG_NCQ_SEND_RECV_SIZE);

		अगर (dev->horkage & ATA_HORKAGE_NO_NCQ_TRIM) अणु
			ata_dev_dbg(dev, "disabling queued TRIM support\n");
			cmds[ATA_LOG_NCQ_SEND_RECV_DSM_OFFSET] &=
				~ATA_LOG_NCQ_SEND_RECV_DSM_TRIM;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ata_dev_config_ncq_non_data(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	अचिन्हित पूर्णांक err_mask;

	अगर (!ata_log_supported(dev, ATA_LOG_NCQ_NON_DATA)) अणु
		ata_dev_warn(dev,
			     "NCQ Send/Recv Log not supported\n");
		वापस;
	पूर्ण
	err_mask = ata_पढ़ो_log_page(dev, ATA_LOG_NCQ_NON_DATA,
				     0, ap->sector_buf, 1);
	अगर (err_mask) अणु
		ata_dev_dbg(dev,
			    "failed to get NCQ Non-Data Log Emask 0x%x\n",
			    err_mask);
	पूर्ण अन्यथा अणु
		u8 *cmds = dev->ncq_non_data_cmds;

		स_नकल(cmds, ap->sector_buf, ATA_LOG_NCQ_NON_DATA_SIZE);
	पूर्ण
पूर्ण

अटल व्योम ata_dev_config_ncq_prio(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	अचिन्हित पूर्णांक err_mask;

	अगर (!(dev->flags & ATA_DFLAG_NCQ_PRIO_ENABLE)) अणु
		dev->flags &= ~ATA_DFLAG_NCQ_PRIO;
		वापस;
	पूर्ण

	err_mask = ata_पढ़ो_log_page(dev,
				     ATA_LOG_IDENTIFY_DEVICE,
				     ATA_LOG_SATA_SETTINGS,
				     ap->sector_buf,
				     1);
	अगर (err_mask) अणु
		ata_dev_dbg(dev,
			    "failed to get Identify Device data, Emask 0x%x\n",
			    err_mask);
		वापस;
	पूर्ण

	अगर (ap->sector_buf[ATA_LOG_NCQ_PRIO_OFFSET] & BIT(3)) अणु
		dev->flags |= ATA_DFLAG_NCQ_PRIO;
	पूर्ण अन्यथा अणु
		dev->flags &= ~ATA_DFLAG_NCQ_PRIO;
		ata_dev_dbg(dev, "SATA page does not support priority\n");
	पूर्ण

पूर्ण

अटल पूर्णांक ata_dev_config_ncq(काष्ठा ata_device *dev,
			       अक्षर *desc, माप_प्रकार desc_sz)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	पूर्णांक hdepth = 0, ddepth = ata_id_queue_depth(dev->id);
	अचिन्हित पूर्णांक err_mask;
	अक्षर *aa_desc = "";

	अगर (!ata_id_has_ncq(dev->id)) अणु
		desc[0] = '\0';
		वापस 0;
	पूर्ण
	अगर (!IS_ENABLED(CONFIG_SATA_HOST))
		वापस 0;
	अगर (dev->horkage & ATA_HORKAGE_NONCQ) अणु
		snम_लिखो(desc, desc_sz, "NCQ (not used)");
		वापस 0;
	पूर्ण
	अगर (ap->flags & ATA_FLAG_NCQ) अणु
		hdepth = min(ap->scsi_host->can_queue, ATA_MAX_QUEUE);
		dev->flags |= ATA_DFLAG_NCQ;
	पूर्ण

	अगर (!(dev->horkage & ATA_HORKAGE_BROKEN_FPDMA_AA) &&
		(ap->flags & ATA_FLAG_FPDMA_AA) &&
		ata_id_has_fpdma_aa(dev->id)) अणु
		err_mask = ata_dev_set_feature(dev, SETFEATURES_SATA_ENABLE,
			SATA_FPDMA_AA);
		अगर (err_mask) अणु
			ata_dev_err(dev,
				    "failed to enable AA (error_mask=0x%x)\n",
				    err_mask);
			अगर (err_mask != AC_ERR_DEV) अणु
				dev->horkage |= ATA_HORKAGE_BROKEN_FPDMA_AA;
				वापस -EIO;
			पूर्ण
		पूर्ण अन्यथा
			aa_desc = ", AA";
	पूर्ण

	अगर (hdepth >= ddepth)
		snम_लिखो(desc, desc_sz, "NCQ (depth %d)%s", ddepth, aa_desc);
	अन्यथा
		snम_लिखो(desc, desc_sz, "NCQ (depth %d/%d)%s", hdepth,
			ddepth, aa_desc);

	अगर ((ap->flags & ATA_FLAG_FPDMA_AUX)) अणु
		अगर (ata_id_has_ncq_send_and_recv(dev->id))
			ata_dev_config_ncq_send_recv(dev);
		अगर (ata_id_has_ncq_non_data(dev->id))
			ata_dev_config_ncq_non_data(dev);
		अगर (ata_id_has_ncq_prio(dev->id))
			ata_dev_config_ncq_prio(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ata_dev_config_sense_reporting(काष्ठा ata_device *dev)
अणु
	अचिन्हित पूर्णांक err_mask;

	अगर (!ata_id_has_sense_reporting(dev->id))
		वापस;

	अगर (ata_id_sense_reporting_enabled(dev->id))
		वापस;

	err_mask = ata_dev_set_feature(dev, SETFEATURE_SENSE_DATA, 0x1);
	अगर (err_mask) अणु
		ata_dev_dbg(dev,
			    "failed to enable Sense Data Reporting, Emask 0x%x\n",
			    err_mask);
	पूर्ण
पूर्ण

अटल व्योम ata_dev_config_zac(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	अचिन्हित पूर्णांक err_mask;
	u8 *identअगरy_buf = ap->sector_buf;

	dev->zac_zones_optimal_खोलो = U32_MAX;
	dev->zac_zones_optimal_nonseq = U32_MAX;
	dev->zac_zones_max_खोलो = U32_MAX;

	/*
	 * Always set the 'ZAC' flag क्रम Host-managed devices.
	 */
	अगर (dev->class == ATA_DEV_ZAC)
		dev->flags |= ATA_DFLAG_ZAC;
	अन्यथा अगर (ata_id_zoned_cap(dev->id) == 0x01)
		/*
		 * Check क्रम host-aware devices.
		 */
		dev->flags |= ATA_DFLAG_ZAC;

	अगर (!(dev->flags & ATA_DFLAG_ZAC))
		वापस;

	अगर (!ata_identअगरy_page_supported(dev, ATA_LOG_ZONED_INFORMATION)) अणु
		ata_dev_warn(dev,
			     "ATA Zoned Information Log not supported\n");
		वापस;
	पूर्ण

	/*
	 * Read IDENTIFY DEVICE data log, page 9 (Zoned-device inक्रमmation)
	 */
	err_mask = ata_पढ़ो_log_page(dev, ATA_LOG_IDENTIFY_DEVICE,
				     ATA_LOG_ZONED_INFORMATION,
				     identअगरy_buf, 1);
	अगर (!err_mask) अणु
		u64 zoned_cap, opt_खोलो, opt_nonseq, max_खोलो;

		zoned_cap = get_unaligned_le64(&identअगरy_buf[8]);
		अगर ((zoned_cap >> 63))
			dev->zac_zoned_cap = (zoned_cap & 1);
		opt_खोलो = get_unaligned_le64(&identअगरy_buf[24]);
		अगर ((opt_खोलो >> 63))
			dev->zac_zones_optimal_खोलो = (u32)opt_खोलो;
		opt_nonseq = get_unaligned_le64(&identअगरy_buf[32]);
		अगर ((opt_nonseq >> 63))
			dev->zac_zones_optimal_nonseq = (u32)opt_nonseq;
		max_खोलो = get_unaligned_le64(&identअगरy_buf[40]);
		अगर ((max_खोलो >> 63))
			dev->zac_zones_max_खोलो = (u32)max_खोलो;
	पूर्ण
पूर्ण

अटल व्योम ata_dev_config_trusted(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	u64 trusted_cap;
	अचिन्हित पूर्णांक err;

	अगर (!ata_id_has_trusted(dev->id))
		वापस;

	अगर (!ata_identअगरy_page_supported(dev, ATA_LOG_SECURITY)) अणु
		ata_dev_warn(dev,
			     "Security Log not supported\n");
		वापस;
	पूर्ण

	err = ata_पढ़ो_log_page(dev, ATA_LOG_IDENTIFY_DEVICE, ATA_LOG_SECURITY,
			ap->sector_buf, 1);
	अगर (err) अणु
		ata_dev_dbg(dev,
			    "failed to read Security Log, Emask 0x%x\n", err);
		वापस;
	पूर्ण

	trusted_cap = get_unaligned_le64(&ap->sector_buf[40]);
	अगर (!(trusted_cap & (1ULL << 63))) अणु
		ata_dev_dbg(dev,
			    "Trusted Computing capability qword not valid!\n");
		वापस;
	पूर्ण

	अगर (trusted_cap & (1 << 0))
		dev->flags |= ATA_DFLAG_TRUSTED;
पूर्ण

/**
 *	ata_dev_configure - Configure the specअगरied ATA/ATAPI device
 *	@dev: Target device to configure
 *
 *	Configure @dev according to @dev->id.  Generic and low-level
 *	driver specअगरic fixups are also applied.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise
 */
पूर्णांक ata_dev_configure(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;
	पूर्णांक prपूर्णांक_info = ehc->i.flags & ATA_EHI_PRINTINFO;
	स्थिर u16 *id = dev->id;
	अचिन्हित दीर्घ xfer_mask;
	अचिन्हित पूर्णांक err_mask;
	अक्षर revbuf[7];		/* XYZ-99\0 */
	अक्षर fwrevbuf[ATA_ID_FW_REV_LEN+1];
	अक्षर modelbuf[ATA_ID_PROD_LEN+1];
	पूर्णांक rc;

	अगर (!ata_dev_enabled(dev) && ata_msg_info(ap)) अणु
		ata_dev_info(dev, "%s: ENTER/EXIT -- nodev\n", __func__);
		वापस 0;
	पूर्ण

	अगर (ata_msg_probe(ap))
		ata_dev_dbg(dev, "%s: ENTER\n", __func__);

	/* set horkage */
	dev->horkage |= ata_dev_blacklisted(dev);
	ata_क्रमce_horkage(dev);

	अगर (dev->horkage & ATA_HORKAGE_DISABLE) अणु
		ata_dev_info(dev, "unsupported device, disabling\n");
		ata_dev_disable(dev);
		वापस 0;
	पूर्ण

	अगर ((!atapi_enabled || (ap->flags & ATA_FLAG_NO_ATAPI)) &&
	    dev->class == ATA_DEV_ATAPI) अणु
		ata_dev_warn(dev, "WARNING: ATAPI is %s, device ignored\n",
			     atapi_enabled ? "not supported with this driver"
			     : "disabled");
		ata_dev_disable(dev);
		वापस 0;
	पूर्ण

	rc = ata_करो_link_spd_horkage(dev);
	अगर (rc)
		वापस rc;

	/* some WD SATA-1 drives have issues with LPM, turn on NOLPM क्रम them */
	अगर ((dev->horkage & ATA_HORKAGE_WD_BROKEN_LPM) &&
	    (id[ATA_ID_SATA_CAPABILITY] & 0xe) == 0x2)
		dev->horkage |= ATA_HORKAGE_NOLPM;

	अगर (ap->flags & ATA_FLAG_NO_LPM)
		dev->horkage |= ATA_HORKAGE_NOLPM;

	अगर (dev->horkage & ATA_HORKAGE_NOLPM) अणु
		ata_dev_warn(dev, "LPM support broken, forcing max_power\n");
		dev->link->ap->target_lpm_policy = ATA_LPM_MAX_POWER;
	पूर्ण

	/* let ACPI work its magic */
	rc = ata_acpi_on_devcfg(dev);
	अगर (rc)
		वापस rc;

	/* massage HPA, करो it early as it might change IDENTIFY data */
	rc = ata_hpa_resize(dev);
	अगर (rc)
		वापस rc;

	/* prपूर्णांक device capabilities */
	अगर (ata_msg_probe(ap))
		ata_dev_dbg(dev,
			    "%s: cfg 49:%04x 82:%04x 83:%04x 84:%04x "
			    "85:%04x 86:%04x 87:%04x 88:%04x\n",
			    __func__,
			    id[49], id[82], id[83], id[84],
			    id[85], id[86], id[87], id[88]);

	/* initialize to-be-configured parameters */
	dev->flags &= ~ATA_DFLAG_CFG_MASK;
	dev->max_sectors = 0;
	dev->cdb_len = 0;
	dev->n_sectors = 0;
	dev->cylinders = 0;
	dev->heads = 0;
	dev->sectors = 0;
	dev->multi_count = 0;

	/*
	 * common ATA, ATAPI feature tests
	 */

	/* find max transfer mode; क्रम prपूर्णांकk only */
	xfer_mask = ata_id_xfermask(id);

	अगर (ata_msg_probe(ap))
		ata_dump_id(id);

	/* SCSI only uses 4-अक्षर revisions, dump full 8 अक्षरs from ATA */
	ata_id_c_string(dev->id, fwrevbuf, ATA_ID_FW_REV,
			माप(fwrevbuf));

	ata_id_c_string(dev->id, modelbuf, ATA_ID_PROD,
			माप(modelbuf));

	/* ATA-specअगरic feature tests */
	अगर (dev->class == ATA_DEV_ATA || dev->class == ATA_DEV_ZAC) अणु
		अगर (ata_id_is_cfa(id)) अणु
			/* CPRM may make this media unusable */
			अगर (id[ATA_ID_CFA_KEY_MGMT] & 1)
				ata_dev_warn(dev,
	"supports DRM functions and may not be fully accessible\n");
			snम_लिखो(revbuf, 7, "CFA");
		पूर्ण अन्यथा अणु
			snम_लिखो(revbuf, 7, "ATA-%d", ata_id_major_version(id));
			/* Warn the user अगर the device has TPM extensions */
			अगर (ata_id_has_tpm(id))
				ata_dev_warn(dev,
	"supports DRM functions and may not be fully accessible\n");
		पूर्ण

		dev->n_sectors = ata_id_n_sectors(id);

		/* get current R/W Multiple count setting */
		अगर ((dev->id[47] >> 8) == 0x80 && (dev->id[59] & 0x100)) अणु
			अचिन्हित पूर्णांक max = dev->id[47] & 0xff;
			अचिन्हित पूर्णांक cnt = dev->id[59] & 0xff;
			/* only recognize/allow घातers of two here */
			अगर (is_घातer_of_2(max) && is_घातer_of_2(cnt))
				अगर (cnt <= max)
					dev->multi_count = cnt;
		पूर्ण

		अगर (ata_id_has_lba(id)) अणु
			स्थिर अक्षर *lba_desc;
			अक्षर ncq_desc[24];

			lba_desc = "LBA";
			dev->flags |= ATA_DFLAG_LBA;
			अगर (ata_id_has_lba48(id)) अणु
				dev->flags |= ATA_DFLAG_LBA48;
				lba_desc = "LBA48";

				अगर (dev->n_sectors >= (1UL << 28) &&
				    ata_id_has_flush_ext(id))
					dev->flags |= ATA_DFLAG_FLUSH_EXT;
			पूर्ण

			/* config NCQ */
			rc = ata_dev_config_ncq(dev, ncq_desc, माप(ncq_desc));
			अगर (rc)
				वापस rc;

			/* prपूर्णांक device info to dmesg */
			अगर (ata_msg_drv(ap) && prपूर्णांक_info) अणु
				ata_dev_info(dev, "%s: %s, %s, max %s\n",
					     revbuf, modelbuf, fwrevbuf,
					     ata_mode_string(xfer_mask));
				ata_dev_info(dev,
					     "%llu sectors, multi %u: %s %s\n",
					(अचिन्हित दीर्घ दीर्घ)dev->n_sectors,
					dev->multi_count, lba_desc, ncq_desc);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* CHS */

			/* Default translation */
			dev->cylinders	= id[1];
			dev->heads	= id[3];
			dev->sectors	= id[6];

			अगर (ata_id_current_chs_valid(id)) अणु
				/* Current CHS translation is valid. */
				dev->cylinders = id[54];
				dev->heads     = id[55];
				dev->sectors   = id[56];
			पूर्ण

			/* prपूर्णांक device info to dmesg */
			अगर (ata_msg_drv(ap) && prपूर्णांक_info) अणु
				ata_dev_info(dev, "%s: %s, %s, max %s\n",
					     revbuf,	modelbuf, fwrevbuf,
					     ata_mode_string(xfer_mask));
				ata_dev_info(dev,
					     "%llu sectors, multi %u, CHS %u/%u/%u\n",
					     (अचिन्हित दीर्घ दीर्घ)dev->n_sectors,
					     dev->multi_count, dev->cylinders,
					     dev->heads, dev->sectors);
			पूर्ण
		पूर्ण

		/* Check and mark DevSlp capability. Get DevSlp timing variables
		 * from SATA Settings page of Identअगरy Device Data Log.
		 */
		अगर (ata_id_has_devslp(dev->id)) अणु
			u8 *sata_setting = ap->sector_buf;
			पूर्णांक i, j;

			dev->flags |= ATA_DFLAG_DEVSLP;
			err_mask = ata_पढ़ो_log_page(dev,
						     ATA_LOG_IDENTIFY_DEVICE,
						     ATA_LOG_SATA_SETTINGS,
						     sata_setting,
						     1);
			अगर (err_mask)
				ata_dev_dbg(dev,
					    "failed to get Identify Device Data, Emask 0x%x\n",
					    err_mask);
			अन्यथा
				क्रम (i = 0; i < ATA_LOG_DEVSLP_SIZE; i++) अणु
					j = ATA_LOG_DEVSLP_OFFSET + i;
					dev->devslp_timing[i] = sata_setting[j];
				पूर्ण
		पूर्ण
		ata_dev_config_sense_reporting(dev);
		ata_dev_config_zac(dev);
		ata_dev_config_trusted(dev);
		dev->cdb_len = 32;
	पूर्ण

	/* ATAPI-specअगरic feature tests */
	अन्यथा अगर (dev->class == ATA_DEV_ATAPI) अणु
		स्थिर अक्षर *cdb_पूर्णांकr_string = "";
		स्थिर अक्षर *atapi_an_string = "";
		स्थिर अक्षर *dma_dir_string = "";
		u32 sntf;

		rc = atapi_cdb_len(id);
		अगर ((rc < 12) || (rc > ATAPI_CDB_LEN)) अणु
			अगर (ata_msg_warn(ap))
				ata_dev_warn(dev, "unsupported CDB len\n");
			rc = -EINVAL;
			जाओ err_out_nosup;
		पूर्ण
		dev->cdb_len = (अचिन्हित पूर्णांक) rc;

		/* Enable ATAPI AN अगर both the host and device have
		 * the support.  If PMP is attached, SNTF is required
		 * to enable ATAPI AN to discern between PHY status
		 * changed notअगरications and ATAPI ANs.
		 */
		अगर (atapi_an &&
		    (ap->flags & ATA_FLAG_AN) && ata_id_has_atapi_AN(id) &&
		    (!sata_pmp_attached(ap) ||
		     sata_scr_पढ़ो(&ap->link, SCR_NOTIFICATION, &sntf) == 0)) अणु
			/* issue SET feature command to turn this on */
			err_mask = ata_dev_set_feature(dev,
					SETFEATURES_SATA_ENABLE, SATA_AN);
			अगर (err_mask)
				ata_dev_err(dev,
					    "failed to enable ATAPI AN (err_mask=0x%x)\n",
					    err_mask);
			अन्यथा अणु
				dev->flags |= ATA_DFLAG_AN;
				atapi_an_string = ", ATAPI AN";
			पूर्ण
		पूर्ण

		अगर (ata_id_cdb_पूर्णांकr(dev->id)) अणु
			dev->flags |= ATA_DFLAG_CDB_INTR;
			cdb_पूर्णांकr_string = ", CDB intr";
		पूर्ण

		अगर (atapi_dmadir || (dev->horkage & ATA_HORKAGE_ATAPI_DMAसूची) || atapi_id_dmadir(dev->id)) अणु
			dev->flags |= ATA_DFLAG_DMAसूची;
			dma_dir_string = ", DMADIR";
		पूर्ण

		अगर (ata_id_has_da(dev->id)) अणु
			dev->flags |= ATA_DFLAG_DA;
			zpodd_init(dev);
		पूर्ण

		/* prपूर्णांक device info to dmesg */
		अगर (ata_msg_drv(ap) && prपूर्णांक_info)
			ata_dev_info(dev,
				     "ATAPI: %s, %s, max %s%s%s%s\n",
				     modelbuf, fwrevbuf,
				     ata_mode_string(xfer_mask),
				     cdb_पूर्णांकr_string, atapi_an_string,
				     dma_dir_string);
	पूर्ण

	/* determine max_sectors */
	dev->max_sectors = ATA_MAX_SECTORS;
	अगर (dev->flags & ATA_DFLAG_LBA48)
		dev->max_sectors = ATA_MAX_SECTORS_LBA48;

	/* Limit PATA drive on SATA cable bridge transfers to udma5,
	   200 sectors */
	अगर (ata_dev_knobble(dev)) अणु
		अगर (ata_msg_drv(ap) && prपूर्णांक_info)
			ata_dev_info(dev, "applying bridge limits\n");
		dev->udma_mask &= ATA_UDMA5;
		dev->max_sectors = ATA_MAX_SECTORS;
	पूर्ण

	अगर ((dev->class == ATA_DEV_ATAPI) &&
	    (atapi_command_packet_set(id) == TYPE_TAPE)) अणु
		dev->max_sectors = ATA_MAX_SECTORS_TAPE;
		dev->horkage |= ATA_HORKAGE_STUCK_ERR;
	पूर्ण

	अगर (dev->horkage & ATA_HORKAGE_MAX_SEC_128)
		dev->max_sectors = min_t(अचिन्हित पूर्णांक, ATA_MAX_SECTORS_128,
					 dev->max_sectors);

	अगर (dev->horkage & ATA_HORKAGE_MAX_SEC_1024)
		dev->max_sectors = min_t(अचिन्हित पूर्णांक, ATA_MAX_SECTORS_1024,
					 dev->max_sectors);

	अगर (dev->horkage & ATA_HORKAGE_MAX_SEC_LBA48)
		dev->max_sectors = ATA_MAX_SECTORS_LBA48;

	अगर (ap->ops->dev_config)
		ap->ops->dev_config(dev);

	अगर (dev->horkage & ATA_HORKAGE_DIAGNOSTIC) अणु
		/* Let the user know. We करोn't want to disallow खोलोs क्रम
		   rescue purposes, or in हाल the venकरोr is just a blithering
		   idiot. Do this after the dev_config call as some controllers
		   with buggy firmware may want to aव्योम reporting false device
		   bugs */

		अगर (prपूर्णांक_info) अणु
			ata_dev_warn(dev,
"Drive reports diagnostics failure. This may indicate a drive\n");
			ata_dev_warn(dev,
"fault or invalid emulation. Contact drive vendor for information.\n");
		पूर्ण
	पूर्ण

	अगर ((dev->horkage & ATA_HORKAGE_FIRMWARE_WARN) && prपूर्णांक_info) अणु
		ata_dev_warn(dev, "WARNING: device requires firmware update to be fully functional\n");
		ata_dev_warn(dev, "         contact the vendor or visit http://ata.wiki.kernel.org\n");
	पूर्ण

	वापस 0;

err_out_nosup:
	अगर (ata_msg_probe(ap))
		ata_dev_dbg(dev, "%s: EXIT, err\n", __func__);
	वापस rc;
पूर्ण

/**
 *	ata_cable_40wire	-	वापस 40 wire cable type
 *	@ap: port
 *
 *	Helper method क्रम drivers which want to hardwire 40 wire cable
 *	detection.
 */

पूर्णांक ata_cable_40wire(काष्ठा ata_port *ap)
अणु
	वापस ATA_CBL_PATA40;
पूर्ण
EXPORT_SYMBOL_GPL(ata_cable_40wire);

/**
 *	ata_cable_80wire	-	वापस 80 wire cable type
 *	@ap: port
 *
 *	Helper method क्रम drivers which want to hardwire 80 wire cable
 *	detection.
 */

पूर्णांक ata_cable_80wire(काष्ठा ata_port *ap)
अणु
	वापस ATA_CBL_PATA80;
पूर्ण
EXPORT_SYMBOL_GPL(ata_cable_80wire);

/**
 *	ata_cable_unknown	-	वापस unknown PATA cable.
 *	@ap: port
 *
 *	Helper method क्रम drivers which have no PATA cable detection.
 */

पूर्णांक ata_cable_unknown(काष्ठा ata_port *ap)
अणु
	वापस ATA_CBL_PATA_UNK;
पूर्ण
EXPORT_SYMBOL_GPL(ata_cable_unknown);

/**
 *	ata_cable_ignore	-	वापस ignored PATA cable.
 *	@ap: port
 *
 *	Helper method क्रम drivers which करोn't use cable type to limit
 *	transfer mode.
 */
पूर्णांक ata_cable_ignore(काष्ठा ata_port *ap)
अणु
	वापस ATA_CBL_PATA_IGN;
पूर्ण
EXPORT_SYMBOL_GPL(ata_cable_ignore);

/**
 *	ata_cable_sata	-	वापस SATA cable type
 *	@ap: port
 *
 *	Helper method क्रम drivers which have SATA cables
 */

पूर्णांक ata_cable_sata(काष्ठा ata_port *ap)
अणु
	वापस ATA_CBL_SATA;
पूर्ण
EXPORT_SYMBOL_GPL(ata_cable_sata);

/**
 *	ata_bus_probe - Reset and probe ATA bus
 *	@ap: Bus to probe
 *
 *	Master ATA bus probing function.  Initiates a hardware-dependent
 *	bus reset, then attempts to identअगरy any devices found on
 *	the bus.
 *
 *	LOCKING:
 *	PCI/etc. bus probe sem.
 *
 *	RETURNS:
 *	Zero on success, negative त्रुटि_सं otherwise.
 */

पूर्णांक ata_bus_probe(काष्ठा ata_port *ap)
अणु
	अचिन्हित पूर्णांक classes[ATA_MAX_DEVICES];
	पूर्णांक tries[ATA_MAX_DEVICES];
	पूर्णांक rc;
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, &ap->link, ALL)
		tries[dev->devno] = ATA_PROBE_MAX_TRIES;

 retry:
	ata_क्रम_each_dev(dev, &ap->link, ALL) अणु
		/* If we issue an SRST then an ATA drive (not ATAPI)
		 * may change configuration and be in PIO0 timing. If
		 * we करो a hard reset (or are coming from घातer on)
		 * this is true क्रम ATA or ATAPI. Until we've set a
		 * suitable controller mode we should not touch the
		 * bus as we may be talking too fast.
		 */
		dev->pio_mode = XFER_PIO_0;
		dev->dma_mode = 0xff;

		/* If the controller has a pio mode setup function
		 * then use it to set the chipset to rights. Don't
		 * touch the DMA setup as that will be dealt with when
		 * configuring devices.
		 */
		अगर (ap->ops->set_piomode)
			ap->ops->set_piomode(ap, dev);
	पूर्ण

	/* reset and determine device classes */
	ap->ops->phy_reset(ap);

	ata_क्रम_each_dev(dev, &ap->link, ALL) अणु
		अगर (dev->class != ATA_DEV_UNKNOWN)
			classes[dev->devno] = dev->class;
		अन्यथा
			classes[dev->devno] = ATA_DEV_NONE;

		dev->class = ATA_DEV_UNKNOWN;
	पूर्ण

	/* पढ़ो IDENTIFY page and configure devices. We have to करो the identअगरy
	   specअगरic sequence bass-ackwards so that PDIAG- is released by
	   the slave device */

	ata_क्रम_each_dev(dev, &ap->link, ALL_REVERSE) अणु
		अगर (tries[dev->devno])
			dev->class = classes[dev->devno];

		अगर (!ata_dev_enabled(dev))
			जारी;

		rc = ata_dev_पढ़ो_id(dev, &dev->class, ATA_READID_POSTRESET,
				     dev->id);
		अगर (rc)
			जाओ fail;
	पूर्ण

	/* Now ask क्रम the cable type as PDIAG- should have been released */
	अगर (ap->ops->cable_detect)
		ap->cbl = ap->ops->cable_detect(ap);

	/* We may have SATA bridge glue hiding here irrespective of
	 * the reported cable types and sensed types.  When SATA
	 * drives indicate we have a bridge, we करोn't know which end
	 * of the link the bridge is which is a problem.
	 */
	ata_क्रम_each_dev(dev, &ap->link, ENABLED)
		अगर (ata_id_is_sata(dev->id))
			ap->cbl = ATA_CBL_SATA;

	/* After the identअगरy sequence we can now set up the devices. We करो
	   this in the normal order so that the user करोesn't get confused */

	ata_क्रम_each_dev(dev, &ap->link, ENABLED) अणु
		ap->link.eh_context.i.flags |= ATA_EHI_PRINTINFO;
		rc = ata_dev_configure(dev);
		ap->link.eh_context.i.flags &= ~ATA_EHI_PRINTINFO;
		अगर (rc)
			जाओ fail;
	पूर्ण

	/* configure transfer mode */
	rc = ata_set_mode(&ap->link, &dev);
	अगर (rc)
		जाओ fail;

	ata_क्रम_each_dev(dev, &ap->link, ENABLED)
		वापस 0;

	वापस -ENODEV;

 fail:
	tries[dev->devno]--;

	चयन (rc) अणु
	हाल -EINVAL:
		/* eeek, something went very wrong, give up */
		tries[dev->devno] = 0;
		अवरोध;

	हाल -ENODEV:
		/* give it just one more chance */
		tries[dev->devno] = min(tries[dev->devno], 1);
		fallthrough;
	हाल -EIO:
		अगर (tries[dev->devno] == 1) अणु
			/* This is the last chance, better to slow
			 * करोwn than lose it.
			 */
			sata_करोwn_spd_limit(&ap->link, 0);
			ata_करोwn_xfermask_limit(dev, ATA_DNXFER_PIO);
		पूर्ण
	पूर्ण

	अगर (!tries[dev->devno])
		ata_dev_disable(dev);

	जाओ retry;
पूर्ण

/**
 *	sata_prपूर्णांक_link_status - Prपूर्णांक SATA link status
 *	@link: SATA link to prपूर्णांकk link status about
 *
 *	This function prपूर्णांकs link speed and status of a SATA link.
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम sata_prपूर्णांक_link_status(काष्ठा ata_link *link)
अणु
	u32 sstatus, scontrol, पंचांगp;

	अगर (sata_scr_पढ़ो(link, SCR_STATUS, &sstatus))
		वापस;
	sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol);

	अगर (ata_phys_link_online(link)) अणु
		पंचांगp = (sstatus >> 4) & 0xf;
		ata_link_info(link, "SATA link up %s (SStatus %X SControl %X)\n",
			      sata_spd_string(पंचांगp), sstatus, scontrol);
	पूर्ण अन्यथा अणु
		ata_link_info(link, "SATA link down (SStatus %X SControl %X)\n",
			      sstatus, scontrol);
	पूर्ण
पूर्ण

/**
 *	ata_dev_pair		-	वापस other device on cable
 *	@adev: device
 *
 *	Obtain the other device on the same cable, or अगर none is
 *	present शून्य is वापसed
 */

काष्ठा ata_device *ata_dev_pair(काष्ठा ata_device *adev)
अणु
	काष्ठा ata_link *link = adev->link;
	काष्ठा ata_device *pair = &link->device[1 - adev->devno];
	अगर (!ata_dev_enabled(pair))
		वापस शून्य;
	वापस pair;
पूर्ण
EXPORT_SYMBOL_GPL(ata_dev_pair);

/**
 *	sata_करोwn_spd_limit - adjust SATA spd limit करोwnward
 *	@link: Link to adjust SATA spd limit क्रम
 *	@spd_limit: Additional limit
 *
 *	Adjust SATA spd limit of @link करोwnward.  Note that this
 *	function only adjusts the limit.  The change must be applied
 *	using sata_set_spd().
 *
 *	If @spd_limit is non-zero, the speed is limited to equal to or
 *	lower than @spd_limit अगर such speed is supported.  If
 *	@spd_limit is slower than any supported speed, only the lowest
 *	supported speed is allowed.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं on failure
 */
पूर्णांक sata_करोwn_spd_limit(काष्ठा ata_link *link, u32 spd_limit)
अणु
	u32 sstatus, spd, mask;
	पूर्णांक rc, bit;

	अगर (!sata_scr_valid(link))
		वापस -EOPNOTSUPP;

	/* If SCR can be पढ़ो, use it to determine the current SPD.
	 * If not, use cached value in link->sata_spd.
	 */
	rc = sata_scr_पढ़ो(link, SCR_STATUS, &sstatus);
	अगर (rc == 0 && ata_sstatus_online(sstatus))
		spd = (sstatus >> 4) & 0xf;
	अन्यथा
		spd = link->sata_spd;

	mask = link->sata_spd_limit;
	अगर (mask <= 1)
		वापस -EINVAL;

	/* unconditionally mask off the highest bit */
	bit = fls(mask) - 1;
	mask &= ~(1 << bit);

	/*
	 * Mask off all speeds higher than or equal to the current one.  At
	 * this poपूर्णांक, अगर current SPD is not available and we previously
	 * recorded the link speed from SStatus, the driver has alपढ़ोy
	 * masked off the highest bit so mask should alपढ़ोy be 1 or 0.
	 * Otherwise, we should not क्रमce 1.5Gbps on a link where we have
	 * not previously recorded speed from SStatus.  Just वापस in this
	 * हाल.
	 */
	अगर (spd > 1)
		mask &= (1 << (spd - 1)) - 1;
	अन्यथा
		वापस -EINVAL;

	/* were we alपढ़ोy at the bottom? */
	अगर (!mask)
		वापस -EINVAL;

	अगर (spd_limit) अणु
		अगर (mask & ((1 << spd_limit) - 1))
			mask &= (1 << spd_limit) - 1;
		अन्यथा अणु
			bit = ffs(mask) - 1;
			mask = 1 << bit;
		पूर्ण
	पूर्ण

	link->sata_spd_limit = mask;

	ata_link_warn(link, "limiting SATA link speed to %s\n",
		      sata_spd_string(fls(mask)));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ATA_ACPI
/**
 *	ata_timing_cycle2mode - find xfer mode क्रम the specअगरied cycle duration
 *	@xfer_shअगरt: ATA_SHIFT_* value क्रम transfer type to examine.
 *	@cycle: cycle duration in ns
 *
 *	Return matching xfer mode क्रम @cycle.  The वापसed mode is of
 *	the transfer type specअगरied by @xfer_shअगरt.  If @cycle is too
 *	slow क्रम @xfer_shअगरt, 0xff is वापसed.  If @cycle is faster
 *	than the fastest known mode, the fasted mode is वापसed.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Matching xfer_mode, 0xff अगर no match found.
 */
u8 ata_timing_cycle2mode(अचिन्हित पूर्णांक xfer_shअगरt, पूर्णांक cycle)
अणु
	u8 base_mode = 0xff, last_mode = 0xff;
	स्थिर काष्ठा ata_xfer_ent *ent;
	स्थिर काष्ठा ata_timing *t;

	क्रम (ent = ata_xfer_tbl; ent->shअगरt >= 0; ent++)
		अगर (ent->shअगरt == xfer_shअगरt)
			base_mode = ent->base;

	क्रम (t = ata_timing_find_mode(base_mode);
	     t && ata_xfer_mode2shअगरt(t->mode) == xfer_shअगरt; t++) अणु
		अचिन्हित लघु this_cycle;

		चयन (xfer_shअगरt) अणु
		हाल ATA_SHIFT_PIO:
		हाल ATA_SHIFT_MWDMA:
			this_cycle = t->cycle;
			अवरोध;
		हाल ATA_SHIFT_UDMA:
			this_cycle = t->udma;
			अवरोध;
		शेष:
			वापस 0xff;
		पूर्ण

		अगर (cycle > this_cycle)
			अवरोध;

		last_mode = t->mode;
	पूर्ण

	वापस last_mode;
पूर्ण
#पूर्ण_अगर

/**
 *	ata_करोwn_xfermask_limit - adjust dev xfer masks करोwnward
 *	@dev: Device to adjust xfer masks
 *	@sel: ATA_DNXFER_* selector
 *
 *	Adjust xfer masks of @dev करोwnward.  Note that this function
 *	करोes not apply the change.  Invoking ata_set_mode() afterwards
 *	will apply the limit.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं on failure
 */
पूर्णांक ata_करोwn_xfermask_limit(काष्ठा ata_device *dev, अचिन्हित पूर्णांक sel)
अणु
	अक्षर buf[32];
	अचिन्हित दीर्घ orig_mask, xfer_mask;
	अचिन्हित दीर्घ pio_mask, mwdma_mask, udma_mask;
	पूर्णांक quiet, highbit;

	quiet = !!(sel & ATA_DNXFER_QUIET);
	sel &= ~ATA_DNXFER_QUIET;

	xfer_mask = orig_mask = ata_pack_xfermask(dev->pio_mask,
						  dev->mwdma_mask,
						  dev->udma_mask);
	ata_unpack_xfermask(xfer_mask, &pio_mask, &mwdma_mask, &udma_mask);

	चयन (sel) अणु
	हाल ATA_DNXFER_PIO:
		highbit = fls(pio_mask) - 1;
		pio_mask &= ~(1 << highbit);
		अवरोध;

	हाल ATA_DNXFER_DMA:
		अगर (udma_mask) अणु
			highbit = fls(udma_mask) - 1;
			udma_mask &= ~(1 << highbit);
			अगर (!udma_mask)
				वापस -ENOENT;
		पूर्ण अन्यथा अगर (mwdma_mask) अणु
			highbit = fls(mwdma_mask) - 1;
			mwdma_mask &= ~(1 << highbit);
			अगर (!mwdma_mask)
				वापस -ENOENT;
		पूर्ण
		अवरोध;

	हाल ATA_DNXFER_40C:
		udma_mask &= ATA_UDMA_MASK_40C;
		अवरोध;

	हाल ATA_DNXFER_FORCE_PIO0:
		pio_mask &= 1;
		fallthrough;
	हाल ATA_DNXFER_FORCE_PIO:
		mwdma_mask = 0;
		udma_mask = 0;
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	xfer_mask &= ata_pack_xfermask(pio_mask, mwdma_mask, udma_mask);

	अगर (!(xfer_mask & ATA_MASK_PIO) || xfer_mask == orig_mask)
		वापस -ENOENT;

	अगर (!quiet) अणु
		अगर (xfer_mask & (ATA_MASK_MWDMA | ATA_MASK_UDMA))
			snम_लिखो(buf, माप(buf), "%s:%s",
				 ata_mode_string(xfer_mask),
				 ata_mode_string(xfer_mask & ATA_MASK_PIO));
		अन्यथा
			snम_लिखो(buf, माप(buf), "%s",
				 ata_mode_string(xfer_mask));

		ata_dev_warn(dev, "limiting speed to %s\n", buf);
	पूर्ण

	ata_unpack_xfermask(xfer_mask, &dev->pio_mask, &dev->mwdma_mask,
			    &dev->udma_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक ata_dev_set_mode(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;
	स्थिर bool nosetxfer = dev->horkage & ATA_HORKAGE_NOSETXFER;
	स्थिर अक्षर *dev_err_whine = "";
	पूर्णांक ign_dev_err = 0;
	अचिन्हित पूर्णांक err_mask = 0;
	पूर्णांक rc;

	dev->flags &= ~ATA_DFLAG_PIO;
	अगर (dev->xfer_shअगरt == ATA_SHIFT_PIO)
		dev->flags |= ATA_DFLAG_PIO;

	अगर (nosetxfer && ap->flags & ATA_FLAG_SATA && ata_id_is_sata(dev->id))
		dev_err_whine = " (SET_XFERMODE skipped)";
	अन्यथा अणु
		अगर (nosetxfer)
			ata_dev_warn(dev,
				     "NOSETXFER but PATA detected - can't "
				     "skip SETXFER, might malfunction\n");
		err_mask = ata_dev_set_xfermode(dev);
	पूर्ण

	अगर (err_mask & ~AC_ERR_DEV)
		जाओ fail;

	/* revalidate */
	ehc->i.flags |= ATA_EHI_POST_SETMODE;
	rc = ata_dev_revalidate(dev, ATA_DEV_UNKNOWN, 0);
	ehc->i.flags &= ~ATA_EHI_POST_SETMODE;
	अगर (rc)
		वापस rc;

	अगर (dev->xfer_shअगरt == ATA_SHIFT_PIO) अणु
		/* Old CFA may refuse this command, which is just fine */
		अगर (ata_id_is_cfa(dev->id))
			ign_dev_err = 1;
		/* Catch several broken garbage emulations plus some pre
		   ATA devices */
		अगर (ata_id_major_version(dev->id) == 0 &&
					dev->pio_mode <= XFER_PIO_2)
			ign_dev_err = 1;
		/* Some very old devices and some bad newer ones fail
		   any kind of SET_XFERMODE request but support PIO0-2
		   timings and no IORDY */
		अगर (!ata_id_has_iordy(dev->id) && dev->pio_mode <= XFER_PIO_2)
			ign_dev_err = 1;
	पूर्ण
	/* Early MWDMA devices करो DMA but करोn't allow DMA mode setting.
	   Don't fail an MWDMA0 set IFF the device indicates it is in MWDMA0 */
	अगर (dev->xfer_shअगरt == ATA_SHIFT_MWDMA &&
	    dev->dma_mode == XFER_MW_DMA_0 &&
	    (dev->id[63] >> 8) & 1)
		ign_dev_err = 1;

	/* अगर the device is actually configured correctly, ignore dev err */
	अगर (dev->xfer_mode == ata_xfer_mask2mode(ata_id_xfermask(dev->id)))
		ign_dev_err = 1;

	अगर (err_mask & AC_ERR_DEV) अणु
		अगर (!ign_dev_err)
			जाओ fail;
		अन्यथा
			dev_err_whine = " (device error ignored)";
	पूर्ण

	DPRINTK("xfer_shift=%u, xfer_mode=0x%x\n",
		dev->xfer_shअगरt, (पूर्णांक)dev->xfer_mode);

	अगर (!(ehc->i.flags & ATA_EHI_QUIET) ||
	    ehc->i.flags & ATA_EHI_DID_HARDRESET)
		ata_dev_info(dev, "configured for %s%s\n",
			     ata_mode_string(ata_xfer_mode2mask(dev->xfer_mode)),
			     dev_err_whine);

	वापस 0;

 fail:
	ata_dev_err(dev, "failed to set xfermode (err_mask=0x%x)\n", err_mask);
	वापस -EIO;
पूर्ण

/**
 *	ata_करो_set_mode - Program timings and issue SET FEATURES - XFER
 *	@link: link on which timings will be programmed
 *	@r_failed_dev: out parameter क्रम failed device
 *
 *	Standard implementation of the function used to tune and set
 *	ATA device disk transfer mode (PIO3, UDMA6, etc.).  If
 *	ata_dev_set_mode() fails, poपूर्णांकer to the failing device is
 *	वापसed in @r_failed_dev.
 *
 *	LOCKING:
 *	PCI/etc. bus probe sem.
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं otherwise
 */

पूर्णांक ata_करो_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed_dev)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_device *dev;
	पूर्णांक rc = 0, used_dma = 0, found = 0;

	/* step 1: calculate xfer_mask */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		अचिन्हित दीर्घ pio_mask, dma_mask;
		अचिन्हित पूर्णांक mode_mask;

		mode_mask = ATA_DMA_MASK_ATA;
		अगर (dev->class == ATA_DEV_ATAPI)
			mode_mask = ATA_DMA_MASK_ATAPI;
		अन्यथा अगर (ata_id_is_cfa(dev->id))
			mode_mask = ATA_DMA_MASK_CFA;

		ata_dev_xfermask(dev);
		ata_क्रमce_xfermask(dev);

		pio_mask = ata_pack_xfermask(dev->pio_mask, 0, 0);

		अगर (libata_dma_mask & mode_mask)
			dma_mask = ata_pack_xfermask(0, dev->mwdma_mask,
						     dev->udma_mask);
		अन्यथा
			dma_mask = 0;

		dev->pio_mode = ata_xfer_mask2mode(pio_mask);
		dev->dma_mode = ata_xfer_mask2mode(dma_mask);

		found = 1;
		अगर (ata_dma_enabled(dev))
			used_dma = 1;
	पूर्ण
	अगर (!found)
		जाओ out;

	/* step 2: always set host PIO timings */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		अगर (dev->pio_mode == 0xff) अणु
			ata_dev_warn(dev, "no PIO support\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		dev->xfer_mode = dev->pio_mode;
		dev->xfer_shअगरt = ATA_SHIFT_PIO;
		अगर (ap->ops->set_piomode)
			ap->ops->set_piomode(ap, dev);
	पूर्ण

	/* step 3: set host DMA timings */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		अगर (!ata_dma_enabled(dev))
			जारी;

		dev->xfer_mode = dev->dma_mode;
		dev->xfer_shअगरt = ata_xfer_mode2shअगरt(dev->dma_mode);
		अगर (ap->ops->set_dmamode)
			ap->ops->set_dmamode(ap, dev);
	पूर्ण

	/* step 4: update devices' xfer mode */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		rc = ata_dev_set_mode(dev);
		अगर (rc)
			जाओ out;
	पूर्ण

	/* Record simplex status. If we selected DMA then the other
	 * host channels are not permitted to करो so.
	 */
	अगर (used_dma && (ap->host->flags & ATA_HOST_SIMPLEX))
		ap->host->simplex_claimed = ap;

 out:
	अगर (rc)
		*r_failed_dev = dev;
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_करो_set_mode);

/**
 *	ata_रुको_पढ़ोy - रुको क्रम link to become पढ़ोy
 *	@link: link to be रुकोed on
 *	@deadline: deadline jअगरfies क्रम the operation
 *	@check_पढ़ोy: callback to check link पढ़ोiness
 *
 *	Wait क्रम @link to become पढ़ोy.  @check_पढ़ोy should वापस
 *	positive number अगर @link is पढ़ोy, 0 अगर it isn't, -ENODEV अगर
 *	link करोesn't seem to be occupied, other त्रुटि_सं क्रम other error
 *	conditions.
 *
 *	Transient -ENODEV conditions are allowed क्रम
 *	ATA_TMOUT_FF_WAIT.
 *
 *	LOCKING:
 *	EH context.
 *
 *	RETURNS:
 *	0 अगर @link is पढ़ोy beक्रमe @deadline; otherwise, -त्रुटि_सं.
 */
पूर्णांक ata_रुको_पढ़ोy(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline,
		   पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *link))
अणु
	अचिन्हित दीर्घ start = jअगरfies;
	अचिन्हित दीर्घ nodev_deadline;
	पूर्णांक warned = 0;

	/* choose which 0xff समयout to use, पढ़ो comment in libata.h */
	अगर (link->ap->host->flags & ATA_HOST_PARALLEL_SCAN)
		nodev_deadline = ata_deadline(start, ATA_TMOUT_FF_WAIT_LONG);
	अन्यथा
		nodev_deadline = ata_deadline(start, ATA_TMOUT_FF_WAIT);

	/* Slave पढ़ोiness can't be tested separately from master.  On
	 * M/S emulation configuration, this function should be called
	 * only on the master and it will handle both master and slave.
	 */
	WARN_ON(link == link->ap->slave_link);

	अगर (समय_after(nodev_deadline, deadline))
		nodev_deadline = deadline;

	जबतक (1) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		पूर्णांक पढ़ोy, पंचांगp;

		पढ़ोy = पंचांगp = check_पढ़ोy(link);
		अगर (पढ़ोy > 0)
			वापस 0;

		/*
		 * -ENODEV could be transient.  Ignore -ENODEV अगर link
		 * is online.  Also, some SATA devices take a दीर्घ
		 * समय to clear 0xff after reset.  Wait क्रम
		 * ATA_TMOUT_FF_WAIT[_LONG] on -ENODEV अगर link isn't
		 * offline.
		 *
		 * Note that some PATA controllers (pata_ali) explode
		 * अगर status रेजिस्टर is पढ़ो more than once when
		 * there's no device attached.
		 */
		अगर (पढ़ोy == -ENODEV) अणु
			अगर (ata_link_online(link))
				पढ़ोy = 0;
			अन्यथा अगर ((link->ap->flags & ATA_FLAG_SATA) &&
				 !ata_link_offline(link) &&
				 समय_beक्रमe(now, nodev_deadline))
				पढ़ोy = 0;
		पूर्ण

		अगर (पढ़ोy)
			वापस पढ़ोy;
		अगर (समय_after(now, deadline))
			वापस -EBUSY;

		अगर (!warned && समय_after(now, start + 5 * HZ) &&
		    (deadline - now > 3 * HZ)) अणु
			ata_link_warn(link,
				"link is slow to respond, please be patient "
				"(ready=%d)\n", पंचांगp);
			warned = 1;
		पूर्ण

		ata_msleep(link->ap, 50);
	पूर्ण
पूर्ण

/**
 *	ata_रुको_after_reset - रुको क्रम link to become पढ़ोy after reset
 *	@link: link to be रुकोed on
 *	@deadline: deadline jअगरfies क्रम the operation
 *	@check_पढ़ोy: callback to check link पढ़ोiness
 *
 *	Wait क्रम @link to become पढ़ोy after reset.
 *
 *	LOCKING:
 *	EH context.
 *
 *	RETURNS:
 *	0 अगर @link is पढ़ोy beक्रमe @deadline; otherwise, -त्रुटि_सं.
 */
पूर्णांक ata_रुको_after_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline,
				पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *link))
अणु
	ata_msleep(link->ap, ATA_WAIT_AFTER_RESET);

	वापस ata_रुको_पढ़ोy(link, deadline, check_पढ़ोy);
पूर्ण
EXPORT_SYMBOL_GPL(ata_रुको_after_reset);

/**
 *	ata_std_prereset - prepare क्रम reset
 *	@link: ATA link to be reset
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	@link is about to be reset.  Initialize it.  Failure from
 *	prereset makes libata पात whole reset sequence and give up
 *	that port, so prereset should be best-efक्रमt.  It करोes its
 *	best to prepare क्रम reset sequence but अगर things go wrong, it
 *	should just whine, not fail.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_std_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(ehc);
	पूर्णांक rc;

	/* अगर we're about to करो hardreset, nothing more to करो */
	अगर (ehc->i.action & ATA_EH_HARDRESET)
		वापस 0;

	/* अगर SATA, resume link */
	अगर (ap->flags & ATA_FLAG_SATA) अणु
		rc = sata_link_resume(link, timing, deadline);
		/* whine about phy resume failure but proceed */
		अगर (rc && rc != -EOPNOTSUPP)
			ata_link_warn(link,
				      "failed to resume link for reset (errno=%d)\n",
				      rc);
	पूर्ण

	/* no poपूर्णांक in trying softreset on offline link */
	अगर (ata_phys_link_offline(link))
		ehc->i.action &= ~ATA_EH_SOFTRESET;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_std_prereset);

/**
 *	sata_std_hardreset - COMRESET w/o रुकोing or classअगरication
 *	@link: link to reset
 *	@class: resulting class of attached device
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Standard SATA COMRESET w/o रुकोing or classअगरication.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 अगर link offline, -EAGAIN अगर link online, -त्रुटि_सं on errors.
 */
पूर्णांक sata_std_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
		       अचिन्हित दीर्घ deadline)
अणु
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(&link->eh_context);
	bool online;
	पूर्णांक rc;

	/* करो hardreset */
	rc = sata_link_hardreset(link, timing, deadline, &online, शून्य);
	वापस online ? -EAGAIN : rc;
पूर्ण
EXPORT_SYMBOL_GPL(sata_std_hardreset);

/**
 *	ata_std_postreset - standard postreset callback
 *	@link: the target ata_link
 *	@classes: classes of attached devices
 *
 *	This function is invoked after a successful reset.  Note that
 *	the device might have been reset more than once using
 *	dअगरferent reset methods beक्रमe postreset is invoked.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 */
व्योम ata_std_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes)
अणु
	u32 serror;

	DPRINTK("ENTER\n");

	/* reset complete, clear SError */
	अगर (!sata_scr_पढ़ो(link, SCR_ERROR, &serror))
		sata_scr_ग_लिखो(link, SCR_ERROR, serror);

	/* prपूर्णांक link status */
	sata_prपूर्णांक_link_status(link);

	DPRINTK("EXIT\n");
पूर्ण
EXPORT_SYMBOL_GPL(ata_std_postreset);

/**
 *	ata_dev_same_device - Determine whether new ID matches configured device
 *	@dev: device to compare against
 *	@new_class: class of the new device
 *	@new_id: IDENTIFY page of the new device
 *
 *	Compare @new_class and @new_id against @dev and determine
 *	whether @dev is the device indicated by @new_class and
 *	@new_id.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	1 अगर @dev matches @new_class and @new_id, 0 otherwise.
 */
अटल पूर्णांक ata_dev_same_device(काष्ठा ata_device *dev, अचिन्हित पूर्णांक new_class,
			       स्थिर u16 *new_id)
अणु
	स्थिर u16 *old_id = dev->id;
	अचिन्हित अक्षर model[2][ATA_ID_PROD_LEN + 1];
	अचिन्हित अक्षर serial[2][ATA_ID_SERNO_LEN + 1];

	अगर (dev->class != new_class) अणु
		ata_dev_info(dev, "class mismatch %d != %d\n",
			     dev->class, new_class);
		वापस 0;
	पूर्ण

	ata_id_c_string(old_id, model[0], ATA_ID_PROD, माप(model[0]));
	ata_id_c_string(new_id, model[1], ATA_ID_PROD, माप(model[1]));
	ata_id_c_string(old_id, serial[0], ATA_ID_SERNO, माप(serial[0]));
	ata_id_c_string(new_id, serial[1], ATA_ID_SERNO, माप(serial[1]));

	अगर (म_भेद(model[0], model[1])) अणु
		ata_dev_info(dev, "model number mismatch '%s' != '%s'\n",
			     model[0], model[1]);
		वापस 0;
	पूर्ण

	अगर (म_भेद(serial[0], serial[1])) अणु
		ata_dev_info(dev, "serial number mismatch '%s' != '%s'\n",
			     serial[0], serial[1]);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/**
 *	ata_dev_reपढ़ो_id - Re-पढ़ो IDENTIFY data
 *	@dev: target ATA device
 *	@पढ़ोid_flags: पढ़ो ID flags
 *
 *	Re-पढ़ो IDENTIFY page and make sure @dev is still attached to
 *	the port.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं otherwise
 */
पूर्णांक ata_dev_reपढ़ो_id(काष्ठा ata_device *dev, अचिन्हित पूर्णांक पढ़ोid_flags)
अणु
	अचिन्हित पूर्णांक class = dev->class;
	u16 *id = (व्योम *)dev->link->ap->sector_buf;
	पूर्णांक rc;

	/* पढ़ो ID data */
	rc = ata_dev_पढ़ो_id(dev, &class, पढ़ोid_flags, id);
	अगर (rc)
		वापस rc;

	/* is the device still there? */
	अगर (!ata_dev_same_device(dev, class, id))
		वापस -ENODEV;

	स_नकल(dev->id, id, माप(id[0]) * ATA_ID_WORDS);
	वापस 0;
पूर्ण

/**
 *	ata_dev_revalidate - Revalidate ATA device
 *	@dev: device to revalidate
 *	@new_class: new class code
 *	@पढ़ोid_flags: पढ़ो ID flags
 *
 *	Re-पढ़ो IDENTIFY page, make sure @dev is still attached to the
 *	port and reconfigure it according to the new IDENTIFY page.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं otherwise
 */
पूर्णांक ata_dev_revalidate(काष्ठा ata_device *dev, अचिन्हित पूर्णांक new_class,
		       अचिन्हित पूर्णांक पढ़ोid_flags)
अणु
	u64 n_sectors = dev->n_sectors;
	u64 n_native_sectors = dev->n_native_sectors;
	पूर्णांक rc;

	अगर (!ata_dev_enabled(dev))
		वापस -ENODEV;

	/* fail early अगर !ATA && !ATAPI to aव्योम issuing [P]IDENTIFY to PMP */
	अगर (ata_class_enabled(new_class) &&
	    new_class != ATA_DEV_ATA &&
	    new_class != ATA_DEV_ATAPI &&
	    new_class != ATA_DEV_ZAC &&
	    new_class != ATA_DEV_SEMB) अणु
		ata_dev_info(dev, "class mismatch %u != %u\n",
			     dev->class, new_class);
		rc = -ENODEV;
		जाओ fail;
	पूर्ण

	/* re-पढ़ो ID */
	rc = ata_dev_reपढ़ो_id(dev, पढ़ोid_flags);
	अगर (rc)
		जाओ fail;

	/* configure device according to the new ID */
	rc = ata_dev_configure(dev);
	अगर (rc)
		जाओ fail;

	/* verअगरy n_sectors hasn't changed */
	अगर (dev->class != ATA_DEV_ATA || !n_sectors ||
	    dev->n_sectors == n_sectors)
		वापस 0;

	/* n_sectors has changed */
	ata_dev_warn(dev, "n_sectors mismatch %llu != %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)n_sectors,
		     (अचिन्हित दीर्घ दीर्घ)dev->n_sectors);

	/*
	 * Something could have caused HPA to be unlocked
	 * involuntarily.  If n_native_sectors hasn't changed and the
	 * new size matches it, keep the device.
	 */
	अगर (dev->n_native_sectors == n_native_sectors &&
	    dev->n_sectors > n_sectors && dev->n_sectors == n_native_sectors) अणु
		ata_dev_warn(dev,
			     "new n_sectors matches native, probably "
			     "late HPA unlock, n_sectors updated\n");
		/* use the larger n_sectors */
		वापस 0;
	पूर्ण

	/*
	 * Some BIOSes boot w/o HPA but resume w/ HPA locked.  Try
	 * unlocking HPA in those हालs.
	 *
	 * https://bugzilla.kernel.org/show_bug.cgi?id=15396
	 */
	अगर (dev->n_native_sectors == n_native_sectors &&
	    dev->n_sectors < n_sectors && n_sectors == n_native_sectors &&
	    !(dev->horkage & ATA_HORKAGE_BROKEN_HPA)) अणु
		ata_dev_warn(dev,
			     "old n_sectors matches native, probably "
			     "late HPA lock, will try to unlock HPA\n");
		/* try unlocking HPA */
		dev->flags |= ATA_DFLAG_UNLOCK_HPA;
		rc = -EIO;
	पूर्ण अन्यथा
		rc = -ENODEV;

	/* restore original n_[native_]sectors and fail */
	dev->n_native_sectors = n_native_sectors;
	dev->n_sectors = n_sectors;
 fail:
	ata_dev_err(dev, "revalidation failed (errno=%d)\n", rc);
	वापस rc;
पूर्ण

काष्ठा ata_blacklist_entry अणु
	स्थिर अक्षर *model_num;
	स्थिर अक्षर *model_rev;
	अचिन्हित दीर्घ horkage;
पूर्ण;

अटल स्थिर काष्ठा ata_blacklist_entry ata_device_blacklist [] = अणु
	/* Devices with DMA related problems under Linux */
	अणु "WDC AC11000H",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "WDC AC22100H",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "WDC AC32500H",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "WDC AC33100H",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "WDC AC31600H",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "WDC AC32100H",	"24.09P07",	ATA_HORKAGE_NODMA पूर्ण,
	अणु "WDC AC23200L",	"21.10N21",	ATA_HORKAGE_NODMA पूर्ण,
	अणु "Compaq CRD-8241B", 	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "CRD-8400B",		शून्य, 		ATA_HORKAGE_NODMA पूर्ण,
	अणु "CRD-848[02]B",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "CRD-84",		शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "SanDisk SDP3B",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "SanDisk SDP3B-64",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "SANYO CD-ROM CRD",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "HITACHI CDR-8",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "HITACHI CDR-8[34]35",शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "Toshiba CD-ROM XM-6202B", शून्य,	ATA_HORKAGE_NODMA पूर्ण,
	अणु "TOSHIBA CD-ROM XM-1702BC", शून्य,	ATA_HORKAGE_NODMA पूर्ण,
	अणु "CD-532E-A", 		शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "E-IDE CD-ROM CR-840",शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "CD-ROM Drive/F5A",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "WPI CDD-820", 	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "SAMSUNG CD-ROM SC-148C", शून्य,	ATA_HORKAGE_NODMA पूर्ण,
	अणु "SAMSUNG CD-ROM SC",	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "ATAPI CD-ROM DRIVE 40X MAXIMUM",शून्य,ATA_HORKAGE_NODMA पूर्ण,
	अणु "_NEC DV5800A", 	शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु "SAMSUNG CD-ROM SN-124", "N001",	ATA_HORKAGE_NODMA पूर्ण,
	अणु "Seagate STT20000A", शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	अणु " 2GB ATA Flash Disk", "ADMA428M",	ATA_HORKAGE_NODMA पूर्ण,
	अणु "VRFDFC22048UCHC-TE*", शून्य,		ATA_HORKAGE_NODMA पूर्ण,
	/* Odd clown on sil3726/4726 PMPs */
	अणु "Config  Disk",	शून्य,		ATA_HORKAGE_DISABLE पूर्ण,

	/* Weird ATAPI devices */
	अणु "TORiSAN DVD-ROM DRD-N216", शून्य,	ATA_HORKAGE_MAX_SEC_128 पूर्ण,
	अणु "QUANTUM DAT    DAT72-000", शून्य,	ATA_HORKAGE_ATAPI_MOD16_DMA पूर्ण,
	अणु "Slimtype DVD A  DS8A8SH", शून्य,	ATA_HORKAGE_MAX_SEC_LBA48 पूर्ण,
	अणु "Slimtype DVD A  DS8A9SH", शून्य,	ATA_HORKAGE_MAX_SEC_LBA48 पूर्ण,

	/*
	 * Causes silent data corruption with higher max sects.
	 * http://lkml.kernel.org/g/x49wpy40ysk.fsf@segfault.boston.devel.redhat.com
	 */
	अणु "ST380013AS",		"3.20",		ATA_HORKAGE_MAX_SEC_1024 पूर्ण,

	/*
	 * These devices समय out with higher max sects.
	 * https://bugzilla.kernel.org/show_bug.cgi?id=121671
	 */
	अणु "LITEON CX1-JB*-HP",	शून्य,		ATA_HORKAGE_MAX_SEC_1024 पूर्ण,
	अणु "LITEON EP1-*",	शून्य,		ATA_HORKAGE_MAX_SEC_1024 पूर्ण,

	/* Devices we expect to fail diagnostics */

	/* Devices where NCQ should be aव्योमed */
	/* NCQ is slow */
	अणु "WDC WD740ADFD-00",	शून्य,		ATA_HORKAGE_NONCQ पूर्ण,
	अणु "WDC WD740ADFD-00NLR1", शून्य,		ATA_HORKAGE_NONCQ, पूर्ण,
	/* http://thपढ़ो.gmane.org/gmane.linux.ide/14907 */
	अणु "FUJITSU MHT2060BH",	शून्य,		ATA_HORKAGE_NONCQ पूर्ण,
	/* NCQ is broken */
	अणु "Maxtor *",		"BANC*",	ATA_HORKAGE_NONCQ पूर्ण,
	अणु "Maxtor 7V300F0",	"VA111630",	ATA_HORKAGE_NONCQ पूर्ण,
	अणु "ST380817AS",		"3.42",		ATA_HORKAGE_NONCQ पूर्ण,
	अणु "ST3160023AS",	"3.42",		ATA_HORKAGE_NONCQ पूर्ण,
	अणु "OCZ CORE_SSD",	"02.10104",	ATA_HORKAGE_NONCQ पूर्ण,

	/* Seagate NCQ + FLUSH CACHE firmware bug */
	अणु "ST31500341AS",	"SD1[5-9]",	ATA_HORKAGE_NONCQ |
						ATA_HORKAGE_FIRMWARE_WARN पूर्ण,

	अणु "ST31000333AS",	"SD1[5-9]",	ATA_HORKAGE_NONCQ |
						ATA_HORKAGE_FIRMWARE_WARN पूर्ण,

	अणु "ST3640[36]23AS",	"SD1[5-9]",	ATA_HORKAGE_NONCQ |
						ATA_HORKAGE_FIRMWARE_WARN पूर्ण,

	अणु "ST3320[68]13AS",	"SD1[5-9]",	ATA_HORKAGE_NONCQ |
						ATA_HORKAGE_FIRMWARE_WARN पूर्ण,

	/* drives which fail FPDMA_AA activation (some may मुक्तze afterwards)
	   the ST disks also have LPM issues */
	अणु "ST1000LM024 HN-M101MBB", शून्य,	ATA_HORKAGE_BROKEN_FPDMA_AA |
						ATA_HORKAGE_NOLPM, पूर्ण,
	अणु "VB0250EAVER",	"HPG7",		ATA_HORKAGE_BROKEN_FPDMA_AA पूर्ण,

	/* Blacklist entries taken from Silicon Image 3124/3132
	   Winकरोws driver .inf file - also several Linux problem reports */
	अणु "HTS541060G9SA00",    "MB3OC60D",     ATA_HORKAGE_NONCQ, पूर्ण,
	अणु "HTS541080G9SA00",    "MB4OC60D",     ATA_HORKAGE_NONCQ, पूर्ण,
	अणु "HTS541010G9SA00",    "MBZOC60D",     ATA_HORKAGE_NONCQ, पूर्ण,

	/* https://bugzilla.kernel.org/show_bug.cgi?id=15573 */
	अणु "C300-CTFDDAC128MAG",	"0001",		ATA_HORKAGE_NONCQ, पूर्ण,

	/* Sandisk SD7/8/9s lock up hard on large trims */
	अणु "SanDisk SD[789]*",	शून्य,		ATA_HORKAGE_MAX_TRIM_128M, पूर्ण,

	/* devices which puke on READ_NATIVE_MAX */
	अणु "HDS724040KLSA80",	"KFAOA20N",	ATA_HORKAGE_BROKEN_HPA, पूर्ण,
	अणु "WDC WD3200JD-00KLB0", "WD-WCAMR1130137", ATA_HORKAGE_BROKEN_HPA पूर्ण,
	अणु "WDC WD2500JD-00HBB0", "WD-WMAL71490727", ATA_HORKAGE_BROKEN_HPA पूर्ण,
	अणु "MAXTOR 6L080L4",	"A93.0500",	ATA_HORKAGE_BROKEN_HPA पूर्ण,

	/* this one allows HPA unlocking but fails IOs on the area */
	अणु "OCZ-VERTEX",		    "1.30",	ATA_HORKAGE_BROKEN_HPA पूर्ण,

	/* Devices which report 1 sector over size HPA */
	अणु "ST340823A",		शून्य,		ATA_HORKAGE_HPA_SIZE, पूर्ण,
	अणु "ST320413A",		शून्य,		ATA_HORKAGE_HPA_SIZE, पूर्ण,
	अणु "ST310211A",		शून्य,		ATA_HORKAGE_HPA_SIZE, पूर्ण,

	/* Devices which get the IVB wrong */
	अणु "QUANTUM FIREBALLlct10 05", "A03.0900", ATA_HORKAGE_IVB, पूर्ण,
	/* Maybe we should just blacklist TSSTcorp... */
	अणु "TSSTcorp CDDVDW SH-S202[HJN]", "SB0[01]",  ATA_HORKAGE_IVB, पूर्ण,

	/* Devices that करो not need bridging limits applied */
	अणु "MTRON MSP-SATA*",		शून्य,	ATA_HORKAGE_BRIDGE_OK, पूर्ण,
	अणु "BUFFALO HD-QSU2/R5",		शून्य,	ATA_HORKAGE_BRIDGE_OK, पूर्ण,

	/* Devices which aren't very happy with higher link speeds */
	अणु "WD My Book",			शून्य,	ATA_HORKAGE_1_5_GBPS, पूर्ण,
	अणु "Seagate FreeAgent GoFlex",	शून्य,	ATA_HORKAGE_1_5_GBPS, पूर्ण,

	/*
	 * Devices which choke on SETXFER.  Applies only अगर both the
	 * device and controller are SATA.
	 */
	अणु "PIONEER DVD-RW  DVRTD08",	शून्य,	ATA_HORKAGE_NOSETXFER पूर्ण,
	अणु "PIONEER DVD-RW  DVRTD08A",	शून्य,	ATA_HORKAGE_NOSETXFER पूर्ण,
	अणु "PIONEER DVD-RW  DVR-215",	शून्य,	ATA_HORKAGE_NOSETXFER पूर्ण,
	अणु "PIONEER DVD-RW  DVR-212D",	शून्य,	ATA_HORKAGE_NOSETXFER पूर्ण,
	अणु "PIONEER DVD-RW  DVR-216D",	शून्य,	ATA_HORKAGE_NOSETXFER पूर्ण,

	/* Crucial BX100 SSD 500GB has broken LPM support */
	अणु "CT500BX100SSD1",		शून्य,	ATA_HORKAGE_NOLPM पूर्ण,

	/* 512GB MX100 with MU01 firmware has both queued TRIM and LPM issues */
	अणु "Crucial_CT512MX100*",	"MU01",	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM |
						ATA_HORKAGE_NOLPM, पूर्ण,
	/* 512GB MX100 with newer firmware has only LPM issues */
	अणु "Crucial_CT512MX100*",	शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM |
						ATA_HORKAGE_NOLPM, पूर्ण,

	/* 480GB+ M500 SSDs have both queued TRIM and LPM issues */
	अणु "Crucial_CT480M500*",		शून्य,	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM |
						ATA_HORKAGE_NOLPM, पूर्ण,
	अणु "Crucial_CT960M500*",		शून्य,	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM |
						ATA_HORKAGE_NOLPM, पूर्ण,

	/* These specअगरic Samsung models/firmware-revs करो not handle LPM well */
	अणु "SAMSUNG MZMPC128HBFU-000MV", "CXM14M1Q", ATA_HORKAGE_NOLPM, पूर्ण,
	अणु "SAMSUNG SSD PM830 mSATA *",  "CXM13D1Q", ATA_HORKAGE_NOLPM, पूर्ण,
	अणु "SAMSUNG MZ7TD256HAFV-000L9", शून्य,       ATA_HORKAGE_NOLPM, पूर्ण,
	अणु "SAMSUNG MZ7TE512HMHP-000L1", "EXT06L0Q", ATA_HORKAGE_NOLPM, पूर्ण,

	/* devices that करोn't properly handle queued TRIM commands */
	अणु "Micron_M500IT_*",		"MU01",	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Micron_M500_*",		शून्य,	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Crucial_CT*M500*",		शून्य,	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Micron_M5[15]0_*",		"MU01",	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Crucial_CT*M550*",		"MU01",	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Crucial_CT*MX100*",		"MU01",	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Samsung SSD 840*",		शून्य,	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Samsung SSD 850*",		शून्य,	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "FCCT*M500*",			शून्य,	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,

	/* devices that करोn't properly handle TRIM commands */
	अणु "SuperSSpeed S238*",		शून्य,	ATA_HORKAGE_NOTRIM, पूर्ण,

	/*
	 * As defined, the DRAT (Deterministic Read After Trim) and RZAT
	 * (Return Zero After Trim) flags in the ATA Command Set are
	 * unreliable in the sense that they only define what happens अगर
	 * the device successfully executed the DSM TRIM command. TRIM
	 * is only advisory, however, and the device is मुक्त to silently
	 * ignore all or parts of the request.
	 *
	 * Whitelist drives that are known to reliably वापस zeroes
	 * after TRIM.
	 */

	/*
	 * The पूर्णांकel 510 drive has buggy DRAT/RZAT. Explicitly exclude
	 * that model beक्रमe whitelisting all other पूर्णांकel SSDs.
	 */
	अणु "INTEL*SSDSC2MH*",		शून्य,	0, पूर्ण,

	अणु "Micron*",			शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Crucial*",			शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "INTEL*SSD*", 		शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "SSD*INTEL*",			शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "Samsung*SSD*",		शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "SAMSUNG*SSD*",		शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "SAMSUNG*MZ7KM*",		शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,
	अणु "ST[1248][0248]0[FH]*",	शून्य,	ATA_HORKAGE_ZERO_AFTER_TRIM, पूर्ण,

	/*
	 * Some WD SATA-I drives spin up and करोwn erratically when the link
	 * is put पूर्णांकo the slumber mode.  We करोn't have full list of the
	 * affected devices.  Disable LPM अगर the device matches one of the
	 * known prefixes and is SATA-1.  As a side effect LPM partial is
	 * lost too.
	 *
	 * https://bugzilla.kernel.org/show_bug.cgi?id=57211
	 */
	अणु "WDC WD800JD-*",		शून्य,	ATA_HORKAGE_WD_BROKEN_LPM पूर्ण,
	अणु "WDC WD1200JD-*",		शून्य,	ATA_HORKAGE_WD_BROKEN_LPM पूर्ण,
	अणु "WDC WD1600JD-*",		शून्य,	ATA_HORKAGE_WD_BROKEN_LPM पूर्ण,
	अणु "WDC WD2000JD-*",		शून्य,	ATA_HORKAGE_WD_BROKEN_LPM पूर्ण,
	अणु "WDC WD2500JD-*",		शून्य,	ATA_HORKAGE_WD_BROKEN_LPM पूर्ण,
	अणु "WDC WD3000JD-*",		शून्य,	ATA_HORKAGE_WD_BROKEN_LPM पूर्ण,
	अणु "WDC WD3200JD-*",		शून्य,	ATA_HORKAGE_WD_BROKEN_LPM पूर्ण,

	/* End Marker */
	अणु पूर्ण
पूर्ण;

अटल अचिन्हित दीर्घ ata_dev_blacklisted(स्थिर काष्ठा ata_device *dev)
अणु
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];
	अचिन्हित अक्षर model_rev[ATA_ID_FW_REV_LEN + 1];
	स्थिर काष्ठा ata_blacklist_entry *ad = ata_device_blacklist;

	ata_id_c_string(dev->id, model_num, ATA_ID_PROD, माप(model_num));
	ata_id_c_string(dev->id, model_rev, ATA_ID_FW_REV, माप(model_rev));

	जबतक (ad->model_num) अणु
		अगर (glob_match(ad->model_num, model_num)) अणु
			अगर (ad->model_rev == शून्य)
				वापस ad->horkage;
			अगर (glob_match(ad->model_rev, model_rev))
				वापस ad->horkage;
		पूर्ण
		ad++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ata_dma_blacklisted(स्थिर काष्ठा ata_device *dev)
अणु
	/* We करोn't support polling DMA.
	 * DMA blacklist those ATAPI devices with CDB-पूर्णांकr (and use PIO)
	 * अगर the LLDD handles only पूर्णांकerrupts in the HSM_ST_LAST state.
	 */
	अगर ((dev->link->ap->flags & ATA_FLAG_PIO_POLLING) &&
	    (dev->flags & ATA_DFLAG_CDB_INTR))
		वापस 1;
	वापस (dev->horkage & ATA_HORKAGE_NODMA) ? 1 : 0;
पूर्ण

/**
 *	ata_is_40wire		-	check drive side detection
 *	@dev: device
 *
 *	Perक्रमm drive side detection decoding, allowing क्रम device venकरोrs
 *	who can't follow the करोcumentation.
 */

अटल पूर्णांक ata_is_40wire(काष्ठा ata_device *dev)
अणु
	अगर (dev->horkage & ATA_HORKAGE_IVB)
		वापस ata_drive_40wire_relaxed(dev->id);
	वापस ata_drive_40wire(dev->id);
पूर्ण

/**
 *	cable_is_40wire		-	40/80/SATA decider
 *	@ap: port to consider
 *
 *	This function encapsulates the policy क्रम speed management
 *	in one place. At the moment we करोn't cache the result but
 *	there is a good हाल क्रम setting ap->cbl to the result when
 *	we are called with unknown cables (and figuring out अगर it
 *	impacts hotplug at all).
 *
 *	Return 1 अगर the cable appears to be 40 wire.
 */

अटल पूर्णांक cable_is_40wire(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;

	/* If the controller thinks we are 40 wire, we are. */
	अगर (ap->cbl == ATA_CBL_PATA40)
		वापस 1;

	/* If the controller thinks we are 80 wire, we are. */
	अगर (ap->cbl == ATA_CBL_PATA80 || ap->cbl == ATA_CBL_SATA)
		वापस 0;

	/* If the प्रणाली is known to be 40 wire लघु cable (eg
	 * laptop), then we allow 80 wire modes even अगर the drive
	 * isn't sure.
	 */
	अगर (ap->cbl == ATA_CBL_PATA40_SHORT)
		वापस 0;

	/* If the controller करोesn't know, we scan.
	 *
	 * Note: We look क्रम all 40 wire detects at this poपूर्णांक.  Any
	 *       80 wire detect is taken to be 80 wire cable because
	 * - in many setups only the one drive (slave अगर present) will
	 *   give a valid detect
	 * - अगर you have a non detect capable drive you करोn't want it
	 *   to colour the choice
	 */
	ata_क्रम_each_link(link, ap, EDGE) अणु
		ata_क्रम_each_dev(dev, link, ENABLED) अणु
			अगर (!ata_is_40wire(dev))
				वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	ata_dev_xfermask - Compute supported xfermask of the given device
 *	@dev: Device to compute xfermask क्रम
 *
 *	Compute supported xfermask of @dev and store it in
 *	dev->*_mask.  This function is responsible क्रम applying all
 *	known limits including host controller limits, device
 *	blacklist, etc...
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम ata_dev_xfermask(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_host *host = ap->host;
	अचिन्हित दीर्घ xfer_mask;

	/* controller modes available */
	xfer_mask = ata_pack_xfermask(ap->pio_mask,
				      ap->mwdma_mask, ap->udma_mask);

	/* drive modes available */
	xfer_mask &= ata_pack_xfermask(dev->pio_mask,
				       dev->mwdma_mask, dev->udma_mask);
	xfer_mask &= ata_id_xfermask(dev->id);

	/*
	 *	CFA Advanced TrueIDE timings are not allowed on a shared
	 *	cable
	 */
	अगर (ata_dev_pair(dev)) अणु
		/* No PIO5 or PIO6 */
		xfer_mask &= ~(0x03 << (ATA_SHIFT_PIO + 5));
		/* No MWDMA3 or MWDMA 4 */
		xfer_mask &= ~(0x03 << (ATA_SHIFT_MWDMA + 3));
	पूर्ण

	अगर (ata_dma_blacklisted(dev)) अणु
		xfer_mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
		ata_dev_warn(dev,
			     "device is on DMA blacklist, disabling DMA\n");
	पूर्ण

	अगर ((host->flags & ATA_HOST_SIMPLEX) &&
	    host->simplex_claimed && host->simplex_claimed != ap) अणु
		xfer_mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
		ata_dev_warn(dev,
			     "simplex DMA is claimed by other device, disabling DMA\n");
	पूर्ण

	अगर (ap->flags & ATA_FLAG_NO_IORDY)
		xfer_mask &= ata_pio_mask_no_iordy(dev);

	अगर (ap->ops->mode_filter)
		xfer_mask = ap->ops->mode_filter(dev, xfer_mask);

	/* Apply cable rule here.  Don't apply it early because when
	 * we handle hot plug the cable type can itself change.
	 * Check this last so that we know अगर the transfer rate was
	 * solely limited by the cable.
	 * Unknown or 80 wire cables reported host side are checked
	 * drive side as well. Cases where we know a 40wire cable
	 * is used safely क्रम 80 are not checked here.
	 */
	अगर (xfer_mask & (0xF8 << ATA_SHIFT_UDMA))
		/* UDMA/44 or higher would be available */
		अगर (cable_is_40wire(ap)) अणु
			ata_dev_warn(dev,
				     "limited to UDMA/33 due to 40-wire cable\n");
			xfer_mask &= ~(0xF8 << ATA_SHIFT_UDMA);
		पूर्ण

	ata_unpack_xfermask(xfer_mask, &dev->pio_mask,
			    &dev->mwdma_mask, &dev->udma_mask);
पूर्ण

/**
 *	ata_dev_set_xfermode - Issue SET FEATURES - XFER MODE command
 *	@dev: Device to which command will be sent
 *
 *	Issue SET FEATURES - XFER MODE command to device @dev
 *	on port @ap.
 *
 *	LOCKING:
 *	PCI/etc. bus probe sem.
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask otherwise.
 */

अटल अचिन्हित पूर्णांक ata_dev_set_xfermode(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;

	/* set up set-features taskfile */
	DPRINTK("set features - xfer mode\n");

	/* Some controllers and ATAPI devices show flaky पूर्णांकerrupt
	 * behavior after setting xfer mode.  Use polling instead.
	 */
	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_SET_FEATURES;
	tf.feature = SETFEATURES_XFER;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_POLLING;
	tf.protocol = ATA_PROT_NODATA;
	/* If we are using IORDY we must send the mode setting command */
	अगर (ata_pio_need_iordy(dev))
		tf.nsect = dev->xfer_mode;
	/* If the device has IORDY and the controller करोes not - turn it off */
 	अन्यथा अगर (ata_id_has_iordy(dev->id))
		tf.nsect = 0x01;
	अन्यथा /* In the ancient relic deparपंचांगent - skip all of this */
		वापस 0;

	/* On some disks, this command causes spin-up, so we need दीर्घer समयout */
	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, 15000);

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	वापस err_mask;
पूर्ण

/**
 *	ata_dev_set_feature - Issue SET FEATURES - SATA FEATURES
 *	@dev: Device to which command will be sent
 *	@enable: Whether to enable or disable the feature
 *	@feature: The sector count represents the feature to set
 *
 *	Issue SET FEATURES - SATA FEATURES command to device @dev
 *	on port @ap with sector count
 *
 *	LOCKING:
 *	PCI/etc. bus probe sem.
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask otherwise.
 */
अचिन्हित पूर्णांक ata_dev_set_feature(काष्ठा ata_device *dev, u8 enable, u8 feature)
अणु
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;
	अचिन्हित दीर्घ समयout = 0;

	/* set up set-features taskfile */
	DPRINTK("set features - SATA features\n");

	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_SET_FEATURES;
	tf.feature = enable;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.protocol = ATA_PROT_NODATA;
	tf.nsect = feature;

	अगर (enable == SETFEATURES_SPINUP)
		समयout = ata_probe_समयout ?
			  ata_probe_समयout * 1000 : SETFEATURES_SPINUP_TIMEOUT;
	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, समयout);

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	वापस err_mask;
पूर्ण
EXPORT_SYMBOL_GPL(ata_dev_set_feature);

/**
 *	ata_dev_init_params - Issue INIT DEV PARAMS command
 *	@dev: Device to which command will be sent
 *	@heads: Number of heads (taskfile parameter)
 *	@sectors: Number of sectors (taskfile parameter)
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask otherwise.
 */
अटल अचिन्हित पूर्णांक ata_dev_init_params(काष्ठा ata_device *dev,
					u16 heads, u16 sectors)
अणु
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;

	/* Number of sectors per track 1-255. Number of heads 1-16 */
	अगर (sectors < 1 || sectors > 255 || heads < 1 || heads > 16)
		वापस AC_ERR_INVALID;

	/* set up init dev params taskfile */
	DPRINTK("init dev params \n");

	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_INIT_DEV_PARAMS;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.protocol = ATA_PROT_NODATA;
	tf.nsect = sectors;
	tf.device |= (heads - 1) & 0x0f; /* max head = num. of heads - 1 */

	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, 0);
	/* A clean पात indicates an original or just out of spec drive
	   and we should जारी as we issue the setup based on the
	   drive reported working geometry */
	अगर (err_mask == AC_ERR_DEV && (tf.feature & ATA_ABORTED))
		err_mask = 0;

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	वापस err_mask;
पूर्ण

/**
 *	atapi_check_dma - Check whether ATAPI DMA can be supported
 *	@qc: Metadata associated with taskfile to check
 *
 *	Allow low-level driver to filter ATA PACKET commands, वापसing
 *	a status indicating whether or not it is OK to use DMA क्रम the
 *	supplied PACKET command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS: 0 when ATAPI DMA can be used
 *               nonzero otherwise
 */
पूर्णांक atapi_check_dma(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	/* Don't allow DMA if it isn't multiple of 16 bytes.  Quite a
	 * few ATAPI devices choke on such DMA requests.
	 */
	अगर (!(qc->dev->horkage & ATA_HORKAGE_ATAPI_MOD16_DMA) &&
	    unlikely(qc->nbytes & 15))
		वापस 1;

	अगर (ap->ops->check_atapi_dma)
		वापस ap->ops->check_atapi_dma(qc);

	वापस 0;
पूर्ण

/**
 *	ata_std_qc_defer - Check whether a qc needs to be deferred
 *	@qc: ATA command in question
 *
 *	Non-NCQ commands cannot run with any other command, NCQ or
 *	not.  As upper layer only knows the queue depth, we are
 *	responsible क्रम मुख्यtaining exclusion.  This function checks
 *	whether a new command @qc can be issued.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	ATA_DEFER_* अगर deferring is needed, 0 otherwise.
 */
पूर्णांक ata_std_qc_defer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_link *link = qc->dev->link;

	अगर (ata_is_ncq(qc->tf.protocol)) अणु
		अगर (!ata_tag_valid(link->active_tag))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!ata_tag_valid(link->active_tag) && !link->sactive)
			वापस 0;
	पूर्ण

	वापस ATA_DEFER_LINK;
पूर्ण
EXPORT_SYMBOL_GPL(ata_std_qc_defer);

क्रमागत ata_completion_errors ata_noop_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	वापस AC_ERR_OK;
पूर्ण
EXPORT_SYMBOL_GPL(ata_noop_qc_prep);

/**
 *	ata_sg_init - Associate command with scatter-gather table.
 *	@qc: Command to be associated
 *	@sg: Scatter-gather table.
 *	@n_elem: Number of elements in s/g table.
 *
 *	Initialize the data-related elements of queued_cmd @qc
 *	to poपूर्णांक to a scatter-gather table @sg, containing @n_elem
 *	elements.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_sg_init(काष्ठा ata_queued_cmd *qc, काष्ठा scatterlist *sg,
		 अचिन्हित पूर्णांक n_elem)
अणु
	qc->sg = sg;
	qc->n_elem = n_elem;
	qc->cursg = qc->sg;
पूर्ण

#अगर_घोषित CONFIG_HAS_DMA

/**
 *	ata_sg_clean - Unmap DMA memory associated with command
 *	@qc: Command containing DMA memory to be released
 *
 *	Unmap all mapped DMA memory associated with this command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल व्योम ata_sg_clean(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा scatterlist *sg = qc->sg;
	पूर्णांक dir = qc->dma_dir;

	WARN_ON_ONCE(sg == शून्य);

	VPRINTK("unmapping %u sg elements\n", qc->n_elem);

	अगर (qc->n_elem)
		dma_unmap_sg(ap->dev, sg, qc->orig_n_elem, dir);

	qc->flags &= ~ATA_QCFLAG_DMAMAP;
	qc->sg = शून्य;
पूर्ण

/**
 *	ata_sg_setup - DMA-map the scatter-gather table associated with a command.
 *	@qc: Command with scatter-gather table to be mapped.
 *
 *	DMA-map the scatter-gather table associated with queued_cmd @qc.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, negative on error.
 *
 */
अटल पूर्णांक ata_sg_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अचिन्हित पूर्णांक n_elem;

	VPRINTK("ENTER, ata%u\n", ap->prपूर्णांक_id);

	n_elem = dma_map_sg(ap->dev, qc->sg, qc->n_elem, qc->dma_dir);
	अगर (n_elem < 1)
		वापस -1;

	VPRINTK("%d sg elements mapped\n", n_elem);
	qc->orig_n_elem = qc->n_elem;
	qc->n_elem = n_elem;
	qc->flags |= ATA_QCFLAG_DMAMAP;

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_HAS_DMA */

अटल अंतरभूत व्योम ata_sg_clean(काष्ठा ata_queued_cmd *qc) अणुपूर्ण
अटल अंतरभूत पूर्णांक ata_sg_setup(काष्ठा ata_queued_cmd *qc) अणु वापस -1; पूर्ण

#पूर्ण_अगर /* !CONFIG_HAS_DMA */

/**
 *	swap_buf_le16 - swap halves of 16-bit words in place
 *	@buf:  Buffer to swap
 *	@buf_words:  Number of 16-bit words in buffer.
 *
 *	Swap halves of 16-bit words अगर needed to convert from
 *	little-endian byte order to native cpu byte order, or
 *	vice-versa.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम swap_buf_le16(u16 *buf, अचिन्हित पूर्णांक buf_words)
अणु
#अगर_घोषित __BIG_ENDIAN
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < buf_words; i++)
		buf[i] = le16_to_cpu(buf[i]);
#पूर्ण_अगर /* __BIG_ENDIAN */
पूर्ण

/**
 *	ata_qc_new_init - Request an available ATA command, and initialize it
 *	@dev: Device from whom we request an available command काष्ठाure
 *	@tag: tag
 *
 *	LOCKING:
 *	None.
 */

काष्ठा ata_queued_cmd *ata_qc_new_init(काष्ठा ata_device *dev, पूर्णांक tag)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_queued_cmd *qc;

	/* no command जबतक frozen */
	अगर (unlikely(ap->pflags & ATA_PFLAG_FROZEN))
		वापस शून्य;

	/* libsas हाल */
	अगर (ap->flags & ATA_FLAG_SAS_HOST) अणु
		tag = ata_sas_allocate_tag(ap);
		अगर (tag < 0)
			वापस शून्य;
	पूर्ण

	qc = __ata_qc_from_tag(ap, tag);
	qc->tag = qc->hw_tag = tag;
	qc->scsicmd = शून्य;
	qc->ap = ap;
	qc->dev = dev;

	ata_qc_reinit(qc);

	वापस qc;
पूर्ण

/**
 *	ata_qc_मुक्त - मुक्त unused ata_queued_cmd
 *	@qc: Command to complete
 *
 *	Deचिन्हित to मुक्त unused ata_queued_cmd object
 *	in हाल something prevents using it.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_qc_मुक्त(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap;
	अचिन्हित पूर्णांक tag;

	WARN_ON_ONCE(qc == शून्य); /* ata_qc_from_tag _might_ वापस शून्य */
	ap = qc->ap;

	qc->flags = 0;
	tag = qc->tag;
	अगर (ata_tag_valid(tag)) अणु
		qc->tag = ATA_TAG_POISON;
		अगर (ap->flags & ATA_FLAG_SAS_HOST)
			ata_sas_मुक्त_tag(tag, ap);
	पूर्ण
पूर्ण

व्योम __ata_qc_complete(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap;
	काष्ठा ata_link *link;

	WARN_ON_ONCE(qc == शून्य); /* ata_qc_from_tag _might_ वापस शून्य */
	WARN_ON_ONCE(!(qc->flags & ATA_QCFLAG_ACTIVE));
	ap = qc->ap;
	link = qc->dev->link;

	अगर (likely(qc->flags & ATA_QCFLAG_DMAMAP))
		ata_sg_clean(qc);

	/* command should be marked inactive atomically with qc completion */
	अगर (ata_is_ncq(qc->tf.protocol)) अणु
		link->sactive &= ~(1 << qc->hw_tag);
		अगर (!link->sactive)
			ap->nr_active_links--;
	पूर्ण अन्यथा अणु
		link->active_tag = ATA_TAG_POISON;
		ap->nr_active_links--;
	पूर्ण

	/* clear exclusive status */
	अगर (unlikely(qc->flags & ATA_QCFLAG_CLEAR_EXCL &&
		     ap->excl_link == link))
		ap->excl_link = शून्य;

	/* atapi: mark qc as inactive to prevent the पूर्णांकerrupt handler
	 * from completing the command twice later, beक्रमe the error handler
	 * is called. (when rc != 0 and atapi request sense is needed)
	 */
	qc->flags &= ~ATA_QCFLAG_ACTIVE;
	ap->qc_active &= ~(1ULL << qc->tag);

	/* call completion callback */
	qc->complete_fn(qc);
पूर्ण

अटल व्योम fill_result_tf(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	qc->result_tf.flags = qc->tf.flags;
	ap->ops->qc_fill_rtf(qc);
पूर्ण

अटल व्योम ata_verअगरy_xfer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_device *dev = qc->dev;

	अगर (!ata_is_data(qc->tf.protocol))
		वापस;

	अगर ((dev->mwdma_mask || dev->udma_mask) && ata_is_pio(qc->tf.protocol))
		वापस;

	dev->flags &= ~ATA_DFLAG_DUBIOUS_XFER;
पूर्ण

/**
 *	ata_qc_complete - Complete an active ATA command
 *	@qc: Command to complete
 *
 *	Indicate to the mid and upper layers that an ATA command has
 *	completed, with either an ok or not-ok status.
 *
 *	Refrain from calling this function multiple बार when
 *	successfully completing multiple NCQ commands.
 *	ata_qc_complete_multiple() should be used instead, which will
 *	properly update IRQ expect state.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_qc_complete(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	/* Trigger the LED (अगर available) */
	ledtrig_disk_activity(!!(qc->tf.flags & ATA_TFLAG_WRITE));

	/* XXX: New EH and old EH use dअगरferent mechanisms to
	 * synchronize EH with regular execution path.
	 *
	 * In new EH, a failed qc is marked with ATA_QCFLAG_FAILED.
	 * Normal execution path is responsible क्रम not accessing a
	 * failed qc.  libata core enक्रमces the rule by वापसing शून्य
	 * from ata_qc_from_tag() क्रम failed qcs.
	 *
	 * Old EH depends on ata_qc_complete() nullअगरying completion
	 * requests अगर ATA_QCFLAG_EH_SCHEDULED is set.  Old EH करोes
	 * not synchronize with पूर्णांकerrupt handler.  Only PIO task is
	 * taken care of.
	 */
	अगर (ap->ops->error_handler) अणु
		काष्ठा ata_device *dev = qc->dev;
		काष्ठा ata_eh_info *ehi = &dev->link->eh_info;

		अगर (unlikely(qc->err_mask))
			qc->flags |= ATA_QCFLAG_FAILED;

		/*
		 * Finish पूर्णांकernal commands without any further processing
		 * and always with the result TF filled.
		 */
		अगर (unlikely(ata_tag_पूर्णांकernal(qc->tag))) अणु
			fill_result_tf(qc);
			trace_ata_qc_complete_पूर्णांकernal(qc);
			__ata_qc_complete(qc);
			वापस;
		पूर्ण

		/*
		 * Non-पूर्णांकernal qc has failed.  Fill the result TF and
		 * summon EH.
		 */
		अगर (unlikely(qc->flags & ATA_QCFLAG_FAILED)) अणु
			fill_result_tf(qc);
			trace_ata_qc_complete_failed(qc);
			ata_qc_schedule_eh(qc);
			वापस;
		पूर्ण

		WARN_ON_ONCE(ap->pflags & ATA_PFLAG_FROZEN);

		/* पढ़ो result TF अगर requested */
		अगर (qc->flags & ATA_QCFLAG_RESULT_TF)
			fill_result_tf(qc);

		trace_ata_qc_complete_करोne(qc);
		/* Some commands need post-processing after successful
		 * completion.
		 */
		चयन (qc->tf.command) अणु
		हाल ATA_CMD_SET_FEATURES:
			अगर (qc->tf.feature != SETFEATURES_WC_ON &&
			    qc->tf.feature != SETFEATURES_WC_OFF &&
			    qc->tf.feature != SETFEATURES_RA_ON &&
			    qc->tf.feature != SETFEATURES_RA_OFF)
				अवरोध;
			fallthrough;
		हाल ATA_CMD_INIT_DEV_PARAMS: /* CHS translation changed */
		हाल ATA_CMD_SET_MULTI: /* multi_count changed */
			/* revalidate device */
			ehi->dev_action[dev->devno] |= ATA_EH_REVALIDATE;
			ata_port_schedule_eh(ap);
			अवरोध;

		हाल ATA_CMD_SLEEP:
			dev->flags |= ATA_DFLAG_SLEEPING;
			अवरोध;
		पूर्ण

		अगर (unlikely(dev->flags & ATA_DFLAG_DUBIOUS_XFER))
			ata_verअगरy_xfer(qc);

		__ata_qc_complete(qc);
	पूर्ण अन्यथा अणु
		अगर (qc->flags & ATA_QCFLAG_EH_SCHEDULED)
			वापस;

		/* पढ़ो result TF अगर failed or requested */
		अगर (qc->err_mask || qc->flags & ATA_QCFLAG_RESULT_TF)
			fill_result_tf(qc);

		__ata_qc_complete(qc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_qc_complete);

/**
 *	ata_qc_get_active - get biपंचांगask of active qcs
 *	@ap: port in question
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Biपंचांगask of active qcs
 */
u64 ata_qc_get_active(काष्ठा ata_port *ap)
अणु
	u64 qc_active = ap->qc_active;

	/* ATA_TAG_INTERNAL is sent to hw as tag 0 */
	अगर (qc_active & (1ULL << ATA_TAG_INTERNAL)) अणु
		qc_active |= (1 << 0);
		qc_active &= ~(1ULL << ATA_TAG_INTERNAL);
	पूर्ण

	वापस qc_active;
पूर्ण
EXPORT_SYMBOL_GPL(ata_qc_get_active);

/**
 *	ata_qc_issue - issue taskfile to device
 *	@qc: command to issue to device
 *
 *	Prepare an ATA command to submission to device.
 *	This includes mapping the data पूर्णांकo a DMA-able
 *	area, filling in the S/G table, and finally
 *	writing the taskfile to hardware, starting the command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_link *link = qc->dev->link;
	u8 prot = qc->tf.protocol;

	/* Make sure only one non-NCQ command is outstanding.  The
	 * check is skipped क्रम old EH because it reuses active qc to
	 * request ATAPI sense.
	 */
	WARN_ON_ONCE(ap->ops->error_handler && ata_tag_valid(link->active_tag));

	अगर (ata_is_ncq(prot)) अणु
		WARN_ON_ONCE(link->sactive & (1 << qc->hw_tag));

		अगर (!link->sactive)
			ap->nr_active_links++;
		link->sactive |= 1 << qc->hw_tag;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(link->sactive);

		ap->nr_active_links++;
		link->active_tag = qc->tag;
	पूर्ण

	qc->flags |= ATA_QCFLAG_ACTIVE;
	ap->qc_active |= 1ULL << qc->tag;

	/*
	 * We guarantee to LLDs that they will have at least one
	 * non-zero sg अगर the command is a data command.
	 */
	अगर (ata_is_data(prot) && (!qc->sg || !qc->n_elem || !qc->nbytes))
		जाओ sys_err;

	अगर (ata_is_dma(prot) || (ata_is_pio(prot) &&
				 (ap->flags & ATA_FLAG_PIO_DMA)))
		अगर (ata_sg_setup(qc))
			जाओ sys_err;

	/* अगर device is sleeping, schedule reset and पात the link */
	अगर (unlikely(qc->dev->flags & ATA_DFLAG_SLEEPING)) अणु
		link->eh_info.action |= ATA_EH_RESET;
		ata_ehi_push_desc(&link->eh_info, "waking up from sleep");
		ata_link_पात(link);
		वापस;
	पूर्ण

	qc->err_mask |= ap->ops->qc_prep(qc);
	अगर (unlikely(qc->err_mask))
		जाओ err;
	trace_ata_qc_issue(qc);
	qc->err_mask |= ap->ops->qc_issue(qc);
	अगर (unlikely(qc->err_mask))
		जाओ err;
	वापस;

sys_err:
	qc->err_mask |= AC_ERR_SYSTEM;
err:
	ata_qc_complete(qc);
पूर्ण

/**
 *	ata_phys_link_online - test whether the given link is online
 *	@link: ATA link to test
 *
 *	Test whether @link is online.  Note that this function वापसs
 *	0 अगर online status of @link cannot be obtained, so
 *	ata_link_online(link) != !ata_link_offline(link).
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	True अगर the port online status is available and online.
 */
bool ata_phys_link_online(काष्ठा ata_link *link)
अणु
	u32 sstatus;

	अगर (sata_scr_पढ़ो(link, SCR_STATUS, &sstatus) == 0 &&
	    ata_sstatus_online(sstatus))
		वापस true;
	वापस false;
पूर्ण

/**
 *	ata_phys_link_offline - test whether the given link is offline
 *	@link: ATA link to test
 *
 *	Test whether @link is offline.  Note that this function
 *	वापसs 0 अगर offline status of @link cannot be obtained, so
 *	ata_link_online(link) != !ata_link_offline(link).
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	True अगर the port offline status is available and offline.
 */
bool ata_phys_link_offline(काष्ठा ata_link *link)
अणु
	u32 sstatus;

	अगर (sata_scr_पढ़ो(link, SCR_STATUS, &sstatus) == 0 &&
	    !ata_sstatus_online(sstatus))
		वापस true;
	वापस false;
पूर्ण

/**
 *	ata_link_online - test whether the given link is online
 *	@link: ATA link to test
 *
 *	Test whether @link is online.  This is identical to
 *	ata_phys_link_online() when there's no slave link.  When
 *	there's a slave link, this function should only be called on
 *	the master link and will वापस true अगर any of M/S links is
 *	online.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	True अगर the port online status is available and online.
 */
bool ata_link_online(काष्ठा ata_link *link)
अणु
	काष्ठा ata_link *slave = link->ap->slave_link;

	WARN_ON(link == slave);	/* shouldn't be called on slave link */

	वापस ata_phys_link_online(link) ||
		(slave && ata_phys_link_online(slave));
पूर्ण
EXPORT_SYMBOL_GPL(ata_link_online);

/**
 *	ata_link_offline - test whether the given link is offline
 *	@link: ATA link to test
 *
 *	Test whether @link is offline.  This is identical to
 *	ata_phys_link_offline() when there's no slave link.  When
 *	there's a slave link, this function should only be called on
 *	the master link and will वापस true अगर both M/S links are
 *	offline.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	True अगर the port offline status is available and offline.
 */
bool ata_link_offline(काष्ठा ata_link *link)
अणु
	काष्ठा ata_link *slave = link->ap->slave_link;

	WARN_ON(link == slave);	/* shouldn't be called on slave link */

	वापस ata_phys_link_offline(link) &&
		(!slave || ata_phys_link_offline(slave));
पूर्ण
EXPORT_SYMBOL_GPL(ata_link_offline);

#अगर_घोषित CONFIG_PM
अटल व्योम ata_port_request_pm(काष्ठा ata_port *ap, pm_message_t mesg,
				अचिन्हित पूर्णांक action, अचिन्हित पूर्णांक ehi_flags,
				bool async)
अणु
	काष्ठा ata_link *link;
	अचिन्हित दीर्घ flags;

	/* Previous resume operation might still be in
	 * progress.  Wait क्रम PM_PENDING to clear.
	 */
	अगर (ap->pflags & ATA_PFLAG_PM_PENDING) अणु
		ata_port_रुको_eh(ap);
		WARN_ON(ap->pflags & ATA_PFLAG_PM_PENDING);
	पूर्ण

	/* request PM ops to EH */
	spin_lock_irqsave(ap->lock, flags);

	ap->pm_mesg = mesg;
	ap->pflags |= ATA_PFLAG_PM_PENDING;
	ata_क्रम_each_link(link, ap, HOST_FIRST) अणु
		link->eh_info.action |= action;
		link->eh_info.flags |= ehi_flags;
	पूर्ण

	ata_port_schedule_eh(ap);

	spin_unlock_irqrestore(ap->lock, flags);

	अगर (!async) अणु
		ata_port_रुको_eh(ap);
		WARN_ON(ap->pflags & ATA_PFLAG_PM_PENDING);
	पूर्ण
पूर्ण

/*
 * On some hardware, device fails to respond after spun करोwn क्रम suspend.  As
 * the device won't be used before being resumed, we don't need to touch the
 * device.  Ask EH to skip the usual stuff and proceed directly to suspend.
 *
 * http://thपढ़ो.gmane.org/gmane.linux.ide/46764
 */
अटल स्थिर अचिन्हित पूर्णांक ata_port_suspend_ehi = ATA_EHI_QUIET
						 | ATA_EHI_NO_AUTOPSY
						 | ATA_EHI_NO_RECOVERY;

अटल व्योम ata_port_suspend(काष्ठा ata_port *ap, pm_message_t mesg)
अणु
	ata_port_request_pm(ap, mesg, 0, ata_port_suspend_ehi, false);
पूर्ण

अटल व्योम ata_port_suspend_async(काष्ठा ata_port *ap, pm_message_t mesg)
अणु
	ata_port_request_pm(ap, mesg, 0, ata_port_suspend_ehi, true);
पूर्ण

अटल पूर्णांक ata_port_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_port *ap = to_ata_port(dev);

	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	ata_port_suspend(ap, PMSG_SUSPEND);
	वापस 0;
पूर्ण

अटल पूर्णांक ata_port_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा ata_port *ap = to_ata_port(dev);

	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	ata_port_suspend(ap, PMSG_FREEZE);
	वापस 0;
पूर्ण

अटल पूर्णांक ata_port_pm_घातeroff(काष्ठा device *dev)
अणु
	ata_port_suspend(to_ata_port(dev), PMSG_HIBERNATE);
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक ata_port_resume_ehi = ATA_EHI_NO_AUTOPSY
						| ATA_EHI_QUIET;

अटल व्योम ata_port_resume(काष्ठा ata_port *ap, pm_message_t mesg)
अणु
	ata_port_request_pm(ap, mesg, ATA_EH_RESET, ata_port_resume_ehi, false);
पूर्ण

अटल व्योम ata_port_resume_async(काष्ठा ata_port *ap, pm_message_t mesg)
अणु
	ata_port_request_pm(ap, mesg, ATA_EH_RESET, ata_port_resume_ehi, true);
पूर्ण

अटल पूर्णांक ata_port_pm_resume(काष्ठा device *dev)
अणु
	ata_port_resume_async(to_ata_port(dev), PMSG_RESUME);
	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	वापस 0;
पूर्ण

/*
 * For ODDs, the upper layer will poll क्रम media change every few seconds,
 * which will make it enter and leave suspend state every few seconds. And
 * as each suspend will cause a hard/soft reset, the gain of runसमय suspend
 * is very little and the ODD may malfunction after स्थिरantly being reset.
 * So the idle callback here will not proceed to suspend अगर a non-ZPODD capable
 * ODD is attached to the port.
 */
अटल पूर्णांक ata_port_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा ata_port *ap = to_ata_port(dev);
	काष्ठा ata_link *link;
	काष्ठा ata_device *adev;

	ata_क्रम_each_link(link, ap, HOST_FIRST) अणु
		ata_क्रम_each_dev(adev, link, ENABLED)
			अगर (adev->class == ATA_DEV_ATAPI &&
			    !zpodd_dev_enabled(adev))
				वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ata_port_runसमय_suspend(काष्ठा device *dev)
अणु
	ata_port_suspend(to_ata_port(dev), PMSG_AUTO_SUSPEND);
	वापस 0;
पूर्ण

अटल पूर्णांक ata_port_runसमय_resume(काष्ठा device *dev)
अणु
	ata_port_resume(to_ata_port(dev), PMSG_AUTO_RESUME);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ata_port_pm_ops = अणु
	.suspend = ata_port_pm_suspend,
	.resume = ata_port_pm_resume,
	.मुक्तze = ata_port_pm_मुक्तze,
	.thaw = ata_port_pm_resume,
	.घातeroff = ata_port_pm_घातeroff,
	.restore = ata_port_pm_resume,

	.runसमय_suspend = ata_port_runसमय_suspend,
	.runसमय_resume = ata_port_runसमय_resume,
	.runसमय_idle = ata_port_runसमय_idle,
पूर्ण;

/* sas ports करोn't participate in pm runसमय management of ata_ports,
 * and need to resume ata devices at the करोमुख्य level, not the per-port
 * level. sas suspend/resume is async to allow parallel port recovery
 * since sas has multiple ata_port instances per Scsi_Host.
 */
व्योम ata_sas_port_suspend(काष्ठा ata_port *ap)
अणु
	ata_port_suspend_async(ap, PMSG_SUSPEND);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_port_suspend);

व्योम ata_sas_port_resume(काष्ठा ata_port *ap)
अणु
	ata_port_resume_async(ap, PMSG_RESUME);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_port_resume);

/**
 *	ata_host_suspend - suspend host
 *	@host: host to suspend
 *	@mesg: PM message
 *
 *	Suspend @host.  Actual operation is perक्रमmed by port suspend.
 */
पूर्णांक ata_host_suspend(काष्ठा ata_host *host, pm_message_t mesg)
अणु
	host->dev->घातer.घातer_state = mesg;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_suspend);

/**
 *	ata_host_resume - resume host
 *	@host: host to resume
 *
 *	Resume @host.  Actual operation is perक्रमmed by port resume.
 */
व्योम ata_host_resume(काष्ठा ata_host *host)
अणु
	host->dev->घातer.घातer_state = PMSG_ON;
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_resume);
#पूर्ण_अगर

स्थिर काष्ठा device_type ata_port_type = अणु
	.name = "ata_port",
#अगर_घोषित CONFIG_PM
	.pm = &ata_port_pm_ops,
#पूर्ण_अगर
पूर्ण;

/**
 *	ata_dev_init - Initialize an ata_device काष्ठाure
 *	@dev: Device काष्ठाure to initialize
 *
 *	Initialize @dev in preparation क्रम probing.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ata_dev_init(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_link *link = ata_dev_phys_link(dev);
	काष्ठा ata_port *ap = link->ap;
	अचिन्हित दीर्घ flags;

	/* SATA spd limit is bound to the attached device, reset together */
	link->sata_spd_limit = link->hw_sata_spd_limit;
	link->sata_spd = 0;

	/* High bits of dev->flags are used to record warm plug
	 * requests which occur asynchronously.  Synchronize using
	 * host lock.
	 */
	spin_lock_irqsave(ap->lock, flags);
	dev->flags &= ~ATA_DFLAG_INIT_MASK;
	dev->horkage = 0;
	spin_unlock_irqrestore(ap->lock, flags);

	स_रखो((व्योम *)dev + ATA_DEVICE_CLEAR_BEGIN, 0,
	       ATA_DEVICE_CLEAR_END - ATA_DEVICE_CLEAR_BEGIN);
	dev->pio_mask = अच_पूर्णांक_उच्च;
	dev->mwdma_mask = अच_पूर्णांक_उच्च;
	dev->udma_mask = अच_पूर्णांक_उच्च;
पूर्ण

/**
 *	ata_link_init - Initialize an ata_link काष्ठाure
 *	@ap: ATA port link is attached to
 *	@link: Link काष्ठाure to initialize
 *	@pmp: Port multiplier port number
 *
 *	Initialize @link.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 */
व्योम ata_link_init(काष्ठा ata_port *ap, काष्ठा ata_link *link, पूर्णांक pmp)
अणु
	पूर्णांक i;

	/* clear everything except क्रम devices */
	स_रखो((व्योम *)link + ATA_LINK_CLEAR_BEGIN, 0,
	       ATA_LINK_CLEAR_END - ATA_LINK_CLEAR_BEGIN);

	link->ap = ap;
	link->pmp = pmp;
	link->active_tag = ATA_TAG_POISON;
	link->hw_sata_spd_limit = अच_पूर्णांक_उच्च;

	/* can't use iterator, ap isn't initialized yet */
	क्रम (i = 0; i < ATA_MAX_DEVICES; i++) अणु
		काष्ठा ata_device *dev = &link->device[i];

		dev->link = link;
		dev->devno = dev - link->device;
#अगर_घोषित CONFIG_ATA_ACPI
		dev->gtf_filter = ata_acpi_gtf_filter;
#पूर्ण_अगर
		ata_dev_init(dev);
	पूर्ण
पूर्ण

/**
 *	sata_link_init_spd - Initialize link->sata_spd_limit
 *	@link: Link to configure sata_spd_limit क्रम
 *
 *	Initialize ``link->[hw_]sata_spd_limit`` to the currently
 *	configured value.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक sata_link_init_spd(काष्ठा ata_link *link)
अणु
	u8 spd;
	पूर्णांक rc;

	rc = sata_scr_पढ़ो(link, SCR_CONTROL, &link->saved_scontrol);
	अगर (rc)
		वापस rc;

	spd = (link->saved_scontrol >> 4) & 0xf;
	अगर (spd)
		link->hw_sata_spd_limit &= (1 << spd) - 1;

	ata_क्रमce_link_limits(link);

	link->sata_spd_limit = link->hw_sata_spd_limit;

	वापस 0;
पूर्ण

/**
 *	ata_port_alloc - allocate and initialize basic ATA port resources
 *	@host: ATA host this allocated port beदीर्घs to
 *
 *	Allocate and initialize basic ATA port resources.
 *
 *	RETURNS:
 *	Allocate ATA port on success, शून्य on failure.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 */
काष्ठा ata_port *ata_port_alloc(काष्ठा ata_host *host)
अणु
	काष्ठा ata_port *ap;

	DPRINTK("ENTER\n");

	ap = kzalloc(माप(*ap), GFP_KERNEL);
	अगर (!ap)
		वापस शून्य;

	ap->pflags |= ATA_PFLAG_INITIALIZING | ATA_PFLAG_FROZEN;
	ap->lock = &host->lock;
	ap->prपूर्णांक_id = -1;
	ap->local_port_no = -1;
	ap->host = host;
	ap->dev = host->dev;

#अगर defined(ATA_VERBOSE_DEBUG)
	/* turn on all debugging levels */
	ap->msg_enable = 0x00FF;
#या_अगर defined(ATA_DEBUG)
	ap->msg_enable = ATA_MSG_DRV | ATA_MSG_INFO | ATA_MSG_CTL | ATA_MSG_WARN | ATA_MSG_ERR;
#अन्यथा
	ap->msg_enable = ATA_MSG_DRV | ATA_MSG_ERR | ATA_MSG_WARN;
#पूर्ण_अगर

	mutex_init(&ap->scsi_scan_mutex);
	INIT_DELAYED_WORK(&ap->hotplug_task, ata_scsi_hotplug);
	INIT_WORK(&ap->scsi_rescan_task, ata_scsi_dev_rescan);
	INIT_LIST_HEAD(&ap->eh_करोne_q);
	init_रुकोqueue_head(&ap->eh_रुको_q);
	init_completion(&ap->park_req_pending);
	समयr_setup(&ap->fastdrain_समयr, ata_eh_fastdrain_समयrfn,
		    TIMER_DEFERRABLE);

	ap->cbl = ATA_CBL_NONE;

	ata_link_init(ap, &ap->link, 0);

#अगर_घोषित ATA_IRQ_TRAP
	ap->stats.unhandled_irq = 1;
	ap->stats.idle_irq = 1;
#पूर्ण_अगर
	ata_sff_port_init(ap);

	वापस ap;
पूर्ण

अटल व्योम ata_devres_release(काष्ठा device *gendev, व्योम *res)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(gendev);
	पूर्णांक i;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		अगर (!ap)
			जारी;

		अगर (ap->scsi_host)
			scsi_host_put(ap->scsi_host);

	पूर्ण

	dev_set_drvdata(gendev, शून्य);
	ata_host_put(host);
पूर्ण

अटल व्योम ata_host_release(काष्ठा kref *kref)
अणु
	काष्ठा ata_host *host = container_of(kref, काष्ठा ata_host, kref);
	पूर्णांक i;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		kमुक्त(ap->pmp_link);
		kमुक्त(ap->slave_link);
		kमुक्त(ap);
		host->ports[i] = शून्य;
	पूर्ण
	kमुक्त(host);
पूर्ण

व्योम ata_host_get(काष्ठा ata_host *host)
अणु
	kref_get(&host->kref);
पूर्ण

व्योम ata_host_put(काष्ठा ata_host *host)
अणु
	kref_put(&host->kref, ata_host_release);
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_put);

/**
 *	ata_host_alloc - allocate and init basic ATA host resources
 *	@dev: generic device this host is associated with
 *	@max_ports: maximum number of ATA ports associated with this host
 *
 *	Allocate and initialize basic ATA host resources.  LLD calls
 *	this function to allocate a host, initializes it fully and
 *	attaches it using ata_host_रेजिस्टर().
 *
 *	@max_ports ports are allocated and host->n_ports is
 *	initialized to @max_ports.  The caller is allowed to decrease
 *	host->n_ports beक्रमe calling ata_host_रेजिस्टर().  The unused
 *	ports will be स्वतःmatically मुक्तd on registration.
 *
 *	RETURNS:
 *	Allocate ATA host on success, शून्य on failure.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 */
काष्ठा ata_host *ata_host_alloc(काष्ठा device *dev, पूर्णांक max_ports)
अणु
	काष्ठा ata_host *host;
	माप_प्रकार sz;
	पूर्णांक i;
	व्योम *dr;

	DPRINTK("ENTER\n");

	/* alloc a container क्रम our list of ATA ports (buses) */
	sz = माप(काष्ठा ata_host) + (max_ports + 1) * माप(व्योम *);
	host = kzalloc(sz, GFP_KERNEL);
	अगर (!host)
		वापस शून्य;

	अगर (!devres_खोलो_group(dev, शून्य, GFP_KERNEL))
		जाओ err_मुक्त;

	dr = devres_alloc(ata_devres_release, 0, GFP_KERNEL);
	अगर (!dr)
		जाओ err_out;

	devres_add(dev, dr);
	dev_set_drvdata(dev, host);

	spin_lock_init(&host->lock);
	mutex_init(&host->eh_mutex);
	host->dev = dev;
	host->n_ports = max_ports;
	kref_init(&host->kref);

	/* allocate ports bound to this host */
	क्रम (i = 0; i < max_ports; i++) अणु
		काष्ठा ata_port *ap;

		ap = ata_port_alloc(host);
		अगर (!ap)
			जाओ err_out;

		ap->port_no = i;
		host->ports[i] = ap;
	पूर्ण

	devres_हटाओ_group(dev, शून्य);
	वापस host;

 err_out:
	devres_release_group(dev, शून्य);
 err_मुक्त:
	kमुक्त(host);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_alloc);

/**
 *	ata_host_alloc_pinfo - alloc host and init with port_info array
 *	@dev: generic device this host is associated with
 *	@ppi: array of ATA port_info to initialize host with
 *	@n_ports: number of ATA ports attached to this host
 *
 *	Allocate ATA host and initialize with info from @ppi.  If शून्य
 *	terminated, @ppi may contain fewer entries than @n_ports.  The
 *	last entry will be used क्रम the reमुख्यing ports.
 *
 *	RETURNS:
 *	Allocate ATA host on success, शून्य on failure.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 */
काष्ठा ata_host *ata_host_alloc_pinfo(काष्ठा device *dev,
				      स्थिर काष्ठा ata_port_info * स्थिर * ppi,
				      पूर्णांक n_ports)
अणु
	स्थिर काष्ठा ata_port_info *pi;
	काष्ठा ata_host *host;
	पूर्णांक i, j;

	host = ata_host_alloc(dev, n_ports);
	अगर (!host)
		वापस शून्य;

	क्रम (i = 0, j = 0, pi = शून्य; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		अगर (ppi[j])
			pi = ppi[j++];

		ap->pio_mask = pi->pio_mask;
		ap->mwdma_mask = pi->mwdma_mask;
		ap->udma_mask = pi->udma_mask;
		ap->flags |= pi->flags;
		ap->link.flags |= pi->link_flags;
		ap->ops = pi->port_ops;

		अगर (!host->ops && (pi->port_ops != &ata_dummy_port_ops))
			host->ops = pi->port_ops;
	पूर्ण

	वापस host;
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_alloc_pinfo);

अटल व्योम ata_host_stop(काष्ठा device *gendev, व्योम *res)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(gendev);
	पूर्णांक i;

	WARN_ON(!(host->flags & ATA_HOST_STARTED));

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		अगर (ap->ops->port_stop)
			ap->ops->port_stop(ap);
	पूर्ण

	अगर (host->ops->host_stop)
		host->ops->host_stop(host);
पूर्ण

/**
 *	ata_finalize_port_ops - finalize ata_port_operations
 *	@ops: ata_port_operations to finalize
 *
 *	An ata_port_operations can inherit from another ops and that
 *	ops can again inherit from another.  This can go on as many
 *	बार as necessary as दीर्घ as there is no loop in the
 *	inheritance chain.
 *
 *	Ops tables are finalized when the host is started.  शून्य or
 *	unspecअगरied entries are inherited from the बंदt ancestor
 *	which has the method and the entry is populated with it.
 *	After finalization, the ops table directly poपूर्णांकs to all the
 *	methods and ->inherits is no दीर्घer necessary and cleared.
 *
 *	Using ATA_OP_शून्य, inheriting ops can क्रमce a method to शून्य.
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम ata_finalize_port_ops(काष्ठा ata_port_operations *ops)
अणु
	अटल DEFINE_SPINLOCK(lock);
	स्थिर काष्ठा ata_port_operations *cur;
	व्योम **begin = (व्योम **)ops;
	व्योम **end = (व्योम **)&ops->inherits;
	व्योम **pp;

	अगर (!ops || !ops->inherits)
		वापस;

	spin_lock(&lock);

	क्रम (cur = ops->inherits; cur; cur = cur->inherits) अणु
		व्योम **inherit = (व्योम **)cur;

		क्रम (pp = begin; pp < end; pp++, inherit++)
			अगर (!*pp)
				*pp = *inherit;
	पूर्ण

	क्रम (pp = begin; pp < end; pp++)
		अगर (IS_ERR(*pp))
			*pp = शून्य;

	ops->inherits = शून्य;

	spin_unlock(&lock);
पूर्ण

/**
 *	ata_host_start - start and मुक्तze ports of an ATA host
 *	@host: ATA host to start ports क्रम
 *
 *	Start and then मुक्तze ports of @host.  Started status is
 *	recorded in host->flags, so this function can be called
 *	multiple बार.  Ports are guaranteed to get started only
 *	once.  If host->ops isn't initialized yet, its set to the
 *	first non-dummy port ops.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 अगर all ports are started successfully, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_host_start(काष्ठा ata_host *host)
अणु
	पूर्णांक have_stop = 0;
	व्योम *start_dr = शून्य;
	पूर्णांक i, rc;

	अगर (host->flags & ATA_HOST_STARTED)
		वापस 0;

	ata_finalize_port_ops(host->ops);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ata_finalize_port_ops(ap->ops);

		अगर (!host->ops && !ata_port_is_dummy(ap))
			host->ops = ap->ops;

		अगर (ap->ops->port_stop)
			have_stop = 1;
	पूर्ण

	अगर (host->ops->host_stop)
		have_stop = 1;

	अगर (have_stop) अणु
		start_dr = devres_alloc(ata_host_stop, 0, GFP_KERNEL);
		अगर (!start_dr)
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		अगर (ap->ops->port_start) अणु
			rc = ap->ops->port_start(ap);
			अगर (rc) अणु
				अगर (rc != -ENODEV)
					dev_err(host->dev,
						"failed to start port %d (errno=%d)\n",
						i, rc);
				जाओ err_out;
			पूर्ण
		पूर्ण
		ata_eh_मुक्तze_port(ap);
	पूर्ण

	अगर (start_dr)
		devres_add(host->dev, start_dr);
	host->flags |= ATA_HOST_STARTED;
	वापस 0;

 err_out:
	जबतक (--i >= 0) अणु
		काष्ठा ata_port *ap = host->ports[i];

		अगर (ap->ops->port_stop)
			ap->ops->port_stop(ap);
	पूर्ण
	devres_मुक्त(start_dr);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_start);

/**
 *	ata_host_init - Initialize a host काष्ठा क्रम sas (ipr, libsas)
 *	@host:	host to initialize
 *	@dev:	device host is attached to
 *	@ops:	port_ops
 *
 */
व्योम ata_host_init(काष्ठा ata_host *host, काष्ठा device *dev,
		   काष्ठा ata_port_operations *ops)
अणु
	spin_lock_init(&host->lock);
	mutex_init(&host->eh_mutex);
	host->n_tags = ATA_MAX_QUEUE;
	host->dev = dev;
	host->ops = ops;
	kref_init(&host->kref);
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_init);

व्योम __ata_port_probe(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	अचिन्हित दीर्घ flags;

	/* kick EH क्रम boot probing */
	spin_lock_irqsave(ap->lock, flags);

	ehi->probe_mask |= ATA_ALL_DEVICES;
	ehi->action |= ATA_EH_RESET;
	ehi->flags |= ATA_EHI_NO_AUTOPSY | ATA_EHI_QUIET;

	ap->pflags &= ~ATA_PFLAG_INITIALIZING;
	ap->pflags |= ATA_PFLAG_LOADING;
	ata_port_schedule_eh(ap);

	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण

पूर्णांक ata_port_probe(काष्ठा ata_port *ap)
अणु
	पूर्णांक rc = 0;

	अगर (ap->ops->error_handler) अणु
		__ata_port_probe(ap);
		ata_port_रुको_eh(ap);
	पूर्ण अन्यथा अणु
		DPRINTK("ata%u: bus probe begin\n", ap->prपूर्णांक_id);
		rc = ata_bus_probe(ap);
		DPRINTK("ata%u: bus probe end\n", ap->prपूर्णांक_id);
	पूर्ण
	वापस rc;
पूर्ण


अटल व्योम async_port_probe(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा ata_port *ap = data;

	/*
	 * If we're not allowed to scan this host in parallel,
	 * we need to रुको until all previous scans have completed
	 * beक्रमe going further.
	 * Jeff Garzik says this is only within a controller, so we
	 * करोn't need to रुको क्रम port 0, only क्रम later ports.
	 */
	अगर (!(ap->host->flags & ATA_HOST_PARALLEL_SCAN) && ap->port_no != 0)
		async_synchronize_cookie(cookie);

	(व्योम)ata_port_probe(ap);

	/* in order to keep device order, we need to synchronize at this poपूर्णांक */
	async_synchronize_cookie(cookie);

	ata_scsi_scan_host(ap, 1);
पूर्ण

/**
 *	ata_host_रेजिस्टर - रेजिस्टर initialized ATA host
 *	@host: ATA host to रेजिस्टर
 *	@sht: ढाँचा क्रम SCSI host
 *
 *	Register initialized ATA host.  @host is allocated using
 *	ata_host_alloc() and fully initialized by LLD.  This function
 *	starts ports, रेजिस्टरs @host with ATA and SCSI layers and
 *	probe रेजिस्टरed devices.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_host_रेजिस्टर(काष्ठा ata_host *host, काष्ठा scsi_host_ढाँचा *sht)
अणु
	पूर्णांक i, rc;

	host->n_tags = clamp(sht->can_queue, 1, ATA_MAX_QUEUE);

	/* host must have been started */
	अगर (!(host->flags & ATA_HOST_STARTED)) अणु
		dev_err(host->dev, "BUG: trying to register unstarted host\n");
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	/* Blow away unused ports.  This happens when LLD can't
	 * determine the exact number of ports to allocate at
	 * allocation समय.
	 */
	क्रम (i = host->n_ports; host->ports[i]; i++)
		kमुक्त(host->ports[i]);

	/* give ports names and add SCSI hosts */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		host->ports[i]->prपूर्णांक_id = atomic_inc_वापस(&ata_prपूर्णांक_id);
		host->ports[i]->local_port_no = i + 1;
	पूर्ण

	/* Create associated sysfs transport objects  */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		rc = ata_tport_add(host->dev,host->ports[i]);
		अगर (rc) अणु
			जाओ err_tadd;
		पूर्ण
	पूर्ण

	rc = ata_scsi_add_hosts(host, sht);
	अगर (rc)
		जाओ err_tadd;

	/* set cable, sata_spd_limit and report */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		अचिन्हित दीर्घ xfer_mask;

		/* set SATA cable type अगर still unset */
		अगर (ap->cbl == ATA_CBL_NONE && (ap->flags & ATA_FLAG_SATA))
			ap->cbl = ATA_CBL_SATA;

		/* init sata_spd_limit to the current value */
		sata_link_init_spd(&ap->link);
		अगर (ap->slave_link)
			sata_link_init_spd(ap->slave_link);

		/* prपूर्णांक per-port info to dmesg */
		xfer_mask = ata_pack_xfermask(ap->pio_mask, ap->mwdma_mask,
					      ap->udma_mask);

		अगर (!ata_port_is_dummy(ap)) अणु
			ata_port_info(ap, "%cATA max %s %s\n",
				      (ap->flags & ATA_FLAG_SATA) ? 'S' : 'P',
				      ata_mode_string(xfer_mask),
				      ap->link.eh_info.desc);
			ata_ehi_clear_desc(&ap->link.eh_info);
		पूर्ण अन्यथा
			ata_port_info(ap, "DUMMY\n");
	पूर्ण

	/* perक्रमm each probe asynchronously */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		ap->cookie = async_schedule(async_port_probe, ap);
	पूर्ण

	वापस 0;

 err_tadd:
	जबतक (--i >= 0) अणु
		ata_tport_delete(host->ports[i]);
	पूर्ण
	वापस rc;

पूर्ण
EXPORT_SYMBOL_GPL(ata_host_रेजिस्टर);

/**
 *	ata_host_activate - start host, request IRQ and रेजिस्टर it
 *	@host: target ATA host
 *	@irq: IRQ to request
 *	@irq_handler: irq_handler used when requesting IRQ
 *	@irq_flags: irq_flags used when requesting IRQ
 *	@sht: scsi_host_ढाँचा to use when रेजिस्टरing the host
 *
 *	After allocating an ATA host and initializing it, most libata
 *	LLDs perक्रमm three steps to activate the host - start host,
 *	request IRQ and रेजिस्टर it.  This helper takes necessary
 *	arguments and perक्रमms the three steps in one go.
 *
 *	An invalid IRQ skips the IRQ registration and expects the host to
 *	have set polling mode on the port. In this हाल, @irq_handler
 *	should be शून्य.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_host_activate(काष्ठा ata_host *host, पूर्णांक irq,
		      irq_handler_t irq_handler, अचिन्हित दीर्घ irq_flags,
		      काष्ठा scsi_host_ढाँचा *sht)
अणु
	पूर्णांक i, rc;
	अक्षर *irq_desc;

	rc = ata_host_start(host);
	अगर (rc)
		वापस rc;

	/* Special हाल क्रम polling mode */
	अगर (!irq) अणु
		WARN_ON(irq_handler);
		वापस ata_host_रेजिस्टर(host, sht);
	पूर्ण

	irq_desc = devm_kaप्र_लिखो(host->dev, GFP_KERNEL, "%s[%s]",
				  dev_driver_string(host->dev),
				  dev_name(host->dev));
	अगर (!irq_desc)
		वापस -ENOMEM;

	rc = devm_request_irq(host->dev, irq, irq_handler, irq_flags,
			      irq_desc, host);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < host->n_ports; i++)
		ata_port_desc(host->ports[i], "irq %d", irq);

	rc = ata_host_रेजिस्टर(host, sht);
	/* अगर failed, just मुक्त the IRQ and leave ports alone */
	अगर (rc)
		devm_मुक्त_irq(host->dev, irq, host);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_activate);

/**
 *	ata_port_detach - Detach ATA port in preparation of device removal
 *	@ap: ATA port to be detached
 *
 *	Detach all ATA devices and the associated SCSI devices of @ap;
 *	then, हटाओ the associated SCSI host.  @ap is guaranteed to
 *	be quiescent on वापस from this function.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
अटल व्योम ata_port_detach(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;

	अगर (!ap->ops->error_handler)
		जाओ skip_eh;

	/* tell EH we're leaving & flush EH */
	spin_lock_irqsave(ap->lock, flags);
	ap->pflags |= ATA_PFLAG_UNLOADING;
	ata_port_schedule_eh(ap);
	spin_unlock_irqrestore(ap->lock, flags);

	/* रुको till EH commits suicide */
	ata_port_रुको_eh(ap);

	/* it better be dead now */
	WARN_ON(!(ap->pflags & ATA_PFLAG_UNLOADED));

	cancel_delayed_work_sync(&ap->hotplug_task);

 skip_eh:
	/* clean up zpodd on port removal */
	ata_क्रम_each_link(link, ap, HOST_FIRST) अणु
		ata_क्रम_each_dev(dev, link, ALL) अणु
			अगर (zpodd_dev_enabled(dev))
				zpodd_निकास(dev);
		पूर्ण
	पूर्ण
	अगर (ap->pmp_link) अणु
		पूर्णांक i;
		क्रम (i = 0; i < SATA_PMP_MAX_PORTS; i++)
			ata_tlink_delete(&ap->pmp_link[i]);
	पूर्ण
	/* हटाओ the associated SCSI host */
	scsi_हटाओ_host(ap->scsi_host);
	ata_tport_delete(ap);
पूर्ण

/**
 *	ata_host_detach - Detach all ports of an ATA host
 *	@host: Host to detach
 *
 *	Detach all ports of @host.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_host_detach(काष्ठा ata_host *host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		/* Ensure ata_port probe has completed */
		async_synchronize_cookie(host->ports[i]->cookie + 1);
		ata_port_detach(host->ports[i]);
	पूर्ण

	/* the host is dead now, dissociate ACPI */
	ata_acpi_dissociate(host);
पूर्ण
EXPORT_SYMBOL_GPL(ata_host_detach);

#अगर_घोषित CONFIG_PCI

/**
 *	ata_pci_हटाओ_one - PCI layer callback क्रम device removal
 *	@pdev: PCI device that was हटाओd
 *
 *	PCI layer indicates to libata via this hook that hot-unplug or
 *	module unload event has occurred.  Detach all ports.  Resource
 *	release is handled via devres.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 */
व्योम ata_pci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);

	ata_host_detach(host);
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_हटाओ_one);

व्योम ata_pci_shutकरोwn_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ap->pflags |= ATA_PFLAG_FROZEN;

		/* Disable port पूर्णांकerrupts */
		अगर (ap->ops->मुक्तze)
			ap->ops->मुक्तze(ap);

		/* Stop the port DMA engines */
		अगर (ap->ops->port_stop)
			ap->ops->port_stop(ap);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_shutकरोwn_one);

/* move to PCI subप्रणाली */
पूर्णांक pci_test_config_bits(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_bits *bits)
अणु
	अचिन्हित दीर्घ पंचांगp = 0;

	चयन (bits->width) अणु
	हाल 1: अणु
		u8 पंचांगp8 = 0;
		pci_पढ़ो_config_byte(pdev, bits->reg, &पंचांगp8);
		पंचांगp = पंचांगp8;
		अवरोध;
	पूर्ण
	हाल 2: अणु
		u16 पंचांगp16 = 0;
		pci_पढ़ो_config_word(pdev, bits->reg, &पंचांगp16);
		पंचांगp = पंचांगp16;
		अवरोध;
	पूर्ण
	हाल 4: अणु
		u32 पंचांगp32 = 0;
		pci_पढ़ो_config_dword(pdev, bits->reg, &पंचांगp32);
		पंचांगp = पंचांगp32;
		अवरोध;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण

	पंचांगp &= bits->mask;

	वापस (पंचांगp == bits->val) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_test_config_bits);

#अगर_घोषित CONFIG_PM
व्योम ata_pci_device_करो_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	pci_save_state(pdev);
	pci_disable_device(pdev);

	अगर (mesg.event & PM_EVENT_SLEEP)
		pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_device_करो_suspend);

पूर्णांक ata_pci_device_करो_resume(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	rc = pcim_enable_device(pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev,
			"failed to enable device after resume (%d)\n", rc);
		वापस rc;
	पूर्ण

	pci_set_master(pdev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_device_करो_resume);

पूर्णांक ata_pci_device_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc = 0;

	rc = ata_host_suspend(host, mesg);
	अगर (rc)
		वापस rc;

	ata_pci_device_करो_suspend(pdev, mesg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_device_suspend);

पूर्णांक ata_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc == 0)
		ata_host_resume(host);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_device_resume);
#पूर्ण_अगर /* CONFIG_PM */
#पूर्ण_अगर /* CONFIG_PCI */

/**
 *	ata_platक्रमm_हटाओ_one - Platक्रमm layer callback क्रम device removal
 *	@pdev: Platक्रमm device that was हटाओd
 *
 *	Platक्रमm layer indicates to libata via this hook that hot-unplug or
 *	module unload event has occurred.  Detach all ports.  Resource
 *	release is handled via devres.
 *
 *	LOCKING:
 *	Inherited from platक्रमm layer (may sleep).
 */
पूर्णांक ata_platक्रमm_हटाओ_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);

	ata_host_detach(host);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_platक्रमm_हटाओ_one);

#अगर_घोषित CONFIG_ATA_FORCE
अटल पूर्णांक __init ata_parse_क्रमce_one(अक्षर **cur,
				      काष्ठा ata_क्रमce_ent *क्रमce_ent,
				      स्थिर अक्षर **reason)
अणु
	अटल स्थिर काष्ठा ata_क्रमce_param क्रमce_tbl[] __initस्थिर = अणु
		अणु "40c",	.cbl		= ATA_CBL_PATA40 पूर्ण,
		अणु "80c",	.cbl		= ATA_CBL_PATA80 पूर्ण,
		अणु "short40c",	.cbl		= ATA_CBL_PATA40_SHORT पूर्ण,
		अणु "unk",	.cbl		= ATA_CBL_PATA_UNK पूर्ण,
		अणु "ign",	.cbl		= ATA_CBL_PATA_IGN पूर्ण,
		अणु "sata",	.cbl		= ATA_CBL_SATA पूर्ण,
		अणु "1.5Gbps",	.spd_limit	= 1 पूर्ण,
		अणु "3.0Gbps",	.spd_limit	= 2 पूर्ण,
		अणु "noncq",	.horkage_on	= ATA_HORKAGE_NONCQ पूर्ण,
		अणु "ncq",	.horkage_off	= ATA_HORKAGE_NONCQ पूर्ण,
		अणु "noncqtrim",	.horkage_on	= ATA_HORKAGE_NO_NCQ_TRIM पूर्ण,
		अणु "ncqtrim",	.horkage_off	= ATA_HORKAGE_NO_NCQ_TRIM पूर्ण,
		अणु "dump_id",	.horkage_on	= ATA_HORKAGE_DUMP_ID पूर्ण,
		अणु "pio0",	.xfer_mask	= 1 << (ATA_SHIFT_PIO + 0) पूर्ण,
		अणु "pio1",	.xfer_mask	= 1 << (ATA_SHIFT_PIO + 1) पूर्ण,
		अणु "pio2",	.xfer_mask	= 1 << (ATA_SHIFT_PIO + 2) पूर्ण,
		अणु "pio3",	.xfer_mask	= 1 << (ATA_SHIFT_PIO + 3) पूर्ण,
		अणु "pio4",	.xfer_mask	= 1 << (ATA_SHIFT_PIO + 4) पूर्ण,
		अणु "pio5",	.xfer_mask	= 1 << (ATA_SHIFT_PIO + 5) पूर्ण,
		अणु "pio6",	.xfer_mask	= 1 << (ATA_SHIFT_PIO + 6) पूर्ण,
		अणु "mwdma0",	.xfer_mask	= 1 << (ATA_SHIFT_MWDMA + 0) पूर्ण,
		अणु "mwdma1",	.xfer_mask	= 1 << (ATA_SHIFT_MWDMA + 1) पूर्ण,
		अणु "mwdma2",	.xfer_mask	= 1 << (ATA_SHIFT_MWDMA + 2) पूर्ण,
		अणु "mwdma3",	.xfer_mask	= 1 << (ATA_SHIFT_MWDMA + 3) पूर्ण,
		अणु "mwdma4",	.xfer_mask	= 1 << (ATA_SHIFT_MWDMA + 4) पूर्ण,
		अणु "udma0",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 0) पूर्ण,
		अणु "udma16",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 0) पूर्ण,
		अणु "udma/16",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 0) पूर्ण,
		अणु "udma1",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 1) पूर्ण,
		अणु "udma25",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 1) पूर्ण,
		अणु "udma/25",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 1) पूर्ण,
		अणु "udma2",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 2) पूर्ण,
		अणु "udma33",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 2) पूर्ण,
		अणु "udma/33",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 2) पूर्ण,
		अणु "udma3",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 3) पूर्ण,
		अणु "udma44",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 3) पूर्ण,
		अणु "udma/44",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 3) पूर्ण,
		अणु "udma4",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 4) पूर्ण,
		अणु "udma66",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 4) पूर्ण,
		अणु "udma/66",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 4) पूर्ण,
		अणु "udma5",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 5) पूर्ण,
		अणु "udma100",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 5) पूर्ण,
		अणु "udma/100",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 5) पूर्ण,
		अणु "udma6",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 6) पूर्ण,
		अणु "udma133",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 6) पूर्ण,
		अणु "udma/133",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 6) पूर्ण,
		अणु "udma7",	.xfer_mask	= 1 << (ATA_SHIFT_UDMA + 7) पूर्ण,
		अणु "nohrst",	.lflags		= ATA_LFLAG_NO_HRST पूर्ण,
		अणु "nosrst",	.lflags		= ATA_LFLAG_NO_SRST पूर्ण,
		अणु "norst",	.lflags		= ATA_LFLAG_NO_HRST | ATA_LFLAG_NO_SRST पूर्ण,
		अणु "rstonce",	.lflags		= ATA_LFLAG_RST_ONCE पूर्ण,
		अणु "atapi_dmadir", .horkage_on	= ATA_HORKAGE_ATAPI_DMAसूची पूर्ण,
		अणु "disable",	.horkage_on	= ATA_HORKAGE_DISABLE पूर्ण,
	पूर्ण;
	अक्षर *start = *cur, *p = *cur;
	अक्षर *id, *val, *endp;
	स्थिर काष्ठा ata_क्रमce_param *match_fp = शून्य;
	पूर्णांक nr_matches = 0, i;

	/* find where this param ends and update *cur */
	जबतक (*p != '\0' && *p != ',')
		p++;

	अगर (*p == '\0')
		*cur = p;
	अन्यथा
		*cur = p + 1;

	*p = '\0';

	/* parse */
	p = म_अक्षर(start, ':');
	अगर (!p) अणु
		val = म_मालाip(start);
		जाओ parse_val;
	पूर्ण
	*p = '\0';

	id = म_मालाip(start);
	val = म_मालाip(p + 1);

	/* parse id */
	p = म_अक्षर(id, '.');
	अगर (p) अणु
		*p++ = '\0';
		क्रमce_ent->device = simple_म_से_अदीर्घ(p, &endp, 10);
		अगर (p == endp || *endp != '\0') अणु
			*reason = "invalid device";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रमce_ent->port = simple_म_से_अदीर्घ(id, &endp, 10);
	अगर (id == endp || *endp != '\0') अणु
		*reason = "invalid port/link";
		वापस -EINVAL;
	पूर्ण

 parse_val:
	/* parse val, allow लघुcuts so that both 1.5 and 1.5Gbps work */
	क्रम (i = 0; i < ARRAY_SIZE(क्रमce_tbl); i++) अणु
		स्थिर काष्ठा ata_क्रमce_param *fp = &क्रमce_tbl[i];

		अगर (strnहालcmp(val, fp->name, म_माप(val)))
			जारी;

		nr_matches++;
		match_fp = fp;

		अगर (strहालcmp(val, fp->name) == 0) अणु
			nr_matches = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!nr_matches) अणु
		*reason = "unknown value";
		वापस -EINVAL;
	पूर्ण
	अगर (nr_matches > 1) अणु
		*reason = "ambiguous value";
		वापस -EINVAL;
	पूर्ण

	क्रमce_ent->param = *match_fp;

	वापस 0;
पूर्ण

अटल व्योम __init ata_parse_क्रमce_param(व्योम)
अणु
	पूर्णांक idx = 0, size = 1;
	पूर्णांक last_port = -1, last_device = -1;
	अक्षर *p, *cur, *next;

	/* calculate maximum number of params and allocate क्रमce_tbl */
	क्रम (p = ata_क्रमce_param_buf; *p; p++)
		अगर (*p == ',')
			size++;

	ata_क्रमce_tbl = kसुस्मृति(size, माप(ata_क्रमce_tbl[0]), GFP_KERNEL);
	अगर (!ata_क्रमce_tbl) अणु
		prपूर्णांकk(KERN_WARNING "ata: failed to extend force table, "
		       "libata.force ignored\n");
		वापस;
	पूर्ण

	/* parse and populate the table */
	क्रम (cur = ata_क्रमce_param_buf; *cur != '\0'; cur = next) अणु
		स्थिर अक्षर *reason = "";
		काष्ठा ata_क्रमce_ent te = अणु .port = -1, .device = -1 पूर्ण;

		next = cur;
		अगर (ata_parse_क्रमce_one(&next, &te, &reason)) अणु
			prपूर्णांकk(KERN_WARNING "ata: failed to parse force "
			       "parameter \"%s\" (%s)\n",
			       cur, reason);
			जारी;
		पूर्ण

		अगर (te.port == -1) अणु
			te.port = last_port;
			te.device = last_device;
		पूर्ण

		ata_क्रमce_tbl[idx++] = te;

		last_port = te.port;
		last_device = te.device;
	पूर्ण

	ata_क्रमce_tbl_size = idx;
पूर्ण

अटल व्योम ata_मुक्त_क्रमce_param(व्योम)
अणु
	kमुक्त(ata_क्रमce_tbl);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ata_parse_क्रमce_param(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ata_मुक्त_क्रमce_param(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init ata_init(व्योम)
अणु
	पूर्णांक rc;

	ata_parse_क्रमce_param();

	rc = ata_sff_init();
	अगर (rc) अणु
		ata_मुक्त_क्रमce_param();
		वापस rc;
	पूर्ण

	libata_transport_init();
	ata_scsi_transport_ढाँचा = ata_attach_transport();
	अगर (!ata_scsi_transport_ढाँचा) अणु
		ata_sff_निकास();
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "libata version " DRV_VERSION " loaded.\n");
	वापस 0;

err_out:
	वापस rc;
पूर्ण

अटल व्योम __निकास ata_निकास(व्योम)
अणु
	ata_release_transport(ata_scsi_transport_ढाँचा);
	libata_transport_निकास();
	ata_sff_निकास();
	ata_मुक्त_क्रमce_param();
पूर्ण

subsys_initcall(ata_init);
module_निकास(ata_निकास);

अटल DEFINE_RATELIMIT_STATE(ratelimit, HZ / 5, 1);

पूर्णांक ata_ratelimit(व्योम)
अणु
	वापस __ratelimit(&ratelimit);
पूर्ण
EXPORT_SYMBOL_GPL(ata_ratelimit);

/**
 *	ata_msleep - ATA EH owner aware msleep
 *	@ap: ATA port to attribute the sleep to
 *	@msecs: duration to sleep in milliseconds
 *
 *	Sleeps @msecs.  If the current task is owner of @ap's EH, the
 *	ownership is released beक्रमe going to sleep and reacquired
 *	after the sleep is complete.  IOW, other ports sharing the
 *	@ap->host will be allowed to own the EH जबतक this task is
 *	sleeping.
 *
 *	LOCKING:
 *	Might sleep.
 */
व्योम ata_msleep(काष्ठा ata_port *ap, अचिन्हित पूर्णांक msecs)
अणु
	bool owns_eh = ap && ap->host->eh_owner == current;

	अगर (owns_eh)
		ata_eh_release(ap);

	अगर (msecs < 20) अणु
		अचिन्हित दीर्घ usecs = msecs * USEC_PER_MSEC;
		usleep_range(usecs, usecs + 50);
	पूर्ण अन्यथा अणु
		msleep(msecs);
	पूर्ण

	अगर (owns_eh)
		ata_eh_acquire(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_msleep);

/**
 *	ata_रुको_रेजिस्टर - रुको until रेजिस्टर value changes
 *	@ap: ATA port to रुको रेजिस्टर क्रम, can be शून्य
 *	@reg: IO-mapped रेजिस्टर
 *	@mask: Mask to apply to पढ़ो रेजिस्टर value
 *	@val: Wait condition
 *	@पूर्णांकerval: polling पूर्णांकerval in milliseconds
 *	@समयout: समयout in milliseconds
 *
 *	Waiting क्रम some bits of रेजिस्टर to change is a common
 *	operation क्रम ATA controllers.  This function पढ़ोs 32bit LE
 *	IO-mapped रेजिस्टर @reg and tests क्रम the following condition.
 *
 *	(*@reg & mask) != val
 *
 *	If the condition is met, it वापसs; otherwise, the process is
 *	repeated after @पूर्णांकerval_msec until समयout.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	The final रेजिस्टर value.
 */
u32 ata_रुको_रेजिस्टर(काष्ठा ata_port *ap, व्योम __iomem *reg, u32 mask, u32 val,
		      अचिन्हित दीर्घ पूर्णांकerval, अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ deadline;
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32(reg);

	/* Calculate समयout _after_ the first पढ़ो to make sure
	 * preceding ग_लिखोs reach the controller beक्रमe starting to
	 * eat away the समयout.
	 */
	deadline = ata_deadline(jअगरfies, समयout);

	जबतक ((पंचांगp & mask) == val && समय_beक्रमe(jअगरfies, deadline)) अणु
		ata_msleep(ap, पूर्णांकerval);
		पंचांगp = ioपढ़ो32(reg);
	पूर्ण

	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL_GPL(ata_रुको_रेजिस्टर);

/*
 * Dummy port_ops
 */
अटल अचिन्हित पूर्णांक ata_dummy_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	वापस AC_ERR_SYSTEM;
पूर्ण

अटल व्योम ata_dummy_error_handler(काष्ठा ata_port *ap)
अणु
	/* truly dummy */
पूर्ण

काष्ठा ata_port_operations ata_dummy_port_ops = अणु
	.qc_prep		= ata_noop_qc_prep,
	.qc_issue		= ata_dummy_qc_issue,
	.error_handler		= ata_dummy_error_handler,
	.sched_eh		= ata_std_sched_eh,
	.end_eh			= ata_std_end_eh,
पूर्ण;
EXPORT_SYMBOL_GPL(ata_dummy_port_ops);

स्थिर काष्ठा ata_port_info ata_dummy_port_info = अणु
	.port_ops		= &ata_dummy_port_ops,
पूर्ण;
EXPORT_SYMBOL_GPL(ata_dummy_port_info);

/*
 * Utility prपूर्णांक functions
 */
व्योम ata_port_prपूर्णांकk(स्थिर काष्ठा ata_port *ap, स्थिर अक्षर *level,
		     स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk("%sata%u: %pV", level, ap->prपूर्णांक_id, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ata_port_prपूर्णांकk);

व्योम ata_link_prपूर्णांकk(स्थिर काष्ठा ata_link *link, स्थिर अक्षर *level,
		     स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (sata_pmp_attached(link->ap) || link->ap->slave_link)
		prपूर्णांकk("%sata%u.%02u: %pV",
		       level, link->ap->prपूर्णांक_id, link->pmp, &vaf);
	अन्यथा
		prपूर्णांकk("%sata%u: %pV",
		       level, link->ap->prपूर्णांक_id, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ata_link_prपूर्णांकk);

व्योम ata_dev_prपूर्णांकk(स्थिर काष्ठा ata_device *dev, स्थिर अक्षर *level,
		    स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk("%sata%u.%02u: %pV",
	       level, dev->link->ap->prपूर्णांक_id, dev->link->pmp + dev->devno,
	       &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ata_dev_prपूर्णांकk);

व्योम ata_prपूर्णांक_version(स्थिर काष्ठा device *dev, स्थिर अक्षर *version)
अणु
	dev_prपूर्णांकk(KERN_DEBUG, dev, "version %s\n", version);
पूर्ण
EXPORT_SYMBOL(ata_prपूर्णांक_version);
