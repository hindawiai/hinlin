<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/यंत्र-m68k/raw_पन.स
 *
 * 10/20/00 RZ: - created from bits of पन.स and ide.h to cleanup namespace
 *
 */

#अगर_अघोषित _RAW_IO_H
#घोषणा _RAW_IO_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/byteorder.h>

/* ++roman: The assignments to temp. vars aव्योम that gcc someबार generates
 * two accesses to memory, which may be undesirable क्रम some devices.
 */
#घोषणा in_8(addr) \
    (अणु u8 __v = (*(__क्रमce अस्थिर u8 *) (addr)); __v; पूर्ण)
#घोषणा in_be16(addr) \
    (अणु u16 __v = (*(__क्रमce अस्थिर u16 *) (addr)); __v; पूर्ण)
#घोषणा in_be32(addr) \
    (अणु u32 __v = (*(__क्रमce अस्थिर u32 *) (addr)); __v; पूर्ण)
#घोषणा in_le16(addr) \
    (अणु u16 __v = le16_to_cpu(*(__क्रमce अस्थिर __le16 *) (addr)); __v; पूर्ण)
#घोषणा in_le32(addr) \
    (अणु u32 __v = le32_to_cpu(*(__क्रमce अस्थिर __le32 *) (addr)); __v; पूर्ण)

#घोषणा out_8(addr,b) (व्योम)((*(__क्रमce अस्थिर u8 *) (addr)) = (b))
#घोषणा out_be16(addr,w) (व्योम)((*(__क्रमce अस्थिर u16 *) (addr)) = (w))
#घोषणा out_be32(addr,l) (व्योम)((*(__क्रमce अस्थिर u32 *) (addr)) = (l))
#घोषणा out_le16(addr,w) (व्योम)((*(__क्रमce अस्थिर __le16 *) (addr)) = cpu_to_le16(w))
#घोषणा out_le32(addr,l) (व्योम)((*(__क्रमce अस्थिर __le32 *) (addr)) = cpu_to_le32(l))

#घोषणा raw_inb in_8
#घोषणा raw_inw in_be16
#घोषणा raw_inl in_be32
#घोषणा __raw_पढ़ोb in_8
#घोषणा __raw_पढ़ोw in_be16
#घोषणा __raw_पढ़ोl in_be32

#घोषणा raw_outb(val,port) out_8((port),(val))
#घोषणा raw_outw(val,port) out_be16((port),(val))
#घोषणा raw_outl(val,port) out_be32((port),(val))
#घोषणा __raw_ग_लिखोb(val,addr) out_8((addr),(val))
#घोषणा __raw_ग_लिखोw(val,addr) out_be16((addr),(val))
#घोषणा __raw_ग_लिखोl(val,addr) out_be32((addr),(val))

/*
 * Atari ROM port (cartridge port) ISA adapter, used क्रम the EtherNEC NE2000
 * network card driver.
 * The ISA adapter connects address lines A9-A13 to ISA address lines A0-A4,
 * and hardwires the rest of the ISA addresses क्रम a base address of 0x300.
 *
 * Data lines D8-D15 are connected to ISA data lines D0-D7 क्रम पढ़ोing.
 * For ग_लिखोs, address lines A1-A8 are latched to ISA data lines D0-D7
 * (meaning the bit pattern on A1-A8 can be पढ़ो back as byte).
 *
 * Read and ग_लिखो operations are distinguished by the base address used:
 * पढ़ोs are from the ROM A side range, ग_लिखोs are through the B side range
 * addresses (A side base + 0x10000).
 *
 * Reads and ग_लिखोs are byte only.
 *
 * 16 bit पढ़ोs and ग_लिखोs are necessary क्रम the NetUSBee adapter's USB
 * chipset - 16 bit words are पढ़ो straight off the ROM port जबतक 16 bit
 * पढ़ोs are split पूर्णांकo two byte ग_लिखोs. The low byte is latched to the
 * NetUSBee buffer by a पढ़ो from the _पढ़ो_ winकरोw (with the data pattern
 * निश्चितed as A1-A8 address pattern). The high byte is then written to the
 * ग_लिखो range as usual, completing the ग_लिखो cycle.
 */

#अगर defined(CONFIG_ATARI_ROM_ISA)
#घोषणा rom_in_8(addr) \
	(अणु u16 __v = (*(__क्रमce अस्थिर u16 *) (addr)); __v >>= 8; __v; पूर्ण)
