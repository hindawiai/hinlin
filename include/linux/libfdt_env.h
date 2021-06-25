<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LIBFDT_ENV_H
#घोषणा LIBFDT_ENV_H

#समावेश <linux/सीमा.स>	/* For पूर्णांक_उच्च */
#समावेश <linux/माला.स>

#समावेश <यंत्र/byteorder.h>

#घोषणा INT32_MAX	S32_MAX
#घोषणा UINT32_MAX	U32_MAX

प्रकार __be16 fdt16_t;
प्रकार __be32 fdt32_t;
प्रकार __be64 fdt64_t;

#घोषणा fdt32_to_cpu(x) be32_to_cpu(x)
#घोषणा cpu_to_fdt32(x) cpu_to_be32(x)
#घोषणा fdt64_to_cpu(x) be64_to_cpu(x)
#घोषणा cpu_to_fdt64(x) cpu_to_be64(x)

#पूर्ण_अगर /* LIBFDT_ENV_H */
