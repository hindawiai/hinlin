<शैली गुरु>
/*
 * linux/arch/arm/mach-omap1/pm.c
 *
 * OMAP Power Management Routines
 *
 * Original code क्रम the SA11x0:
 * Copyright (c) 2001 Clअगरf Brake <cbrake@accelent.com>
 *
 * Modअगरied क्रम the PXA250 by Nicolas Pitre:
 * Copyright (c) 2002 Monta Vista Software, Inc.
 *
 * Modअगरied क्रम the OMAP1510 by David Singleton:
 * Copyright (c) 2002 Monta Vista Software, Inc.
 *
 * Cleanup 2004 क्रम OMAP1510/1610 by Dirk Behme <dirk.behme@de.bosch.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/suspend.h>
#समावेश <linux/sched.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/atomic.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/tc.h>
#समावेश <mach/mux.h>
#समावेश <linux/omap-dma.h>
#समावेश <घड़ीsource/समयr-ti-dm.h>

#समावेश <mach/irqs.h>

#समावेश "iomap.h"
#समावेश "clock.h"
#समावेश "pm.h"
#समावेश "soc.h"
#समावेश "sram.h"

अटल अचिन्हित पूर्णांक arm_sleep_save[ARM_SLEEP_SAVE_SIZE];
अटल अचिन्हित लघु dsp_sleep_save[DSP_SLEEP_SAVE_SIZE];
अटल अचिन्हित लघु ulpd_sleep_save[ULPD_SLEEP_SAVE_SIZE];
अटल अचिन्हित पूर्णांक mpui7xx_sleep_save[MPUI7XX_SLEEP_SAVE_SIZE];
अटल अचिन्हित पूर्णांक mpui1510_sleep_save[MPUI1510_SLEEP_SAVE_SIZE];
अटल अचिन्हित पूर्णांक mpui1610_sleep_save[MPUI1610_SLEEP_SAVE_SIZE];

अटल अचिन्हित लघु enable_dyn_sleep;

अटल sमाप_प्रकार idle_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%hu\n", enable_dyn_sleep);
पूर्ण

अटल sमाप_प्रकार idle_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  स्थिर अक्षर * buf, माप_प्रकार n)
अणु
	अचिन्हित लघु value;
	अगर (माला_पूछो(buf, "%hu", &value) != 1 ||
	    (value != 0 && value != 1) ||
	    (value != 0 && !IS_ENABLED(CONFIG_OMAP_32K_TIMER))) अणु
		pr_err("idle_sleep_store: Invalid value\n");
		वापस -EINVAL;
	पूर्ण
	enable_dyn_sleep = value;
	वापस n;
पूर्ण

अटल काष्ठा kobj_attribute sleep_जबतक_idle_attr =
	__ATTR(sleep_जबतक_idle, 0644, idle_show, idle_store);


अटल व्योम (*omap_sram_suspend)(अचिन्हित दीर्घ r0, अचिन्हित दीर्घ r1) = शून्य;

/*
 * Let's घातer करोwn on idle, but only अगर we are really
 * idle, because once we start करोwn the path of
 * going idle we जारी to करो idle even अगर we get
 * a घड़ी tick पूर्णांकerrupt . .
 */
व्योम omap1_pm_idle(व्योम)
अणु
	बाह्य __u32 arm_idlect1_mask;
	__u32 use_idlect1 = arm_idlect1_mask;

	local_fiq_disable();

#अगर defined(CONFIG_OMAP_MPU_TIMER) && !defined(CONFIG_OMAP_DM_TIMER)
	use_idlect1 = use_idlect1 & ~(1 << 9);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OMAP_DM_TIMER
	use_idlect1 = omap_dm_समयr_modअगरy_idlect_mask(use_idlect1);
#पूर्ण_अगर

	अगर (omap_dma_running())
		use_idlect1 &= ~(1 << 6);

	/*
	 * We should be able to हटाओ the करो_sleep variable and multiple
	 * tests above as soon as drivers, समयr and DMA code have been fixed.
	 * Even the sleep block count should become obsolete.
	 */
	अगर ((use_idlect1 != ~0) || !enable_dyn_sleep) अणु

		__u32 saved_idlect1 = omap_पढ़ोl(ARM_IDLECT1);
		अगर (cpu_is_omap15xx())
			use_idlect1 &= OMAP1510_BIG_SLEEP_REQUEST;
		अन्यथा
			use_idlect1 &= OMAP1610_IDLECT1_SLEEP_VAL;
		omap_ग_लिखोl(use_idlect1, ARM_IDLECT1);
		__यंत्र__ अस्थिर ("mcr	p15, 0, r0, c7, c0, 4");
		omap_ग_लिखोl(saved_idlect1, ARM_IDLECT1);

		local_fiq_enable();
		वापस;
	पूर्ण
	omap_sram_suspend(omap_पढ़ोl(ARM_IDLECT1),
			  omap_पढ़ोl(ARM_IDLECT2));

	local_fiq_enable();
