<शैली गुरु>
/*
 * Header क्रम code common to all OMAP2+ machines.
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
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2PLUS_COMMON_H
#घोषणा __ARCH_ARM_MACH_OMAP2PLUS_COMMON_H
#अगर_अघोषित __ASSEMBLER__

#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/platक्रमm_data/i2c-omap.h>
#समावेश <linux/reboot.h>
#समावेश <linux/irqchip/irq-omap-पूर्णांकc.h>

#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "i2c.h"
#समावेश "serial.h"

#समावेश "usb.h"

#घोषणा OMAP_INTC_START		NR_IRQS

बाह्य पूर्णांक (*omap_pm_soc_init)(व्योम);
पूर्णांक omap_pm_nop_init(व्योम);

#अगर defined(CONFIG_PM) && defined(CONFIG_ARCH_OMAP2)
पूर्णांक omap2_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap2_pm_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PM) && defined(CONFIG_ARCH_OMAP3)
पूर्णांक omap3_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap3_pm_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PM) && (defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || defined(CONFIG_SOC_DRA7XX))
पूर्णांक omap4_pm_init(व्योम);
पूर्णांक omap4_pm_init_early(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap4_pm_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक omap4_pm_init_early(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PM) && (defined(CONFIG_SOC_AM33XX) || \
	defined(CONFIG_SOC_AM43XX))
पूर्णांक amx3_common_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक amx3_common_pm_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम omap2_init_common_infraकाष्ठाure(व्योम);

बाह्य व्योम omap_init_समय(व्योम);
बाह्य व्योम omap3_secure_sync32k_समयr_init(व्योम);
बाह्य व्योम omap3_gpसमयr_समयr_init(व्योम);
बाह्य व्योम omap4_local_समयr_init(व्योम);
#अगर_घोषित CONFIG_CACHE_L2X0
पूर्णांक omap_l2_cache_init(व्योम);
#घोषणा OMAP_L2C_AUX_CTRL	(L2C_AUX_CTRL_SHARED_OVERRIDE | \
				 L310_AUX_CTRL_DATA_PREFETCH | \
				 L310_AUX_CTRL_INSTR_PREFETCH)
व्योम omap4_l2c310_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित reg);
#अन्यथा
अटल अंतरभूत पूर्णांक omap_l2_cache_init(व्योम)
अणु
	वापस 0;
पूर्ण

#घोषणा OMAP_L2C_AUX_CTRL	0
#घोषणा omap4_l2c310_ग_लिखो_sec	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_HAS_REALTIME_COUNTER
बाह्य व्योम omap5_realसमय_प्रकारimer_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap5_realसमय_प्रकारimer_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

व्योम omap2420_init_early(व्योम);
व्योम omap2430_init_early(व्योम);
व्योम omap3430_init_early(व्योम);
व्योम omap35xx_init_early(व्योम);
व्योम omap3630_init_early(व्योम);
व्योम omap3_init_early(व्योम);	/* Do not use this one */
व्योम am33xx_init_early(व्योम);
व्योम am35xx_init_early(व्योम);
व्योम ti814x_init_early(व्योम);
व्योम ti816x_init_early(व्योम);
व्योम am33xx_init_early(व्योम);
व्योम am43xx_init_early(व्योम);
व्योम am43xx_init_late(व्योम);
व्योम omap4430_init_early(व्योम);
व्योम omap5_init_early(व्योम);
व्योम omap3_init_late(व्योम);
व्योम omap4430_init_late(व्योम);
व्योम omap2420_init_late(व्योम);
व्योम omap2430_init_late(व्योम);
व्योम ti81xx_init_late(व्योम);
व्योम am33xx_init_late(व्योम);
व्योम omap5_init_late(व्योम);
पूर्णांक omap2_common_pm_late_init(व्योम);
व्योम dra7xx_init_early(व्योम);
व्योम dra7xx_init_late(व्योम);