#घोषणा rom_in_be16(addr) \
	(अणु u16 __v = (*(__क्रमce अस्थिर u16 *) (addr)); __v; पूर्ण)
#घोषणा rom_in_le16(addr) \
	(अणु u16 __v = le16_to_cpu(*(__क्रमce अस्थिर u16 *) (addr)); __v; पूर्ण)

#घोषणा rom_out_8(addr, b)	\
	(अणुu8 __maybe_unused __w, __v = (b);  u32 _addr = ((u32) (addr)); \
	__w = ((*(__क्रमce अस्थिर u8 *)  ((_addr | 0x10000) + (__v<<1)))); पूर्ण)
#घोषणा rom_out_be16(addr, w)	\
	(अणुu16 __maybe_unused __w, __v = (w); u32 _addr = ((u32) (addr)); \
	__w = ((*(__क्रमce अस्थिर u16 *) ((_addr & 0xFFFF0000UL) + ((__v & 0xFF)<<1)))); \
	__w = ((*(__क्रमce अस्थिर u16 *) ((_addr | 0x10000) + ((__v >> 8)<<1)))); पूर्ण)
#घोषणा rom_out_le16(addr, w)	\
	(अणुu16 __maybe_unused __w, __v = (w); u32 _addr = ((u32) (addr)); \
	__w = ((*(__क्रमce अस्थिर u16 *) ((_addr & 0xFFFF0000UL) + ((__v >> 8)<<1)))); \
	__w = ((*(__क्रमce अस्थिर u16 *) ((_addr | 0x10000) + ((__v & 0xFF)<<1)))); पूर्ण)

#घोषणा raw_rom_inb rom_in_8
#घोषणा raw_rom_inw rom_in_be16

#घोषणा raw_rom_outb(val, port) rom_out_8((port), (val))
#घोषणा raw_rom_outw(val, port) rom_out_be16((port), (val))
#पूर्ण_अगर /* CONFIG_ATARI_ROM_ISA */