पूर्ण

/*
 * Configuration of the wakeup event is board specअगरic. For the
 * moment we put it पूर्णांकo this helper function. Later it may move
 * to board specअगरic files.
 */
अटल व्योम omap_pm_wakeup_setup(व्योम)
अणु
	u32 level1_wake = 0;
	u32 level2_wake = OMAP_IRQ_BIT(INT_UART2);

	/*
	 * Turn off all पूर्णांकerrupts except GPIO bank 1, L1-2nd level cascade,
	 * and the L2 wakeup पूर्णांकerrupts: keypad and UART2. Note that the
	 * drivers must still separately call omap_set_gpio_wakeup() to
	 * wake up to a GPIO पूर्णांकerrupt.
	 */
	अगर (cpu_is_omap7xx())
		level1_wake = OMAP_IRQ_BIT(INT_7XX_GPIO_BANK1) |
			OMAP_IRQ_BIT(INT_7XX_IH2_IRQ);
	अन्यथा अगर (cpu_is_omap15xx())
		level1_wake = OMAP_IRQ_BIT(INT_GPIO_BANK1) |
			OMAP_IRQ_BIT(INT_1510_IH2_IRQ);
	अन्यथा अगर (cpu_is_omap16xx())
		level1_wake = OMAP_IRQ_BIT(INT_GPIO_BANK1) |
			OMAP_IRQ_BIT(INT_1610_IH2_IRQ);

	omap_ग_लिखोl(~level1_wake, OMAP_IH1_MIR);

	अगर (cpu_is_omap7xx()) अणु
		omap_ग_लिखोl(~level2_wake, OMAP_IH2_0_MIR);
		omap_ग_लिखोl(~(OMAP_IRQ_BIT(INT_7XX_WAKE_UP_REQ) |
				OMAP_IRQ_BIT(INT_7XX_MPUIO_KEYPAD)),
				OMAP_IH2_1_MIR);
	पूर्ण अन्यथा अगर (cpu_is_omap15xx()) अणु
		level2_wake |= OMAP_IRQ_BIT(INT_KEYBOARD);
		omap_ग_लिखोl(~level2_wake,  OMAP_IH2_MIR);
	पूर्ण अन्यथा अगर (cpu_is_omap16xx()) अणु
		level2_wake |= OMAP_IRQ_BIT(INT_KEYBOARD);
		omap_ग_लिखोl(~level2_wake, OMAP_IH2_0_MIR);

		/* INT_1610_WAKE_UP_REQ is needed क्रम GPIO wakeup... */
		omap_ग_लिखोl(~OMAP_IRQ_BIT(INT_1610_WAKE_UP_REQ),
			    OMAP_IH2_1_MIR);
		omap_ग_लिखोl(~0x0, OMAP_IH2_2_MIR);
		omap_ग_लिखोl(~0x0, OMAP_IH2_3_MIR);
	पूर्ण

	/*  New IRQ agreement, recalculate in cascade order */
	omap_ग_लिखोl(1, OMAP_IH2_CONTROL);
	omap_ग_लिखोl(1, OMAP_IH1_CONTROL);
पूर्ण

#घोषणा EN_DSPCK	13	/* ARM_CKCTL */
#घोषणा EN_APICK	6	/* ARM_IDLECT2 */
#घोषणा DSP_EN		1	/* ARM_RSTCT1 */

