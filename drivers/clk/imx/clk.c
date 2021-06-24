<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश "clk.h"

#घोषणा CCM_CCDR			0x4
#घोषणा CCDR_MMDC_CH0_MASK		BIT(17)
#घोषणा CCDR_MMDC_CH1_MASK		BIT(16)

DEFINE_SPINLOCK(imx_ccm_lock);
EXPORT_SYMBOL_GPL(imx_ccm_lock);

व्योम imx_unरेजिस्टर_घड़ीs(काष्ठा clk *clks[], अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		clk_unरेजिस्टर(clks[i]);
पूर्ण

व्योम imx_unरेजिस्टर_hw_घड़ीs(काष्ठा clk_hw *hws[], अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		clk_hw_unरेजिस्टर(hws[i]);
पूर्ण
EXPORT_SYMBOL_GPL(imx_unरेजिस्टर_hw_घड़ीs);

व्योम imx_mmdc_mask_handshake(व्योम __iomem *ccm_base,
				    अचिन्हित पूर्णांक chn)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl_relaxed(ccm_base + CCM_CCDR);
	reg |= chn == 0 ? CCDR_MMDC_CH0_MASK : CCDR_MMDC_CH1_MASK;
	ग_लिखोl_relaxed(reg, ccm_base + CCM_CCDR);
पूर्ण

व्योम imx_check_घड़ीs(काष्ठा clk *clks[], अचिन्हित पूर्णांक count)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < count; i++)
		अगर (IS_ERR(clks[i]))
			pr_err("i.MX clk %u: register failed with %ld\n",
			       i, PTR_ERR(clks[i]));
पूर्ण

व्योम imx_check_clk_hws(काष्ठा clk_hw *clks[], अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (IS_ERR(clks[i]))
			pr_err("i.MX clk %u: register failed with %ld\n",
			       i, PTR_ERR(clks[i]));
पूर्ण
EXPORT_SYMBOL_GPL(imx_check_clk_hws);

अटल काष्ठा clk *imx_obtain_fixed_घड़ी_from_dt(स्थिर अक्षर *name)
अणु
	काष्ठा of_phandle_args phandle;
	काष्ठा clk *clk = ERR_PTR(-ENODEV);
	अक्षर *path;

	path = kaप्र_लिखो(GFP_KERNEL, "/clocks/%s", name);
	अगर (!path)
		वापस ERR_PTR(-ENOMEM);

	phandle.np = of_find_node_by_path(path);
	kमुक्त(path);

	अगर (phandle.np) अणु
		clk = of_clk_get_from_provider(&phandle);
		of_node_put(phandle.np);
	पूर्ण
	वापस clk;
पूर्ण

काष्ठा clk *imx_obtain_fixed_घड़ी(
			स्थिर अक्षर *name, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk *clk;

	clk = imx_obtain_fixed_घड़ी_from_dt(name);
	अगर (IS_ERR(clk))
		clk = imx_clk_fixed(name, rate);
	वापस clk;
पूर्ण

काष्ठा clk_hw *imx_obtain_fixed_घड़ी_hw(
			स्थिर अक्षर *name, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk *clk;

	clk = imx_obtain_fixed_घड़ी_from_dt(name);
	अगर (IS_ERR(clk))
		clk = imx_clk_fixed(name, rate);
	वापस __clk_get_hw(clk);
पूर्ण

काष्ठा clk_hw * imx_obtain_fixed_clk_hw(काष्ठा device_node *np,
					स्थिर अक्षर *name)
अणु
	काष्ठा clk *clk;

	clk = of_clk_get_by_name(np, name);
	अगर (IS_ERR(clk))
		वापस ERR_PTR(-ENOENT);

	वापस __clk_get_hw(clk);
पूर्ण
EXPORT_SYMBOL_GPL(imx_obtain_fixed_clk_hw);

/*
 * This fixups the रेजिस्टर CCM_CSCMR1 ग_लिखो value.
 * The ग_लिखो/पढ़ो/भागider values of the aclk_podf field
 * of that रेजिस्टर have the relationship described by
 * the following table:
 *
 * ग_लिखो value       पढ़ो value        भागider
 * 3b'000            3b'110            7
 * 3b'001            3b'111            8
 * 3b'010            3b'100            5
 * 3b'011            3b'101            6
 * 3b'100            3b'010            3
 * 3b'101            3b'011            4
 * 3b'110            3b'000            1
 * 3b'111            3b'001            2(शेष)
 *
 * That's why we करो the xor operation below.
 */
#घोषणा CSCMR1_FIXUP	0x00600000

व्योम imx_cscmr1_fixup(u32 *val)
अणु
	*val ^= CSCMR1_FIXUP;
	वापस;
पूर्ण

#अगर_अघोषित MODULE

अटल bool imx_keep_uart_घड़ीs;
अटल पूर्णांक imx_enabled_uart_घड़ीs;
अटल काष्ठा clk **imx_uart_घड़ीs;

अटल पूर्णांक __init imx_keep_uart_घड़ीs_param(अक्षर *str)
अणु
	imx_keep_uart_घड़ीs = 1;

	वापस 0;
पूर्ण
__setup_param("earlycon", imx_keep_uart_earlycon,
	      imx_keep_uart_घड़ीs_param, 0);
__setup_param("earlyprintk", imx_keep_uart_earlyprपूर्णांकk,
	      imx_keep_uart_घड़ीs_param, 0);

व्योम imx_रेजिस्टर_uart_घड़ीs(अचिन्हित पूर्णांक clk_count)
अणु
	imx_enabled_uart_घड़ीs = 0;

/* i.MX boards use device trees now.  For build tests without CONFIG_OF, करो nothing */
#अगर_घोषित CONFIG_OF
	अगर (imx_keep_uart_घड़ीs) अणु
		पूर्णांक i;

		imx_uart_घड़ीs = kसुस्मृति(clk_count, माप(काष्ठा clk *), GFP_KERNEL);

		अगर (!of_मानक_निकास)
			वापस;

		क्रम (i = 0; i < clk_count; i++) अणु
			imx_uart_घड़ीs[imx_enabled_uart_घड़ीs] = of_clk_get(of_मानक_निकास, i);

			/* Stop अगर there are no more of_मानक_निकास references */
			अगर (IS_ERR(imx_uart_घड़ीs[imx_enabled_uart_घड़ीs]))
				वापस;

			/* Only enable the घड़ी अगर it's not शून्य */
			अगर (imx_uart_घड़ीs[imx_enabled_uart_घड़ीs])
				clk_prepare_enable(imx_uart_घड़ीs[imx_enabled_uart_घड़ीs++]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init imx_clk_disable_uart(व्योम)
अणु
	अगर (imx_keep_uart_घड़ीs && imx_enabled_uart_घड़ीs) अणु
		पूर्णांक i;

		क्रम (i = 0; i < imx_enabled_uart_घड़ीs; i++) अणु
			clk_disable_unprepare(imx_uart_घड़ीs[i]);
			clk_put(imx_uart_घड़ीs[i]);
		पूर्ण
		kमुक्त(imx_uart_घड़ीs);
	पूर्ण

	वापस 0;
पूर्ण
late_initcall_sync(imx_clk_disable_uart);
#पूर्ण_अगर

MODULE_LICENSE("GPL v2");
