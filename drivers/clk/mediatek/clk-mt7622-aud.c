<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 MediaTek Inc.
 * Author: Chen Zhong <chen.zhong@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

#समावेश <dt-bindings/घड़ी/mt7622-clk.h>

#घोषणा GATE_AUDIO0(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audio0_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

#घोषणा GATE_AUDIO1(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audio1_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

#घोषणा GATE_AUDIO2(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audio2_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

#घोषणा GATE_AUDIO3(_id, _name, _parent, _shअगरt) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &audio3_cg_regs,			\
		.shअगरt = _shअगरt,			\
		.ops = &mtk_clk_gate_ops_no_setclr,	\
	पूर्ण

अटल स्थिर काष्ठा mtk_gate_regs audio0_cg_regs = अणु
	.set_ofs = 0x0,
	.clr_ofs = 0x0,
	.sta_ofs = 0x0,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs audio1_cg_regs = अणु
	.set_ofs = 0x10,
	.clr_ofs = 0x10,
	.sta_ofs = 0x10,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs audio2_cg_regs = अणु
	.set_ofs = 0x14,
	.clr_ofs = 0x14,
	.sta_ofs = 0x14,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate_regs audio3_cg_regs = अणु
	.set_ofs = 0x634,
	.clr_ofs = 0x634,
	.sta_ofs = 0x634,
पूर्ण;

अटल स्थिर काष्ठा mtk_gate audio_clks[] = अणु
	/* AUDIO0 */
	GATE_AUDIO0(CLK_AUDIO_AFE, "audio_afe", "rtc", 2),
	GATE_AUDIO0(CLK_AUDIO_HDMI, "audio_hdmi", "apll1_ck_sel", 20),
	GATE_AUDIO0(CLK_AUDIO_SPDF, "audio_spdf", "apll1_ck_sel", 21),
	GATE_AUDIO0(CLK_AUDIO_APLL, "audio_apll", "apll1_ck_sel", 23),
	/* AUDIO1 */
	GATE_AUDIO1(CLK_AUDIO_I2SIN1, "audio_i2sin1", "a1sys_hp_sel", 0),
	GATE_AUDIO1(CLK_AUDIO_I2SIN2, "audio_i2sin2", "a1sys_hp_sel", 1),
	GATE_AUDIO1(CLK_AUDIO_I2SIN3, "audio_i2sin3", "a1sys_hp_sel", 2),
	GATE_AUDIO1(CLK_AUDIO_I2SIN4, "audio_i2sin4", "a1sys_hp_sel", 3),
	GATE_AUDIO1(CLK_AUDIO_I2SO1, "audio_i2so1", "a1sys_hp_sel", 6),
	GATE_AUDIO1(CLK_AUDIO_I2SO2, "audio_i2so2", "a1sys_hp_sel", 7),
	GATE_AUDIO1(CLK_AUDIO_I2SO3, "audio_i2so3", "a1sys_hp_sel", 8),
	GATE_AUDIO1(CLK_AUDIO_I2SO4, "audio_i2so4", "a1sys_hp_sel", 9),
	GATE_AUDIO1(CLK_AUDIO_ASRCI1, "audio_asrci1", "asm_h_sel", 12),
	GATE_AUDIO1(CLK_AUDIO_ASRCI2, "audio_asrci2", "asm_h_sel", 13),
	GATE_AUDIO1(CLK_AUDIO_ASRCO1, "audio_asrco1", "asm_h_sel", 14),
	GATE_AUDIO1(CLK_AUDIO_ASRCO2, "audio_asrco2", "asm_h_sel", 15),
	GATE_AUDIO1(CLK_AUDIO_INTसूची, "audio_intdir", "intdir_sel", 20),
	GATE_AUDIO1(CLK_AUDIO_A1SYS, "audio_a1sys", "a1sys_hp_sel", 21),
	GATE_AUDIO1(CLK_AUDIO_A2SYS, "audio_a2sys", "a2sys_hp_sel", 22),
	GATE_AUDIO1(CLK_AUDIO_AFE_CONN, "audio_afe_conn", "a1sys_hp_sel", 23),
	/* AUDIO2 */
	GATE_AUDIO2(CLK_AUDIO_UL1, "audio_ul1", "a1sys_hp_sel", 0),
	GATE_AUDIO2(CLK_AUDIO_UL2, "audio_ul2", "a1sys_hp_sel", 1),
	GATE_AUDIO2(CLK_AUDIO_UL3, "audio_ul3", "a1sys_hp_sel", 2),
	GATE_AUDIO2(CLK_AUDIO_UL4, "audio_ul4", "a1sys_hp_sel", 3),
	GATE_AUDIO2(CLK_AUDIO_UL5, "audio_ul5", "a1sys_hp_sel", 4),
	GATE_AUDIO2(CLK_AUDIO_UL6, "audio_ul6", "a1sys_hp_sel", 5),
	GATE_AUDIO2(CLK_AUDIO_DL1, "audio_dl1", "a1sys_hp_sel", 6),
	GATE_AUDIO2(CLK_AUDIO_DL2, "audio_dl2", "a1sys_hp_sel", 7),
	GATE_AUDIO2(CLK_AUDIO_DL3, "audio_dl3", "a1sys_hp_sel", 8),
	GATE_AUDIO2(CLK_AUDIO_DL4, "audio_dl4", "a1sys_hp_sel", 9),
	GATE_AUDIO2(CLK_AUDIO_DL5, "audio_dl5", "a1sys_hp_sel", 10),
	GATE_AUDIO2(CLK_AUDIO_DL6, "audio_dl6", "a1sys_hp_sel", 11),
	GATE_AUDIO2(CLK_AUDIO_DLMCH, "audio_dlmch", "a1sys_hp_sel", 12),
	GATE_AUDIO2(CLK_AUDIO_ARB1, "audio_arb1", "a1sys_hp_sel", 13),
	GATE_AUDIO2(CLK_AUDIO_AWB, "audio_awb", "a1sys_hp_sel", 14),
	GATE_AUDIO2(CLK_AUDIO_AWB2, "audio_awb2", "a1sys_hp_sel", 15),
	GATE_AUDIO2(CLK_AUDIO_DAI, "audio_dai", "a1sys_hp_sel", 16),
	GATE_AUDIO2(CLK_AUDIO_MOD, "audio_mod", "a1sys_hp_sel", 17),
	/* AUDIO3 */
	GATE_AUDIO3(CLK_AUDIO_ASRCI3, "audio_asrci3", "asm_h_sel", 2),
	GATE_AUDIO3(CLK_AUDIO_ASRCI4, "audio_asrci4", "asm_h_sel", 3),
	GATE_AUDIO3(CLK_AUDIO_ASRCO3, "audio_asrco3", "asm_h_sel", 6),
	GATE_AUDIO3(CLK_AUDIO_ASRCO4, "audio_asrco4", "asm_h_sel", 7),
	GATE_AUDIO3(CLK_AUDIO_MEM_ASRC1, "audio_mem_asrc1", "asm_h_sel", 10),
	GATE_AUDIO3(CLK_AUDIO_MEM_ASRC2, "audio_mem_asrc2", "asm_h_sel", 11),
	GATE_AUDIO3(CLK_AUDIO_MEM_ASRC3, "audio_mem_asrc3", "asm_h_sel", 12),
	GATE_AUDIO3(CLK_AUDIO_MEM_ASRC4, "audio_mem_asrc4", "asm_h_sel", 13),
	GATE_AUDIO3(CLK_AUDIO_MEM_ASRC5, "audio_mem_asrc5", "asm_h_sel", 14),