व्योम omap1_pm_suspend(व्योम)
अणु
	अचिन्हित दीर्घ arg0 = 0, arg1 = 0;

	prपूर्णांकk(KERN_INFO "PM: OMAP%x is trying to enter deep sleep...\n",
		omap_rev());

	omap_serial_wake_trigger(1);

	अगर (!cpu_is_omap15xx())
		omap_ग_लिखोw(0xffff, ULPD_SOFT_DISABLE_REQ_REG);

	/*
	 * Step 1: turn off पूर्णांकerrupts (FIXME: NOTE: alपढ़ोy disabled)
	 */

	local_irq_disable();
	local_fiq_disable();

	/*
	 * Step 2: save रेजिस्टरs
	 *
	 * The omap is a strange/beautअगरul device. The caches, memory
	 * and रेजिस्टर state are preserved across घातer saves.
	 * We have to save and restore very little रेजिस्टर state to
	 * idle the omap.
         *
	 * Save पूर्णांकerrupt, MPUI, ARM and UPLD control रेजिस्टरs.
	 */

	अगर (cpu_is_omap7xx()) अणु
		MPUI7XX_SAVE(OMAP_IH1_MIR);
		MPUI7XX_SAVE(OMAP_IH2_0_MIR);
		MPUI7XX_SAVE(OMAP_IH2_1_MIR);
		MPUI7XX_SAVE(MPUI_CTRL);
		MPUI7XX_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI7XX_SAVE(MPUI_DSP_API_CONFIG);
		MPUI7XX_SAVE(EMIFS_CONFIG);
		MPUI7XX_SAVE(EMIFF_SDRAM_CONFIG);

	पूर्ण अन्यथा अगर (cpu_is_omap15xx()) अणु
		MPUI1510_SAVE(OMAP_IH1_MIR);
		MPUI1510_SAVE(OMAP_IH2_MIR);
		MPUI1510_SAVE(MPUI_CTRL);
		MPUI1510_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1510_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1510_SAVE(EMIFS_CONFIG);
		MPUI1510_SAVE(EMIFF_SDRAM_CONFIG);
	पूर्ण अन्यथा अगर (cpu_is_omap16xx()) अणु
		MPUI1610_SAVE(OMAP_IH1_MIR);
		MPUI1610_SAVE(OMAP_IH2_0_MIR);
		MPUI1610_SAVE(OMAP_IH2_1_MIR);
		MPUI1610_SAVE(OMAP_IH2_2_MIR);
		MPUI1610_SAVE(OMAP_IH2_3_MIR);
		MPUI1610_SAVE(MPUI_CTRL);
		MPUI1610_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1610_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1610_SAVE(EMIFS_CONFIG);
		MPUI1610_SAVE(EMIFF_SDRAM_CONFIG);
	पूर्ण

	ARM_SAVE(ARM_CKCTL);
	ARM_SAVE(ARM_IDLECT1);
	ARM_SAVE(ARM_IDLECT2);
	अगर (!(cpu_is_omap15xx()))
		ARM_SAVE(ARM_IDLECT3);
	ARM_SAVE(ARM_EWUPCT);
	ARM_SAVE(ARM_RSTCT1);
	ARM_SAVE(ARM_RSTCT2);
	ARM_SAVE(ARM_SYSST);
	ULPD_SAVE(ULPD_CLOCK_CTRL);
	ULPD_SAVE(ULPD_STATUS_REQ);

	/* (Step 3 हटाओd - we now allow deep sleep by शेष) */

	/*
	 * Step 4: OMAP DSP Shutकरोwn
	 */

	/* stop DSP */
	omap_ग_लिखोw(omap_पढ़ोw(ARM_RSTCT1) & ~(1 << DSP_EN), ARM_RSTCT1);

		/* shut करोwn dsp_ck */
	अगर (!cpu_is_omap7xx())
		omap_ग_लिखोw(omap_पढ़ोw(ARM_CKCTL) & ~(1 << EN_DSPCK), ARM_CKCTL);

	/* temporarily enabling api_ck to access DSP रेजिस्टरs */
	omap_ग_लिखोw(omap_पढ़ोw(ARM_IDLECT2) | 1 << EN_APICK, ARM_IDLECT2);

	/* save DSP रेजिस्टरs */
	DSP_SAVE(DSP_IDLECT2);

	/* Stop all DSP करोमुख्य घड़ीs */
	__raw_ग_लिखोw(0, DSP_IDLECT2);

	/*
	 * Step 5: Wakeup Event Setup
	 */

	omap_pm_wakeup_setup();

	/*
	 * Step 6: ARM and Traffic controller shutकरोwn
	 */

	/* disable ARM watchकरोg */
	omap_ग_लिखोl(0x00F5, OMAP_WDT_TIMER_MODE);
	omap_ग_लिखोl(0x00A0, OMAP_WDT_TIMER_MODE);

	/*
	 * Step 6b: ARM and Traffic controller shutकरोwn
	 *
	 * Step 6 जारीs here. Prepare jump to घातer management
	 * assembly code in पूर्णांकernal SRAM.
	 *
	 * Since the omap_cpu_suspend routine has been copied to
	 * SRAM, we'll करो an indirect procedure call to it and pass the
	 * contents of arm_idlect1 and arm_idlect2 so it can restore
	 * them when it wakes up and it will वापस.
	 */

	arg0 = arm_sleep_save[ARM_SLEEP_SAVE_ARM_IDLECT1];
	arg1 = arm_sleep_save[ARM_SLEEP_SAVE_ARM_IDLECT2];

	/*
	 * Step 6c: ARM and Traffic controller shutकरोwn
	 *
	 * Jump to assembly code. The processor will stay there
	 * until wake up.
	 */
	omap_sram_suspend(arg0, arg1);

	/*
	 * If we are here, processor is woken up!
	 */

	/*
	 * Restore DSP घड़ीs
	 */

	/* again temporarily enabling api_ck to access DSP रेजिस्टरs */
	omap_ग_लिखोw(omap_पढ़ोw(ARM_IDLECT2) | 1 << EN_APICK, ARM_IDLECT2);

	/* Restore DSP करोमुख्य घड़ीs */
	DSP_RESTORE(DSP_IDLECT2);

	/*
	 * Restore ARM state, except ARM_IDLECT1/2 which omap_cpu_suspend did
	 */

	अगर (!(cpu_is_omap15xx()))
		ARM_RESTORE(ARM_IDLECT3);
	ARM_RESTORE(ARM_CKCTL);
	ARM_RESTORE(ARM_EWUPCT);
	ARM_RESTORE(ARM_RSTCT1);
	ARM_RESTORE(ARM_RSTCT2);
	ARM_RESTORE(ARM_SYSST);
	ULPD_RESTORE(ULPD_CLOCK_CTRL);
	ULPD_RESTORE(ULPD_STATUS_REQ);

	अगर (cpu_is_omap7xx()) अणु
		MPUI7XX_RESTORE(EMIFS_CONFIG);
		MPUI7XX_RESTORE(EMIFF_SDRAM_CONFIG);
		MPUI7XX_RESTORE(OMAP_IH1_MIR);
		MPUI7XX_RESTORE(OMAP_IH2_0_MIR);
		MPUI7XX_RESTORE(OMAP_IH2_1_MIR);
	पूर्ण अन्यथा अगर (cpu_is_omap15xx()) अणु
		MPUI1510_RESTORE(MPUI_CTRL);
		MPUI1510_RESTORE(MPUI_DSP_BOOT_CONFIG);
		MPUI1510_RESTORE(MPUI_DSP_API_CONFIG);
		MPUI1510_RESTORE(EMIFS_CONFIG);
		MPUI1510_RESTORE(EMIFF_SDRAM_CONFIG);
		MPUI1510_RESTORE(OMAP_IH1_MIR);
		MPUI1510_RESTORE(OMAP_IH2_MIR);
	पूर्ण अन्यथा अगर (cpu_is_omap16xx()) अणु
		MPUI1610_RESTORE(MPUI_CTRL);
		MPUI1610_RESTORE(MPUI_DSP_BOOT_CONFIG);
		MPUI1610_RESTORE(MPUI_DSP_API_CONFIG);
		MPUI1610_RESTORE(EMIFS_CONFIG);
		MPUI1610_RESTORE(EMIFF_SDRAM_CONFIG);

		MPUI1610_RESTORE(OMAP_IH1_MIR);
		MPUI1610_RESTORE(OMAP_IH2_0_MIR);
		MPUI1610_RESTORE(OMAP_IH2_1_MIR);
		MPUI1610_RESTORE(OMAP_IH2_2_MIR);
		MPUI1610_RESTORE(OMAP_IH2_3_MIR);
	पूर्ण

	अगर (!cpu_is_omap15xx())
		omap_ग_लिखोw(0, ULPD_SOFT_DISABLE_REQ_REG);

	/*
	 * Re-enable पूर्णांकerrupts
	 */

	local_irq_enable();
	local_fiq_enable();

	omap_serial_wake_trigger(0);

	prपूर्णांकk(KERN_INFO "PM: OMAP%x is re-starting from deep sleep...\n",
		omap_rev());
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
/*
 * Read प्रणाली PM रेजिस्टरs क्रम debugging
 */
