<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1996-2001  Linus Torvalds & author (see below)
 */

/*
 *  Version 0.03	Cleaned स्वतः-tune, added probe
 *  Version 0.04	Added second channel tuning
 *  Version 0.05	Enhanced tuning ; added qd6500 support
 *  Version 0.06	Added करोs driver's list
 *  Version 0.07	Second channel bug fix 
 *
 * QDI QD6500/QD6580 EIDE controller fast support
 *
 * To activate controller support, use "ide0=qd65xx"
 */

/*
 * Rewritten from the work of Colten Edwards <pje120@cs.usask.ca> by
 * Samuel Thibault <samuel.thibault@ens-lyon.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/ioport.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "qd65xx"

#समावेश "qd65xx.h"

/*
 * I/O ports are 0x30-0x31 (and 0x32-0x33 क्रम qd6580)
 *            or 0xb0-0xb1 (and 0xb2-0xb3 क्रम qd6580)
 *	-- qd6500 is a single IDE पूर्णांकerface
 *	-- qd6580 is a dual IDE पूर्णांकerface
 *
 * More research on qd6580 being करोne by willmore@cig.mot.com (David)
 * More Inक्रमmation given by Petr Soucek (petr@ryston.cz)
 * http://www.ryston.cz/petr/vlb
 */

/*
 * base: Timer1
 *
 *
 * base+0x01: Config (R/O)
 *
 * bit 0: ide baseport: 1 = 0x1f0 ; 0 = 0x170 (only useful क्रम qd6500)
 * bit 1: qd65xx baseport: 1 = 0xb0 ; 0 = 0x30
 * bit 2: ID3: bus speed: 1 = <=33MHz ; 0 = >33MHz
 * bit 3: qd6500: 1 = disabled, 0 = enabled
 *        qd6580: 1
 * upper nibble:
 *        qd6500: 1100
 *        qd6580: either 1010 or 0101
 *
 *
 * base+0x02: Timer2 (qd6580 only)
 *
 *
 * base+0x03: Control (qd6580 only)
 *
 * bits 0-3 must always be set 1
 * bit 4 must be set 1, but is set 0 by करोs driver जबतक measuring vlb घड़ी
 * bit 0 : 1 = Only primary port enabled : channel 0 क्रम hda, channel 1 क्रम hdb
 *         0 = Primary and Secondary ports enabled : channel 0 क्रम hda & hdb
 *                                                   channel 1 क्रम hdc & hdd
 * bit 1 : 1 = only disks on primary port
 *         0 = disks & ATAPI devices on primary port
 * bit 2-4 : always 0
 * bit 5 : status, but of what ?
 * bit 6 : always set 1 by करोs driver
 * bit 7 : set 1 क्रम non-ATAPI devices on primary port
 *	(maybe पढ़ो-ahead and post-ग_लिखो buffer ?)
 */

अटल पूर्णांक timings[4]=अणु-1,-1,-1,-1पूर्ण; /* stores current timing क्रम each समयr */

/*
 * qd65xx_select:
 *
 * This routine is invoked to prepare क्रम access to a given drive.
 */

अटल व्योम qd65xx_dev_select(ide_drive_t *drive)
अणु
	u8 index = ((	(QD_TIMREG(drive)) & 0x80 ) >> 7) |
			(QD_TIMREG(drive) & 0x02);

	अगर (timings[index] != QD_TIMING(drive))
		outb(timings[index] = QD_TIMING(drive), QD_TIMREG(drive));

	outb(drive->select | ATA_DEVICE_OBS, drive->hwअगर->io_ports.device_addr);
पूर्ण

/*
 * qd6500_compute_timing
 *
 * computes the timing value where
 *	lower nibble represents active समय,   in count of VLB घड़ीs
 *	upper nibble represents recovery समय, in count of VLB घड़ीs
 */

