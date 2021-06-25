<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ide.h>

#अगर defined(CONFIG_ARM) || defined(CONFIG_M68K) || defined(CONFIG_MIPS) || \
    defined(CONFIG_PARISC) || defined(CONFIG_PPC) || defined(CONFIG_SPARC)
#समावेश <यंत्र/ide.h>
#अन्यथा
#समावेश <यंत्र-generic/ide_iops.h>
#पूर्ण_अगर

/*
 *	Conventional PIO operations क्रम ATA devices
 */

अटल u8 ide_inb(अचिन्हित दीर्घ port)
अणु
	वापस (u8) inb(port);
पूर्ण

अटल व्योम ide_outb(u8 val, अचिन्हित दीर्घ port)
अणु
	outb(val, port);
पूर्ण

/*
 *	MMIO operations, typically used क्रम SATA controllers
 */

अटल u8 ide_mm_inb(अचिन्हित दीर्घ port)
अणु
	वापस (u8) पढ़ोb((व्योम __iomem *) port);
पूर्ण

अटल व्योम ide_mm_outb(u8 value, अचिन्हित दीर्घ port)
अणु
	ग_लिखोb(value, (व्योम __iomem *) port);
पूर्ण

व्योम ide_exec_command(ide_hwअगर_t *hwअगर, u8 cmd)
अणु
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		ग_लिखोb(cmd, (व्योम __iomem *)hwअगर->io_ports.command_addr);
	अन्यथा
		outb(cmd, hwअगर->io_ports.command_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_exec_command);

u8 ide_पढ़ो_status(ide_hwअगर_t *hwअगर)
अणु
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		वापस पढ़ोb((व्योम __iomem *)hwअगर->io_ports.status_addr);
	अन्यथा
		वापस inb(hwअगर->io_ports.status_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_पढ़ो_status);

u8 ide_पढ़ो_altstatus(ide_hwअगर_t *hwअगर)
अणु
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		वापस पढ़ोb((व्योम __iomem *)hwअगर->io_ports.ctl_addr);
	अन्यथा
		वापस inb(hwअगर->io_ports.ctl_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_पढ़ो_altstatus);

व्योम ide_ग_लिखो_devctl(ide_hwअगर_t *hwअगर, u8 ctl)
अणु
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		ग_लिखोb(ctl, (व्योम __iomem *)hwअगर->io_ports.ctl_addr);
	अन्यथा
		outb(ctl, hwअगर->io_ports.ctl_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_ग_लिखो_devctl);