अटल पूर्णांक omap_pm_debug_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ARM_SAVE(ARM_CKCTL);
	ARM_SAVE(ARM_IDLECT1);
	ARM_SAVE(ARM_IDLECT2);
	अगर (!(cpu_is_omap15xx()))
		ARM_SAVE(ARM_IDLECT3);
	ARM_SAVE(ARM_EWUPCT);
	ARM_SAVE(ARM_RSTCT1);
	ARM_SAVE(ARM_RSTCT2);
	ARM_SAVE(ARM_SYSST);

	ULPD_SAVE(ULPD_IT_STATUS);
	ULPD_SAVE(ULPD_CLOCK_CTRL);
	ULPD_SAVE(ULPD_SOFT_REQ);
	ULPD_SAVE(ULPD_STATUS_REQ);
	ULPD_SAVE(ULPD_DPLL_CTRL);
	ULPD_SAVE(ULPD_POWER_CTRL);

	अगर (cpu_is_omap7xx()) अणु
		MPUI7XX_SAVE(MPUI_CTRL);
		MPUI7XX_SAVE(MPUI_DSP_STATUS);
		MPUI7XX_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI7XX_SAVE(MPUI_DSP_API_CONFIG);
		MPUI7XX_SAVE(EMIFF_SDRAM_CONFIG);
		MPUI7XX_SAVE(EMIFS_CONFIG);
	पूर्ण अन्यथा अगर (cpu_is_omap15xx()) अणु
		MPUI1510_SAVE(MPUI_CTRL);
		MPUI1510_SAVE(MPUI_DSP_STATUS);
		MPUI1510_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1510_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1510_SAVE(EMIFF_SDRAM_CONFIG);
		MPUI1510_SAVE(EMIFS_CONFIG);
	पूर्ण अन्यथा अगर (cpu_is_omap16xx()) अणु
		MPUI1610_SAVE(MPUI_CTRL);
		MPUI1610_SAVE(MPUI_DSP_STATUS);
		MPUI1610_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1610_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1610_SAVE(EMIFF_SDRAM_CONFIG);
		MPUI1610_SAVE(EMIFS_CONFIG);
	पूर्ण

	seq_म_लिखो(m,
		   "ARM_CKCTL_REG:            0x%-8x     \n"
		   "ARM_IDLECT1_REG:          0x%-8x     \n"
		   "ARM_IDLECT2_REG:          0x%-8x     \n"
		   "ARM_IDLECT3_REG:	      0x%-8x     \n"
		   "ARM_EWUPCT_REG:           0x%-8x     \n"
		   "ARM_RSTCT1_REG:           0x%-8x     \n"
		   "ARM_RSTCT2_REG:           0x%-8x     \n"
		   "ARM_SYSST_REG:            0x%-8x     \n"
		   "ULPD_IT_STATUS_REG:       0x%-4x     \n"
		   "ULPD_CLOCK_CTRL_REG:      0x%-4x     \n"
		   "ULPD_SOFT_REQ_REG:        0x%-4x     \n"
		   "ULPD_DPLL_CTRL_REG:       0x%-4x     \n"
		   "ULPD_STATUS_REQ_REG:      0x%-4x     \n"
		   "ULPD_POWER_CTRL_REG:      0x%-4x     \n",
		   ARM_SHOW(ARM_CKCTL),
		   ARM_SHOW(ARM_IDLECT1),
		   ARM_SHOW(ARM_IDLECT2),
		   ARM_SHOW(ARM_IDLECT3),
		   ARM_SHOW(ARM_EWUPCT),
		   ARM_SHOW(ARM_RSTCT1),
		   ARM_SHOW(ARM_RSTCT2),
		   ARM_SHOW(ARM_SYSST),
		   ULPD_SHOW(ULPD_IT_STATUS),
		   ULPD_SHOW(ULPD_CLOCK_CTRL),
		   ULPD_SHOW(ULPD_SOFT_REQ),
		   ULPD_SHOW(ULPD_DPLL_CTRL),
		   ULPD_SHOW(ULPD_STATUS_REQ),
		   ULPD_SHOW(ULPD_POWER_CTRL));

	अगर (cpu_is_omap7xx()) अणु
		seq_म_लिखो(m,
			   "MPUI7XX_CTRL_REG	     0x%-8x \n"
			   "MPUI7XX_DSP_STATUS_REG:      0x%-8x \n"
			   "MPUI7XX_DSP_BOOT_CONFIG_REG: 0x%-8x \n"
			   "MPUI7XX_DSP_API_CONFIG_REG:  0x%-8x \n"
			   "MPUI7XX_SDRAM_CONFIG_REG:    0x%-8x \n"
			   "MPUI7XX_EMIFS_CONFIG_REG:    0x%-8x \n",
			   MPUI7XX_SHOW(MPUI_CTRL),
			   MPUI7XX_SHOW(MPUI_DSP_STATUS),
			   MPUI7XX_SHOW(MPUI_DSP_BOOT_CONFIG),
			   MPUI7XX_SHOW(MPUI_DSP_API_CONFIG),
			   MPUI7XX_SHOW(EMIFF_SDRAM_CONFIG),
			   MPUI7XX_SHOW(EMIFS_CONFIG));
	पूर्ण अन्यथा अगर (cpu_is_omap15xx()) अणु
		seq_म_लिखो(m,
			   "MPUI1510_CTRL_REG             0x%-8x \n"
			   "MPUI1510_DSP_STATUS_REG:      0x%-8x \n"
			   "MPUI1510_DSP_BOOT_CONFIG_REG: 0x%-8x \n"
			   "MPUI1510_DSP_API_CONFIG_REG:  0x%-8x \n"
			   "MPUI1510_SDRAM_CONFIG_REG:    0x%-8x \n"
			   "MPUI1510_EMIFS_CONFIG_REG:    0x%-8x \n",
			   MPUI1510_SHOW(MPUI_CTRL),
			   MPUI1510_SHOW(MPUI_DSP_STATUS),
			   MPUI1510_SHOW(MPUI_DSP_BOOT_CONFIG),
			   MPUI1510_SHOW(MPUI_DSP_API_CONFIG),
			   MPUI1510_SHOW(EMIFF_SDRAM_CONFIG),
			   MPUI1510_SHOW(EMIFS_CONFIG));
	पूर्ण अन्यथा अगर (cpu_is_omap16xx()) अणु
		seq_म_लिखो(m,
			   "MPUI1610_CTRL_REG             0x%-8x \n"
			   "MPUI1610_DSP_STATUS_REG:      0x%-8x \n"
			   "MPUI1610_DSP_BOOT_CONFIG_REG: 0x%-8x \n"
			   "MPUI1610_DSP_API_CONFIG_REG:  0x%-8x \n"
			   "MPUI1610_SDRAM_CONFIG_REG:    0x%-8x \n"
			   "MPUI1610_EMIFS_CONFIG_REG:    0x%-8x \n",
			   MPUI1610_SHOW(MPUI_CTRL),
			   MPUI1610_SHOW(MPUI_DSP_STATUS),
			   MPUI1610_SHOW(MPUI_DSP_BOOT_CONFIG),
			   MPUI1610_SHOW(MPUI_DSP_API_CONFIG),
			   MPUI1610_SHOW(EMIFF_SDRAM_CONFIG),
			   MPUI1610_SHOW(EMIFS_CONFIG));
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(omap_pm_debug);

