<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "hardware.h"
#समावेश "common.h"

अचिन्हित पूर्णांक __mxc_cpu_type;
अटल अचिन्हित पूर्णांक imx_soc_revision;

व्योम mxc_set_cpu_type(अचिन्हित पूर्णांक type)
अणु
	__mxc_cpu_type = type;
पूर्ण

व्योम imx_set_soc_revision(अचिन्हित पूर्णांक rev)
अणु
	imx_soc_revision = rev;
पूर्ण

अचिन्हित पूर्णांक imx_get_soc_revision(व्योम)
अणु
	वापस imx_soc_revision;
पूर्ण

व्योम imx_prपूर्णांक_silicon_rev(स्थिर अक्षर *cpu, पूर्णांक srev)
अणु
	अगर (srev == IMX_CHIP_REVISION_UNKNOWN)
		pr_info("CPU identified as %s, unknown revision\n", cpu);
	अन्यथा
		pr_info("CPU identified as %s, silicon rev %d.%d\n",
				cpu, (srev >> 4) & 0xf, srev & 0xf);
पूर्ण

व्योम __init imx_set_aips(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक reg;
/*
 * Set all MPROTx to be non-bufferable, trusted क्रम R/W,
 * not क्रमced to user-mode.
 */
	imx_ग_लिखोl(0x77777777, base + 0x0);
	imx_ग_लिखोl(0x77777777, base + 0x4);

/*
 * Set all OPACRx to be non-bufferable, to not require
 * supervisor privilege level क्रम access, allow क्रम
 * ग_लिखो access and untrusted master access.
 */
	imx_ग_लिखोl(0x0, base + 0x40);
	imx_ग_लिखोl(0x0, base + 0x44);
	imx_ग_लिखोl(0x0, base + 0x48);
	imx_ग_लिखोl(0x0, base + 0x4C);
	reg = imx_पढ़ोl(base + 0x50) & 0x00FFFFFF;
	imx_ग_लिखोl(reg, base + 0x50);
पूर्ण

व्योम __init imx_aips_allow_unprivileged_access(
		स्थिर अक्षर *compat)
अणु
	व्योम __iomem *aips_base_addr;
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, शून्य, compat) अणु
		aips_base_addr = of_iomap(np, 0);
		WARN_ON(!aips_base_addr);
		imx_set_aips(aips_base_addr);
	पूर्ण
पूर्ण
