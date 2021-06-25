<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause) */
#अगर_अघोषित LIBFDT_ENV_H
#घोषणा LIBFDT_ENV_H
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 * Copyright 2012 Kim Phillips, Freescale Semiconductor.
 */

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <सीमा.स>

#अगर_घोषित __CHECKER__
#घोषणा FDT_FORCE __attribute__((क्रमce))
#घोषणा FDT_BITWISE __attribute__((bitwise))
#अन्यथा
#घोषणा FDT_FORCE
#घोषणा FDT_BITWISE
#पूर्ण_अगर

प्रकार uपूर्णांक16_t FDT_BITWISE fdt16_t;
प्रकार uपूर्णांक32_t FDT_BITWISE fdt32_t;
प्रकार uपूर्णांक64_t FDT_BITWISE fdt64_t;

#घोषणा EXTRACT_BYTE(x, n)	((अचिन्हित दीर्घ दीर्घ)((uपूर्णांक8_t *)&x)[n])
#घोषणा CPU_TO_FDT16(x) ((EXTRACT_BYTE(x, 0) << 8) | EXTRACT_BYTE(x, 1))
#घोषणा CPU_TO_FDT32(x) ((EXTRACT_BYTE(x, 0) << 24) | (EXTRACT_BYTE(x, 1) << 16) | \
			 (EXTRACT_BYTE(x, 2) << 8) | EXTRACT_BYTE(x, 3))
#घोषणा CPU_TO_FDT64(x) ((EXTRACT_BYTE(x, 0) << 56) | (EXTRACT_BYTE(x, 1) << 48) | \
			 (EXTRACT_BYTE(x, 2) << 40) | (EXTRACT_BYTE(x, 3) << 32) | \
			 (EXTRACT_BYTE(x, 4) << 24) | (EXTRACT_BYTE(x, 5) << 16) | \
			 (EXTRACT_BYTE(x, 6) << 8) | EXTRACT_BYTE(x, 7))

अटल अंतरभूत uपूर्णांक16_t fdt16_to_cpu(fdt16_t x)
अणु
	वापस (FDT_FORCE uपूर्णांक16_t)CPU_TO_FDT16(x);
पूर्ण
अटल अंतरभूत fdt16_t cpu_to_fdt16(uपूर्णांक16_t x)
अणु
	वापस (FDT_FORCE fdt16_t)CPU_TO_FDT16(x);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t fdt32_to_cpu(fdt32_t x)
अणु
	वापस (FDT_FORCE uपूर्णांक32_t)CPU_TO_FDT32(x);
पूर्ण
अटल अंतरभूत fdt32_t cpu_to_fdt32(uपूर्णांक32_t x)
अणु
	वापस (FDT_FORCE fdt32_t)CPU_TO_FDT32(x);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t fdt64_to_cpu(fdt64_t x)
अणु
	वापस (FDT_FORCE uपूर्णांक64_t)CPU_TO_FDT64(x);
पूर्ण
अटल अंतरभूत fdt64_t cpu_to_fdt64(uपूर्णांक64_t x)
अणु
	वापस (FDT_FORCE fdt64_t)CPU_TO_FDT64(x);
पूर्ण
#अघोषित CPU_TO_FDT64
#अघोषित CPU_TO_FDT32
#अघोषित CPU_TO_FDT16
#अघोषित EXTRACT_BYTE

#अगर_घोषित __APPLE__
#समावेश <AvailabilityMacros.h>

/* strnlen() is not available on Mac OS < 10.7 */
# अगर !defined(MAC_OS_X_VERSION_10_7) || (MAC_OS_X_VERSION_MAX_ALLOWED < \
                                         MAC_OS_X_VERSION_10_7)

#घोषणा strnlen fdt_strnlen

/*
 * fdt_strnlen: वापसs the length of a string or max_count - which ever is
 * smallest.
 * Input 1 string: the string whose size is to be determined
 * Input 2 max_count: the maximum value वापसed by this function
 * Output: length of the string or max_count (the smallest of the two)
 */
अटल अंतरभूत माप_प्रकार fdt_strnlen(स्थिर अक्षर *string, माप_प्रकार max_count)
अणु
    स्थिर अक्षर *p = स_प्रथम(string, 0, max_count);
    वापस p ? p - string : max_count;
पूर्ण

#पूर्ण_अगर /* !defined(MAC_OS_X_VERSION_10_7) || (MAC_OS_X_VERSION_MAX_ALLOWED <
          MAC_OS_X_VERSION_10_7) */

#पूर्ण_अगर /* __APPLE__ */

#पूर्ण_अगर /* LIBFDT_ENV_H */
