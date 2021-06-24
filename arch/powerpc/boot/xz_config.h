<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __XZ_CONFIG_H__
#घोषणा __XZ_CONFIG_H__

/*
 * most of this is copied from lib/xz/xz_निजी.h, we can't use their defines
 * since the boot wrapper is not built in the same environment as the rest of
 * the kernel.
 */

#समावेश "types.h"
#समावेश "swab.h"

अटल अंतरभूत uपूर्णांक32_t swab32p(व्योम *p)
अणु
	uपूर्णांक32_t *q = p;

	वापस swab32(*q);
पूर्ण

#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा get_le32(p) (*((uपूर्णांक32_t *) (p)))
#घोषणा cpu_to_be32(x) swab32(x)
अटल अंतरभूत u32 be32_to_cpup(स्थिर u32 *p)
अणु
	वापस swab32p((u32 *)p);
पूर्ण
#अन्यथा
#घोषणा get_le32(p) swab32p(p)
#घोषणा cpu_to_be32(x) (x)
अटल अंतरभूत u32 be32_to_cpup(स्थिर u32 *p)
अणु
	वापस *p;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत uपूर्णांक32_t get_unaligned_be32(स्थिर व्योम *p)
अणु
	वापस be32_to_cpup(p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be32(u32 val, व्योम *p)
अणु
	*((u32 *)p) = cpu_to_be32(val);
पूर्ण

#घोषणा memeq(a, b, size) (स_भेद(a, b, size) == 0)
#घोषणा memzero(buf, size) स_रखो(buf, 0, size)

/* prevent the inclusion of the xz-preboot MM headers */
#घोषणा DECOMPR_MM_H
#घोषणा स_हटाओ स_हटाओ
#घोषणा XZ_EXTERN अटल

/* xz.h needs to be included directly since we need क्रमागत xz_mode */
#समावेश "../../../include/linux/xz.h"

#अघोषित XZ_EXTERN

#पूर्ण_अगर
