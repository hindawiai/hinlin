<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* This file is meant to be include multiple बार by other headers */
/* last 2 argments are used by platक्रमms/cell/io-workarounds.[ch] */

DEF_PCI_AC_RET(पढ़ोb, u8, (स्थिर PCI_IO_ADDR addr), (addr), mem, addr)
DEF_PCI_AC_RET(पढ़ोw, u16, (स्थिर PCI_IO_ADDR addr), (addr), mem, addr)
DEF_PCI_AC_RET(पढ़ोl, u32, (स्थिर PCI_IO_ADDR addr), (addr), mem, addr)
DEF_PCI_AC_RET(पढ़ोw_be, u16, (स्थिर PCI_IO_ADDR addr), (addr), mem, addr)
DEF_PCI_AC_RET(पढ़ोl_be, u32, (स्थिर PCI_IO_ADDR addr), (addr), mem, addr)
DEF_PCI_AC_NORET(ग_लिखोb, (u8 val, PCI_IO_ADDR addr), (val, addr), mem, addr)
DEF_PCI_AC_NORET(ग_लिखोw, (u16 val, PCI_IO_ADDR addr), (val, addr), mem, addr)
DEF_PCI_AC_NORET(ग_लिखोl, (u32 val, PCI_IO_ADDR addr), (val, addr), mem, addr)
DEF_PCI_AC_NORET(ग_लिखोw_be, (u16 val, PCI_IO_ADDR addr), (val, addr), mem, addr)
DEF_PCI_AC_NORET(ग_लिखोl_be, (u32 val, PCI_IO_ADDR addr), (val, addr), mem, addr)

#अगर_घोषित __घातerpc64__
DEF_PCI_AC_RET(पढ़ोq, u64, (स्थिर PCI_IO_ADDR addr), (addr), mem, addr)
DEF_PCI_AC_RET(पढ़ोq_be, u64, (स्थिर PCI_IO_ADDR addr), (addr), mem, addr)
DEF_PCI_AC_NORET(ग_लिखोq, (u64 val, PCI_IO_ADDR addr), (val, addr), mem, addr)
DEF_PCI_AC_NORET(ग_लिखोq_be, (u64 val, PCI_IO_ADDR addr), (val, addr), mem, addr)
#पूर्ण_अगर /* __घातerpc64__ */

DEF_PCI_AC_RET(inb, u8, (अचिन्हित दीर्घ port), (port), pio, port)
DEF_PCI_AC_RET(inw, u16, (अचिन्हित दीर्घ port), (port), pio, port)
DEF_PCI_AC_RET(inl, u32, (अचिन्हित दीर्घ port), (port), pio, port)
DEF_PCI_AC_NORET(outb, (u8 val, अचिन्हित दीर्घ port), (val, port), pio, port)
DEF_PCI_AC_NORET(outw, (u16 val, अचिन्हित दीर्घ port), (val, port), pio, port)
DEF_PCI_AC_NORET(outl, (u32 val, अचिन्हित दीर्घ port), (val, port), pio, port)

DEF_PCI_AC_NORET(पढ़ोsb, (स्थिर PCI_IO_ADDR a, व्योम *b, अचिन्हित दीर्घ c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NORET(पढ़ोsw, (स्थिर PCI_IO_ADDR a, व्योम *b, अचिन्हित दीर्घ c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NORET(पढ़ोsl, (स्थिर PCI_IO_ADDR a, व्योम *b, अचिन्हित दीर्घ c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NORET(ग_लिखोsb, (PCI_IO_ADDR a, स्थिर व्योम *b, अचिन्हित दीर्घ c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NORET(ग_लिखोsw, (PCI_IO_ADDR a, स्थिर व्योम *b, अचिन्हित दीर्घ c),
		 (a, b, c), mem, a)
DEF_PCI_AC_NORET(ग_लिखोsl, (PCI_IO_ADDR a, स्थिर व्योम *b, अचिन्हित दीर्घ c),
		 (a, b, c), mem, a)

DEF_PCI_AC_NORET(insb, (अचिन्हित दीर्घ p, व्योम *b, अचिन्हित दीर्घ c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NORET(insw, (अचिन्हित दीर्घ p, व्योम *b, अचिन्हित दीर्घ c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NORET(insl, (अचिन्हित दीर्घ p, व्योम *b, अचिन्हित दीर्घ c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NORET(outsb, (अचिन्हित दीर्घ p, स्थिर व्योम *b, अचिन्हित दीर्घ c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NORET(outsw, (अचिन्हित दीर्घ p, स्थिर व्योम *b, अचिन्हित दीर्घ c),
		 (p, b, c), pio, p)
DEF_PCI_AC_NORET(outsl, (अचिन्हित दीर्घ p, स्थिर व्योम *b, अचिन्हित दीर्घ c),
		 (p, b, c), pio, p)

DEF_PCI_AC_NORET(स_रखो_io, (PCI_IO_ADDR a, पूर्णांक c, अचिन्हित दीर्घ n),
		 (a, c, n), mem, a)
DEF_PCI_AC_NORET(स_नकल_fromio, (व्योम *d, स्थिर PCI_IO_ADDR s, अचिन्हित दीर्घ n),
		 (d, s, n), mem, s)
DEF_PCI_AC_NORET(स_नकल_toio, (PCI_IO_ADDR d, स्थिर व्योम *s, अचिन्हित दीर्घ n),
		 (d, s, n), mem, d)
