<शैली गुरु>
/*======================================================================

    A driver क्रम PCMCIA IDE/ATA disk cards

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is David A. Hinds
    <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU General Public License version 2 (the "GPL"), in
    which हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.

======================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/ide.h>
#समावेश <linux/major.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>

#घोषणा DRV_NAME "ide-cs"

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("PCMCIA ATA/IDE card driver");
MODULE_LICENSE("Dual MPL/GPL");

/*====================================================================*/

प्रकार काष्ठा ide_info_t अणु
	काष्ठा pcmcia_device	*p_dev;
	काष्ठा ide_host		*host;
	पूर्णांक			ndev;
पूर्ण ide_info_t;

अटल व्योम ide_release(काष्ठा pcmcia_device *);
अटल पूर्णांक ide_config(काष्ठा pcmcia_device *);

अटल व्योम ide_detach(काष्ठा pcmcia_device *p_dev);

अटल पूर्णांक ide_probe(काष्ठा pcmcia_device *link)
अणु
    ide_info_t *info;

    dev_dbg(&link->dev, "ide_attach()\n");

    /* Create new ide device */
    info = kzalloc(माप(*info), GFP_KERNEL);
    अगर (!info)
	वापस -ENOMEM;

    info->p_dev = link;
    link->priv = info;

    link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO |
	    CONF_AUTO_SET_VPP | CONF_AUTO_CHECK_VCC;

    वापस ide_config(link);
पूर्ण /* ide_attach */

अटल व्योम ide_detach(काष्ठा pcmcia_device *link)
अणु
    ide_info_t *info = link->priv;

    dev_dbg(&link->dev, "ide_detach(0x%p)\n", link);

    ide_release(link);

    kमुक्त(info);
पूर्ण /* ide_detach */

अटल स्थिर काष्ठा ide_port_ops idecs_port_ops = अणु
	.quirkproc		= ide_undecoded_slave,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info idecs_port_info = अणु
	.port_ops		= &idecs_port_ops,
	.host_flags		= IDE_HFLAG_NO_DMA,
	.irq_flags		= IRQF_SHARED,
	.chipset		= ide_pci,
पूर्ण;

अटल काष्ठा ide_host *idecs_रेजिस्टर(अचिन्हित दीर्घ io, अचिन्हित दीर्घ ctl,
				अचिन्हित दीर्घ irq, काष्ठा pcmcia_device *handle)
अणु
    काष्ठा ide_host *host;
    ide_hwअगर_t *hwअगर;
    पूर्णांक i, rc;
    काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;

    अगर (!request_region(io, 8, DRV_NAME)) अणु
	prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX-0x%lX not free.\n",
			DRV_NAME, io, io + 7);
	वापस शून्य;
    पूर्ण

    अगर (!request_region(ctl, 1, DRV_NAME)) अणु
	prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX not free.\n",
			DRV_NAME, ctl);
	release_region(io, 8);
	वापस शून्य;
    पूर्ण

    स_रखो(&hw, 0, माप(hw));
    ide_std_init_ports(&hw, io, ctl);
    hw.irq = irq;
    hw.dev = &handle->dev;

    rc = ide_host_add(&idecs_port_info, hws, 1, &host);
    अगर (rc)
	जाओ out_release;

    hwअगर = host->ports[0];

    अगर (hwअगर->present)
	वापस host;

    /* retry registration in हाल device is still spinning up */
    क्रम (i = 0; i < 10; i++) अणु
	msleep(100);
	ide_port_scan(hwअगर);
	अगर (hwअगर->present)
	    वापस host;
    पूर्ण

    वापस host;

out_release:
    release_region(ctl, 1);
    release_region(io, 8);
    वापस शून्य;
पूर्ण

