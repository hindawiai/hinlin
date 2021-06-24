<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NVRAM_H
#घोषणा _LINUX_NVRAM_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <uapi/linux/nvram.h>

#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/machdep.h>
#पूर्ण_अगर

/**
 * काष्ठा nvram_ops - NVRAM functionality made available to drivers
 * @पढ़ो: validate checksum (अगर any) then load a range of bytes from NVRAM
 * @ग_लिखो: store a range of bytes to NVRAM then update checksum (अगर any)
 * @पढ़ो_byte: load a single byte from NVRAM
 * @ग_लिखो_byte: store a single byte to NVRAM
 * @get_size: वापस the fixed number of bytes in the NVRAM
 *
 * Architectures which provide an nvram ops काष्ठा need not implement all
 * of these methods. If the NVRAM hardware can be accessed only one byte
 * at a समय then it may be sufficient to provide .पढ़ो_byte and .ग_लिखो_byte.
 * If the NVRAM has a checksum (and it is to be checked) the .पढ़ो and
 * .ग_लिखो methods can be used to implement that efficiently.
 *
 * Portable drivers may use the wrapper functions defined here.
 * The nvram_पढ़ो() and nvram_ग_लिखो() functions call the .पढ़ो and .ग_लिखो
 * methods when available and fall back on the .पढ़ो_byte and .ग_लिखो_byte
 * methods otherwise.
 */

काष्ठा nvram_ops अणु
	sमाप_प्रकार         (*get_size)(व्योम);
	अचिन्हित अक्षर   (*पढ़ो_byte)(पूर्णांक);
	व्योम            (*ग_लिखो_byte)(अचिन्हित अक्षर, पूर्णांक);
	sमाप_प्रकार         (*पढ़ो)(अक्षर *, माप_प्रकार, loff_t *);
	sमाप_प्रकार         (*ग_लिखो)(अक्षर *, माप_प्रकार, loff_t *);
#अगर defined(CONFIG_X86) || defined(CONFIG_M68K)
	दीर्घ            (*initialize)(व्योम);
	दीर्घ            (*set_checksum)(व्योम);
#पूर्ण_अगर
पूर्ण;

बाह्य स्थिर काष्ठा nvram_ops arch_nvram_ops;

अटल अंतरभूत sमाप_प्रकार nvram_get_size(व्योम)
अणु
#अगर_घोषित CONFIG_PPC
	अगर (ppc_md.nvram_size)
		वापस ppc_md.nvram_size();
#अन्यथा
	अगर (arch_nvram_ops.get_size)
		वापस arch_nvram_ops.get_size();
#पूर्ण_अगर
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर nvram_पढ़ो_byte(पूर्णांक addr)
अणु
#अगर_घोषित CONFIG_PPC
	अगर (ppc_md.nvram_पढ़ो_val)
		वापस ppc_md.nvram_पढ़ो_val(addr);
#अन्यथा
	अगर (arch_nvram_ops.पढ़ो_byte)
		वापस arch_nvram_ops.पढ़ो_byte(addr);
#पूर्ण_अगर
	वापस 0xFF;
पूर्ण

अटल अंतरभूत व्योम nvram_ग_लिखो_byte(अचिन्हित अक्षर val, पूर्णांक addr)
अणु
#अगर_घोषित CONFIG_PPC
	अगर (ppc_md.nvram_ग_लिखो_val)
		ppc_md.nvram_ग_लिखो_val(addr, val);
#अन्यथा
	अगर (arch_nvram_ops.ग_लिखो_byte)
		arch_nvram_ops.ग_लिखो_byte(val, addr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत sमाप_प्रकार nvram_पढ़ो_bytes(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार nvram_size = nvram_get_size();
	loff_t i;
	अक्षर *p = buf;

	अगर (nvram_size < 0)
		वापस nvram_size;
	क्रम (i = *ppos; count > 0 && i < nvram_size; ++i, ++p, --count)
		*p = nvram_पढ़ो_byte(i);
	*ppos = i;
	वापस p - buf;
पूर्ण

अटल अंतरभूत sमाप_प्रकार nvram_ग_लिखो_bytes(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार nvram_size = nvram_get_size();
	loff_t i;
	अक्षर *p = buf;

	अगर (nvram_size < 0)
		वापस nvram_size;
	क्रम (i = *ppos; count > 0 && i < nvram_size; ++i, ++p, --count)
		nvram_ग_लिखो_byte(*p, i);
	*ppos = i;
	वापस p - buf;
पूर्ण

अटल अंतरभूत sमाप_प्रकार nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
#अगर_घोषित CONFIG_PPC
	अगर (ppc_md.nvram_पढ़ो)
		वापस ppc_md.nvram_पढ़ो(buf, count, ppos);
#अन्यथा
	अगर (arch_nvram_ops.पढ़ो)
		वापस arch_nvram_ops.पढ़ो(buf, count, ppos);
#पूर्ण_अगर
	वापस nvram_पढ़ो_bytes(buf, count, ppos);
पूर्ण

अटल अंतरभूत sमाप_प्रकार nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
#अगर_घोषित CONFIG_PPC
	अगर (ppc_md.nvram_ग_लिखो)
		वापस ppc_md.nvram_ग_लिखो(buf, count, ppos);
#अन्यथा
	अगर (arch_nvram_ops.ग_लिखो)
		वापस arch_nvram_ops.ग_लिखो(buf, count, ppos);
#पूर्ण_अगर
	वापस nvram_ग_लिखो_bytes(buf, count, ppos);
पूर्ण

#पूर्ण_अगर  /* _LINUX_NVRAM_H */