अटल व्योम omap_pm_init_debugfs(व्योम)
अणु
	काष्ठा dentry *d;

	d = debugfs_create_dir("pm_debug", शून्य);
	debugfs_create_file("omap_pm", S_IWUSR | S_IRUGO, d, शून्य,
			    &omap_pm_debug_fops);
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/*
 *	omap_pm_prepare - Do preliminary suspend work.
 *
 */
अटल पूर्णांक omap_pm_prepare(व्योम)
अणु
	/* We cannot sleep in idle until we have resumed */
	cpu_idle_poll_ctrl(true);
	वापस 0;
पूर्ण


/*
 *	omap_pm_enter - Actually enter a sleep state.
 *	@state:		State we're entering.
 *
 */

अटल पूर्णांक omap_pm_enter(suspend_state_t state)
अणु
	चयन (state)
	अणु
	हाल PM_SUSPEND_MEM:
		omap1_pm_suspend();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


/**
 *	omap_pm_finish - Finish up suspend sequence.
 *
 *	This is called after we wake back up (or अगर entering the sleep state
 *	failed).
 */

अटल व्योम omap_pm_finish(व्योम)
अणु
	cpu_idle_poll_ctrl(false);
पूर्ण


अटल irqवापस_t omap_wakeup_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	वापस IRQ_HANDLED;
पूर्ण