व्योम ide_dev_select(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 select = drive->select | ATA_DEVICE_OBS;

	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		ग_लिखोb(select, (व्योम __iomem *)hwअगर->io_ports.device_addr);
	अन्यथा
		outb(select, hwअगर->io_ports.device_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_dev_select);

व्योम ide_tf_load(ide_drive_t *drive, काष्ठा ide_taskfile *tf, u8 valid)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	व्योम (*tf_outb)(u8 addr, अचिन्हित दीर्घ port);
	u8 mmio = (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;

	अगर (mmio)
		tf_outb = ide_mm_outb;
	अन्यथा
		tf_outb = ide_outb;

	अगर (valid & IDE_VALID_FEATURE)
		tf_outb(tf->feature, io_ports->feature_addr);
	अगर (valid & IDE_VALID_NSECT)
		tf_outb(tf->nsect, io_ports->nsect_addr);
	अगर (valid & IDE_VALID_LBAL)
		tf_outb(tf->lbal, io_ports->lbal_addr);
	अगर (valid & IDE_VALID_LBAM)
		tf_outb(tf->lbam, io_ports->lbam_addr);
	अगर (valid & IDE_VALID_LBAH)
		tf_outb(tf->lbah, io_ports->lbah_addr);
	अगर (valid & IDE_VALID_DEVICE)
		tf_outb(tf->device, io_ports->device_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_tf_load);

व्योम ide_tf_पढ़ो(ide_drive_t *drive, काष्ठा ide_taskfile *tf, u8 valid)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	u8 (*tf_inb)(अचिन्हित दीर्घ port);
	u8 mmio = (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;

	अगर (mmio)
		tf_inb  = ide_mm_inb;
	अन्यथा
		tf_inb  = ide_inb;

	अगर (valid & IDE_VALID_ERROR)
		tf->error  = tf_inb(io_ports->feature_addr);
	अगर (valid & IDE_VALID_NSECT)
		tf->nsect  = tf_inb(io_ports->nsect_addr);
	अगर (valid & IDE_VALID_LBAL)
		tf->lbal   = tf_inb(io_ports->lbal_addr);
	अगर (valid & IDE_VALID_LBAM)
		tf->lbam   = tf_inb(io_ports->lbam_addr);
	अगर (valid & IDE_VALID_LBAH)
		tf->lbah   = tf_inb(io_ports->lbah_addr);
	अगर (valid & IDE_VALID_DEVICE)
		tf->device = tf_inb(io_ports->device_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_tf_पढ़ो);

/*
 * Some localbus EIDE पूर्णांकerfaces require a special access sequence
 * when using 32-bit I/O inकाष्ठाions to transfer data.  We call this
 * the "vlb_sync" sequence, which consists of three successive पढ़ोs
 * of the sector count रेजिस्टर location, with पूर्णांकerrupts disabled
 * to ensure that the पढ़ोs all happen together.
 */
अटल व्योम ata_vlb_sync(अचिन्हित दीर्घ port)
अणु
	(व्योम)inb(port);
	(व्योम)inb(port);
	(व्योम)inb(port);
पूर्ण

/*
 * This is used क्रम most PIO data transfers *from* the IDE पूर्णांकerface
 *
 * These routines will round up any request क्रम an odd number of bytes,
 * so अगर an odd len is specअगरied, be sure that there's at least one
 * extra byte allocated क्रम the buffer.
 */
व्योम ide_input_data(ide_drive_t *drive, काष्ठा ide_cmd *cmd, व्योम *buf,
		    अचिन्हित पूर्णांक len)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	अचिन्हित दीर्घ data_addr = io_ports->data_addr;
	अचिन्हित पूर्णांक words = (len + 1) >> 1;
	u8 io_32bit = drive->io_32bit;
	u8 mmio = (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;

	अगर (io_32bit) अणु
		अचिन्हित दीर्घ flags;

		अगर ((io_32bit & 2) && !mmio) अणु
			local_irq_save(flags);
			ata_vlb_sync(io_ports->nsect_addr);
		पूर्ण

		words >>= 1;
		अगर (mmio)
			__ide_mm_insl((व्योम __iomem *)data_addr, buf, words);
		अन्यथा
			insl(data_addr, buf, words);

		अगर ((io_32bit & 2) && !mmio)
			local_irq_restore(flags);

		अगर (((len + 1) & 3) < 2)
			वापस;

		buf += len & ~3;
		words = 1;
	पूर्ण

	अगर (mmio)
		__ide_mm_insw((व्योम __iomem *)data_addr, buf, words);
	अन्यथा
		insw(data_addr, buf, words);
पूर्ण
EXPORT_SYMBOL_GPL(ide_input_data);

/*
 * This is used क्रम most PIO data transfers *to* the IDE पूर्णांकerface
 */
व्योम ide_output_data(ide_drive_t *drive, काष्ठा ide_cmd *cmd, व्योम *buf,
		     अचिन्हित पूर्णांक len)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	अचिन्हित दीर्घ data_addr = io_ports->data_addr;
	अचिन्हित पूर्णांक words = (len + 1) >> 1;
	u8 io_32bit = drive->io_32bit;
	u8 mmio = (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;

	अगर (io_32bit) अणु
		अचिन्हित दीर्घ flags;

		अगर ((io_32bit & 2) && !mmio) अणु
			local_irq_save(flags);
			ata_vlb_sync(io_ports->nsect_addr);
		पूर्ण

		words >>= 1;
		अगर (mmio)
			__ide_mm_outsl((व्योम __iomem *)data_addr, buf, words);
		अन्यथा
			outsl(data_addr, buf, words);

		अगर ((io_32bit & 2) && !mmio)
			local_irq_restore(flags);

		अगर (((len + 1) & 3) < 2)
			वापस;

		buf += len & ~3;
		words = 1;
	पूर्ण

	अगर (mmio)
		__ide_mm_outsw((व्योम __iomem *)data_addr, buf, words);
	अन्यथा
		outsw(data_addr, buf, words);
पूर्ण
EXPORT_SYMBOL_GPL(ide_output_data);

स्थिर काष्ठा ide_tp_ops शेष_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ide_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;
