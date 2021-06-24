<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BOARD_H__
#घोषणा __BOARD_H__

#समावेश <linux/init.h>
#समावेश <linux/of.h>

काष्ठा board_staging_clk अणु
	स्थिर अक्षर *clk;
	स्थिर अक्षर *con_id;
	स्थिर अक्षर *dev_id;
पूर्ण;

काष्ठा board_staging_dev अणु
	/* Platक्रमm Device */
	काष्ठा platक्रमm_device *pdev;
	/* Clocks (optional) */
	स्थिर काष्ठा board_staging_clk *घड़ीs;
	अचिन्हित पूर्णांक nघड़ीs;
	/* Generic PM Doमुख्य (optional) */
	स्थिर अक्षर *करोमुख्य;
पूर्ण;

काष्ठा resource;

bool board_staging_dt_node_available(स्थिर काष्ठा resource *resource,
				     अचिन्हित पूर्णांक num_resources);
पूर्णांक board_staging_gic_setup_xlate(स्थिर अक्षर *gic_match, अचिन्हित पूर्णांक base);
व्योम board_staging_gic_fixup_resources(काष्ठा resource *res, अचिन्हित पूर्णांक nres);
पूर्णांक board_staging_रेजिस्टर_घड़ी(स्थिर काष्ठा board_staging_clk *bsc);
पूर्णांक board_staging_रेजिस्टर_device(स्थिर काष्ठा board_staging_dev *dev);
व्योम board_staging_रेजिस्टर_devices(स्थिर काष्ठा board_staging_dev *devs,
				    अचिन्हित पूर्णांक ndevs);

#घोषणा board_staging(str, fn)			\
अटल पूर्णांक __init runसमय_board_check(व्योम)	\
अणु						\
	अगर (of_machine_is_compatible(str))	\
		fn();				\
						\
	वापस 0;				\
पूर्ण						\
						\
device_initcall(runसमय_board_check)

#पूर्ण_अगर /* __BOARD_H__ */