अटल u8 qd6500_compute_timing (ide_hwअगर_t *hwअगर, पूर्णांक active_समय, पूर्णांक recovery_समय)
अणु
	पूर्णांक clk = ide_vlb_clk ? ide_vlb_clk : 50;
	u8 act_cyc, rec_cyc;

	अगर (clk <= 33) अणु
		act_cyc =  9 - IDE_IN(active_समय   * clk / 1000 + 1, 2,  9);
		rec_cyc = 15 - IDE_IN(recovery_समय * clk / 1000 + 1, 0, 15);
	पूर्ण अन्यथा अणु
		act_cyc =  8 - IDE_IN(active_समय   * clk / 1000 + 1, 1,  8);
		rec_cyc = 18 - IDE_IN(recovery_समय * clk / 1000 + 1, 3, 18);
	पूर्ण

	वापस (rec_cyc << 4) | 0x08 | act_cyc;
पूर्ण

/*
 * qd6580_compute_timing
 *
 * idem क्रम qd6580
 */

अटल u8 qd6580_compute_timing (पूर्णांक active_समय, पूर्णांक recovery_समय)
अणु
	पूर्णांक clk = ide_vlb_clk ? ide_vlb_clk : 50;
	u8 act_cyc, rec_cyc;

	act_cyc = 17 - IDE_IN(active_समय   * clk / 1000 + 1, 2, 17);
	rec_cyc = 15 - IDE_IN(recovery_समय * clk / 1000 + 1, 2, 15);

	वापस (rec_cyc << 4) | act_cyc;
पूर्ण

/*
 * qd_find_disk_type
 *
 * tries to find timing from करोs driver's table
 */

अटल पूर्णांक qd_find_disk_type (ide_drive_t *drive,
		पूर्णांक *active_समय, पूर्णांक *recovery_समय)
