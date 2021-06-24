<शैली गुरु>
/*
	ppc6lnx.c (c) 2001 Micro Solutions Inc.
		Released under the terms of the GNU General Public license

	ppc6lnx.c  is a par of the protocol driver क्रम the Micro Solutions
		"BACKPACK" parallel port IDE adapter
		(Works on Series 6 drives)

*/

//***************************************************************************

// PPC 6 Code in C sanitized क्रम LINUX
// Original x86 ASM by Ron, Converted to C by Clive

//***************************************************************************


#घोषणा port_stb					1
#घोषणा port_afd					2
#घोषणा cmd_stb						port_afd
#घोषणा port_init					4
#घोषणा data_stb					port_init
#घोषणा port_sel					8
#घोषणा port_पूर्णांक					16
#घोषणा port_dir					0x20

#घोषणा ECR_EPP	0x80
#घोषणा ECR_BI	0x20

//***************************************************************************

//  60772 Commands

#घोषणा ACCESS_REG				0x00
#घोषणा ACCESS_PORT				0x40

#घोषणा ACCESS_READ				0x00
#घोषणा ACCESS_WRITE			0x20

//  60772 Command Prefix

#घोषणा CMD_PREFIX_SET		0xe0		// Special command that modअगरies the next command's operation
#घोषणा CMD_PREFIX_RESET	0xc0		// Resets current cmd modअगरier reg bits
 #घोषणा PREFIX_IO16			0x01		// perक्रमm 16-bit wide I/O
 #घोषणा PREFIX_FASTWR		0x04		// enable PPC mode fast-ग_लिखो
 #घोषणा PREFIX_BLK				0x08		// enable block transfer mode

// 60772 Registers

#घोषणा REG_STATUS				0x00		// status रेजिस्टर
 #घोषणा STATUS_IRQA			0x01		// Peripheral IRQA line
 #घोषणा STATUS_EEPROM_DO	0x40		// Serial EEPROM data bit
#घोषणा REG_VERSION				0x01		// PPC version रेजिस्टर (पढ़ो)
#घोषणा REG_HWCFG					0x02		// Hardware Config रेजिस्टर
#घोषणा REG_RAMSIZE				0x03		// Size of RAM Buffer
 #घोषणा RAMSIZE_128K			0x02
#घोषणा REG_EEPROM				0x06		// EEPROM control रेजिस्टर
 #घोषणा EEPROM_SK				0x01		// eeprom SK bit
 #घोषणा EEPROM_DI				0x02		// eeprom DI bit
 #घोषणा EEPROM_CS				0x04		// eeprom CS bit
 #घोषणा EEPROM_EN				0x08		// eeprom output enable
#घोषणा REG_BLKSIZE				0x08		// Block transfer len (24 bit)

//***************************************************************************

प्रकार काष्ठा ppc_storage अणु
	u16	lpt_addr;				// LPT base address
	u8	ppc_id;
	u8	mode;						// operating mode
					// 0 = PPC Uni SW
					// 1 = PPC Uni FW
					// 2 = PPC Bi SW
					// 3 = PPC Bi FW
					// 4 = EPP Byte
					// 5 = EPP Word
					// 6 = EPP Dword
	u8	ppc_flags;
	u8	org_data;				// original LPT data port contents
	u8	org_ctrl;				// original LPT control port contents
	u8	cur_ctrl;				// current control port contents
पूर्ण Interface;

//***************************************************************************

// ppc_flags

#घोषणा fअगरo_रुको					0x10

//***************************************************************************

// DONT CHANGE THESE LEST YOU BREAK EVERYTHING - BIT FIELD DEPENDENCIES

#घोषणा PPCMODE_UNI_SW		0
#घोषणा PPCMODE_UNI_FW		1
#घोषणा PPCMODE_BI_SW			2
#घोषणा PPCMODE_BI_FW			3
#घोषणा PPCMODE_EPP_BYTE	4
#घोषणा PPCMODE_EPP_WORD	5
#घोषणा PPCMODE_EPP_DWORD	6

//***************************************************************************