#अगर_घोषित CONFIG_SOC_BUS
व्योम omap_soc_device_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap_soc_device_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_OMAP2420) || defined(CONFIG_SOC_OMAP2430)
व्योम omap2xxx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd);
#अन्यथा
अटल अंतरभूत व्योम omap2xxx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_AM33XX
व्योम am33xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd);
#अन्यथा
अटल अंतरभूत व्योम am33xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
व्योम omap3xxx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd);
#अन्यथा
अटल अंतरभूत व्योम omap3xxx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_TI81XX
व्योम ti81xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd);
#अन्यथा
अटल अंतरभूत व्योम ti81xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DRA7XX) || defined(CONFIG_SOC_AM43XX)
व्योम omap44xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd);
#अन्यथा
अटल अंतरभूत व्योम omap44xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OMAP_INTERCONNECT_BARRIER
व्योम omap_barrier_reserve_memblock(व्योम);
व्योम omap_barriers_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap_barrier_reserve_memblock(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/* This माला_लो called from mach-omap2/io.c, करो not call this */
व्योम __init omap2_set_globals_tap(u32 class, व्योम __iomem *tap);

व्योम __init omap242x_map_io(व्योम);
व्योम __init omap243x_map_io(व्योम);
व्योम __init omap3_map_io(व्योम);
व्योम __init am33xx_map_io(व्योम);
व्योम __init omap4_map_io(व्योम);
व्योम __init omap5_map_io(व्योम);
व्योम __init dra7xx_map_io(व्योम);
व्योम __init ti81xx_map_io(व्योम);

/**
 * omap_test_समयout - busy-loop, testing a condition
 * @cond: condition to test until it evaluates to true
 * @समयout: maximum number of microseconds in the समयout
 * @index: loop index (पूर्णांकeger)
 *
 * Loop रुकोing क्रम @cond to become true or until at least @समयout
 * microseconds have passed.  To use, define some पूर्णांकeger @index in the
 * calling code.  After running, अगर @index == @समयout, then the loop has
 * समयd out.
 */
#घोषणा omap_test_समयout(cond, समयout, index)			\
(अणु								\
	क्रम (index = 0; index < समयout; index++) अणु		\
		अगर (cond)					\
			अवरोध;					\
		udelay(1);					\
	पूर्ण							\
पूर्ण)

बाह्य काष्ठा device *omap2_get_mpuss_device(व्योम);
बाह्य काष्ठा device *omap2_get_iva_device(व्योम);
बाह्य काष्ठा device *omap2_get_l3_device(व्योम);
बाह्य काष्ठा device *omap4_get_dsp_device(व्योम);

व्योम omap_gic_of_init(व्योम);

#अगर_घोषित CONFIG_CACHE_L2X0
बाह्य व्योम __iomem *omap4_get_l2cache_base(व्योम);
#पूर्ण_अगर

काष्ठा device_node;

#अगर_घोषित CONFIG_SMP
बाह्य व्योम __iomem *omap4_get_scu_base(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __iomem *omap4_get_scu_base(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम gic_dist_disable(व्योम);
बाह्य व्योम gic_dist_enable(व्योम);
बाह्य bool gic_dist_disabled(व्योम);
बाह्य व्योम gic_समयr_retrigger(व्योम);
बाह्य व्योम _omap_smc1(u32 fn, u32 arg);
बाह्य व्योम omap4_sar_ram_init(व्योम);
बाह्य व्योम __iomem *omap4_get_sar_ram_base(व्योम);
बाह्य व्योम omap4_mpuss_early_init(व्योम);
बाह्य व्योम omap_करो_wfi(व्योम);


#अगर_घोषित CONFIG_SMP
/* Needed क्रम secondary core boot */
बाह्य u32 omap_modअगरy_auxcoreboot0(u32 set_mask, u32 clear_mask);
बाह्य व्योम omap_auxcoreboot_addr(u32 cpu_addr);
बाह्य u32 omap_पढ़ो_auxcoreboot0(व्योम);

बाह्य व्योम omap4_cpu_die(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक omap4_cpu_समाप्त(अचिन्हित पूर्णांक cpu);

बाह्य स्थिर काष्ठा smp_operations omap4_smp_ops;
#पूर्ण_अगर

बाह्य u32 omap4_get_cpu1_ns_pa_addr(व्योम);

#अगर defined(CONFIG_SMP) && defined(CONFIG_PM)
बाह्य पूर्णांक omap4_mpuss_init(व्योम);
बाह्य पूर्णांक omap4_enter_lowघातer(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक घातer_state);
बाह्य पूर्णांक omap4_hotplug_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक घातer_state);
#अन्यथा
अटल अंतरभूत पूर्णांक omap4_enter_lowघातer(अचिन्हित पूर्णांक cpu,
					अचिन्हित पूर्णांक घातer_state)
अणु
	cpu_करो_idle();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक omap4_hotplug_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक घातer_state)
अणु
	cpu_करो_idle();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक omap4_mpuss_init(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP4
व्योम omap4_secondary_startup(व्योम);
व्योम omap4460_secondary_startup(व्योम);
पूर्णांक omap4_finish_suspend(अचिन्हित दीर्घ cpu_state);
व्योम omap4_cpu_resume(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap4_secondary_startup(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम omap4460_secondary_startup(व्योम)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक omap4_finish_suspend(अचिन्हित दीर्घ cpu_state)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम omap4_cpu_resume(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_OMAP5) || defined(CONFIG_SOC_DRA7XX)
व्योम omap5_secondary_startup(व्योम);
व्योम omap5_secondary_hyp_startup(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap5_secondary_startup(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम omap5_secondary_hyp_startup(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा omap_प्रणाली_dma_plat_info;

व्योम pdata_quirks_init(स्थिर काष्ठा of_device_id *);
व्योम omap_auxdata_legacy_init(काष्ठा device *dev);
व्योम omap_pcs_legacy_init(पूर्णांक irq, व्योम (*rearm)(व्योम));
बाह्य काष्ठा omap_प्रणाली_dma_plat_info dma_plat_info;

काष्ठा omap_sdrc_params;
बाह्य व्योम omap_sdrc_init(काष्ठा omap_sdrc_params *sdrc_cs0,
				      काष्ठा omap_sdrc_params *sdrc_cs1);
बाह्य व्योम omap_reserve(व्योम);

काष्ठा omap_hwmod;
बाह्य पूर्णांक omap_dss_reset(काष्ठा omap_hwmod *);

/* SoC specअगरic घड़ी initializer */
पूर्णांक omap_clk_init(व्योम);

#पूर्ण_अगर /* __ASSEMBLER__ */
#पूर्ण_अगर /* __ARCH_ARM_MACH_OMAP2PLUS_COMMON_H */
