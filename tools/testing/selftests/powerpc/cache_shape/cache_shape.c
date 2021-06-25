<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2017, Michael Ellerman, IBM Corp.
 */

#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <link.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "utils.h"

#अगर_अघोषित AT_L1I_CACHESIZE
#घोषणा AT_L1I_CACHESIZE	40
#घोषणा AT_L1I_CACHEGEOMETRY	41
#घोषणा AT_L1D_CACHESIZE	42
#घोषणा AT_L1D_CACHEGEOMETRY	43
#घोषणा AT_L2_CACHESIZE		44
#घोषणा AT_L2_CACHEGEOMETRY	45
#घोषणा AT_L3_CACHESIZE		46
#घोषणा AT_L3_CACHEGEOMETRY	47
#पूर्ण_अगर

अटल व्योम prपूर्णांक_size(स्थिर अक्षर *label, uपूर्णांक32_t val)
अणु
	म_लिखो("%s cache size: %#10x %10dB %10dK\n", label, val, val, val / 1024);
पूर्ण

अटल व्योम prपूर्णांक_geo(स्थिर अक्षर *label, uपूर्णांक32_t val)
अणु
	uपूर्णांक16_t assoc;

	म_लिखो("%s line size:  %#10x       ", label, val & 0xFFFF);

	assoc = val >> 16;
	अगर (assoc)
		म_लिखो("%u-way", assoc);
	अन्यथा
		म_लिखो("fully");

	म_लिखो(" associative\n");
पूर्ण

अटल पूर्णांक test_cache_shape()
अणु
	अटल अक्षर buffer[4096];
	ElfW(auxv_t) *p;
	पूर्णांक found;

	FAIL_IF(पढ़ो_auxv(buffer, माप(buffer)));

	found = 0;

	p = find_auxv_entry(AT_L1I_CACHESIZE, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_size("L1I ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	p = find_auxv_entry(AT_L1I_CACHEGEOMETRY, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_geo("L1I ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	p = find_auxv_entry(AT_L1D_CACHESIZE, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_size("L1D ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	p = find_auxv_entry(AT_L1D_CACHEGEOMETRY, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_geo("L1D ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	p = find_auxv_entry(AT_L2_CACHESIZE, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_size("L2  ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	p = find_auxv_entry(AT_L2_CACHEGEOMETRY, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_geo("L2  ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	p = find_auxv_entry(AT_L3_CACHESIZE, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_size("L3  ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	p = find_auxv_entry(AT_L3_CACHEGEOMETRY, buffer);
	अगर (p) अणु
		found++;
		prपूर्णांक_geo("L3  ", (uपूर्णांक32_t)p->a_un.a_val);
	पूर्ण

	/* If we found none we're probably on a system where they don't exist */
	SKIP_IF(found == 0);

	/* But अगर we found any, we expect to find them all */
	FAIL_IF(found != 8);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_cache_shape, "cache_shape");
पूर्ण
