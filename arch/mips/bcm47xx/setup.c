<शैली गुरु>
/*
 *  Copyright (C) 2004 Florian Schirmer <jolt@tuxbox.org>
 *  Copyright (C) 2006 Felix Fietkau <nbd@खोलोwrt.org>
 *  Copyright (C) 2006 Michael Buesch <m@bues.ch>
 *  Copyright (C) 2010 Waldemar Brodkorb <wbx@खोलोadk.org>
 *  Copyright (C) 2010-2012 Hauke Mehrtens <hauke@hauke-m.de>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश "bcm47xx_private.h"

#समावेश <linux/bcm47xx_sprom.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_embedded.h>
#समावेश <linux/bcma/bcma_soc.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>
#समावेश <bcm47xx.h>
#समावेश <bcm47xx_board.h>

जोड़ bcm47xx_bus bcm47xx_bus;
EXPORT_SYMBOL(bcm47xx_bus);

क्रमागत bcm47xx_bus_type bcm47xx_bus_type;
EXPORT_SYMBOL(bcm47xx_bus_type);

अटल व्योम bcm47xx_machine_restart(अक्षर *command)
अणु
	pr_alert("Please stand by while rebooting the system...\n");
	local_irq_disable();
	/* Set the watchकरोg समयr to reset immediately */
	चयन (bcm47xx_bus_type) अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	हाल BCM47XX_BUS_TYPE_SSB:
		अगर (bcm47xx_bus.ssb.chip_id == 0x4785)
			ग_लिखो_c0_diag4(1 << 22);
		ssb_watchकरोg_समयr_set(&bcm47xx_bus.ssb, 1);
		अगर (bcm47xx_bus.ssb.chip_id == 0x4785) अणु
			__यंत्र__ __अस्थिर__(
				".set\tmips3\n\t"
				"sync\n\t"
				"wait\n\t"
				".set\tmips0");
		पूर्ण
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	हाल BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchकरोg_समयr_set(&bcm47xx_bus.bcma.bus.drv_cc, 1);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	जबतक (1)
		cpu_relax();
पूर्ण

अटल व्योम bcm47xx_machine_halt(व्योम)
अणु
	/* Disable पूर्णांकerrupts and watchकरोg and spin क्रमever */
	local_irq_disable();
	चयन (bcm47xx_bus_type) अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	हाल BCM47XX_BUS_TYPE_SSB:
		ssb_watchकरोg_समयr_set(&bcm47xx_bus.ssb, 0);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	हाल BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchकरोg_समयr_set(&bcm47xx_bus.bcma.bus.drv_cc, 0);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	जबतक (1)
		cpu_relax();
पूर्ण

#अगर_घोषित CONFIG_BCM47XX_SSB
अटल व्योम __init bcm47xx_रेजिस्टर_ssb(व्योम)
अणु
	पूर्णांक err;
	अक्षर buf[100];
	काष्ठा ssb_mipscore *mcore;

	err = ssb_bus_host_soc_रेजिस्टर(&bcm47xx_bus.ssb, SSB_ENUM_BASE);
	अगर (err)
		panic("Failed to initialize SSB bus (err %d)", err);

	mcore = &bcm47xx_bus.ssb.mipscore;
	अगर (bcm47xx_nvram_दो_पर्या("kernel_args", buf, माप(buf)) >= 0) अणु
		अगर (म_माला(buf, "console=ttyS1")) अणु
			काष्ठा ssb_serial_port port;

			pr_debug("Swapping serial ports!\n");
			/* swap serial ports */
			स_नकल(&port, &mcore->serial_ports[0], माप(port));
			स_नकल(&mcore->serial_ports[0], &mcore->serial_ports[1],
			       माप(port));
			स_नकल(&mcore->serial_ports[1], &port, माप(port));
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCM47XX_BCMA
अटल व्योम __init bcm47xx_रेजिस्टर_bcma(व्योम)
अणु
	पूर्णांक err;

	err = bcma_host_soc_रेजिस्टर(&bcm47xx_bus.bcma);
	अगर (err)
		panic("Failed to register BCMA bus (err %d)", err);
पूर्ण
#पूर्ण_अगर

/*
 * Memory setup is करोne in the early part of MIPS's arch_mem_init. It's supposed
 * to detect memory and record it with memblock_add.
 * Any extra initializaion perक्रमmed here must not use kदो_स्मृति or booपंचांगem.
 */
