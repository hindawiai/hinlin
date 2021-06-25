<शैली गुरु>
/*
 *  Atari Falcon IDE Driver
 *
 *     Created 12 Jul 1997 by Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stdma.h>
#समावेश <यंत्र/ide.h>

#घोषणा DRV_NAME "falconide"

    /*
     *  Offsets from base address
     */

#घोषणा ATA_HD_CONTROL	0x39

    /*
     *  falconide_पूर्णांकr_lock is used to obtain access to the IDE पूर्णांकerrupt,
     *  which is shared between several drivers.
     */

अटल पूर्णांक falconide_पूर्णांकr_lock;

अटल व्योम falconide_release_lock(व्योम)
अणु
	अगर (falconide_पूर्णांकr_lock == 0) अणु
		prपूर्णांकk(KERN_ERR "%s: bug\n", __func__);
		वापस;
	पूर्ण
	falconide_पूर्णांकr_lock = 0;
	stdma_release();
पूर्ण

अटल व्योम falconide_get_lock(irq_handler_t handler, व्योम *data)
अणु
	अगर (falconide_पूर्णांकr_lock == 0) अणु
		stdma_lock(handler, data);
		falconide_पूर्णांकr_lock = 1;
	पूर्ण
पूर्ण

अटल व्योम falconide_input_data(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
				 व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ data_addr = drive->hwअगर->io_ports.data_addr;

	अगर (drive->media == ide_disk && cmd && (cmd->tf_flags & IDE_TFLAG_FS)) अणु
		__ide_mm_insw(data_addr, buf, (len + 1) / 2);
		वापस;
	पूर्ण

	raw_insw_swapw((u16 *)data_addr, buf, (len + 1) / 2);
पूर्ण

अटल व्योम falconide_output_data(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
				  व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ data_addr = drive->hwअगर->io_ports.data_addr;

	अगर (drive->media == ide_disk && cmd && (cmd->tf_flags & IDE_TFLAG_FS)) अणु
		__ide_mm_outsw(data_addr, buf, (len + 1) / 2);
		वापस;
	पूर्ण

	raw_outsw_swapw((u16 *)data_addr, buf, (len + 1) / 2);
पूर्ण

/* Atari has a byte-swapped IDE पूर्णांकerface */
अटल स्थिर काष्ठा ide_tp_ops falconide_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ide_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= falconide_input_data,
	.output_data		= falconide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info falconide_port_info = अणु
	.get_lock		= falconide_get_lock,
	.release_lock		= falconide_release_lock,
	.tp_ops			= &falconide_tp_ops,
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_SERIALIZE |
				  IDE_HFLAG_NO_DMA,
	.irq_flags		= IRQF_SHARED,
	.chipset		= ide_generic,
पूर्ण;

अटल व्योम __init falconide_setup_ports(काष्ठा ide_hw *hw, अचिन्हित दीर्घ base)
अणु
	पूर्णांक i;

	स_रखो(hw, 0, माप(*hw));

	hw->io_ports.data_addr = base;

	क्रम (i = 1; i < 8; i++)
		hw->io_ports_array[i] = base + 1 + i * 4;

	hw->io_ports.ctl_addr = base + ATA_HD_CONTROL;

	hw->irq = IRQ_MFP_IDE;
पूर्ण

    /*
     *  Probe क्रम a Falcon IDE पूर्णांकerface
     */

अटल पूर्णांक __init falconide_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा ide_host *host;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;
	अचिन्हित दीर्घ base;
	पूर्णांक rc;

	dev_info(&pdev->dev, "Atari Falcon IDE controller\n");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), DRV_NAME)) अणु
		dev_err(&pdev->dev, "resources busy\n");
		वापस -EBUSY;
	पूर्ण

	base = (अचिन्हित दीर्घ)res->start;

	falconide_setup_ports(&hw, base);

	host = ide_host_alloc(&falconide_port_info, hws, 1);
	अगर (host == शून्य) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	falconide_get_lock(शून्य, शून्य);
	rc = ide_host_रेजिस्टर(host, &falconide_port_info, hws);
	falconide_release_lock();

	अगर (rc)
		जाओ err_मुक्त;

	platक्रमm_set_drvdata(pdev, host);
	वापस 0;
err_मुक्त:
	ide_host_मुक्त(host);
err:
	release_mem_region(res->start, resource_size(res));
	वापस rc;
पूर्ण

अटल पूर्णांक falconide_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_host *host = platक्रमm_get_drvdata(pdev);

	ide_host_हटाओ(host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ide_falcon_driver = अणु
	.हटाओ = falconide_हटाओ,
	.driver   = अणु
		.name	= "atari-falcon-ide",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(ide_falcon_driver, falconide_init);

MODULE_AUTHOR("Geert Uytterhoeven");
MODULE_DESCRIPTION("low-level driver for Atari Falcon IDE");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:atari-falcon-ide");