अटल अंतरभूत व्योम raw_insb(अस्थिर u8 __iomem *port, u8 *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

        क्रम (i = 0; i < len; i++)
		*buf++ = in_8(port);
पूर्ण

अटल अंतरभूत व्योम raw_outsb(अस्थिर u8 __iomem *port, स्थिर u8 *buf,
			     अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (nr & 15) अणु
		पंचांगp = (nr & 15) - 1;
		यंत्र अस्थिर (
			"1: moveb %0@+,%2@; dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
	अगर (nr >> 4) अणु
		पंचांगp = (nr >> 4) - 1;
		यंत्र अस्थिर (
			"1: "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"moveb %0@+,%2@; "
			"dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम raw_insw(अस्थिर u16 __iomem *port, u16 *buf, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (nr & 15) अणु
		पंचांगp = (nr & 15) - 1;
		यंत्र अस्थिर (
			"1: movew %2@,%0@+; dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
	अगर (nr >> 4) अणु
		पंचांगp = (nr >> 4) - 1;
		यंत्र अस्थिर (
			"1: "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"movew %2@,%0@+; "
			"dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम raw_outsw(अस्थिर u16 __iomem *port, स्थिर u16 *buf,
			     अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (nr & 15) अणु
		पंचांगp = (nr & 15) - 1;
		यंत्र अस्थिर (
			"1: movew %0@+,%2@; dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
	अगर (nr >> 4) अणु
		पंचांगp = (nr >> 4) - 1;
		यंत्र अस्थिर (
			"1: "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"movew %0@+,%2@; "
			"dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम raw_insl(अस्थिर u32 __iomem *port, u32 *buf, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (nr & 15) अणु
		पंचांगp = (nr & 15) - 1;
		यंत्र अस्थिर (
			"1: movel %2@,%0@+; dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
	अगर (nr >> 4) अणु
		पंचांगp = (nr >> 4) - 1;
		यंत्र अस्थिर (
			"1: "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"movel %2@,%0@+; "
			"dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम raw_outsl(अस्थिर u32 __iomem *port, स्थिर u32 *buf,
			     अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (nr & 15) अणु
		पंचांगp = (nr & 15) - 1;
		यंत्र अस्थिर (
			"1: movel %0@+,%2@; dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
	अगर (nr >> 4) अणु
		पंचांगp = (nr >> 4) - 1;
		यंत्र अस्थिर (
			"1: "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"movel %0@+,%2@; "
			"dbra %1,1b"
			: "=a" (buf), "=d" (पंचांगp)
			: "a" (port), "0" (buf),
			  "1" (पंचांगp));
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम raw_insw_swapw(अस्थिर u16 __iomem *port, u16 *buf,
				  अचिन्हित पूर्णांक nr)
अणु
    अगर ((nr) % 8)
	__यंत्र__ __अस्थिर__
	       ("\tmovel %0,%/a0\n\t"
		"movel %1,%/a1\n\t"
		"movel %2,%/d6\n\t"
		"subql #1,%/d6\n"
		"1:\tmovew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"dbra %/d6,1b"
		:
		: "g" (port), "g" (buf), "g" (nr)
		: "d0", "a0", "a1", "d6");
    अन्यथा
	__यंत्र__ __अस्थिर__
	       ("movel %0,%/a0\n\t"
		"movel %1,%/a1\n\t"
		"movel %2,%/d6\n\t"
		"lsrl  #3,%/d6\n\t"
		"subql #1,%/d6\n"
		"1:\tmovew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"movew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"movew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"movew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"movew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"movew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"movew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"movew %/a0@,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a1@+\n\t"
		"dbra %/d6,1b"
                :
		: "g" (port), "g" (buf), "g" (nr)
		: "d0", "a0", "a1", "d6");
पूर्ण

अटल अंतरभूत व्योम raw_outsw_swapw(अस्थिर u16 __iomem *port, स्थिर u16 *buf,
				   अचिन्हित पूर्णांक nr)
अणु
    अगर ((nr) % 8)
	__यंत्र__ __अस्थिर__
	       ("movel %0,%/a0\n\t"
		"movel %1,%/a1\n\t"
		"movel %2,%/d6\n\t"
		"subql #1,%/d6\n"
		"1:\tmovew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"dbra %/d6,1b"
                :
		: "g" (port), "g" (buf), "g" (nr)
		: "d0", "a0", "a1", "d6");
    अन्यथा
	__यंत्र__ __अस्थिर__
	       ("movel %0,%/a0\n\t"
		"movel %1,%/a1\n\t"
		"movel %2,%/d6\n\t"
		"lsrl  #3,%/d6\n\t"
		"subql #1,%/d6\n"
		"1:\tmovew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"movew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"movew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"movew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"movew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"movew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"movew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"movew %/a1@+,%/d0\n\t"
		"rolw  #8,%/d0\n\t"
		"movew %/d0,%/a0@\n\t"
		"dbra %/d6,1b"
                :
		: "g" (port), "g" (buf), "g" (nr)
		: "d0", "a0", "a1", "d6");
पूर्ण


#अगर defined(CONFIG_ATARI_ROM_ISA)
अटल अंतरभूत व्योम raw_rom_insb(अस्थिर u8 __iomem *port, u8 *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		*buf++ = rom_in_8(port);
पूर्ण

अटल अंतरभूत व्योम raw_rom_outsb(अस्थिर u8 __iomem *port, स्थिर u8 *buf,
			     अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		rom_out_8(port, *buf++);
पूर्ण

अटल अंतरभूत व्योम raw_rom_insw(अस्थिर u16 __iomem *port, u16 *buf,
				   अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr; i++)
		*buf++ = rom_in_be16(port);
पूर्ण

अटल अंतरभूत व्योम raw_rom_outsw(अस्थिर u16 __iomem *port, स्थिर u16 *buf,
				   अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr; i++)
		rom_out_be16(port, *buf++);
पूर्ण

अटल अंतरभूत व्योम raw_rom_insw_swapw(अस्थिर u16 __iomem *port, u16 *buf,
				   अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr; i++)
		*buf++ = rom_in_le16(port);
पूर्ण

अटल अंतरभूत व्योम raw_rom_outsw_swapw(अस्थिर u16 __iomem *port, स्थिर u16 *buf,
				   अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr; i++)
		rom_out_le16(port, *buf++);
पूर्ण
#पूर्ण_अगर /* CONFIG_ATARI_ROM_ISA */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _RAW_IO_H */
