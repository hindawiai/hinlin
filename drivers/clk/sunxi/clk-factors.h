<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_SUNXI_CLK_FACTORS_H
#घोषणा __MACH_SUNXI_CLK_FACTORS_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>

#घोषणा SUNXI_FACTORS_NOT_APPLICABLE	(0)

काष्ठा clk_factors_config अणु
	u8 nshअगरt;
	u8 nwidth;
	u8 kshअगरt;
	u8 kwidth;
	u8 mshअगरt;
	u8 mwidth;
	u8 pshअगरt;
	u8 pwidth;
	u8 n_start;
पूर्ण;

काष्ठा factors_request अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ parent_rate;
	u8 parent_index;
	u8 n;
	u8 k;
	u8 m;
	u8 p;
पूर्ण;

काष्ठा factors_data अणु
	पूर्णांक enable;
	पूर्णांक mux;
	पूर्णांक muxmask;
	स्थिर काष्ठा clk_factors_config *table;
	व्योम (*getter)(काष्ठा factors_request *req);
	व्योम (*recalc)(काष्ठा factors_request *req);
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा clk_factors अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	स्थिर काष्ठा clk_factors_config *config;
	व्योम (*get_factors)(काष्ठा factors_request *req);
	व्योम (*recalc)(काष्ठा factors_request *req);
	spinlock_t *lock;
	/* क्रम cleanup */
	काष्ठा clk_mux *mux;
	काष्ठा clk_gate *gate;
पूर्ण;

काष्ठा clk *sunxi_factors_रेजिस्टर(काष्ठा device_node *node,
				   स्थिर काष्ठा factors_data *data,
				   spinlock_t *lock,
				   व्योम __iomem *reg);
काष्ठा clk *sunxi_factors_रेजिस्टर_critical(काष्ठा device_node *node,
					    स्थिर काष्ठा factors_data *data,
					    spinlock_t *lock,
					    व्योम __iomem *reg);

व्योम sunxi_factors_unरेजिस्टर(काष्ठा device_node *node, काष्ठा clk *clk);

#पूर्ण_अगर
