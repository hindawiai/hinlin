<शैली गुरु>
/*
 *  Copyright (C) 2004 Florian Schirmer <jolt@tuxbox.org>
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

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <bcm47xx.h>

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	u32 cause;

	cause = पढ़ो_c0_cause() & पढ़ो_c0_status() & CAUSEF_IP;

	clear_c0_status(cause);

	अगर (cause & CAUSEF_IP7)
		करो_IRQ(7);
	अगर (cause & CAUSEF_IP2)
		करो_IRQ(2);
	अगर (cause & CAUSEF_IP3)
		करो_IRQ(3);
	अगर (cause & CAUSEF_IP4)
		करो_IRQ(4);
	अगर (cause & CAUSEF_IP5)
		करो_IRQ(5);
	अगर (cause & CAUSEF_IP6)
		करो_IRQ(6);
पूर्ण

#घोषणा DEFINE_HWx_IRQDISPATCH(x)					\
	अटल व्योम bcm47xx_hw ## x ## _irqdispatch(व्योम)		\
	अणु								\
		करो_IRQ(x);						\
	पूर्ण
DEFINE_HWx_IRQDISPATCH(2)
DEFINE_HWx_IRQDISPATCH(3)
DEFINE_HWx_IRQDISPATCH(4)
DEFINE_HWx_IRQDISPATCH(5)
DEFINE_HWx_IRQDISPATCH(6)
DEFINE_HWx_IRQDISPATCH(7)

व्योम __init arch_init_irq(व्योम)
अणु
	/*
	 * This is the first arch callback after mm_init (we can use kदो_स्मृति),
	 * so let's finish bus initialization now.
	 */
	bcm47xx_bus_setup();

#अगर_घोषित CONFIG_BCM47XX_BCMA
	अगर (bcm47xx_bus_type == BCM47XX_BUS_TYPE_BCMA) अणु
		bcma_ग_लिखो32(bcm47xx_bus.bcma.bus.drv_mips.core,
			     BCMA_MIPS_MIPS74K_INTMASK(5), 1 << 31);
		/*
		 * the kernel पढ़ोs the समयr irq from some रेजिस्टर and thinks
		 * it's #5, but we offset it by 2 and route to #7
		 */
		cp0_compare_irq = 7;
	पूर्ण
#पूर्ण_अगर
	mips_cpu_irq_init();

	अगर (cpu_has_vपूर्णांक) अणु
		pr_info("Setting up vectored interrupts\n");
		set_vi_handler(2, bcm47xx_hw2_irqdispatch);
		set_vi_handler(3, bcm47xx_hw3_irqdispatch);
		set_vi_handler(4, bcm47xx_hw4_irqdispatch);
		set_vi_handler(5, bcm47xx_hw5_irqdispatch);
		set_vi_handler(6, bcm47xx_hw6_irqdispatch);
		set_vi_handler(7, bcm47xx_hw7_irqdispatch);
	पूर्ण
पूर्ण
