<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_OS_H__
#घोषणा __NVKM_OS_H__
#समावेश <nvअगर/os.h>

#अगर_घोषित __BIG_ENDIAN
#घोषणा ioपढ़ो16_native ioपढ़ो16be
#घोषणा ioग_लिखो16_native ioग_लिखो16be
#घोषणा ioपढ़ो32_native  ioपढ़ो32be
#घोषणा ioग_लिखो32_native ioग_लिखो32be
#अन्यथा
#घोषणा ioपढ़ो16_native ioपढ़ो16
#घोषणा ioग_लिखो16_native ioग_लिखो16
#घोषणा ioपढ़ो32_native  ioपढ़ो32
#घोषणा ioग_लिखो32_native ioग_लिखो32
#पूर्ण_अगर

#घोषणा ioग_लिखो64_native(v,p) करो अणु                                             \
	u32 __iomem *_p = (u32 __iomem *)(p);				       \
	u64 _v = (v);							       \
	ioग_लिखो32_native(lower_32_bits(_v), &_p[0]);			       \
	ioग_लिखो32_native(upper_32_bits(_v), &_p[1]);			       \
पूर्ण जबतक(0)

काष्ठा nvkm_blob अणु
	व्योम *data;
	u32 size;
पूर्ण;

अटल अंतरभूत व्योम
nvkm_blob_dtor(काष्ठा nvkm_blob *blob)
अणु
	kमुक्त(blob->data);
	blob->data = शून्य;
	blob->size = 0;
पूर्ण
#पूर्ण_अगर
