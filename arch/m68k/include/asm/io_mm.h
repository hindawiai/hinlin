<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/यंत्र-m68k/पन.स
 *
 * 4/1/00 RZ: - rewritten to aव्योम clashes between ISA/PCI and other
 *              IO access
 *            - added Q40 support
 *            - added skeleton क्रम GG-II and Amiga PCMCIA
 * 2/3/01 RZ: - moved a few more defs पूर्णांकo raw_पन.स
 *
 * inX/outX should not be used by any driver unless it करोes
 * ISA access. Other drivers should use function defined in raw_पन.स
 * or define its own macros on top of these.
 *
 *    inX(),outX()              are क्रम ISA I/O
 *    isa_पढ़ोX(),isa_ग_लिखोX()  are क्रम ISA memory
 */

#अगर_अघोषित _M68K_IO_MM_H
#घोषणा _M68K_IO_MM_H

#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <यंत्र/raw_पन.स>
#समावेश <यंत्र/virtconvert.h>
#समावेश <यंत्र/kmap.h>

#समावेश <यंत्र-generic/iomap.h>

#अगर_घोषित CONFIG_ATARI
#घोषणा atari_पढ़ोb   raw_inb
#घोषणा atari_ग_लिखोb  raw_outb

#घोषणा atari_inb_p   raw_inb
#घोषणा atari_outb_p  raw_outb
#पूर्ण_अगर


/*
 * IO/MEM definitions क्रम various ISA bridges
 */


#अगर_घोषित CONFIG_Q40

#घोषणा q40_isa_io_base  0xff400000
#घोषणा q40_isa_mem_base 0xff800000

#घोषणा Q40_ISA_IO_B(ioaddr) (q40_isa_io_base+1+4*((अचिन्हित दीर्घ)(ioaddr)))
#घोषणा Q40_ISA_IO_W(ioaddr) (q40_isa_io_base+  4*((अचिन्हित दीर्घ)(ioaddr)))
#घोषणा Q40_ISA_MEM_B(madr)  (q40_isa_mem_base+1+4*((अचिन्हित दीर्घ)(madr)))
#घोषणा Q40_ISA_MEM_W(madr)  (q40_isa_mem_base+  4*((अचिन्हित दीर्घ)(madr)))

#घोषणा MULTI_ISA 0
#पूर्ण_अगर /* Q40 */

#अगर_घोषित CONFIG_AMIGA_PCMCIA
#समावेश <यंत्र/amigayle.h>

#घोषणा AG_ISA_IO_B(ioaddr) ( GAYLE_IO+(ioaddr)+(((ioaddr)&1)*GAYLE_ODD) )
#घोषणा AG_ISA_IO_W(ioaddr) ( GAYLE_IO+(ioaddr) )

#अगर_अघोषित MULTI_ISA
#घोषणा MULTI_ISA 0
#अन्यथा
#अघोषित MULTI_ISA
#घोषणा MULTI_ISA 1
#पूर्ण_अगर
#पूर्ण_अगर /* AMIGA_PCMCIA */

#अगर_घोषित CONFIG_ATARI_ROM_ISA

#घोषणा enec_isa_पढ़ो_base  0xfffa0000
#घोषणा enec_isa_ग_लिखो_base 0xfffb0000

#घोषणा ENEC_ISA_IO_B(ioaddr)	(enec_isa_पढ़ो_base+((((अचिन्हित दीर्घ)(ioaddr))&0x7F)<<9))
#घोषणा ENEC_ISA_IO_W(ioaddr)	(enec_isa_पढ़ो_base+((((अचिन्हित दीर्घ)(ioaddr))&0x7F)<<9))
#घोषणा ENEC_ISA_MEM_B(madr)	(enec_isa_पढ़ो_base+((((अचिन्हित दीर्घ)(madr))&0x7F)<<9))
#घोषणा ENEC_ISA_MEM_W(madr)	(enec_isa_पढ़ो_base+((((अचिन्हित दीर्घ)(madr))&0x7F)<<9))