व्योम __init plat_mem_setup(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	अगर (c->cputype == CPU_74K) अणु
		pr_info("Using bcma bus\n");
#अगर_घोषित CONFIG_BCM47XX_BCMA
		bcm47xx_bus_type = BCM47XX_BUS_TYPE_BCMA;
		bcm47xx_रेजिस्टर_bcma();
		bcm47xx_set_प्रणाली_type(bcm47xx_bus.bcma.bus.chipinfo.id);
#अगर_घोषित CONFIG_HIGHMEM
		bcm47xx_prom_highmem_init();
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		pr_info("Using ssb bus\n");
#अगर_घोषित CONFIG_BCM47XX_SSB
		bcm47xx_bus_type = BCM47XX_BUS_TYPE_SSB;
		bcm47xx_sprom_रेजिस्टर_fallbacks();
		bcm47xx_रेजिस्टर_ssb();
		bcm47xx_set_प्रणाली_type(bcm47xx_bus.ssb.chip_id);
#पूर्ण_अगर
	पूर्ण

	_machine_restart = bcm47xx_machine_restart;
	_machine_halt = bcm47xx_machine_halt;
	pm_घातer_off = bcm47xx_machine_halt;
पूर्ण

#अगर_घोषित CONFIG_BCM47XX_BCMA
अटल काष्ठा device * __init bcm47xx_setup_device(व्योम)
अणु
	काष्ठा device *dev;
	पूर्णांक err;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	err = dev_set_name(dev, "bcm47xx_soc");
	अगर (err) अणु
		pr_err("Failed to set SoC device name: %d\n", err);
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	err = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (err)
		pr_err("Failed to set SoC DMA mask: %d\n", err);

	वापस dev;
पूर्ण
#पूर्ण_अगर

/*
 * This finishes bus initialization करोing things that were not possible without
 * kदो_स्मृति. Make sure to call it late enough (after mm_init).
 */
व्योम __init bcm47xx_bus_setup(व्योम)
अणु
#अगर_घोषित CONFIG_BCM47XX_BCMA
	अगर (bcm47xx_bus_type == BCM47XX_BUS_TYPE_BCMA) अणु
		पूर्णांक err;

		bcm47xx_bus.bcma.dev = bcm47xx_setup_device();
		अगर (!bcm47xx_bus.bcma.dev)
			panic("Failed to setup SoC device\n");

		err = bcma_host_soc_init(&bcm47xx_bus.bcma);
		अगर (err)
			panic("Failed to initialize BCMA bus (err %d)", err);
	पूर्ण
#पूर्ण_अगर

	/* With bus initialized we can access NVRAM and detect the board */
	bcm47xx_board_detect();
	mips_set_machine_name(bcm47xx_board_get_name());
पूर्ण

अटल पूर्णांक __init bcm47xx_cpu_fixes(व्योम)
अणु
	चयन (bcm47xx_bus_type) अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	हाल BCM47XX_BUS_TYPE_SSB:
		/* Nothing to करो */
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	हाल BCM47XX_BUS_TYPE_BCMA:
		/* The BCM4706 has a problem with the CPU रुको inकाष्ठाion.
		 * When r4k_रुको or r4k_रुको_irqoff is used will just hang and
		 * not वापस from a msleep(). Removing the cpu_रुको
		 * functionality is a workaround क्रम this problem. The BCM4716
		 * करोes not have this problem.
		 */
		अगर (bcm47xx_bus.bcma.bus.chipinfo.id == BCMA_CHIP_ID_BCM4706)
			cpu_रुको = शून्य;
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(bcm47xx_cpu_fixes);

अटल काष्ठा fixed_phy_status bcm47xx_fixed_phy_status __initdata = अणु
	.link	= 1,
	.speed	= SPEED_100,
	.duplex	= DUPLEX_FULL,
पूर्ण;

अटल पूर्णांक __init bcm47xx_रेजिस्टर_bus_complete(व्योम)
अणु
	चयन (bcm47xx_bus_type) अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	हाल BCM47XX_BUS_TYPE_SSB:
		/* Nothing to करो */
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	हाल BCM47XX_BUS_TYPE_BCMA:
		अगर (device_रेजिस्टर(bcm47xx_bus.bcma.dev))
			pr_err("Failed to register SoC device\n");
		bcma_bus_रेजिस्टर(&bcm47xx_bus.bcma.bus);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	bcm47xx_buttons_रेजिस्टर();
	bcm47xx_leds_रेजिस्टर();
	bcm47xx_workarounds();

	fixed_phy_add(PHY_POLL, 0, &bcm47xx_fixed_phy_status);
	वापस 0;
पूर्ण
device_initcall(bcm47xx_रेजिस्टर_bus_complete);
