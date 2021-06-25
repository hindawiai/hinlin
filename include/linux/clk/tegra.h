<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __LINUX_CLK_TEGRA_H_
#घोषणा __LINUX_CLK_TEGRA_H_

#समावेश <linux/types.h>
#समावेश <linux/bug.h>

/*
 * Tegra CPU घड़ी and reset control ops
 *
 * रुको_क्रम_reset:
 *	keep रुकोing until the CPU in reset state
 * put_in_reset:
 *	put the CPU in reset state
 * out_of_reset:
 *	release the CPU from reset state
 * enable_घड़ी:
 *	CPU घड़ी un-gate
 * disable_घड़ी:
 *	CPU घड़ी gate
 * rail_off_पढ़ोy:
 *	CPU is पढ़ोy क्रम rail off
 * suspend:
 *	save the घड़ी settings when CPU go पूर्णांकo low-घातer state
 * resume:
 *	restore the घड़ी settings when CPU निकास low-घातer state
 */
काष्ठा tegra_cpu_car_ops अणु
	व्योम (*रुको_क्रम_reset)(u32 cpu);
	व्योम (*put_in_reset)(u32 cpu);
	व्योम (*out_of_reset)(u32 cpu);
	व्योम (*enable_घड़ी)(u32 cpu);
	व्योम (*disable_घड़ी)(u32 cpu);
#अगर_घोषित CONFIG_PM_SLEEP
	bool (*rail_off_पढ़ोy)(व्योम);
	व्योम (*suspend)(व्योम);
	व्योम (*resume)(व्योम);
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा tegra_cpu_car_ops *tegra_cpu_car_ops;

अटल अंतरभूत व्योम tegra_रुको_cpu_in_reset(u32 cpu)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->रुको_क्रम_reset))
		वापस;

	tegra_cpu_car_ops->रुको_क्रम_reset(cpu);
पूर्ण

अटल अंतरभूत व्योम tegra_put_cpu_in_reset(u32 cpu)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->put_in_reset))
		वापस;

	tegra_cpu_car_ops->put_in_reset(cpu);
पूर्ण

अटल अंतरभूत व्योम tegra_cpu_out_of_reset(u32 cpu)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->out_of_reset))
		वापस;

	tegra_cpu_car_ops->out_of_reset(cpu);
पूर्ण

अटल अंतरभूत व्योम tegra_enable_cpu_घड़ी(u32 cpu)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->enable_घड़ी))
		वापस;

	tegra_cpu_car_ops->enable_घड़ी(cpu);
पूर्ण

अटल अंतरभूत व्योम tegra_disable_cpu_घड़ी(u32 cpu)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->disable_घड़ी))
		वापस;

	tegra_cpu_car_ops->disable_घड़ी(cpu);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल अंतरभूत bool tegra_cpu_rail_off_पढ़ोy(व्योम)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->rail_off_पढ़ोy))
		वापस false;

	वापस tegra_cpu_car_ops->rail_off_पढ़ोy();
पूर्ण

अटल अंतरभूत व्योम tegra_cpu_घड़ी_suspend(व्योम)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->suspend))
		वापस;

	tegra_cpu_car_ops->suspend();
पूर्ण

अटल अंतरभूत व्योम tegra_cpu_घड़ी_resume(व्योम)
अणु
	अगर (WARN_ON(!tegra_cpu_car_ops->resume))
		वापस;

	tegra_cpu_car_ops->resume();
पूर्ण
#अन्यथा
अटल अंतरभूत bool tegra_cpu_rail_off_पढ़ोy(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम tegra_cpu_घड़ी_suspend(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम tegra_cpu_घड़ी_resume(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक tegra210_plle_hw_sequence_start(व्योम);
बाह्य bool tegra210_plle_hw_sequence_is_enabled(व्योम);
बाह्य व्योम tegra210_xusb_pll_hw_control_enable(व्योम);
बाह्य व्योम tegra210_xusb_pll_hw_sequence_start(व्योम);
बाह्य व्योम tegra210_sata_pll_hw_control_enable(व्योम);
बाह्य व्योम tegra210_sata_pll_hw_sequence_start(व्योम);
बाह्य व्योम tegra210_set_sata_pll_seq_sw(bool state);
बाह्य व्योम tegra210_put_uपंचांगipll_in_iddq(व्योम);
बाह्य व्योम tegra210_put_uपंचांगipll_out_iddq(व्योम);
बाह्य पूर्णांक tegra210_clk_handle_mbist_war(अचिन्हित पूर्णांक id);
बाह्य व्योम tegra210_clk_emc_dll_enable(bool flag);
बाह्य व्योम tegra210_clk_emc_dll_update_setting(u32 emc_dll_src_value);
बाह्य व्योम tegra210_clk_emc_update_setting(u32 emc_src_value);

काष्ठा clk;
काष्ठा tegra_emc;

प्रकार दीर्घ (tegra20_clk_emc_round_cb)(अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ min_rate,
					अचिन्हित दीर्घ max_rate,
					व्योम *arg);

व्योम tegra20_clk_set_emc_round_callback(tegra20_clk_emc_round_cb *round_cb,
					व्योम *cb_arg);
पूर्णांक tegra20_clk_prepare_emc_mc_same_freq(काष्ठा clk *emc_clk, bool same);

प्रकार पूर्णांक (tegra124_emc_prepare_timing_change_cb)(काष्ठा tegra_emc *emc,
						    अचिन्हित दीर्घ rate);
प्रकार व्योम (tegra124_emc_complete_timing_change_cb)(काष्ठा tegra_emc *emc,
						      अचिन्हित दीर्घ rate);
व्योम tegra124_clk_set_emc_callbacks(tegra124_emc_prepare_timing_change_cb *prep_cb,
				    tegra124_emc_complete_timing_change_cb *complete_cb);

काष्ठा tegra210_clk_emc_config अणु
	अचिन्हित दीर्घ rate;
	bool same_freq;
	u32 value;

	अचिन्हित दीर्घ parent_rate;
	u8 parent;
पूर्ण;

काष्ठा tegra210_clk_emc_provider अणु
	काष्ठा module *owner;
	काष्ठा device *dev;

	काष्ठा tegra210_clk_emc_config *configs;
	अचिन्हित पूर्णांक num_configs;

	पूर्णांक (*set_rate)(काष्ठा device *dev,
			स्थिर काष्ठा tegra210_clk_emc_config *config);
पूर्ण;

पूर्णांक tegra210_clk_emc_attach(काष्ठा clk *clk,
			    काष्ठा tegra210_clk_emc_provider *provider);
व्योम tegra210_clk_emc_detach(काष्ठा clk *clk);

#पूर्ण_अगर /* __LINUX_CLK_TEGRA_H_ */
