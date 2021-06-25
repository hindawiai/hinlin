<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * QNAP TS-x09 Boards common functions
 *
 * Maपूर्णांकainers: Lennert Buytenhek <buytenh@marvell.com>
 *		Byron Bradley <byron.bbradley@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/समयx.h>
#समावेश <linux/serial_reg.h>
#समावेश "orion5x.h"
#समावेश "tsx09-common.h"
#समावेश "common.h"

/*****************************************************************************
 * QNAP TS-x09 specअगरic घातer off method via UART1-attached PIC
 ****************************************************************************/

#घोषणा UART1_REG(x)	(UART1_VIRT_BASE + ((UART_##x) << 2))

व्योम qnap_tsx09_घातer_off(व्योम)
अणु
	/* 19200 baud भागisor */
	स्थिर अचिन्हित भागisor = ((orion5x_tclk + (8 * 19200)) / (16 * 19200));

	pr_info("%s: triggering power-off...\n", __func__);

	/* hijack uart1 and reset पूर्णांकo sane state (19200,8n1) */
	ग_लिखोl(0x83, UART1_REG(LCR));
	ग_लिखोl(भागisor & 0xff, UART1_REG(DLL));
	ग_लिखोl((भागisor >> 8) & 0xff, UART1_REG(DLM));
	ग_लिखोl(0x03, UART1_REG(LCR));
	ग_लिखोl(0x00, UART1_REG(IER));
	ग_लिखोl(0x00, UART1_REG(FCR));
	ग_लिखोl(0x00, UART1_REG(MCR));

	/* send the घातer-off command 'A' to PIC */
	ग_लिखोl('A', UART1_REG(TX));
पूर्ण

/*****************************************************************************
 * Ethernet
 ****************************************************************************/

काष्ठा mv643xx_eth_platक्रमm_data qnap_tsx09_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

अटल पूर्णांक __init qnap_tsx09_parse_hex_nibble(अक्षर n)
अणु
	अगर (n >= '0' && n <= '9')
		वापस n - '0';

	अगर (n >= 'A' && n <= 'F')
		वापस n - 'A' + 10;

	अगर (n >= 'a' && n <= 'f')
		वापस n - 'a' + 10;

	वापस -1;
पूर्ण

अटल पूर्णांक __init qnap_tsx09_parse_hex_byte(स्थिर अक्षर *b)
अणु
	पूर्णांक hi;
	पूर्णांक lo;

	hi = qnap_tsx09_parse_hex_nibble(b[0]);
	lo = qnap_tsx09_parse_hex_nibble(b[1]);

	अगर (hi < 0 || lo < 0)
		वापस -1;

	वापस (hi << 4) | lo;
पूर्ण

अटल पूर्णांक __init qnap_tsx09_check_mac_addr(स्थिर अक्षर *addr_str)
अणु
	u_पूर्णांक8_t addr[6];
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		पूर्णांक byte;

		/*
		 * Enक्रमce "xx:xx:xx:xx:xx:xx\n" क्रमmat.
		 */
		अगर (addr_str[(i * 3) + 2] != ((i < 5) ? ':' : '\n'))
			वापस -1;

		byte = qnap_tsx09_parse_hex_byte(addr_str + (i * 3));
		अगर (byte < 0)
			वापस -1;
		addr[i] = byte;
	पूर्ण

	prपूर्णांकk(KERN_INFO "tsx09: found ethernet mac address %pM\n", addr);

	स_नकल(qnap_tsx09_eth_data.mac_addr, addr, 6);

	वापस 0;
पूर्ण

/*
 * The 'NAS Config' flash partition has an ext2 fileप्रणाली which
 * contains a file that has the ethernet MAC address in plain text
 * (क्रमmat "xx:xx:xx:xx:xx:xx\n").
 */
व्योम __init qnap_tsx09_find_mac_addr(u32 mem_base, u32 size)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = mem_base; addr < (mem_base + size); addr += 1024) अणु
		अक्षर *nor_page;
		पूर्णांक ret = 0;

		nor_page = ioremap(addr, 1024);
		अगर (nor_page != शून्य) अणु
			ret = qnap_tsx09_check_mac_addr(nor_page);
			iounmap(nor_page);
		पूर्ण

		अगर (ret == 0)
			अवरोध;
	पूर्ण
पूर्ण
