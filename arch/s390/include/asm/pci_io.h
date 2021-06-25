<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_PCI_IO_H
#घोषणा _ASM_S390_PCI_IO_H

#अगर_घोषित CONFIG_PCI

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/pci_insn.h>

/* I/O size स्थिरraपूर्णांकs */
#घोषणा ZPCI_MAX_READ_SIZE	8
#घोषणा ZPCI_MAX_WRITE_SIZE	128

/* I/O Map */
#घोषणा ZPCI_IOMAP_SHIFT		48
#घोषणा ZPCI_IOMAP_ADDR_BASE		0x8000000000000000UL
#घोषणा ZPCI_IOMAP_ADDR_OFF_MASK	((1UL << ZPCI_IOMAP_SHIFT) - 1)
#घोषणा ZPCI_IOMAP_MAX_ENTRIES							\
	((अच_दीर्घ_उच्च - ZPCI_IOMAP_ADDR_BASE + 1) / (1UL << ZPCI_IOMAP_SHIFT))
#घोषणा ZPCI_IOMAP_ADDR_IDX_MASK						\
	(~ZPCI_IOMAP_ADDR_OFF_MASK - ZPCI_IOMAP_ADDR_BASE)

काष्ठा zpci_iomap_entry अणु
	u32 fh;
	u8 bar;
	u16 count;
पूर्ण;

बाह्य काष्ठा zpci_iomap_entry *zpci_iomap_start;

#घोषणा ZPCI_ADDR(idx) (ZPCI_IOMAP_ADDR_BASE | ((u64) idx << ZPCI_IOMAP_SHIFT))
#घोषणा ZPCI_IDX(addr)								\
	(((__क्रमce u64) addr & ZPCI_IOMAP_ADDR_IDX_MASK) >> ZPCI_IOMAP_SHIFT)
#घोषणा ZPCI_OFFSET(addr)							\
	((__क्रमce u64) addr & ZPCI_IOMAP_ADDR_OFF_MASK)

#घोषणा ZPCI_CREATE_REQ(handle, space, len)					\
	((u64) handle << 32 | space << 16 | len)

#घोषणा zpci_पढ़ो(LENGTH, RETTYPE)						\
अटल अंतरभूत RETTYPE zpci_पढ़ो_##RETTYPE(स्थिर अस्थिर व्योम __iomem *addr)	\
अणु										\
	u64 data;								\
	पूर्णांक rc;									\
										\
	rc = zpci_load(&data, addr, LENGTH);					\
	अगर (rc)									\
		data = -1ULL;							\
	वापस (RETTYPE) data;							\
पूर्ण

#घोषणा zpci_ग_लिखो(LENGTH, VALTYPE)						\
अटल अंतरभूत व्योम zpci_ग_लिखो_##VALTYPE(VALTYPE val,				\
					स्थिर अस्थिर व्योम __iomem *addr)	\
अणु										\
	u64 data = (VALTYPE) val;						\
										\
	zpci_store(addr, data, LENGTH);						\
पूर्ण

zpci_पढ़ो(8, u64)
zpci_पढ़ो(4, u32)
zpci_पढ़ो(2, u16)
zpci_पढ़ो(1, u8)
zpci_ग_लिखो(8, u64)
zpci_ग_लिखो(4, u32)
zpci_ग_लिखो(2, u16)
zpci_ग_लिखो(1, u8)

अटल अंतरभूत पूर्णांक zpci_ग_लिखो_single(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
				    अचिन्हित दीर्घ len)
अणु
	u64 val;

	चयन (len) अणु
	हाल 1:
		val = (u64) *((u8 *) src);
		अवरोध;
	हाल 2:
		val = (u64) *((u16 *) src);
		अवरोध;
	हाल 4:
		val = (u64) *((u32 *) src);
		अवरोध;
	हाल 8:
		val = (u64) *((u64 *) src);
		अवरोध;
	शेष:
		val = 0;		/* let FW report error */
		अवरोध;
	पूर्ण
	वापस zpci_store(dst, val, len);
पूर्ण

अटल अंतरभूत पूर्णांक zpci_पढ़ो_single(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
				   अचिन्हित दीर्घ len)
अणु
	u64 data;
	पूर्णांक cc;

	cc = zpci_load(&data, src, len);
	अगर (cc)
		जाओ out;

	चयन (len) अणु
	हाल 1:
		*((u8 *) dst) = (u8) data;
		अवरोध;
	हाल 2:
		*((u16 *) dst) = (u16) data;
		अवरोध;
	हाल 4:
		*((u32 *) dst) = (u32) data;
		अवरोध;
	हाल 8:
		*((u64 *) dst) = (u64) data;
		अवरोध;
	पूर्ण
out:
	वापस cc;
पूर्ण

पूर्णांक zpci_ग_लिखो_block(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
		     अचिन्हित दीर्घ len);

अटल अंतरभूत u8 zpci_get_max_ग_लिखो_size(u64 src, u64 dst, पूर्णांक len, पूर्णांक max)
अणु
	पूर्णांक count = len > max ? max : len, size = 1;

	जबतक (!(src & 0x1) && !(dst & 0x1) && ((size << 1) <= count)) अणु
		dst = dst >> 1;
		src = src >> 1;
		size = size << 1;
	पूर्ण
	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक zpci_स_नकल_fromio(व्योम *dst,
				     स्थिर अस्थिर व्योम __iomem *src,
				     अचिन्हित दीर्घ n)
अणु
	पूर्णांक size, rc = 0;

	जबतक (n > 0) अणु
		size = zpci_get_max_ग_लिखो_size((u64 __क्रमce) src,
					       (u64) dst, n,
					       ZPCI_MAX_READ_SIZE);
		rc = zpci_पढ़ो_single(dst, src, size);
		अगर (rc)
			अवरोध;
		src += size;
		dst += size;
		n -= size;
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक zpci_स_नकल_toio(अस्थिर व्योम __iomem *dst,
				   स्थिर व्योम *src, अचिन्हित दीर्घ n)
अणु
	पूर्णांक size, rc = 0;

	अगर (!src)
		वापस -EINVAL;

	जबतक (n > 0) अणु
		size = zpci_get_max_ग_लिखो_size((u64 __क्रमce) dst,
					       (u64) src, n,
					       ZPCI_MAX_WRITE_SIZE);
		अगर (size > 8) /* मुख्य path */
			rc = zpci_ग_लिखो_block(dst, src, size);
		अन्यथा
			rc = zpci_ग_लिखो_single(dst, src, size);
		अगर (rc)
			अवरोध;
		src += size;
		dst += size;
		n -= size;
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक zpci_स_रखो_io(अस्थिर व्योम __iomem *dst,
				 अचिन्हित अक्षर val, माप_प्रकार count)
अणु
	u8 *src = kदो_स्मृति(count, GFP_KERNEL);
	पूर्णांक rc;

	अगर (src == शून्य)
		वापस -ENOMEM;
	स_रखो(src, val, count);

	rc = zpci_स_नकल_toio(dst, src, count);
	kमुक्त(src);
	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI */

#पूर्ण_अगर /* _ASM_S390_PCI_IO_H */