#अगर_अघोषित MULTI_ISA
#घोषणा MULTI_ISA 0
#अन्यथा
#अघोषित MULTI_ISA
#घोषणा MULTI_ISA 1
#पूर्ण_अगर
#पूर्ण_अगर /* ATARI_ROM_ISA */


#अगर defined(CONFIG_ISA) || defined(CONFIG_ATARI_ROM_ISA)

#अगर MULTI_ISA == 0
#अघोषित MULTI_ISA
#पूर्ण_अगर

#घोषणा ISA_TYPE_Q40  (1)
#घोषणा ISA_TYPE_AG   (2)
#घोषणा ISA_TYPE_ENEC (3)

#अगर defined(CONFIG_Q40) && !defined(MULTI_ISA)
#घोषणा ISA_TYPE ISA_TYPE_Q40
#घोषणा ISA_SEX  0
#पूर्ण_अगर
#अगर defined(CONFIG_AMIGA_PCMCIA) && !defined(MULTI_ISA)
#घोषणा ISA_TYPE ISA_TYPE_AG
#घोषणा ISA_SEX  1
#पूर्ण_अगर
#अगर defined(CONFIG_ATARI_ROM_ISA) && !defined(MULTI_ISA)
#घोषणा ISA_TYPE ISA_TYPE_ENEC
#घोषणा ISA_SEX  0
#पूर्ण_अगर

#अगर_घोषित MULTI_ISA
बाह्य पूर्णांक isa_type;
बाह्य पूर्णांक isa_sex;

#घोषणा ISA_TYPE isa_type
#घोषणा ISA_SEX  isa_sex
#पूर्ण_अगर

/*
 * define अंतरभूत addr translation functions. Normally only one variant will
 * be compiled in so the हाल statement will be optimised away
 */

अटल अंतरभूत u8 __iomem *isa_itb(अचिन्हित दीर्घ addr)
अणु
  चयन(ISA_TYPE)
    अणु
