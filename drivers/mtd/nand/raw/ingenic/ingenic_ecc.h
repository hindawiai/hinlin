<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DRIVERS_MTD_न_अंकD_INGENIC_ECC_INTERNAL_H__
#घोषणा __DRIVERS_MTD_न_अंकD_INGENIC_ECC_INTERNAL_H__

#समावेश <linux/compiler_types.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <uapi/यंत्र-generic/त्रुटि_सं-base.h>

काष्ठा clk;
काष्ठा device;
काष्ठा ingenic_ecc;
काष्ठा platक्रमm_device;

/**
 * काष्ठा ingenic_ecc_params - ECC parameters
 * @size: data bytes per ECC step.
 * @bytes: ECC bytes per step.
 * @strength: number of correctable bits per ECC step.
 */
काष्ठा ingenic_ecc_params अणु
	पूर्णांक size;
	पूर्णांक bytes;
	पूर्णांक strength;
पूर्ण;

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_INGENIC_ECC)
पूर्णांक ingenic_ecc_calculate(काष्ठा ingenic_ecc *ecc,
			  काष्ठा ingenic_ecc_params *params,
			  स्थिर u8 *buf, u8 *ecc_code);
पूर्णांक ingenic_ecc_correct(काष्ठा ingenic_ecc *ecc,
			काष्ठा ingenic_ecc_params *params, u8 *buf,
			u8 *ecc_code);

व्योम ingenic_ecc_release(काष्ठा ingenic_ecc *ecc);
काष्ठा ingenic_ecc *of_ingenic_ecc_get(काष्ठा device_node *np);
#अन्यथा /* CONFIG_MTD_न_अंकD_INGENIC_ECC */
पूर्णांक ingenic_ecc_calculate(काष्ठा ingenic_ecc *ecc,
			  काष्ठा ingenic_ecc_params *params,
			  स्थिर u8 *buf, u8 *ecc_code)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक ingenic_ecc_correct(काष्ठा ingenic_ecc *ecc,
			काष्ठा ingenic_ecc_params *params, u8 *buf,
			u8 *ecc_code)
अणु
	वापस -ENODEV;
पूर्ण

व्योम ingenic_ecc_release(काष्ठा ingenic_ecc *ecc)
अणु
पूर्ण

काष्ठा ingenic_ecc *of_ingenic_ecc_get(काष्ठा device_node *np)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर /* CONFIG_MTD_न_अंकD_INGENIC_ECC */

काष्ठा ingenic_ecc_ops अणु
	व्योम (*disable)(काष्ठा ingenic_ecc *ecc);
	पूर्णांक (*calculate)(काष्ठा ingenic_ecc *ecc,
			 काष्ठा ingenic_ecc_params *params,
			 स्थिर u8 *buf, u8 *ecc_code);
	पूर्णांक (*correct)(काष्ठा ingenic_ecc *ecc,
			काष्ठा ingenic_ecc_params *params,
			u8 *buf, u8 *ecc_code);
पूर्ण;

काष्ठा ingenic_ecc अणु
	काष्ठा device *dev;
	स्थिर काष्ठा ingenic_ecc_ops *ops;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा mutex lock;
पूर्ण;

पूर्णांक ingenic_ecc_probe(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __DRIVERS_MTD_न_अंकD_INGENIC_ECC_INTERNAL_H__ */
