<शैली गुरु>
/*
 *  Amiga Buddha, Catweasel and X-Surf IDE Driver
 *
 *	Copyright (C) 1997, 2001 by Geert Uytterhoeven and others
 *
 *  This driver was written based on the specअगरications in README.buddha and
 *  the X-Surf info from Inside_XSurf.txt available at
 *  http://www.jschoenfeld.com
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 *  TODO:
 *    - test it :-)
 *    - tune the timings using the speed-रेजिस्टर
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/zorro.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>


    /*
     *  The Buddha has 2 IDE पूर्णांकerfaces, the Catweasel has 3, X-Surf has 2
     */

#घोषणा BUDDHA_NUM_HWIFS	2
#घोषणा CATWEASEL_NUM_HWIFS	3
#घोषणा XSURF_NUM_HWIFS         2

#घोषणा MAX_NUM_HWIFS		3

    /*
     *  Bases of the IDE पूर्णांकerfaces (relative to the board address)
     */

#घोषणा BUDDHA_BASE1	0x800
#घोषणा BUDDHA_BASE2	0xa00
#घोषणा BUDDHA_BASE3	0xc00

#घोषणा XSURF_BASE1     0xb000 /* 2.5" Interface */
#घोषणा XSURF_BASE2     0xd000 /* 3.5" Interface */

अटल u_पूर्णांक buddha_bases[CATWEASEL_NUM_HWIFS] __initdata = अणु
    BUDDHA_BASE1, BUDDHA_BASE2, BUDDHA_BASE3
पूर्ण;

अटल u_पूर्णांक xsurf_bases[XSURF_NUM_HWIFS] __initdata = अणु
     XSURF_BASE1, XSURF_BASE2
पूर्ण;

    /*
     *  Offsets from one of the above bases
     */

#घोषणा BUDDHA_CONTROL	0x11a

    /*
     *  Other रेजिस्टरs
     */

#घोषणा BUDDHA_IRQ1	0xf00		/* MSB = 1, Harddisk is source of */
#घोषणा BUDDHA_IRQ2	0xf40		/* पूर्णांकerrupt */
#घोषणा BUDDHA_IRQ3	0xf80

#घोषणा XSURF_IRQ1      0x7e
#घोषणा XSURF_IRQ2      0x7e

अटल पूर्णांक buddha_irqports[CATWEASEL_NUM_HWIFS] __initdata = अणु
    BUDDHA_IRQ1, BUDDHA_IRQ2, BUDDHA_IRQ3
पूर्ण;

अटल पूर्णांक xsurf_irqports[XSURF_NUM_HWIFS] __initdata = अणु
    XSURF_IRQ1, XSURF_IRQ2
पूर्ण;

#घोषणा BUDDHA_IRQ_MR	0xfc0		/* master पूर्णांकerrupt enable */


    /*
     *  Board inक्रमmation
     */

प्रकार क्रमागत BuddhaType_Enum अणु
    BOARD_BUDDHA, BOARD_CATWEASEL, BOARD_XSURF
पूर्ण BuddhaType;

अटल स्थिर अक्षर *buddha_board_name[] = अणु "Buddha", "Catweasel", "X-Surf" पूर्ण;

    /*
     *  Check and acknowledge the पूर्णांकerrupt status
     */

अटल पूर्णांक buddha_test_irq(ide_hwअगर_t *hwअगर)
अणु
    अचिन्हित अक्षर ch;

    ch = z_पढ़ोb(hwअगर->io_ports.irq_addr);
    अगर (!(ch & 0x80))
	    वापस 0;
    वापस 1;
पूर्ण

अटल व्योम xsurf_clear_irq(ide_drive_t *drive)
अणु
    /*
     * X-Surf needs 0 written to IRQ रेजिस्टर to ensure ISA bit A11 stays at 0
     */
    z_ग_लिखोb(0, drive->hwअगर->io_ports.irq_addr);
पूर्ण

अटल व्योम __init buddha_setup_ports(काष्ठा ide_hw *hw, अचिन्हित दीर्घ base,
				      अचिन्हित दीर्घ ctl, अचिन्हित दीर्घ irq_port)