अटल पूर्णांक ppc6_select(Interface *ppc);
अटल व्योम ppc6_deselect(Interface *ppc);
अटल व्योम ppc6_send_cmd(Interface *ppc, u8 cmd);
अटल व्योम ppc6_wr_data_byte(Interface *ppc, u8 data);
अटल u8 ppc6_rd_data_byte(Interface *ppc);
अटल u8 ppc6_rd_port(Interface *ppc, u8 port);
अटल व्योम ppc6_wr_port(Interface *ppc, u8 port, u8 data);
अटल व्योम ppc6_rd_data_blk(Interface *ppc, u8 *data, दीर्घ count);
अटल व्योम ppc6_रुको_क्रम_fअगरo(Interface *ppc);
अटल व्योम ppc6_wr_data_blk(Interface *ppc, u8 *data, दीर्घ count);
अटल व्योम ppc6_rd_port16_blk(Interface *ppc, u8 port, u8 *data, दीर्घ length);
अटल व्योम ppc6_wr_port16_blk(Interface *ppc, u8 port, u8 *data, दीर्घ length);
अटल व्योम ppc6_wr_extout(Interface *ppc, u8 regdata);
अटल पूर्णांक ppc6_खोलो(Interface *ppc);
अटल व्योम ppc6_बंद(Interface *ppc);

//***************************************************************************

अटल पूर्णांक ppc6_select(Interface *ppc)
अणु
	u8 i, j, k;

	i = inb(ppc->lpt_addr + 1);

	अगर (i & 1)
		outb(i, ppc->lpt_addr + 1);

	ppc->org_data = inb(ppc->lpt_addr);

	ppc->org_ctrl = inb(ppc->lpt_addr + 2) & 0x5F; // पढ़ोback ctrl

	ppc->cur_ctrl = ppc->org_ctrl;

	ppc->cur_ctrl |= port_sel;

	outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

	अगर (ppc->org_data == 'b')
		outb('x', ppc->lpt_addr);

	outb('b', ppc->lpt_addr);
	outb('p', ppc->lpt_addr);
	outb(ppc->ppc_id, ppc->lpt_addr);
	outb(~ppc->ppc_id,ppc->lpt_addr);

	ppc->cur_ctrl &= ~port_sel;

	outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

	ppc->cur_ctrl = (ppc->cur_ctrl & port_पूर्णांक) | port_init;

	outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

	i = ppc->mode & 0x0C;

	अगर (i == 0)
		i = (ppc->mode & 2) | 1;

	outb(i, ppc->lpt_addr);

	ppc->cur_ctrl |= port_sel;

	outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

	// DELAY

	ppc->cur_ctrl |= port_afd;

	outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

	j = ((i & 0x08) << 4) | ((i & 0x07) << 3);

	k = inb(ppc->lpt_addr + 1) & 0xB8;

	अगर (j == k)
	अणु
		ppc->cur_ctrl &= ~port_afd;

		outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

		k = (inb(ppc->lpt_addr + 1) & 0xB8) ^ 0xB8;

		अगर (j == k)
		अणु
			अगर (i & 4)	// EPP
				ppc->cur_ctrl &= ~(port_sel | port_init);
			अन्यथा				// PPC/ECP
				ppc->cur_ctrl &= ~port_sel;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			वापस(1);
		पूर्ण
	पूर्ण

	outb(ppc->org_ctrl, ppc->lpt_addr + 2);

	outb(ppc->org_data, ppc->lpt_addr);

	वापस(0); // FAIL
पूर्ण

//***************************************************************************

अटल व्योम ppc6_deselect(Interface *ppc)
अणु
	अगर (ppc->mode & 4)	// EPP
		ppc->cur_ctrl |= port_init;
	अन्यथा								// PPC/ECP
		ppc->cur_ctrl |= port_sel;

	outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

	outb(ppc->org_data, ppc->lpt_addr);

	outb((ppc->org_ctrl | port_sel), ppc->lpt_addr + 2);

	outb(ppc->org_ctrl, ppc->lpt_addr + 2);
पूर्ण

//***************************************************************************