अणु
	काष्ठा qd65xx_timing_s *p;
	अक्षर *m = (अक्षर *)&drive->id[ATA_ID_PROD];
	अक्षर model[ATA_ID_PROD_LEN];

	अगर (*m == 0)
		वापस 0;

	म_नकलन(model, m, ATA_ID_PROD_LEN);
	ide_fixstring(model, ATA_ID_PROD_LEN, 1); /* byte-swap */

	क्रम (p = qd65xx_timing ; p->offset != -1 ; p++) अणु
		अगर (!म_भेदन(p->model, model+p->offset, 4)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: listed !\n", drive->name);
			*active_समय = p->active;
			*recovery_समय = p->recovery;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * qd_set_timing:
 *
 * records the timing
 */

अटल व्योम qd_set_timing (ide_drive_t *drive, u8 timing)
अणु
	अचिन्हित दीर्घ data = (अचिन्हित दीर्घ)ide_get_drivedata(drive);

	data &= 0xff00;
	data |= timing;
	ide_set_drivedata(drive, (व्योम *)data);

	prपूर्णांकk(KERN_DEBUG "%s: %#x\n", drive->name, timing);
पूर्ण

अटल व्योम qd6500_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	u16 *id = drive->id;
	पूर्णांक active_समय   = 175;
	पूर्णांक recovery_समय = 415; /* worst हाल values from the करोs driver */

	/* FIXME: use drive->pio_mode value */
	अगर (!qd_find_disk_type(drive, &active_समय, &recovery_समय) &&
	    (id[ATA_ID_OLD_PIO_MODES] & 0xff) && (id[ATA_ID_FIELD_VALID] & 2) &&
	    id[ATA_ID_EIDE_PIO] >= 240) अणु
		prपूर्णांकk(KERN_INFO "%s: PIO mode%d\n", drive->name,
			id[ATA_ID_OLD_PIO_MODES] & 0xff);
		active_समय = 110;
		recovery_समय = drive->id[ATA_ID_EIDE_PIO] - 120;
	पूर्ण

	qd_set_timing(drive, qd6500_compute_timing(drive->hwअगर,
				active_समय, recovery_समय));
पूर्ण

अटल व्योम qd6580_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	काष्ठा ide_timing *t = ide_timing_find_mode(XFER_PIO_0 + pio);
	अचिन्हित पूर्णांक cycle_समय;
	पूर्णांक active_समय   = 175;
	पूर्णांक recovery_समय = 415; /* worst हाल values from the करोs driver */
	u8 base = (hwअगर->config_data & 0xff00) >> 8;

	अगर (drive->id && !qd_find_disk_type(drive, &active_समय, &recovery_समय)) अणु
		cycle_समय = ide_pio_cycle_समय(drive, pio);

		चयन (pio) अणु
			हाल 0: अवरोध;
			हाल 3:
				अगर (cycle_समय >= 110) अणु
					active_समय = 86;
					recovery_समय = cycle_समय - 102;
				पूर्ण अन्यथा
					prपूर्णांकk(KERN_WARNING "%s: Strange recovery time !\n",drive->name);
				अवरोध;
			हाल 4:
				अगर (cycle_समय >= 69) अणु
					active_समय = 70;
					recovery_समय = cycle_समय - 61;
				पूर्ण अन्यथा
					prपूर्णांकk(KERN_WARNING "%s: Strange recovery time !\n",drive->name);
				अवरोध;
			शेष:
				अगर (cycle_समय >= 180) अणु
					active_समय = 110;
					recovery_समय = cycle_समय - 120;
				पूर्ण अन्यथा अणु
					active_समय = t->active;
					recovery_समय = cycle_समय - active_समय;
				पूर्ण
		पूर्ण
		prपूर्णांकk(KERN_INFO "%s: PIO mode%d\n", drive->name,pio);
	पूर्ण

	अगर (!hwअगर->channel && drive->media != ide_disk) अणु
		outb(0x5f, QD_CONTROL_PORT);
		prपूर्णांकk(KERN_WARNING "%s: ATAPI: disabled read-ahead FIFO "
			"and post-write buffer on %s.\n",
			drive->name, hwअगर->name);
	पूर्ण

	qd_set_timing(drive, qd6580_compute_timing(active_समय, recovery_समय));
पूर्ण

/*
 * qd_testreg
 *
 * tests अगर the given port is a रेजिस्टर
 */

अटल पूर्णांक __init qd_testreg(पूर्णांक port)
अणु
	अचिन्हित दीर्घ flags;
	u8 savereg, पढ़ोreg;

	local_irq_save(flags);
	savereg = inb_p(port);
	outb_p(QD_TESTVAL, port);	/* safe value */
	पढ़ोreg = inb_p(port);
	outb(savereg, port);
	local_irq_restore(flags);

	अगर (savereg == QD_TESTVAL) अणु
		prपूर्णांकk(KERN_ERR "Outch ! the probe for qd65xx isn't reliable !\n");
		prपूर्णांकk(KERN_ERR "Please contact maintainers to tell about your hardware\n");
		prपूर्णांकk(KERN_ERR "Assuming qd65xx is not present.\n");
		वापस 1;
	पूर्ण

	वापस (पढ़ोreg != QD_TESTVAL);
पूर्ण

अटल व्योम __init qd6500_init_dev(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 base = (hwअगर->config_data & 0xff00) >> 8;
	u8 config = QD_CONFIG(hwअगर);

	ide_set_drivedata(drive, (व्योम *)QD6500_DEF_DATA);
पूर्ण

अटल व्योम __init qd6580_init_dev(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित दीर्घ t1, t2;
	u8 base = (hwअगर->config_data & 0xff00) >> 8;
	u8 config = QD_CONFIG(hwअगर);

	अगर (hwअगर->host_flags & IDE_HFLAG_SINGLE) अणु
		t1 = QD6580_DEF_DATA;
		t2 = QD6580_DEF_DATA2;
	पूर्ण अन्यथा
		t2 = t1 = hwअगर->channel ? QD6580_DEF_DATA2 : QD6580_DEF_DATA;

	ide_set_drivedata(drive, (व्योम *)((drive->dn & 1) ? t2 : t1));
पूर्ण

अटल स्थिर काष्ठा ide_tp_ops qd65xx_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= qd65xx_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops qd6500_port_ops = अणु
	.init_dev		= qd6500_init_dev,
	.set_pio_mode		= qd6500_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops qd6580_port_ops = अणु
	.init_dev		= qd6580_init_dev,
	.set_pio_mode		= qd6580_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info qd65xx_port_info __initस्थिर = अणु
	.name			= DRV_NAME,
	.tp_ops 		= &qd65xx_tp_ops,
	.chipset		= ide_qd65xx,
	.host_flags		= IDE_HFLAG_IO_32BIT |
				  IDE_HFLAG_NO_DMA,
	.pio_mask		= ATA_PIO4,
पूर्ण;

/*
 * qd_probe:
 *
 * looks at the specअगरied baseport, and अगर qd found, रेजिस्टरs & initialises it
 * वापस 1 अगर another qd may be probed
 */

अटल पूर्णांक __init qd_probe(पूर्णांक base)
अणु
	पूर्णांक rc;
	u8 config, unit, control;
	काष्ठा ide_port_info d = qd65xx_port_info;

	config = inb(QD_CONFIG_PORT);

	अगर (! ((config & QD_CONFIG_BASEPORT) >> 1 == (base == 0xb0)) )
		वापस -ENODEV;

	unit = ! (config & QD_CONFIG_IDE_BASEPORT);

	अगर (unit)
		d.host_flags |= IDE_HFLAG_QD_2ND_PORT;

	चयन (config & 0xf0) अणु
	हाल QD_CONFIG_QD6500:
		अगर (qd_testreg(base))
			 वापस -ENODEV;	/* bad रेजिस्टर */

		अगर (config & QD_CONFIG_DISABLED) अणु
			prपूर्णांकk(KERN_WARNING "qd6500 is disabled !\n");
			वापस -ENODEV;
		पूर्ण

		prपूर्णांकk(KERN_NOTICE "qd6500 at %#x\n", base);
		prपूर्णांकk(KERN_DEBUG "qd6500: config=%#x, ID3=%u\n",
			config, QD_ID3);

		d.port_ops = &qd6500_port_ops;
		d.host_flags |= IDE_HFLAG_SINGLE;
		अवरोध;
	हाल QD_CONFIG_QD6580_A:
	हाल QD_CONFIG_QD6580_B:
		अगर (qd_testreg(base) || qd_testreg(base + 0x02))
			वापस -ENODEV;	/* bad रेजिस्टरs */

		control = inb(QD_CONTROL_PORT);

		prपूर्णांकk(KERN_NOTICE "qd6580 at %#x\n", base);
		prपूर्णांकk(KERN_DEBUG "qd6580: config=%#x, control=%#x, ID3=%u\n",
			config, control, QD_ID3);

		outb(QD_DEF_CONTR, QD_CONTROL_PORT);

		d.port_ops = &qd6580_port_ops;
		अगर (control & QD_CONTR_SEC_DISABLED)
			d.host_flags |= IDE_HFLAG_SINGLE;

		prपूर्णांकk(KERN_INFO "qd6580: %s IDE board\n",
			(control & QD_CONTR_SEC_DISABLED) ? "single" : "dual");
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	rc = ide_legacy_device_add(&d, (base << 8) | config);

	अगर (d.host_flags & IDE_HFLAG_SINGLE)
		वापस (rc == 0) ? 1 : rc;

	वापस rc;
पूर्ण

अटल bool probe_qd65xx;

module_param_named(probe, probe_qd65xx, bool, 0);
MODULE_PARM_DESC(probe, "probe for QD65xx chipsets");

अटल पूर्णांक __init qd65xx_init(व्योम)
अणु
	पूर्णांक rc1, rc2 = -ENODEV;

	अगर (probe_qd65xx == 0)
		वापस -ENODEV;

	rc1 = qd_probe(0x30);
	अगर (rc1)
		rc2 = qd_probe(0xb0);

	अगर (rc1 < 0 && rc2 < 0)
		वापस -ENODEV;

	वापस 0;
पूर्ण

module_init(qd65xx_init);

MODULE_AUTHOR("Samuel Thibault");
MODULE_DESCRIPTION("support of qd65xx vlb ide chipset");
MODULE_LICENSE("GPL");