अणु
	पूर्णांक i;

	स_रखो(hw, 0, माप(*hw));

	hw->io_ports.data_addr = base;

	क्रम (i = 1; i < 8; i++)
		hw->io_ports_array[i] = base + 2 + i * 4;

	hw->io_ports.ctl_addr = ctl;
	hw->io_ports.irq_addr = irq_port;

	hw->irq = IRQ_AMIGA_PORTS;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops buddha_port_ops = अणु
	.test_irq		= buddha_test_irq,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops xsurf_port_ops = अणु
	.clear_irq		= xsurf_clear_irq,
	.test_irq		= buddha_test_irq,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info buddha_port_info = अणु
	.port_ops		= &buddha_port_ops,
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_NO_DMA,
	.irq_flags		= IRQF_SHARED,
	.chipset		= ide_generic,
पूर्ण;

    /*
     *  Probe क्रम a Buddha or Catweasel IDE पूर्णांकerface
     */

अटल पूर्णांक __init buddha_init(व्योम)
अणु
	काष्ठा zorro_dev *z = शून्य;
	u_दीर्घ buddha_board = 0;
	BuddhaType type;
	पूर्णांक buddha_num_hwअगरs, i;

	जबतक ((z = zorro_find_device(ZORRO_WILDCARD, z))) अणु
		अचिन्हित दीर्घ board;
		काष्ठा ide_hw hw[MAX_NUM_HWIFS], *hws[MAX_NUM_HWIFS];
		काष्ठा ide_port_info d = buddha_port_info;

		अगर (z->id == ZORRO_PROD_INDIVIDUAL_COMPUTERS_BUDDHA) अणु
			buddha_num_hwअगरs = BUDDHA_NUM_HWIFS;
			type=BOARD_BUDDHA;
		पूर्ण अन्यथा अगर (z->id == ZORRO_PROD_INDIVIDUAL_COMPUTERS_CATWEASEL) अणु
			buddha_num_hwअगरs = CATWEASEL_NUM_HWIFS;
			type=BOARD_CATWEASEL;
		पूर्ण अन्यथा अगर (z->id == ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF) अणु
			buddha_num_hwअगरs = XSURF_NUM_HWIFS;
			type=BOARD_XSURF;
			d.port_ops = &xsurf_port_ops;
		पूर्ण अन्यथा 
			जारी;
		
		board = z->resource.start;

		अगर(type != BOARD_XSURF) अणु
			अगर (!request_mem_region(board+BUDDHA_BASE1, 0x800, "IDE"))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!request_mem_region(board+XSURF_BASE1, 0x1000, "IDE"))
				जारी;
			अगर (!request_mem_region(board+XSURF_BASE2, 0x1000, "IDE"))
				जाओ fail_base2;
			अगर (!request_mem_region(board+XSURF_IRQ1, 0x8, "IDE")) अणु
				release_mem_region(board+XSURF_BASE2, 0x1000);
fail_base2:
				release_mem_region(board+XSURF_BASE1, 0x1000);
				जारी;
			पूर्ण
		पूर्ण	  
		buddha_board = (अचिन्हित दीर्घ)ZTWO_VADDR(board);
		
		/* ग_लिखो to BUDDHA_IRQ_MR to enable the board IRQ */
		/* X-Surf करोesn't have this.  IRQs are always on */
		अगर (type != BOARD_XSURF)
			z_ग_लिखोb(0, buddha_board+BUDDHA_IRQ_MR);

		prपूर्णांकk(KERN_INFO "ide: %s IDE controller\n",
				 buddha_board_name[type]);

		क्रम (i = 0; i < buddha_num_hwअगरs; i++) अणु
			अचिन्हित दीर्घ base, ctl, irq_port;

			अगर (type != BOARD_XSURF) अणु
				base = buddha_board + buddha_bases[i];
				ctl = base + BUDDHA_CONTROL;
				irq_port = buddha_board + buddha_irqports[i];
			पूर्ण अन्यथा अणु
				base = buddha_board + xsurf_bases[i];
				/* X-Surf has no CS1* (Control/AltStat) */
				ctl = 0;
				irq_port = buddha_board + xsurf_irqports[i];
			पूर्ण

			buddha_setup_ports(&hw[i], base, ctl, irq_port);

			hws[i] = &hw[i];
		पूर्ण

		ide_host_add(&d, hws, i, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

module_init(buddha_init);

MODULE_LICENSE("GPL");