अटल पूर्णांक pcmcia_check_one_config(काष्ठा pcmcia_device *pdev, व्योम *priv_data)
अणु
	पूर्णांक *is_kme = priv_data;

	अगर ((pdev->resource[0]->flags & IO_DATA_PATH_WIDTH)
	    != IO_DATA_PATH_WIDTH_8) अणु
		pdev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
		pdev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	पूर्ण
	pdev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	pdev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;

	अगर (pdev->resource[1]->end) अणु
		pdev->resource[0]->end = 8;
		pdev->resource[1]->end = (*is_kme) ? 2 : 1;
	पूर्ण अन्यथा अणु
		अगर (pdev->resource[0]->end < 16)
			वापस -ENODEV;
	पूर्ण

	वापस pcmcia_request_io(pdev);
पूर्ण

अटल पूर्णांक ide_config(काष्ठा pcmcia_device *link)
अणु
    ide_info_t *info = link->priv;
    पूर्णांक ret = 0, is_kme = 0;
    अचिन्हित दीर्घ io_base, ctl_base;
    काष्ठा ide_host *host;

    dev_dbg(&link->dev, "ide_config(0x%p)\n", link);

    is_kme = ((link->manf_id == MANFID_KME) &&
	      ((link->card_id == PRODID_KME_KXLC005_A) ||
	       (link->card_id == PRODID_KME_KXLC005_B)));

    अगर (pcmcia_loop_config(link, pcmcia_check_one_config, &is_kme)) अणु
	    link->config_flags &= ~CONF_AUTO_CHECK_VCC;
	    अगर (pcmcia_loop_config(link, pcmcia_check_one_config, &is_kme))
		    जाओ failed; /* No suitable config found */
    पूर्ण
    io_base = link->resource[0]->start;
    अगर (link->resource[1]->end)
	    ctl_base = link->resource[1]->start;
    अन्यथा
	    ctl_base = link->resource[0]->start + 0x0e;

    अगर (!link->irq)
	    जाओ failed;

    ret = pcmcia_enable_device(link);
    अगर (ret)
	    जाओ failed;

    /* disable drive पूर्णांकerrupts during IDE probe */
    outb(0x02, ctl_base);

    /* special setup क्रम KXLC005 card */
    अगर (is_kme)
	outb(0x81, ctl_base+1);

     host = idecs_रेजिस्टर(io_base, ctl_base, link->irq, link);
     अगर (host == शून्य && resource_size(link->resource[0]) == 0x20) अणु
	    outb(0x02, ctl_base + 0x10);
	    host = idecs_रेजिस्टर(io_base + 0x10, ctl_base + 0x10,
				  link->irq, link);
    पूर्ण

    अगर (host == शून्य)
	जाओ failed;

    info->ndev = 1;
    info->host = host;
    dev_info(&link->dev, "ide-cs: hd%c: Vpp = %d.%d\n",
	    'a' + host->ports[0]->index * 2,
	    link->vpp / 10, link->vpp % 10);

    वापस 0;

failed:
    ide_release(link);
    वापस -ENODEV;
पूर्ण /* ide_config */

अटल व्योम ide_release(काष्ठा pcmcia_device *link)
अणु
    ide_info_t *info = link->priv;
    काष्ठा ide_host *host = info->host;

    dev_dbg(&link->dev, "ide_release(0x%p)\n", link);

    अगर (info->ndev) अणु
	ide_hwअगर_t *hwअगर = host->ports[0];
	अचिन्हित दीर्घ data_addr, ctl_addr;

	data_addr = hwअगर->io_ports.data_addr;
	ctl_addr = hwअगर->io_ports.ctl_addr;

	ide_host_हटाओ(host);
	info->ndev = 0;

	release_region(ctl_addr, 1);
	release_region(data_addr, 8);
    पूर्ण

    pcmcia_disable_device(link);
पूर्ण /* ide_release */


