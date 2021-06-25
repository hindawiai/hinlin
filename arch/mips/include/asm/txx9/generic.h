<शैली गुरु>
/*
 * linux/include/यंत्र-mips/txx9/generic.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_TXX9_GENERIC_H
#घोषणा __ASM_TXX9_GENERIC_H

#समावेश <linux/init.h>
#समावेश <linux/ioport.h>	/* क्रम काष्ठा resource */

बाह्य काष्ठा resource txx9_ce_res[];
#घोषणा TXX9_CE(n)	(अचिन्हित दीर्घ)(txx9_ce_res[(n)].start)
बाह्य अचिन्हित पूर्णांक txx9_pcode;
बाह्य अक्षर txx9_pcode_str[8];
व्योम txx9_reg_res_init(अचिन्हित पूर्णांक pcode, अचिन्हित दीर्घ base,
		       अचिन्हित दीर्घ size);

बाह्य अचिन्हित पूर्णांक txx9_master_घड़ी;
बाह्य अचिन्हित पूर्णांक txx9_cpu_घड़ी;
बाह्य अचिन्हित पूर्णांक txx9_gbus_घड़ी;
#घोषणा TXX9_IMCLK	(txx9_gbus_घड़ी / 2)

बाह्य पूर्णांक txx9_ccfg_toeon;
काष्ठा uart_port;
पूर्णांक early_serial_txx9_setup(काष्ठा uart_port *port);

काष्ठा pci_dev;
काष्ठा txx9_board_vec अणु
	स्थिर अक्षर *प्रणाली;
	व्योम (*prom_init)(व्योम);
	व्योम (*mem_setup)(व्योम);
	व्योम (*irq_setup)(व्योम);
	व्योम (*समय_init)(व्योम);
	व्योम (*arch_init)(व्योम);
	व्योम (*device_init)(व्योम);
#अगर_घोषित CONFIG_PCI
	पूर्णांक (*pci_map_irq)(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);
#पूर्ण_अगर
पूर्ण;
बाह्य काष्ठा txx9_board_vec *txx9_board_vec;
बाह्य पूर्णांक (*txx9_irq_dispatch)(पूर्णांक pending);
स्थिर अक्षर *prom_दो_पर्या(स्थिर अक्षर *name);
व्योम txx9_wdt_init(अचिन्हित दीर्घ base);
व्योम txx9_wdt_now(अचिन्हित दीर्घ base);
व्योम txx9_spi_init(पूर्णांक busid, अचिन्हित दीर्घ base, पूर्णांक irq);
व्योम txx9_ethaddr_init(अचिन्हित पूर्णांक id, अचिन्हित अक्षर *ethaddr);
व्योम txx9_sio_init(अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
		   अचिन्हित पूर्णांक line, अचिन्हित पूर्णांक sclk, पूर्णांक nocts);
#अगर_घोषित CONFIG_EARLY_PRINTK
बाह्य व्योम (*txx9_prom_अक्षर_दो)(अक्षर c);
व्योम txx9_sio_अक्षर_दो_init(अचिन्हित दीर्घ baseaddr);
#अन्यथा
अटल अंतरभूत व्योम txx9_sio_अक्षर_दो_init(अचिन्हित दीर्घ baseaddr)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा physmap_flash_data;
व्योम txx9_physmap_flash_init(पूर्णांक no, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size,
			     स्थिर काष्ठा physmap_flash_data *pdata);

/* 8 bit version of __fls(): find first bit set (वापसs 0..7) */
अटल अंतरभूत अचिन्हित पूर्णांक __fls8(अचिन्हित अक्षर x)
अणु
	पूर्णांक r = 7;

	अगर (!(x & 0xf0)) अणु
		r -= 4;
		x <<= 4;
	पूर्ण
	अगर (!(x & 0xc0)) अणु
		r -= 2;
		x <<= 2;
	पूर्ण
	अगर (!(x & 0x80))
		r -= 1;
	वापस r;
पूर्ण

व्योम txx9_iocled_init(अचिन्हित दीर्घ baseaddr,
		      पूर्णांक basक्रमागत, अचिन्हित पूर्णांक num, पूर्णांक lowactive,
		      स्थिर अक्षर *color, अक्षर **deftriggers);

/* 7SEG LED */
व्योम txx9_7segled_init(अचिन्हित पूर्णांक num,
		       व्योम (*अ_दो)(अचिन्हित पूर्णांक pos, अचिन्हित अक्षर val));
पूर्णांक txx9_7segled_अ_दो(अचिन्हित पूर्णांक pos, अक्षर c);

व्योम __init txx9_aclc_init(अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
			   अचिन्हित पूर्णांक dmac_id,
			   अचिन्हित पूर्णांक dma_chan_out,
			   अचिन्हित पूर्णांक dma_chan_in);
व्योम __init txx9_sramc_init(काष्ठा resource *r);

#पूर्ण_अगर /* __ASM_TXX9_GENERIC_H */