अटल व्योम ppc6_send_cmd(Interface *ppc, u8 cmd)
अणु
	चयन(ppc->mode)
	अणु
		हाल PPCMODE_UNI_SW :
		हाल PPCMODE_UNI_FW :
		हाल PPCMODE_BI_SW :
		हाल PPCMODE_BI_FW :
		अणु
			outb(cmd, ppc->lpt_addr);

			ppc->cur_ctrl ^= cmd_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_BYTE :
		हाल PPCMODE_EPP_WORD :
		हाल PPCMODE_EPP_DWORD :
		अणु
			outb(cmd, ppc->lpt_addr + 3);

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

//***************************************************************************

अटल व्योम ppc6_wr_data_byte(Interface *ppc, u8 data)
अणु
	चयन(ppc->mode)
	अणु
		हाल PPCMODE_UNI_SW :
		हाल PPCMODE_UNI_FW :
		हाल PPCMODE_BI_SW :
		हाल PPCMODE_BI_FW :
		अणु
			outb(data, ppc->lpt_addr);

			ppc->cur_ctrl ^= data_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_BYTE :
		हाल PPCMODE_EPP_WORD :
		हाल PPCMODE_EPP_DWORD :
		अणु
			outb(data, ppc->lpt_addr + 4);

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

//***************************************************************************