अटल स्थिर काष्ठा pcmcia_device_id ide_ids[] = अणु
	PCMCIA_DEVICE_FUNC_ID(4),
	PCMCIA_DEVICE_MANF_CARD(0x0000, 0x0000),	/* Corsair */
	PCMCIA_DEVICE_MANF_CARD(0x0007, 0x0000),	/* Hitachi */
	PCMCIA_DEVICE_MANF_CARD(0x000a, 0x0000),	/* I-O Data CFA */
	PCMCIA_DEVICE_MANF_CARD(0x001c, 0x0001),	/* Mitsubishi CFA */
	PCMCIA_DEVICE_MANF_CARD(0x0032, 0x0704),
	PCMCIA_DEVICE_MANF_CARD(0x0032, 0x2904),
	PCMCIA_DEVICE_MANF_CARD(0x0045, 0x0401),	/* SanDisk CFA */
	PCMCIA_DEVICE_MANF_CARD(0x004f, 0x0000),	/* Kingston */
	PCMCIA_DEVICE_MANF_CARD(0x0097, 0x1620), 	/* TI emulated */
	PCMCIA_DEVICE_MANF_CARD(0x0098, 0x0000),	/* Toshiba */
	PCMCIA_DEVICE_MANF_CARD(0x00a4, 0x002d),
	PCMCIA_DEVICE_MANF_CARD(0x00ce, 0x0000),	/* Samsung */
	PCMCIA_DEVICE_MANF_CARD(0x0319, 0x0000),	/* Hitachi */
	PCMCIA_DEVICE_MANF_CARD(0x2080, 0x0001),
	PCMCIA_DEVICE_MANF_CARD(0x4e01, 0x0100),	/* Viking CFA */
	PCMCIA_DEVICE_MANF_CARD(0x4e01, 0x0200),	/* Lexar, Viking CFA */
	PCMCIA_DEVICE_PROD_ID123("Caravelle", "PSC-IDE ", "PSC000", 0x8c36137c, 0xd0693ab8, 0x2768a9f0),
	PCMCIA_DEVICE_PROD_ID123("CDROM", "IDE", "MCD-601p", 0x1b9179ca, 0xede88951, 0x0d902f74),
	PCMCIA_DEVICE_PROD_ID123("PCMCIA", "IDE CARD", "F1", 0x281f1c5d, 0x1907960c, 0xf7fde8b9),
	PCMCIA_DEVICE_PROD_ID12("ARGOSY", "CD-ROM", 0x78f308dc, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("ARGOSY", "PnPIDE", 0x78f308dc, 0x0c694728),
	PCMCIA_DEVICE_PROD_ID12("CNF   ", "CD-ROM", 0x46d7db81, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("CNF CD-M", "CD-ROM", 0x7d93b852, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("Creative Technology Ltd.", "PCMCIA CD-ROM Interface Card", 0xff8c8a45, 0xfe8020c4),
	PCMCIA_DEVICE_PROD_ID12("Digital Equipment Corporation.", "Digital Mobile Media CD-ROM", 0x17692a66, 0xef1dcbde),
	PCMCIA_DEVICE_PROD_ID12("EXP", "CD+GAME", 0x6f58c983, 0x63c13aaf),
	PCMCIA_DEVICE_PROD_ID12("EXP   ", "CD-ROM", 0x0a5c52fd, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("EXP   ", "PnPIDE", 0x0a5c52fd, 0x0c694728),
	PCMCIA_DEVICE_PROD_ID12("FREECOM", "PCCARD-IDE", 0x5714cbf7, 0x48e0ab8e),
	PCMCIA_DEVICE_PROD_ID12("HITACHI", "FLASH", 0xf4f43949, 0x9eb86aae),
	PCMCIA_DEVICE_PROD_ID12("HITACHI", "microdrive", 0xf4f43949, 0xa6d76178),
	PCMCIA_DEVICE_PROD_ID12("Hyperstone", "Model1", 0x3d5b9ef5, 0xca6ab420),
	PCMCIA_DEVICE_PROD_ID12("IBM", "microdrive", 0xb569a6e5, 0xa6d76178),
	PCMCIA_DEVICE_PROD_ID12("IBM", "IBM17JSSFP20", 0xb569a6e5, 0xf2508753),
	PCMCIA_DEVICE_PROD_ID12("KINGSTON", "CF CARD 1GB", 0x2e6d1829, 0x55d5bffb),
	PCMCIA_DEVICE_PROD_ID12("KINGSTON", "CF CARD 4GB", 0x2e6d1829, 0x531e7d10),
	PCMCIA_DEVICE_PROD_ID12("KINGSTON", "CF8GB", 0x2e6d1829, 0xacbe682e),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "CBIDE2      ", 0x547e66dc, 0x8671043b),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "PCIDE", 0x547e66dc, 0x5c5ab149),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "PCIDEII", 0x547e66dc, 0xb3662674),
	PCMCIA_DEVICE_PROD_ID12("LOOKMEET", "CBIDE2      ", 0xe37be2b5, 0x8671043b),
	PCMCIA_DEVICE_PROD_ID12("M-Systems", "CF300", 0x7ed2ad87, 0x7e9e78ee),
	PCMCIA_DEVICE_PROD_ID12("M-Systems", "CF500", 0x7ed2ad87, 0x7a13045c),
	PCMCIA_DEVICE_PROD_ID2("NinjaATA-", 0xebe0bd79),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "CD-ROM", 0x281f1c5d, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "PnPIDE", 0x281f1c5d, 0x0c694728),
	PCMCIA_DEVICE_PROD_ID12("SHUTTLE TECHNOLOGY LTD.", "PCCARD-IDE/ATAPI Adapter", 0x4a3f0ba0, 0x322560e1),
	PCMCIA_DEVICE_PROD_ID12("SEAGATE", "ST1", 0x87c1b330, 0xe1f30883),
	PCMCIA_DEVICE_PROD_ID12("SAMSUNG", "04/05/06", 0x43d74cb4, 0x6a22777d),
	PCMCIA_DEVICE_PROD_ID12("SMI VENDOR", "SMI PRODUCT", 0x30896c92, 0x703cc5f6),
	PCMCIA_DEVICE_PROD_ID12("TOSHIBA", "MK2001MPL", 0xb4585a1a, 0x3489e003),
	PCMCIA_DEVICE_PROD_ID1("TRANSCEND    512M   ", 0xd0909443),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS1GCF45", 0x709b1bf1, 0xf68b6f32),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS1GCF80", 0x709b1bf1, 0x2a54d4b1),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS2GCF120", 0x709b1bf1, 0x969aa4f2),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS4GCF120", 0x709b1bf1, 0xf54a91c8),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS4GCF133", 0x709b1bf1, 0x7558f133),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS8GCF133", 0x709b1bf1, 0xb2f89b47),
	PCMCIA_DEVICE_PROD_ID12("WIT", "IDE16", 0x244e5994, 0x3e232852),
	PCMCIA_DEVICE_PROD_ID12("WEIDA", "TWTTI", 0xcc7cf69c, 0x212bb918),
	PCMCIA_DEVICE_PROD_ID1("STI Flash", 0xe4a13209),
	PCMCIA_DEVICE_PROD_ID12("STI", "Flash 5.0", 0xbf2df18d, 0x8cb57a0e),
	PCMCIA_MFC_DEVICE_PROD_ID12(1, "SanDisk", "ConnectPlus", 0x7a954bd9, 0x74be00c6),
	PCMCIA_DEVICE_PROD_ID2("Flash Card", 0x5a362506),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, ide_ids);

अटल काष्ठा pcmcia_driver ide_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "ide-cs",
	.probe		= ide_probe,
	.हटाओ		= ide_detach,
	.id_table       = ide_ids,
पूर्ण;

अटल पूर्णांक __init init_ide_cs(व्योम)
अणु
	वापस pcmcia_रेजिस्टर_driver(&ide_cs_driver);
पूर्ण

अटल व्योम __निकास निकास_ide_cs(व्योम)
अणु
	pcmcia_unरेजिस्टर_driver(&ide_cs_driver);
पूर्ण

late_initcall(init_ide_cs);
module_निकास(निकास_ide_cs);
