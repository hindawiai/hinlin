<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mcfclk.h -- coldfire specअगरic घड़ी काष्ठाure
 */


#अगर_अघोषित mcfclk_h
#घोषणा mcfclk_h

काष्ठा clk;

काष्ठा clk_ops अणु
	व्योम (*enable)(काष्ठा clk *);
	व्योम (*disable)(काष्ठा clk *);
पूर्ण;

काष्ठा clk अणु
	स्थिर अक्षर *name;
	काष्ठा clk_ops *clk_ops;
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ enabled;
	u8 slot;
पूर्ण;

बाह्य काष्ठा clk *mcf_clks[];

#अगर_घोषित MCFPM_PPMCR0
बाह्य काष्ठा clk_ops clk_ops0;
#अगर_घोषित MCFPM_PPMCR1
बाह्य काष्ठा clk_ops clk_ops1;
#पूर्ण_अगर /* MCFPM_PPMCR1 */

बाह्य काष्ठा clk_ops clk_ops2;

#घोषणा DEFINE_CLK(clk_bank, clk_name, clk_slot, clk_rate) \
अटल काष्ठा clk __clk_##clk_bank##_##clk_slot = अणु \
	.name = clk_name, \
	.clk_ops = &clk_ops##clk_bank, \
	.rate = clk_rate, \
	.slot = clk_slot, \
पूर्ण

व्योम __clk_init_enabled(काष्ठा clk *);
व्योम __clk_init_disabled(काष्ठा clk *);
#अन्यथा
#घोषणा DEFINE_CLK(clk_ref, clk_name, clk_rate) \
        अटल काष्ठा clk clk_##clk_ref = अणु \
                .name = clk_name, \
                .rate = clk_rate, \
        पूर्ण
#पूर्ण_अगर /* MCFPM_PPMCR0 */

#पूर्ण_अगर /* mcfclk_h */