अटल स्थिर काष्ठा platक्रमm_suspend_ops omap_pm_ops = अणु
	.prepare	= omap_pm_prepare,
	.enter		= omap_pm_enter,
	.finish		= omap_pm_finish,
	.valid		= suspend_valid_only_mem,
पूर्ण;

अटल पूर्णांक __init omap_pm_init(व्योम)
अणु
	पूर्णांक error = 0;
	पूर्णांक irq;

	अगर (!cpu_class_is_omap1())
		वापस -ENODEV;

	pr_info("Power Management for TI OMAP.\n");

	अगर (!IS_ENABLED(CONFIG_OMAP_32K_TIMER))
		pr_info("OMAP1 PM: sleep states in idle disabled due to no 32KiHz timer\n");

	अगर (!IS_ENABLED(CONFIG_OMAP_DM_TIMER))
		pr_info("OMAP1 PM: sleep states in idle disabled due to no DMTIMER support\n");

	अगर (IS_ENABLED(CONFIG_OMAP_32K_TIMER) &&
	    IS_ENABLED(CONFIG_OMAP_DM_TIMER)) अणु
		/* OMAP16xx only */
		pr_info("OMAP1 PM: sleep states in idle enabled\n");
		enable_dyn_sleep = 1;
	पूर्ण

	/*
	 * We copy the assembler sleep/wakeup routines to SRAM.
	 * These routines need to be in SRAM as that's the only
	 * memory the MPU can see when it wakes up.
	 */
	अगर (cpu_is_omap7xx()) अणु
		omap_sram_suspend = omap_sram_push(omap7xx_cpu_suspend,
						   omap7xx_cpu_suspend_sz);
	पूर्ण अन्यथा अगर (cpu_is_omap15xx()) अणु
		omap_sram_suspend = omap_sram_push(omap1510_cpu_suspend,
						   omap1510_cpu_suspend_sz);
	पूर्ण अन्यथा अगर (cpu_is_omap16xx()) अणु
		omap_sram_suspend = omap_sram_push(omap1610_cpu_suspend,
						   omap1610_cpu_suspend_sz);
	पूर्ण

	अगर (omap_sram_suspend == शून्य) अणु
		prपूर्णांकk(KERN_ERR "PM not initialized: Missing SRAM support\n");
		वापस -ENODEV;
	पूर्ण

	arm_pm_idle = omap1_pm_idle;

	अगर (cpu_is_omap7xx())
		irq = INT_7XX_WAKE_UP_REQ;
	अन्यथा अगर (cpu_is_omap16xx())
		irq = INT_1610_WAKE_UP_REQ;
	अन्यथा
		irq = -1;

	अगर (irq >= 0) अणु
		अगर (request_irq(irq, omap_wakeup_पूर्णांकerrupt, 0, "peripheral wakeup", शून्य))
			pr_err("Failed to request irq %d (peripheral wakeup)\n", irq);
	पूर्ण

	/* Program new घातer ramp-up समय
	 * (0 क्रम most boards since we करोn't lower voltage when in deep sleep)
	 */
	omap_ग_लिखोw(ULPD_SETUP_ANALOG_CELL_3_VAL, ULPD_SETUP_ANALOG_CELL_3);

	/* Setup ULPD POWER_CTRL_REG - enter deep sleep whenever possible */
	omap_ग_लिखोw(ULPD_POWER_CTRL_REG_VAL, ULPD_POWER_CTRL);

	/* Configure IDLECT3 */
	अगर (cpu_is_omap7xx())
		omap_ग_लिखोl(OMAP7XX_IDLECT3_VAL, OMAP7XX_IDLECT3);
	अन्यथा अगर (cpu_is_omap16xx())
		omap_ग_लिखोl(OMAP1610_IDLECT3_VAL, OMAP1610_IDLECT3);

	suspend_set_ops(&omap_pm_ops);

#अगर_घोषित CONFIG_DEBUG_FS
	omap_pm_init_debugfs();
#पूर्ण_अगर

	error = sysfs_create_file(घातer_kobj, &sleep_जबतक_idle_attr.attr);
	अगर (error)
		prपूर्णांकk(KERN_ERR "sysfs_create_file failed: %d\n", error);

	अगर (cpu_is_omap16xx()) अणु
		/* configure LOW_PWR pin */
		omap_cfg_reg(T20_1610_LOW_PWR);
	पूर्ण

	वापस error;
पूर्ण
__initcall(omap_pm_init);
