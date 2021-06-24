<शैली गुरु>
/*
 * BRIEF MODULE DESCRIPTION
 *	Au1xx0 Power Management routines.
 *
 * Copyright 2001, 2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 *
 *  Some of the routines are right out of init/मुख्य.c, whose
 *  copyrights apply here.
 *
 *  This program is मुक्त software; you can redistribute	 it and/or modअगरy it
 *  under  the terms of	 the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the	License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED	  ``AS	IS'' AND   ANY	EXPRESS OR IMPLIED
 *  WARRANTIES,	  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO	EVENT  SHALL   THE AUTHOR  BE	 LIABLE FOR ANY	  सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED	  TO, PROCUREMENT OF  SUBSTITUTE GOODS	OR SERVICES; LOSS OF
 *  USE, DATA,	OR PROFITS; OR	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN	 CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/pm.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>

/*
 * We need to save/restore a bunch of core रेजिस्टरs that are
 * either अस्थिर or reset to some state across a processor sleep.
 * If पढ़ोing a रेजिस्टर करोesn't provide a proper result क्रम a
 * later restore, we have to provide a function क्रम loading that
 * रेजिस्टर and save a copy.
 *
 * We only have to save/restore रेजिस्टरs that aren't otherwise
 * करोne as part of a driver pm_* function.
 */
अटल अचिन्हित पूर्णांक sleep_sys_घड़ीs[5];
अटल अचिन्हित पूर्णांक sleep_sys_pinfunc;
अटल अचिन्हित पूर्णांक sleep_अटल_memctlr[4][3];


अटल व्योम save_core_regs(व्योम)
अणु
	/* Clocks and PLLs. */
	sleep_sys_घड़ीs[0] = alchemy_rdsys(AU1000_SYS_FREQCTRL0);
	sleep_sys_घड़ीs[1] = alchemy_rdsys(AU1000_SYS_FREQCTRL1);
	sleep_sys_घड़ीs[2] = alchemy_rdsys(AU1000_SYS_CLKSRC);
	sleep_sys_घड़ीs[3] = alchemy_rdsys(AU1000_SYS_CPUPLL);
	sleep_sys_घड़ीs[4] = alchemy_rdsys(AU1000_SYS_AUXPLL);

	/* pin mux config */
	sleep_sys_pinfunc = alchemy_rdsys(AU1000_SYS_PINFUNC);

	/* Save the अटल memory controller configuration. */
	sleep_अटल_memctlr[0][0] = alchemy_rdsmem(AU1000_MEM_STCFG0);
	sleep_अटल_memctlr[0][1] = alchemy_rdsmem(AU1000_MEM_STTIME0);
	sleep_अटल_memctlr[0][2] = alchemy_rdsmem(AU1000_MEM_STADDR0);
	sleep_अटल_memctlr[1][0] = alchemy_rdsmem(AU1000_MEM_STCFG1);
	sleep_अटल_memctlr[1][1] = alchemy_rdsmem(AU1000_MEM_STTIME1);
	sleep_अटल_memctlr[1][2] = alchemy_rdsmem(AU1000_MEM_STADDR1);
	sleep_अटल_memctlr[2][0] = alchemy_rdsmem(AU1000_MEM_STCFG2);
	sleep_अटल_memctlr[2][1] = alchemy_rdsmem(AU1000_MEM_STTIME2);
	sleep_अटल_memctlr[2][2] = alchemy_rdsmem(AU1000_MEM_STADDR2);
	sleep_अटल_memctlr[3][0] = alchemy_rdsmem(AU1000_MEM_STCFG3);
	sleep_अटल_memctlr[3][1] = alchemy_rdsmem(AU1000_MEM_STTIME3);
	sleep_अटल_memctlr[3][2] = alchemy_rdsmem(AU1000_MEM_STADDR3);
पूर्ण

अटल व्योम restore_core_regs(व्योम)
अणु
	/* restore घड़ी configuration.  Writing CPUPLL last will
	 * stall a bit and stabilize other घड़ीs (unless this is
	 * one of those Au1000 with a ग_लिखो-only PLL, where we करोnt
	 * have a valid value)
	 */
	alchemy_wrsys(sleep_sys_घड़ीs[0], AU1000_SYS_FREQCTRL0);
	alchemy_wrsys(sleep_sys_घड़ीs[1], AU1000_SYS_FREQCTRL1);
	alchemy_wrsys(sleep_sys_घड़ीs[2], AU1000_SYS_CLKSRC);
	alchemy_wrsys(sleep_sys_घड़ीs[4], AU1000_SYS_AUXPLL);
	अगर (!au1xxx_cpu_has_pll_wo())
		alchemy_wrsys(sleep_sys_घड़ीs[3], AU1000_SYS_CPUPLL);

	alchemy_wrsys(sleep_sys_pinfunc, AU1000_SYS_PINFUNC);

	/* Restore the अटल memory controller configuration. */
	alchemy_wrsmem(sleep_अटल_memctlr[0][0], AU1000_MEM_STCFG0);
	alchemy_wrsmem(sleep_अटल_memctlr[0][1], AU1000_MEM_STTIME0);
	alchemy_wrsmem(sleep_अटल_memctlr[0][2], AU1000_MEM_STADDR0);
	alchemy_wrsmem(sleep_अटल_memctlr[1][0], AU1000_MEM_STCFG1);
	alchemy_wrsmem(sleep_अटल_memctlr[1][1], AU1000_MEM_STTIME1);
	alchemy_wrsmem(sleep_अटल_memctlr[1][2], AU1000_MEM_STADDR1);
	alchemy_wrsmem(sleep_अटल_memctlr[2][0], AU1000_MEM_STCFG2);
	alchemy_wrsmem(sleep_अटल_memctlr[2][1], AU1000_MEM_STTIME2);
	alchemy_wrsmem(sleep_अटल_memctlr[2][2], AU1000_MEM_STADDR2);
	alchemy_wrsmem(sleep_अटल_memctlr[3][0], AU1000_MEM_STCFG3);
	alchemy_wrsmem(sleep_अटल_memctlr[3][1], AU1000_MEM_STTIME3);
	alchemy_wrsmem(sleep_अटल_memctlr[3][2], AU1000_MEM_STADDR3);
पूर्ण

व्योम au_sleep(व्योम)
अणु
	save_core_regs();

	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1100:
		alchemy_sleep_au1000();
		अवरोध;
	हाल ALCHEMY_CPU_AU1550:
	हाल ALCHEMY_CPU_AU1200:
		alchemy_sleep_au1550();
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		alchemy_sleep_au1300();
		अवरोध;
	पूर्ण

	restore_core_regs();
पूर्ण
