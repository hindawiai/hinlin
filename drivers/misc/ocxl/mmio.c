<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2019 IBM Corp.
#समावेश <linux/sched/mm.h>
#समावेश "trace.h"
#समावेश "ocxl_internal.h"

पूर्णांक ocxl_global_mmio_पढ़ो32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u32 *val)
अणु
	अगर (offset > afu->config.global_mmio_size - 4)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		*val = पढ़ोl_be((अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		*val = पढ़ोl((अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_पढ़ो32);

पूर्णांक ocxl_global_mmio_पढ़ो64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u64 *val)
अणु
	अगर (offset > afu->config.global_mmio_size - 8)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		*val = पढ़ोq_be((अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		*val = पढ़ोq((अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_पढ़ो64);

पूर्णांक ocxl_global_mmio_ग_लिखो32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u32 val)
अणु
	अगर (offset > afu->config.global_mmio_size - 4)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		ग_लिखोl_be(val, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		ग_लिखोl(val, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण


	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_ग_लिखो32);

पूर्णांक ocxl_global_mmio_ग_लिखो64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u64 val)
अणु
	अगर (offset > afu->config.global_mmio_size - 8)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		ग_लिखोq_be(val, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		ग_लिखोq(val, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण


	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_ग_लिखो64);

पूर्णांक ocxl_global_mmio_set32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u32 mask)
अणु
	u32 पंचांगp;

	अगर (offset > afu->config.global_mmio_size - 4)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		पंचांगp = पढ़ोl_be((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp |= mask;
		ग_लिखोl_be(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		पंचांगp = पढ़ोl((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp |= mask;
		ग_लिखोl(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_set32);

पूर्णांक ocxl_global_mmio_set64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u64 mask)
अणु
	u64 पंचांगp;

	अगर (offset > afu->config.global_mmio_size - 8)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		पंचांगp = पढ़ोq_be((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp |= mask;
		ग_लिखोq_be(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		पंचांगp = पढ़ोq((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp |= mask;
		ग_लिखोq(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_set64);

पूर्णांक ocxl_global_mmio_clear32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u32 mask)
अणु
	u32 पंचांगp;

	अगर (offset > afu->config.global_mmio_size - 4)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		पंचांगp = पढ़ोl_be((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp &= ~mask;
		ग_लिखोl_be(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		पंचांगp = पढ़ोl((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp &= ~mask;
		ग_लिखोl(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण


	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_clear32);

पूर्णांक ocxl_global_mmio_clear64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
				क्रमागत ocxl_endian endian, u64 mask)
अणु
	u64 पंचांगp;

	अगर (offset > afu->config.global_mmio_size - 8)
		वापस -EINVAL;

#अगर_घोषित __BIG_ENDIAN__
	अगर (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#पूर्ण_अगर

	चयन (endian) अणु
	हाल OCXL_BIG_ENDIAN:
		पंचांगp = पढ़ोq_be((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp &= ~mask;
		ग_लिखोq_be(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;

	शेष:
		पंचांगp = पढ़ोq((अक्षर *)afu->global_mmio_ptr + offset);
		पंचांगp &= ~mask;
		ग_लिखोq(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);
		अवरोध;
	पूर्ण

	ग_लिखोq(पंचांगp, (अक्षर *)afu->global_mmio_ptr + offset);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_global_mmio_clear64);
