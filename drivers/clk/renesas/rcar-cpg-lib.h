<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * R-Car Gen3 Clock Pulse Generator Library
 *
 * Copyright (C) 2015-2018 Glider bvba
 * Copyright (C) 2019 Renesas Electronics Corp.
 *
 * Based on clk-rcar-gen3.c
 *
 * Copyright (C) 2015 Renesas Electronics Corp.
 */

#अगर_अघोषित __CLK_RENESAS_RCAR_CPG_LIB_H__
#घोषणा __CLK_RENESAS_RCAR_CPG_LIB_H__

बाह्य spinlock_t cpg_lock;

काष्ठा cpg_simple_notअगरier अणु
	काष्ठा notअगरier_block nb;
	व्योम __iomem *reg;
	u32 saved;
पूर्ण;

व्योम cpg_simple_notअगरier_रेजिस्टर(काष्ठा raw_notअगरier_head *notअगरiers,
				  काष्ठा cpg_simple_notअगरier *csn);

व्योम cpg_reg_modअगरy(व्योम __iomem *reg, u32 clear, u32 set);

काष्ठा clk * __init cpg_sd_clk_रेजिस्टर(स्थिर अक्षर *name,
	व्योम __iomem *base, अचिन्हित पूर्णांक offset, स्थिर अक्षर *parent_name,
	काष्ठा raw_notअगरier_head *notअगरiers, bool skip_first);

#पूर्ण_अगर