पूर्ण;

अटल पूर्णांक clk_mt7622_audiosys_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक r;

	clk_data = mtk_alloc_clk_data(CLK_AUDIO_NR_CLK);

	mtk_clk_रेजिस्टर_gates(node, audio_clks, ARRAY_SIZE(audio_clks),
			       clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (r) अणु
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

		जाओ err_clk_provider;
	पूर्ण

	r = devm_of_platक्रमm_populate(&pdev->dev);
	अगर (r)
		जाओ err_plat_populate;

	वापस 0;

err_plat_populate:
	of_clk_del_provider(node);
err_clk_provider:
	वापस r;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match_clk_mt7622_aud[] = अणु
	अणु
		.compatible = "mediatek,mt7622-audsys",
		.data = clk_mt7622_audiosys_init,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक clk_mt7622_aud_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक (*clk_init)(काष्ठा platक्रमm_device *);
	पूर्णांक r;

	clk_init = of_device_get_match_data(&pdev->dev);
	अगर (!clk_init)
		वापस -EINVAL;

	r = clk_init(pdev);
	अगर (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver clk_mt7622_aud_drv = अणु
	.probe = clk_mt7622_aud_probe,
	.driver = अणु
		.name = "clk-mt7622-aud",
		.of_match_table = of_match_clk_mt7622_aud,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(clk_mt7622_aud_drv);
