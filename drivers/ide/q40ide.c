<शैली गुरु>
/*
 *  Q40 I/O port IDE Driver
 *
 *     (c) Riअक्षरd Zidlicky
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ide.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/ide.h>

    /*
     *  Bases of the IDE पूर्णांकerfaces
     */

#घोषणा Q40IDE_NUM_HWIFS	2

#घोषणा PCIDE_BASE1	0x1f0
#घोषणा PCIDE_BASE2	0x170
#घोषणा PCIDE_BASE3	0x1e8
#घोषणा PCIDE_BASE4	0x168
#घोषणा PCIDE_BASE5	0x1e0
#घोषणा PCIDE_BASE6	0x160

अटल स्थिर अचिन्हित दीर्घ pcide_bases[Q40IDE_NUM_HWIFS] = अणु
    PCIDE_BASE1, PCIDE_BASE2, /* PCIDE_BASE3, PCIDE_BASE4  , PCIDE_BASE5,
    PCIDE_BASE6 */
पूर्ण;

अटल पूर्णांक q40ide_शेष_irq(अचिन्हित दीर्घ base)
अणु
           चयन (base) अणु
	            हाल 0x1f0: वापस 14;
		    हाल 0x170: वापस 15;
		    हाल 0x1e8: वापस 11;
		    शेष:
			वापस 0;
	   पूर्ण
पूर्ण


/*
 * Addresses are pretranslated क्रम Q40 ISA access.
 */
अटल व्योम q40_ide_setup_ports(काष्ठा ide_hw *hw, अचिन्हित दीर्घ base, पूर्णांक irq)
अणु
	स_रखो(hw, 0, माप(*hw));
	/* BIG FAT WARNING: 
	   assumption: only DATA port is ever used in 16 bit mode */
	hw->io_ports.data_addr = Q40_ISA_IO_W(base);
	hw->io_ports.error_addr = Q40_ISA_IO_B(base + 1);
	hw->io_ports.nsect_addr = Q40_ISA_IO_B(base + 2);
	hw->io_ports.lbal_addr = Q40_ISA_IO_B(base + 3);
	hw->io_ports.lbam_addr = Q40_ISA_IO_B(base + 4);
	hw->io_ports.lbah_addr = Q40_ISA_IO_B(base + 5);
	hw->io_ports.device_addr = Q40_ISA_IO_B(base + 6);
	hw->io_ports.status_addr = Q40_ISA_IO_B(base + 7);
	hw->io_ports.ctl_addr = Q40_ISA_IO_B(base + 0x206);

	hw->irq = irq;
पूर्ण

अटल व्योम q40ide_input_data(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
			      व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ data_addr = drive->hwअगर->io_ports.data_addr;

	अगर (drive->media == ide_disk && cmd && (cmd->tf_flags & IDE_TFLAG_FS)) अणु
		__ide_mm_insw(data_addr, buf, (len + 1) / 2);
		वापस;
	पूर्ण

	raw_insw_swapw((u16 *)data_addr, buf, (len + 1) / 2);
पूर्ण

अटल व्योम q40ide_output_data(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
			       व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ data_addr = drive->hwअगर->io_ports.data_addr;

	अगर (drive->media == ide_disk && cmd && (cmd->tf_flags & IDE_TFLAG_FS)) अणु
		__ide_mm_outsw(data_addr, buf, (len + 1) / 2);
		वापस;
	पूर्ण

	raw_outsw_swapw((u16 *)data_addr, buf, (len + 1) / 2);
पूर्ण

/* Q40 has a byte-swapped IDE पूर्णांकerface */
अटल स्थिर काष्ठा ide_tp_ops q40ide_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ide_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= q40ide_input_data,
	.output_data		= q40ide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info q40ide_port_info = अणु
	.tp_ops			= &q40ide_tp_ops,
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_NO_DMA,
	.irq_flags		= IRQF_SHARED,
	.chipset		= ide_generic,
पूर्ण;

/* 
 * the अटल array is needed to have the name reported in /proc/ioports,
 * hwअगर->name unक्रमtunately isn't available yet
 */
अटल स्थिर अक्षर *q40_ide_names[Q40IDE_NUM_HWIFS]=अणु
	"ide0", "ide1"
पूर्ण;

/*
 *  Probe क्रम Q40 IDE पूर्णांकerfaces
 */

अटल पूर्णांक __init q40ide_init(व्योम)
अणु
    पूर्णांक i;
    काष्ठा ide_hw hw[Q40IDE_NUM_HWIFS], *hws[] = अणु शून्य, शून्य पूर्ण;

    अगर (!MACH_IS_Q40)
      वापस -ENODEV;

    prपूर्णांकk(KERN_INFO "ide: Q40 IDE controller\n");

    क्रम (i = 0; i < Q40IDE_NUM_HWIFS; i++) अणु
	स्थिर अक्षर *name = q40_ide_names[i];

	अगर (!request_region(pcide_bases[i], 8, name)) अणु
		prपूर्णांकk("could not reserve ports %lx-%lx for %s\n",
		       pcide_bases[i],pcide_bases[i]+8,name);
		जारी;
	पूर्ण
	अगर (!request_region(pcide_bases[i]+0x206, 1, name)) अणु
		prपूर्णांकk("could not reserve port %lx for %s\n",
		       pcide_bases[i]+0x206,name);
		release_region(pcide_bases[i], 8);
		जारी;
	पूर्ण
	q40_ide_setup_ports(&hw[i], pcide_bases[i],
			q40ide_शेष_irq(pcide_bases[i]));

	hws[i] = &hw[i];
    पूर्ण

    वापस ide_host_add(&q40ide_port_info, hws, Q40IDE_NUM_HWIFS, शून्य);
पूर्ण

module_init(q40ide_init);

MODULE_LICENSE("GPL");