#अगर_घोषित CONFIG_Q40
    हाल ISA_TYPE_Q40: वापस (u8 __iomem *)Q40_ISA_IO_B(addr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMIGA_PCMCIA
    हाल ISA_TYPE_AG: वापस (u8 __iomem *)AG_ISA_IO_B(addr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI_ROM_ISA
    हाल ISA_TYPE_ENEC: वापस (u8 __iomem *)ENEC_ISA_IO_B(addr);
#पूर्ण_अगर
    शेष: वापस शून्य; /* aव्योम warnings, just in हाल */
    पूर्ण
पूर्ण
अटल अंतरभूत u16 __iomem *isa_itw(अचिन्हित दीर्घ addr)
अणु
  चयन(ISA_TYPE)
    अणु
#अगर_घोषित CONFIG_Q40
    हाल ISA_TYPE_Q40: वापस (u16 __iomem *)Q40_ISA_IO_W(addr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMIGA_PCMCIA
    हाल ISA_TYPE_AG: वापस (u16 __iomem *)AG_ISA_IO_W(addr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI_ROM_ISA
    हाल ISA_TYPE_ENEC: वापस (u16 __iomem *)ENEC_ISA_IO_W(addr);
#पूर्ण_अगर
    शेष: वापस शून्य; /* aव्योम warnings, just in हाल */
    पूर्ण
पूर्ण
अटल अंतरभूत u32 __iomem *isa_itl(अचिन्हित दीर्घ addr)
अणु
  चयन(ISA_TYPE)
    अणु
#अगर_घोषित CONFIG_AMIGA_PCMCIA
    हाल ISA_TYPE_AG: वापस (u32 __iomem *)AG_ISA_IO_W(addr);
#पूर्ण_अगर
    शेष: वापस 0; /* aव्योम warnings, just in हाल */
    पूर्ण
पूर्ण
अटल अंतरभूत u8 __iomem *isa_mtb(अचिन्हित दीर्घ addr)
अणु
  चयन(ISA_TYPE)
    अणु
#अगर_घोषित CONFIG_Q40
    हाल ISA_TYPE_Q40: वापस (u8 __iomem *)Q40_ISA_MEM_B(addr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMIGA_PCMCIA
    हाल ISA_TYPE_AG: वापस (u8 __iomem *)addr;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI_ROM_ISA
    हाल ISA_TYPE_ENEC: वापस (u8 __iomem *)ENEC_ISA_MEM_B(addr);
#पूर्ण_अगर
    शेष: वापस शून्य; /* aव्योम warnings, just in हाल */
    पूर्ण
पूर्ण
अटल अंतरभूत u16 __iomem *isa_mtw(अचिन्हित दीर्घ addr)
अणु
  चयन(ISA_TYPE)
    अणु
#अगर_घोषित CONFIG_Q40
    हाल ISA_TYPE_Q40: वापस (u16 __iomem *)Q40_ISA_MEM_W(addr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMIGA_PCMCIA
    हाल ISA_TYPE_AG: वापस (u16 __iomem *)addr;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI_ROM_ISA
    हाल ISA_TYPE_ENEC: वापस (u16 __iomem *)ENEC_ISA_MEM_W(addr);
#पूर्ण_अगर
    शेष: वापस शून्य; /* aव्योम warnings, just in हाल */
    पूर्ण
पूर्ण


#घोषणा isa_inb(port)      in_8(isa_itb(port))
#घोषणा isa_inw(port)      (ISA_SEX ? in_be16(isa_itw(port)) : in_le16(isa_itw(port)))
#घोषणा isa_inl(port)      (ISA_SEX ? in_be32(isa_itl(port)) : in_le32(isa_itl(port)))
#घोषणा isa_outb(val,port) out_8(isa_itb(port),(val))
#घोषणा isa_outw(val,port) (ISA_SEX ? out_be16(isa_itw(port),(val)) : out_le16(isa_itw(port),(val)))
#घोषणा isa_outl(val,port) (ISA_SEX ? out_be32(isa_itl(port),(val)) : out_le32(isa_itl(port),(val)))

#घोषणा isa_पढ़ोb(p)       in_8(isa_mtb((अचिन्हित दीर्घ)(p)))
#घोषणा isa_पढ़ोw(p)       \
	(ISA_SEX ? in_be16(isa_mtw((अचिन्हित दीर्घ)(p)))	\
		 : in_le16(isa_mtw((अचिन्हित दीर्घ)(p))))
#घोषणा isa_ग_लिखोb(val,p)  out_8(isa_mtb((अचिन्हित दीर्घ)(p)),(val))
#घोषणा isa_ग_लिखोw(val,p)  \
	(ISA_SEX ? out_be16(isa_mtw((अचिन्हित दीर्घ)(p)),(val))	\
		 : out_le16(isa_mtw((अचिन्हित दीर्घ)(p)),(val)))

#अगर_घोषित CONFIG_ATARI_ROM_ISA
#घोषणा isa_rom_inb(port)      rom_in_8(isa_itb(port))
#घोषणा isa_rom_inw(port)	\
	(ISA_SEX ? rom_in_be16(isa_itw(port))	\
		 : rom_in_le16(isa_itw(port)))

#घोषणा isa_rom_outb(val, port) rom_out_8(isa_itb(port), (val))
#घोषणा isa_rom_outw(val, port)	\
	(ISA_SEX ? rom_out_be16(isa_itw(port), (val))	\
		 : rom_out_le16(isa_itw(port), (val)))

#घोषणा isa_rom_पढ़ोb(p)       rom_in_8(isa_mtb((अचिन्हित दीर्घ)(p)))
#घोषणा isa_rom_पढ़ोw(p)       \
	(ISA_SEX ? rom_in_be16(isa_mtw((अचिन्हित दीर्घ)(p)))	\
		 : rom_in_le16(isa_mtw((अचिन्हित दीर्घ)(p))))
#घोषणा isa_rom_पढ़ोw_swap(p)       \
	(ISA_SEX ? rom_in_le16(isa_mtw((अचिन्हित दीर्घ)(p)))	\
		 : rom_in_be16(isa_mtw((अचिन्हित दीर्घ)(p))))
#घोषणा isa_rom_पढ़ोw_raw(p)   rom_in_be16(isa_mtw((अचिन्हित दीर्घ)(p)))

#घोषणा isa_rom_ग_लिखोb(val, p)  rom_out_8(isa_mtb((अचिन्हित दीर्घ)(p)), (val))
#घोषणा isa_rom_ग_लिखोw(val, p)  \
	(ISA_SEX ? rom_out_be16(isa_mtw((अचिन्हित दीर्घ)(p)), (val))	\
		 : rom_out_le16(isa_mtw((अचिन्हित दीर्घ)(p)), (val)))
#घोषणा isa_rom_ग_लिखोw_swap(val, p)  \
	(ISA_SEX ? rom_out_le16(isa_mtw((अचिन्हित दीर्घ)(p)), (val))	\
		 : rom_out_be16(isa_mtw((अचिन्हित दीर्घ)(p)), (val)))
#घोषणा isa_rom_ग_लिखोw_raw(val, p)  rom_out_be16(isa_mtw((अचिन्हित दीर्घ)(p)), (val))
#पूर्ण_अगर /* CONFIG_ATARI_ROM_ISA */

अटल अंतरभूत व्योम isa_delay(व्योम)
अणु
  चयन(ISA_TYPE)
    अणु
#अगर_घोषित CONFIG_Q40
    हाल ISA_TYPE_Q40: isa_outb(0,0x80); अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMIGA_PCMCIA
    हाल ISA_TYPE_AG: अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATARI_ROM_ISA
    हाल ISA_TYPE_ENEC: अवरोध;
#पूर्ण_अगर
    शेष: अवरोध; /* aव्योम warnings */
    पूर्ण
पूर्ण

#घोषणा isa_inb_p(p)      (अणुu8 v=isa_inb(p);isa_delay();v;पूर्ण)
#घोषणा isa_outb_p(v,p)   (अणुisa_outb((v),(p));isa_delay();पूर्ण)
#घोषणा isa_inw_p(p)      (अणुu16 v=isa_inw(p);isa_delay();v;पूर्ण)
#घोषणा isa_outw_p(v,p)   (अणुisa_outw((v),(p));isa_delay();पूर्ण)
#घोषणा isa_inl_p(p)      (अणुu32 v=isa_inl(p);isa_delay();v;पूर्ण)
#घोषणा isa_outl_p(v,p)   (अणुisa_outl((v),(p));isa_delay();पूर्ण)

#घोषणा isa_insb(port, buf, nr) raw_insb(isa_itb(port), (u8 *)(buf), (nr))
#घोषणा isa_outsb(port, buf, nr) raw_outsb(isa_itb(port), (u8 *)(buf), (nr))

#घोषणा isa_insw(port, buf, nr)     \
       (ISA_SEX ? raw_insw(isa_itw(port), (u16 *)(buf), (nr)) :    \
                  raw_insw_swapw(isa_itw(port), (u16 *)(buf), (nr)))

#घोषणा isa_outsw(port, buf, nr)    \
       (ISA_SEX ? raw_outsw(isa_itw(port), (u16 *)(buf), (nr)) :  \
                  raw_outsw_swapw(isa_itw(port), (u16 *)(buf), (nr)))

#घोषणा isa_insl(port, buf, nr)     \
       (ISA_SEX ? raw_insl(isa_itl(port), (u32 *)(buf), (nr)) :    \
                  raw_insw_swapw(isa_itw(port), (u16 *)(buf), (nr)<<1))

#घोषणा isa_outsl(port, buf, nr)    \
       (ISA_SEX ? raw_outsl(isa_itl(port), (u32 *)(buf), (nr)) :  \
                  raw_outsw_swapw(isa_itw(port), (u16 *)(buf), (nr)<<1))


#अगर_घोषित CONFIG_ATARI_ROM_ISA
#घोषणा isa_rom_inb_p(p)	(अणु u8 _v = isa_rom_inb(p); isa_delay(); _v; पूर्ण)
#घोषणा isa_rom_inw_p(p)	(अणु u16 _v = isa_rom_inw(p); isa_delay(); _v; पूर्ण)
#घोषणा isa_rom_outb_p(v, p)	(अणु isa_rom_outb((v), (p)); isa_delay(); पूर्ण)
#घोषणा isa_rom_outw_p(v, p)	(अणु isa_rom_outw((v), (p)); isa_delay(); पूर्ण)

#घोषणा isa_rom_insb(port, buf, nr) raw_rom_insb(isa_itb(port), (u8 *)(buf), (nr))

#घोषणा isa_rom_insw(port, buf, nr)     \
       (ISA_SEX ? raw_rom_insw(isa_itw(port), (u16 *)(buf), (nr)) :    \
		  raw_rom_insw_swapw(isa_itw(port), (u16 *)(buf), (nr)))

#घोषणा isa_rom_outsb(port, buf, nr) raw_rom_outsb(isa_itb(port), (u8 *)(buf), (nr))

#घोषणा isa_rom_outsw(port, buf, nr)    \
       (ISA_SEX ? raw_rom_outsw(isa_itw(port), (u16 *)(buf), (nr)) :  \
		  raw_rom_outsw_swapw(isa_itw(port), (u16 *)(buf), (nr)))
#पूर्ण_अगर /* CONFIG_ATARI_ROM_ISA */

#पूर्ण_अगर  /* CONFIG_ISA || CONFIG_ATARI_ROM_ISA */


#अगर defined(CONFIG_ISA) && !defined(CONFIG_ATARI_ROM_ISA)
#घोषणा inb     isa_inb
#घोषणा inb_p   isa_inb_p
#घोषणा outb    isa_outb
#घोषणा outb_p  isa_outb_p
#घोषणा inw     isa_inw
#घोषणा inw_p   isa_inw_p
#घोषणा outw    isa_outw
#घोषणा outw_p  isa_outw_p
#घोषणा inl     isa_inl
#घोषणा inl_p   isa_inl_p
#घोषणा outl    isa_outl
#घोषणा outl_p  isa_outl_p
#घोषणा insb    isa_insb
#घोषणा insw    isa_insw
#घोषणा insl    isa_insl
#घोषणा outsb   isa_outsb
#घोषणा outsw   isa_outsw
#घोषणा outsl   isa_outsl
#घोषणा पढ़ोb   isa_पढ़ोb
#घोषणा पढ़ोw   isa_पढ़ोw
#घोषणा ग_लिखोb  isa_ग_लिखोb
#घोषणा ग_लिखोw  isa_ग_लिखोw
#पूर्ण_अगर  /* CONFIG_ISA && !CONFIG_ATARI_ROM_ISA */

#अगर_घोषित CONFIG_ATARI_ROM_ISA
/*
 * kernel with both ROM port ISA and IDE compiled in, those have
 * conflicting defs क्रम in/out. Simply consider port < 1024
 * ROM port ISA and everything अन्यथा regular ISA क्रम IDE. पढ़ो,ग_लिखो defined
 * below.
 */
#घोषणा inb(port)	((port) < 1024 ? isa_rom_inb(port) : in_8(port))
#घोषणा inb_p(port)	((port) < 1024 ? isa_rom_inb_p(port) : in_8(port))
#घोषणा inw(port)	((port) < 1024 ? isa_rom_inw(port) : in_le16(port))
#घोषणा inw_p(port)	((port) < 1024 ? isa_rom_inw_p(port) : in_le16(port))
#घोषणा inl		isa_inl
#घोषणा inl_p		isa_inl_p

#घोषणा outb(val, port)	((port) < 1024 ? isa_rom_outb((val), (port)) : out_8((port), (val)))
#घोषणा outb_p(val, port) ((port) < 1024 ? isa_rom_outb_p((val), (port)) : out_8((port), (val)))
#घोषणा outw(val, port)	((port) < 1024 ? isa_rom_outw((val), (port)) : out_le16((port), (val)))
#घोषणा outw_p(val, port) ((port) < 1024 ? isa_rom_outw_p((val), (port)) : out_le16((port), (val)))
#घोषणा outl		isa_outl
#घोषणा outl_p		isa_outl_p

#घोषणा insb(port, buf, nr)	((port) < 1024 ? isa_rom_insb((port), (buf), (nr)) : isa_insb((port), (buf), (nr)))
#घोषणा insw(port, buf, nr)	((port) < 1024 ? isa_rom_insw((port), (buf), (nr)) : isa_insw((port), (buf), (nr)))
#घोषणा insl			isa_insl
#घोषणा outsb(port, buf, nr)	((port) < 1024 ? isa_rom_outsb((port), (buf), (nr)) : isa_outsb((port), (buf), (nr)))
#घोषणा outsw(port, buf, nr)	((port) < 1024 ? isa_rom_outsw((port), (buf), (nr)) : isa_outsw((port), (buf), (nr)))
#घोषणा outsl			isa_outsl

#घोषणा पढ़ोb(addr)		in_8(addr)
#घोषणा ग_लिखोb(val, addr)	out_8((addr), (val))
#घोषणा पढ़ोw(addr)		in_le16(addr)
#घोषणा ग_लिखोw(val, addr)	out_le16((addr), (val))
#पूर्ण_अगर /* CONFIG_ATARI_ROM_ISA */

#घोषणा पढ़ोl(addr)      in_le32(addr)
#घोषणा ग_लिखोl(val,addr) out_le32((addr),(val))

#घोषणा पढ़ोsb(port, buf, nr)     raw_insb((port), (u8 *)(buf), (nr))
#घोषणा पढ़ोsw(port, buf, nr)     raw_insw((port), (u16 *)(buf), (nr))
#घोषणा पढ़ोsl(port, buf, nr)     raw_insl((port), (u32 *)(buf), (nr))
#घोषणा ग_लिखोsb(port, buf, nr)    raw_outsb((port), (u8 *)(buf), (nr))
#घोषणा ग_लिखोsw(port, buf, nr)    raw_outsw((port), (u16 *)(buf), (nr))
#घोषणा ग_लिखोsl(port, buf, nr)    raw_outsl((port), (u32 *)(buf), (nr))

#अगर_अघोषित CONFIG_SUN3
#घोषणा IO_SPACE_LIMIT 0xffff
#अन्यथा
#घोषणा IO_SPACE_LIMIT 0x0fffffff
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#घोषणा __ARCH_HAS_NO_PAGE_ZERO_MAPPED		1

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

#घोषणा पढ़ोb_relaxed(addr)	पढ़ोb(addr)
#घोषणा पढ़ोw_relaxed(addr)	पढ़ोw(addr)
#घोषणा पढ़ोl_relaxed(addr)	पढ़ोl(addr)

#घोषणा ग_लिखोb_relaxed(b, addr)	ग_लिखोb(b, addr)
#घोषणा ग_लिखोw_relaxed(b, addr)	ग_लिखोw(b, addr)
#घोषणा ग_लिखोl_relaxed(b, addr)	ग_लिखोl(b, addr)

#पूर्ण_अगर /* _M68K_IO_MM_H */