अटल u8 ppc6_rd_data_byte(Interface *ppc)
अणु
	u8 data = 0;

	चयन(ppc->mode)
	अणु
		हाल PPCMODE_UNI_SW :
		हाल PPCMODE_UNI_FW :
		अणु
			ppc->cur_ctrl = (ppc->cur_ctrl & ~port_stb) ^ data_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			// DELAY

			data = inb(ppc->lpt_addr + 1);

			data = ((data & 0x80) >> 1) | ((data & 0x38) >> 3);

			ppc->cur_ctrl |= port_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			// DELAY

			data |= inb(ppc->lpt_addr + 1) & 0xB8;

			अवरोध;
		पूर्ण

		हाल PPCMODE_BI_SW :
		हाल PPCMODE_BI_FW :
		अणु
			ppc->cur_ctrl |= port_dir;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			ppc->cur_ctrl = (ppc->cur_ctrl | port_stb) ^ data_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			data = inb(ppc->lpt_addr);

			ppc->cur_ctrl &= ~port_stb;

			outb(ppc->cur_ctrl,ppc->lpt_addr + 2);

			ppc->cur_ctrl &= ~port_dir;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_BYTE :
		हाल PPCMODE_EPP_WORD :
		हाल PPCMODE_EPP_DWORD :
		अणु
			outb((ppc->cur_ctrl | port_dir),ppc->lpt_addr + 2);

			data = inb(ppc->lpt_addr + 4);

			outb(ppc->cur_ctrl,ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण
	पूर्ण

	वापस(data);
पूर्ण

//***************************************************************************

अटल u8 ppc6_rd_port(Interface *ppc, u8 port)
अणु
	ppc6_send_cmd(ppc,(u8)(port | ACCESS_PORT | ACCESS_READ));

	वापस(ppc6_rd_data_byte(ppc));
पूर्ण

//***************************************************************************

अटल व्योम ppc6_wr_port(Interface *ppc, u8 port, u8 data)
अणु
	ppc6_send_cmd(ppc,(u8)(port | ACCESS_PORT | ACCESS_WRITE));

	ppc6_wr_data_byte(ppc, data);
पूर्ण

//***************************************************************************

अटल व्योम ppc6_rd_data_blk(Interface *ppc, u8 *data, दीर्घ count)
अणु
	चयन(ppc->mode)
	अणु
		हाल PPCMODE_UNI_SW :
		हाल PPCMODE_UNI_FW :
		अणु
			जबतक(count)
			अणु
				u8 d;

				ppc->cur_ctrl = (ppc->cur_ctrl & ~port_stb) ^ data_stb;

				outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

				// DELAY

				d = inb(ppc->lpt_addr + 1);

				d = ((d & 0x80) >> 1) | ((d & 0x38) >> 3);

				ppc->cur_ctrl |= port_stb;

				outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

				// DELAY

				d |= inb(ppc->lpt_addr + 1) & 0xB8;

				*data++ = d;
				count--;
			पूर्ण

			अवरोध;
		पूर्ण

		हाल PPCMODE_BI_SW :
		हाल PPCMODE_BI_FW :
		अणु
			ppc->cur_ctrl |= port_dir;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			ppc->cur_ctrl |= port_stb;

			जबतक(count)
			अणु
				ppc->cur_ctrl ^= data_stb;

				outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

				*data++ = inb(ppc->lpt_addr);
				count--;
			पूर्ण

			ppc->cur_ctrl &= ~port_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			ppc->cur_ctrl &= ~port_dir;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_BYTE :
		अणु
			outb((ppc->cur_ctrl | port_dir), ppc->lpt_addr + 2);

			// DELAY

			जबतक(count)
			अणु
				*data++ = inb(ppc->lpt_addr + 4);
				count--;
			पूर्ण

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_WORD :
		अणु
			outb((ppc->cur_ctrl | port_dir), ppc->lpt_addr + 2);

			// DELAY

			जबतक(count > 1)
			अणु
				*((u16 *)data) = inw(ppc->lpt_addr + 4);
				data  += 2;
				count -= 2;
			पूर्ण

			जबतक(count)
			अणु
				*data++ = inb(ppc->lpt_addr + 4);
				count--;
			पूर्ण

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_DWORD :
		अणु
			outb((ppc->cur_ctrl | port_dir),ppc->lpt_addr + 2);

			// DELAY

			जबतक(count > 3)
			अणु
				*((u32 *)data) = inl(ppc->lpt_addr + 4);
				data  += 4;
				count -= 4;
			पूर्ण

			जबतक(count)
			अणु
				*data++ = inb(ppc->lpt_addr + 4);
				count--;
			पूर्ण

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			अवरोध;
		पूर्ण
	पूर्ण

पूर्ण

//***************************************************************************

अटल व्योम ppc6_रुको_क्रम_fअगरo(Interface *ppc)
अणु
	पूर्णांक i;

	अगर (ppc->ppc_flags & fअगरo_रुको)
	अणु
		क्रम(i=0; i<20; i++)
			inb(ppc->lpt_addr + 1);
	पूर्ण
पूर्ण

//***************************************************************************

अटल व्योम ppc6_wr_data_blk(Interface *ppc, u8 *data, दीर्घ count)
अणु
	चयन(ppc->mode)
	अणु
		हाल PPCMODE_UNI_SW :
		हाल PPCMODE_BI_SW :
		अणु
			जबतक(count--)
			अणु
				outb(*data++, ppc->lpt_addr);

				ppc->cur_ctrl ^= data_stb;

				outb(ppc->cur_ctrl, ppc->lpt_addr + 2);
			पूर्ण

			अवरोध;
		पूर्ण

		हाल PPCMODE_UNI_FW :
		हाल PPCMODE_BI_FW :
		अणु
			u8 this, last;

			ppc6_send_cmd(ppc,(CMD_PREFIX_SET | PREFIX_FASTWR));

			ppc->cur_ctrl |= port_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			last = *data;

			outb(last, ppc->lpt_addr);

			जबतक(count)
			अणु
				this = *data++;
				count--;

				अगर (this == last)
				अणु
					ppc->cur_ctrl ^= data_stb;

					outb(ppc->cur_ctrl, ppc->lpt_addr + 2);
				पूर्ण
				अन्यथा
				अणु
					outb(this, ppc->lpt_addr);

					last = this;
				पूर्ण
			पूर्ण

			ppc->cur_ctrl &= ~port_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			ppc6_send_cmd(ppc,(CMD_PREFIX_RESET | PREFIX_FASTWR));

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_BYTE :
		अणु
			जबतक(count)
			अणु
				outb(*data++,ppc->lpt_addr + 4);
				count--;
			पूर्ण

			ppc6_रुको_क्रम_fअगरo(ppc);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_WORD :
		अणु
			जबतक(count > 1)
			अणु
				outw(*((u16 *)data),ppc->lpt_addr + 4);
				data  += 2;
				count -= 2;
			पूर्ण

			जबतक(count)
			अणु
				outb(*data++,ppc->lpt_addr + 4);
				count--;
			पूर्ण

			ppc6_रुको_क्रम_fअगरo(ppc);

			अवरोध;
		पूर्ण

		हाल PPCMODE_EPP_DWORD :
		अणु
			जबतक(count > 3)
			अणु
				outl(*((u32 *)data),ppc->lpt_addr + 4);
				data  += 4;
				count -= 4;
			पूर्ण

			जबतक(count)
			अणु
				outb(*data++,ppc->lpt_addr + 4);
				count--;
			पूर्ण

			ppc6_रुको_क्रम_fअगरo(ppc);

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

//***************************************************************************

अटल व्योम ppc6_rd_port16_blk(Interface *ppc, u8 port, u8 *data, दीर्घ length)
अणु
	length = length << 1;

	ppc6_send_cmd(ppc, (REG_BLKSIZE | ACCESS_REG | ACCESS_WRITE));
	ppc6_wr_data_byte(ppc,(u8)length);
	ppc6_wr_data_byte(ppc,(u8)(length >> 8));
	ppc6_wr_data_byte(ppc,0);

	ppc6_send_cmd(ppc, (CMD_PREFIX_SET | PREFIX_IO16 | PREFIX_BLK));

	ppc6_send_cmd(ppc, (u8)(port | ACCESS_PORT | ACCESS_READ));

	ppc6_rd_data_blk(ppc, data, length);

	ppc6_send_cmd(ppc, (CMD_PREFIX_RESET | PREFIX_IO16 | PREFIX_BLK));
पूर्ण

//***************************************************************************

अटल व्योम ppc6_wr_port16_blk(Interface *ppc, u8 port, u8 *data, दीर्घ length)
अणु
	length = length << 1;

	ppc6_send_cmd(ppc, (REG_BLKSIZE | ACCESS_REG | ACCESS_WRITE));
	ppc6_wr_data_byte(ppc,(u8)length);
	ppc6_wr_data_byte(ppc,(u8)(length >> 8));
	ppc6_wr_data_byte(ppc,0);

	ppc6_send_cmd(ppc, (CMD_PREFIX_SET | PREFIX_IO16 | PREFIX_BLK));

	ppc6_send_cmd(ppc, (u8)(port | ACCESS_PORT | ACCESS_WRITE));

	ppc6_wr_data_blk(ppc, data, length);

	ppc6_send_cmd(ppc, (CMD_PREFIX_RESET | PREFIX_IO16 | PREFIX_BLK));
पूर्ण

//***************************************************************************

अटल व्योम ppc6_wr_extout(Interface *ppc, u8 regdata)
अणु
	ppc6_send_cmd(ppc,(REG_VERSION | ACCESS_REG | ACCESS_WRITE));

	ppc6_wr_data_byte(ppc, (u8)((regdata & 0x03) << 6));
पूर्ण

//***************************************************************************

अटल पूर्णांक ppc6_खोलो(Interface *ppc)
अणु
	पूर्णांक ret;

	ret = ppc6_select(ppc);

	अगर (ret == 0)
		वापस(ret);

	ppc->ppc_flags &= ~fअगरo_रुको;

	ppc6_send_cmd(ppc, (ACCESS_REG | ACCESS_WRITE | REG_RAMSIZE));
	ppc6_wr_data_byte(ppc, RAMSIZE_128K);

	ppc6_send_cmd(ppc, (ACCESS_REG | ACCESS_READ | REG_VERSION));

	अगर ((ppc6_rd_data_byte(ppc) & 0x3F) == 0x0C)
		ppc->ppc_flags |= fअगरo_रुको;

	वापस(ret);
पूर्ण

//***************************************************************************

अटल व्योम ppc6_बंद(Interface *ppc)
अणु
	ppc6_deselect(ppc);
पूर्ण

//***************************************************************************

